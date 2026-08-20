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

void *hack_thread(void *arg) {
    // 1. Cast the passed argument back to jobject
    jobject globalContext = (jobject)arg;

    // 2. Wait for IL2CPP to load into memory
    do {
        sleep(1);
        g_il2cppBaseMap = KittyMemory::getElfBaseMap("libil2cpp.so");
    } while (!g_il2cppBaseMap.isValid());

    // 3. Attach this background thread to the JVM to get a valid JNIEnv
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, nullptr);

    // 4. NOW initialize BNM (it will succeed because libil2cpp is in memory)
    BNM::Loading::TryLoadByJNI(env, globalContext);
    
    // 5. Clean up the global reference to prevent memory leaks
    env->DeleteGlobalRef(globalContext);

    // 6. Original logic: Wait for Unity
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

    // 7. Detach thread from JVM before exiting
    jvm->DetachCurrentThread();

    return nullptr;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jvm = vm; // Store the JavaVM globally
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_modfs_xposedmenu_Inject_startModMenu(JNIEnv *env, jclass clazz, jobject activityContext) {
    
    // Note: BNM::Loading::TryLoadByJNI has been moved to hack_thread.

    // 1. Resolve UnityPlayer class using the target app's ClassLoader
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

    // 2. Create a Global Reference of the Activity context to pass to the new thread
    jobject globalContext = env->NewGlobalRef(activityContext);

    // 3. Start the hack thread and pass the globalContext as the 4th argument
    int ret;
    pthread_t ntid;
    if ((ret = pthread_create(&ntid, nullptr, hack_thread, (void*)globalContext))) {
        LOGE("can't create thread: %s\n", strerror(ret));
    }
}