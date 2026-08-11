# XposedImGuiMenu - Project Instructions (GEMINI.md)

Welcome to the **XposedImGuiMenu** repository. This document serves as the developer instructions, architectural guide, and system reference for AI agents and human developers working on this project.

---

## 1. Project Overview

`XposedImGuiMenu` is an Android Xposed module that injects a native graphical ImGui overlay menu at runtime into target games (primarily Unity-based IL2CPP games). 

### Key Technical Pillars
* **Java Bootstrap (Xposed Hook):** 
  Intercepts Android process initialization via `IXposedHookZygoteInit` on Zygote startup. Hooks `android.app.LoadedApk.createAppFactory` to detect target game launch, unpacks/loads the native payload shared library (`libxposedmenu.so`), and injects it into the target class loader.
* **Graphical Overlay (ImGui + EGL):** 
  Once loaded into the game's native process, the module hooks standard EGL functions (`eglSwapBuffers`) in `libEGL.so` to render the user interface overlay on top of the game using OpenGL ES3 (or ES2 for compatibility).
* **Native Hooking & Utilities (Dobby & KittyMemory):**
  Uses **Dobby** for inline hooking/dynamic patching of target functions, and **KittyMemory** (along with `KittyScanner` / `MemoryPatch`) to patch binary offsets and scan target libraries (like `libil2cpp.so` or `libunity.so`) in memory.
* **IL2CPP Helpers (BNM-Android):** 
  Includes **BNM** (Beyond Normal Method) to facilitate robust, C++20-compliant programmatic interaction with Unity's internal IL2CPP structures, methods, fields, and classes.
* **Prebuilt Networking Libraries:** 
  Statically links pre-compiled `libcURL` and `openSSL` libraries for safe network-based features (such as user authentication or key validation).

---

## 2. Directory Structure

The repository is structured as a standard Android multi-module Gradle project with C++ native components (JNI):

```
XposedImGuiMenu-1/
├── build.gradle                             # Root-level Gradle plugin configuration
├── settings.gradle                          # Defines the ':app' module
├── gradle.properties                        # Android/Gradle build properties
├── gradle/
│   └── libs.versions.toml                   # Centralized dependency/plugin version catalog
├── app/
│   ├── build.gradle                         # Module-level build configuration (SDK versions, CMake, ndk, ABI filters)
│   ├── src/
│   │   └── main/
│   │       ├── AndroidManifest.xml          # Xposed module registration metadata and scope configuration
│   │       ├── assets/
│   │       │   └── xposed_init              # Lists the entry point class (org.modfs.xposedmenu.Inject)
│   │       ├── java/org/modfs/xposedmenu/
│   │       │   └── Inject.java              # Main Java Xposed entry point. Handles library loading
│   │       └── cpp/
│   │           ├── CMakeLists.txt           # CMake compilation config for the native component (libxposedmenu.so)
│   │           ├── main.cpp                 # Main native JNI entry point (JNI_OnLoad, thread creation, EGL hook setup)
│   │           ├── Menu.h                   # ImGui menu layout and overlay rendering logic
│   │           ├── Game/                    # Target game hooks, memory patches, and offset/pointer mappings
│   │           │   ├── GameValues.h         # Game-specific toggle and state definitions
│   │           │   ├── Hooks.h              # Function hooks (Dobby) definition
│   │           │   ├── Patches.h            # Static and runtime memory patching (KittyMemory)
│   │           │   └── Pointers.h           # Offsets and function-pointer resolving definitions
│   │           ├── include/                 # Native support headers (logs, custom pointer wrappers, inputs)
│   │           │   ├── includes.h           # Unified header inclusions
│   │           │   ├── input.h              # JNI-backed Android input handling for ImGui
│   │           │   ├── JNIStuff.h           # JNI utility mappings
│   │           │   ├── log.h                # Android __android_log_print wrapper macros
│   │           │   ├── Misc.h               # Utility functions and core HOOK/PATCH helper macros
│   │           │   └── ptr.h                # Template-wrapped function pointer utility
│   │           ├── compiled_libs/           # Pre-compiled static/dynamic libraries (curl, openssl) for ABI architectures
│   │           └── libraries/               # Git submodules for core native engines (BNM-Android, Dobby, ImGui, KittyMemory)
```

---

## 3. Building and Running

The project requires the **Android NDK** (version `25.2.9519653` is specified in `app/build.gradle`) and JDK 17+.

### Key Commands (via Gradle Wrapper)

* **Clean Build Output:**
  ```bash
  ./gradlew clean
  ```
* **Full Project Build:**
  ```bash
  ./gradlew build
  ```
* **Assemble Debug APK:**
  ```bash
  ./gradlew :app:assembleDebug
  ```
* **Assemble Release APK:**
  ```bash
  ./gradlew :app:assembleRelease
  ```
* **Run Linting / Code Quality Analysis:**
  ```bash
  ./gradlew :app:lint
  ```

### Distribution & Compatibility Notes
1. **ABI Selection:** To reduce APK size significantly, restrict target compilation architectures in `app/build.gradle` inside the `defaultConfig.ndk` block:
   ```groovy
   ndk {
       abiFilters 'arm64-v8a' // Or include others: 'armeabi-v7a', 'x86_64', 'x86'
   }
   ```
2. **Installation:** 
   * On rooted devices, install the generated APK and enable the module in an Xposed manager (e.g. LSPosed), then reboot or restart the target app.
   * On non-rooted devices, the module is fully compatible with **LSPatch** (stealthy non-root APK patching).

---

## 4. Development Conventions & Configuration

When extending or customizing this project, adhere strictly to the following procedures and guidelines:

### Step 1: Target Customization (Java & Manifest)
Before building, you **must** configure the package target:
* **`app/src/main/java/org/modfs/xposedmenu/Inject.java`:**
  Update the target package name and ABI:
  ```java
  String app_name = "com.frivolition.daysbygone"; // Set to your target package name
  String target_abi = Build.SUPPORTED_ABIS[0];     // Set/filter your target ABI
  ```
* **`app/src/main/AndroidManifest.xml`:**
  Update target package name in the `<queries>` block and the `xposedscope` meta-data value:
  ```xml
  <queries>
      <package android:name="com.frivolition.daysbygone" />
  </queries>
  ...
  <meta-data
      android:name="xposedscope"
      android:value="com.frivolition.daysbygone" />
  ```

### Step 2: Native C++ Setup (Logging and Rendering)
* **Log Tag (`app/src/main/cpp/include/log.h`):**
  Redefine `LOG_TAG` to your module's preferred log identifier (visible via `logcat`):
  ```cpp
  #define LOG_TAG "YourCustomMenuTag"
  ```
* **ImGui Menu UI (`app/src/main/cpp/Menu.h`):**
  Implement your graphical toggles and menu structure inside the `DrawMenu()` loop. Avoid resource-heavy calculations directly in `DrawMenu()`, as it runs inside the game render thread (`eglSwapBuffers`).
* **Game Values (`app/src/main/cpp/Game/GameValues.h`):**
  Store all global toggle states and configuration variables (e.g., `bool some_feature = false;`) here to preserve clean separation from the drawing logic.

### Step 3: Offsets, Hooks, and Patches
Use the optimized macros in `app/src/main/cpp/include/Misc.h` to execute modifications safely relative to the base address of the IL2CPP game image:
* **Static Memory Patching (`app/src/main/cpp/Game/Patches.h`):**
  Write patches using `PATCH(offset, hex)` or runtime-switchable patches using `PATCH_SWITCH(offset, hex, toggle_boolean)`:
  ```cpp
  void InitPatches() {
      PATCH("0x123456", "C0035FD6"); // Hex code for RET instruction
  }
  ```
* **Function Hooking (`app/src/main/cpp/Game/Hooks.h`):**
  Define old-function storage pointer wrappers and hooking operations:
  ```cpp
  float (*old_some_method)(...);
  float some_method(void* instance) {
      if (some_feature) { ... }
      return old_some_method(instance);
  }
  void Hooks() {
      HOOKD("0x123456", some_method); // Auto-binds to old_some_method
  }
  ```
* **Pointer Offsets (`app/src/main/cpp/Game/Pointers.h`):**
  Utilize the custom type-safe `Pointer` class for mapping offsets to callable functions:
  ```cpp
  Pointer<int(float)> some_pointer;
  void Pointers() {
      some_pointer = OFFSET("0x123456");
  }
  ```
* **Field Manipulation:**
  Use the field accessor template `GetField<Type>(instance, offset)` to directly read/write values:
  ```cpp
  GetField<int>(instance, 0x10) = 99; // Set int field 0x10 to 99
  ```

### Dependency Rules
* Do not edit the external submodule sources under `app/src/main/cpp/libraries/` directly. 
* Target SDK must remain compatible with C++20 because **BNM-Android** utilizes standard C++20 features.
* The prebuilt libraries (`libcurl.a` and `libssl.a`/`libcrypto.a`) are located under `app/src/main/cpp/compiled_libs/<library>/<ABI>/lib/` and are automatically statically linked via CMake.
