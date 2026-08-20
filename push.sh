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

# Grab the commit message from the 1st argument
COMMIT_MSG="$1"

# If no message was provided, prompt for one
if [ -z "$COMMIT_MSG" ]; then
    read -rp "Enter commit message: " COMMIT_MSG
fi

# Exit if commit message is still empty
if [ -z "$COMMIT_MSG" ]; then
    echo "Aborted: Commit message cannot be empty."
    exit 1
fi

# 1. Stage all changes
git add . || exit 1

# 2. Show current status
echo "--- Current Git Status in $PROJECT_DIR ---"
git status
echo "------------------------------------------"

# 3. Pause and wait for user keypress
echo ""
read -n 1 -s -r -p "Press ANY KEY to commit & push (or Ctrl+C to cancel)..."
echo ""
echo ""

# 4. Commit and Push
git commit -m "$COMMIT_MSG" && git push
