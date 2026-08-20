#include "includes.h"

EGLBoolean (*old_eglSwapBuffers)(...);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (!init) {
        SetupImGui();
        init = true;
    }

    ImGuiIO &io = GetIO();
    if (io.WantTextInput && !iskeyboardopen) {
        displayKeyboard();
        iskeyboardopen = true;
    } else if (!io.WantTextInput && iskeyboardopen) {
        displayKeyboard();
        iskeyboardopen = false;
    }

    ImGui_ImplOpenGL3_NewFrame();
    NewFrame();

    DrawMenu();

    EndFrame();
    Render();
    glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

    Patches();

    return old_eglSwapBuffers(dpy, surface);
}

void OnBNMLoaded() {
    BNM_LOG_INFO("=========================================");
    BNM_LOG_INFO("BNM has been loaded");

    Features::freeShop::initHook();
    // Features::SpeedHack::initHook();
    // Features::SkillsHack::initHook();
    // Features::LowestWave::initHook();
    // Features::Equipment::initHook();
    Features::set0Prices::initHook();
    // Features::RuneLevel::initHook();
    // Features::Expedition::initHook();

    BNM_LOG_INFO("=========================================");
}

void *hack_thread(void *) {
    // 1. Wait for KittyMemory to find libil2cpp.so
    do {
        sleep(1);
        g_il2cppBaseMap = KittyMemory::getElfBaseMap("libil2cpp.so");
    } while (!g_il2cppBaseMap.isValid());

    BNM_LOG_INFO("[BNM Debug] libil2cpp.so found via KittyMemory!");

    // 2. Attach this background thread to the JVM so BNM has a valid JNI environment
    JNIEnv *env;
    if (jvm->AttachCurrentThread(&env, nullptr) == JNI_OK) {
        BNM_LOG_INFO("[BNM Debug] Thread attached to JVM successfully.");
    } else {
        LOGE("[BNM Debug] Failed to attach thread to JVM.");
    }

    // 3. Create an ElfScanner using the base address to handle symbol lookups for BNM
    static ElfScanner il2cppScanner = ElfScanner::createWithMap(g_il2cppBaseMap);

    BNM::Loading::SetMethodFinder([](const char *name, void *) -> void* {
        return (void *)il2cppScanner.findSymbol(name);
    }, nullptr);

    BNM::Loading::AddOnLoadedEvent(OnBNMLoaded);
    BNM::Loading::AllowLateInitHook();
    BNM::Loading::TryLoadByUsersFinder();

    // 4. Wait for BNM to finish loading
    do {
        sleep(1);
    } while (!BNM::IsLoaded());

    BNM_LOG_INFO("[BNM Debug] BNM is fully loaded and ready!");

    // 5. Scan for libunity.so
    do {
        sleep(1);
        unityMaps = ElfScanner::createWithPath("libunity.so");
    } while (!unityMaps.isValid());

    // input native function
    RegisterNativeFn nativeInjectEventFn = KittyScanner::findRegisterNativeFn(unityMaps, "nativeInjectEvent");

    if (nativeInjectEventFn.isValid()) {
        HOOKD_ABS(nativeInjectEventFn.fnPtr, nativeInjectEvent);
    } else {
        LOGE("InjectEventPtr is dead, menu unable to initialize.");
    }

    Pointers();
    InitPatches();
    Hooks();

    DobbyHookSM("libEGL.so", "eglSwapBuffers", (void *) hook_eglSwapBuffers, (void **) &old_eglSwapBuffers);

    LOGI("Menu finished loading");

    // 6. Cleanly detach the thread from the JVM before exiting
    jvm->DetachCurrentThread();

    return nullptr;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jvm = vm; // Store the JavaVM globally
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    
    // BNM::Loading::AddOnLoadedEvent(OnBNMLoaded);
    // BNM::Loading::AllowLateInitHook();
    // BNM::Loading::TryLoadByJNI(env);

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_modfs_xposedmenu_Inject_startModMenu(JNIEnv *env, jclass clazz, jobject activityContext) {
    int ret;
    pthread_t ntid;
    
    // Just start the thread, no arguments needed
    if ((ret = pthread_create(&ntid, nullptr, hack_thread, nullptr))) {
        LOGE("can't create thread: %s\n", strerror(ret));
    }
}