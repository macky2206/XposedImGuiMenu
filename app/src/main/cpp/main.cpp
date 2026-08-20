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

void *hack_thread(void *) {
    do {
        sleep(1);
        g_il2cppBaseMap = KittyMemory::getElfBaseMap("libil2cpp.so");
    } while (!g_il2cppBaseMap.isValid());

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

    return nullptr;
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


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jvm = vm; // Store the JavaVM globally
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    
    BNM::Loading::AddOnLoadedEvent(OnBNMLoaded);
    BNM::Loading::TryLoadByJNI(env);

    return JNI_VERSION_1_6;
}

// 2. Added JNI Bridge: This catches the Activity from Inject.java
extern "C"
JNIEXPORT void JNICALL
Java_org_modfs_xposedmenu_Inject_startModMenu(JNIEnv *env, jclass clazz, jobject activityContext) {

    jclass activityClass = env->GetObjectClass(activityContext);
    jmethodID getClassLoaderMethod = env->GetMethodID(activityClass, "getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject targetClassLoader = env->CallObjectMethod(activityContext, getClassLoaderMethod);

    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    jmethodID loadClassMethod = env->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    jstring unityClassName = env->NewStringUTF("com.unity3d.player.UnityPlayer");
    jclass localUnityPlayerCls = (jclass) env->CallObjectMethod(targetClassLoader, loadClassMethod, unityClassName);
    env->DeleteLocalRef(unityClassName);
    
    if (localUnityPlayerCls != nullptr) {
        UnityPlayer_cls = (jclass) env->NewGlobalRef(localUnityPlayerCls);
        UnityPlayer_CurrentActivity_fid = env->GetStaticFieldID(UnityPlayer_cls, "currentActivity", "Landroid/app/Activity;");
    } else {
        LOGE("Failed to find com.unity3d.player.UnityPlayer using target ClassLoader!");
    }

    int ret;
    pthread_t ntid;
    if ((ret = pthread_create(&ntid, nullptr, hack_thread, nullptr))) {
        LOGE("can't create thread: %s\n", strerror(ret));
    }
}