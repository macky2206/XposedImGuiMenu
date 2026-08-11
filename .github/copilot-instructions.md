# Copilot instructions for XposedImGuiMenu

Purpose: help future Copilot sessions quickly understand how to build, test, and modify this Android/Xposed + native C++ project.

---

## Quick build, test & lint commands

- Full build: ./gradlew build
- App debug APK: ./gradlew :app:assembleDebug
- App release APK: ./gradlew :app:assembleRelease
- Clean: ./gradlew clean
- Lint (module): ./gradlew :app:lint
- Single unit test task (if present): ./gradlew :app:testDebugUnitTest

Notes:
- Use the included Gradle wrapper (./gradlew). The project uses the Gradle version catalog at gradle/libs.versions.toml.
- To build only for a specific ABI, edit `app/build.gradle` -> defaultConfig.ndk.abiFilters (remove ABIs you don't need) or set ABI filters in your CI build tasks.
- Native build (CMake) runs automatically as part of the Gradle build (app/src/main/cpp/CMakeLists.txt). NDK version is set in app/build.gradle (ndkVersion).

---

## High-level architecture

- Android Xposed module (Java): app/src/main/java/org/modfs/xposedmenu/Inject.java
  - Implements IXposedHookZygoteInit and injects the native library into the target app process (package name and ABI are hard-coded in Inject.java and the manifest placeholders).
  - The APK also includes `app/src/main/assets/xposed_init` pointing at the Inject class.

- Native C++ library (CMake): app/src/main/cpp/
  - Main entry: main.cpp — JNI_OnLoad spawns a thread that locates il2cpp/libunity via KittyMemory/ElfScanner, installs hooks (Dobby), and draws an ImGui menu by hooking eglSwapBuffers.
  - Third-party native components are included as git submodules under app/src/main/cpp/libraries (ImGui, KittyMemory, Dobby, BNM-Android). Several prebuilt static libs are stored in app/src/main/cpp/compiled_libs/<lib>/<ABI> and linked by CMake.

- Packaging and resources
  - CMake builds a shared library named libxposedmenu.so and Android packaging expects the lib and xposed_init asset. AndroidManifest.xml contains placeholders (package name) and xposed metadata — update these before building.
  - app/build.gradle sets compileSdk/targetSdk, Java compatibility (17), and externalNativeBuild/CMake config.

---

## Key repository conventions

- Submodules: Several native dependencies are Git submodules. Clone with: `git clone --recursive <repo>` or run `git submodule update --init --recursive` after cloning.
- ABI management: Keep apk small and compatible by editing `abiFilters` in app/build.gradle to include only the ABIs you target. CMake uses ${CMAKE_ANDROID_ARCH_ABI} to pick compiled static libs in compiled_libs/.
- Edit-before-compile places:
  - app/src/main/java/org/modfs/xposedmenu/Inject.java — set `app_name` and `target_abi` to match the target application and ABI.
  - app/src/main/AndroidManifest.xml — set package names in <queries> and `xposedscope`.
- Native libs: Prebuilt curl/openssl static libs live under app/src/main/cpp/compiled_libs/*/<abi> and are linked statically in CMakeLists.txt. Don’t compress `.so` in resources (app/build.gradle sets androidResources.noCompress 'so').
- Version catalog: Dependencies and plugin versions are centralized in gradle/libs.versions.toml; plugin aliasing is used in build scripts.

---

## Files to check when changing behavior

- Java hook: app/src/main/java/org/modfs/xposedmenu/Inject.java
- Native entry and rendering loop: app/src/main/cpp/main.cpp
- CMake configuration: app/src/main/cpp/CMakeLists.txt
- Native libraries and headers: app/src/main/cpp/libraries/ and app/src/main/cpp/compiled_libs/
- Packaging & manifest: app/src/main/AndroidManifest.xml and app/src/main/assets/xposed_init

---

If this file already exists, merge these sections into the existing guidance and preserve any repository-specific notes already present.

