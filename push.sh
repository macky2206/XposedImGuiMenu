#!/usr/bin/env bash

# Set the target project directory
PROJECT_DIR="/sdcard/proj/XposedImGuiMenu"

# Navigate to the project folder
if [ -d "$PROJECT_DIR" ]; then
    cd "$PROJECT_DIR" || exit 1
else
    echo "Error: Directory $PROJECT_DIR does not exist."
    exit 1
fi

# Auto-detect the commit message if not provided manually
if [ -n "$1" ]; then
    # Allow manual override if you type something like: push "hotfix"
    COMMIT_MSG="$1"
else
    # Search git history for the most recent message starting with "cycle"
    # and extract only the numbers from it.
    LAST_CYCLE=$(git log --grep="^cycle[0-9]" -1 --pretty=%s | grep -oE '[0-9]+')
    
    # If no previous cycle commit is found, fallback to 10 since you are on 9
    if [ -z "$LAST_CYCLE" ]; then
        NEXT_CYCLE=1
    else
        NEXT_CYCLE=$((LAST_CYCLE + 1))
    fi
    
    COMMIT_MSG="cycle$NEXT_CYCLE"
fi

# 1. Stage all changes
git add . || exit 1

# 2. Show current status and the auto-generated message
echo "--- Current Git Status in $PROJECT_DIR ---"
git status
echo "------------------------------------------"
echo ">>> Next commit message: \"$COMMIT_MSG\" <<<"
echo "------------------------------------------"

# 3. Pause and wait for user keypress
echo ""
read -n 1 -s -r -p "Press ANY KEY to commit & push (or Ctrl+C to cancel)..."
echo ""
echo ""

# 4. Commit and Push
git commit -m "$COMMIT_MSG" && git push
