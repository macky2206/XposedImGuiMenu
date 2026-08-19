package org.modfs.xposedmenu;

import android.os.Build;
import android.os.Bundle;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.Objects;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage.LoadPackageParam;

public class Inject implements IXposedHookLoadPackage {
    boolean loaded = false;
    String app_name = "com.frivolition.daysbygone"; // target package to inject
    String target_abi = Build.SUPPORTED_ABIS[0]; // SET THIS TO THE ABI YOU'RE TARGETING

    public static InputStream resourceStream(String name) {
        return Objects.requireNonNull(Inject.class.getClassLoader()).getResourceAsStream(name);
    }

    // Declare the native method to pass the Activity context to C++
    public static native void startModMenu(Object activityContext);

    @Override
    public void handleLoadPackage(LoadPackageParam lpparam) throws Throwable {
        // Only proceed if the package matches the target game
        if (!lpparam.packageName.equals(app_name)) {
            return;
        }

        // Hook UnityPlayerActivity's onCreate method
        XposedHelpers.findAndHookMethod(
                "com.unity3d.player.UnityPlayerActivity",
                lpparam.classLoader,
                "onCreate",
                Bundle.class,
                new XC_MethodHook() {
                    @Override
                    protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                        if (!loaded) {
                            // Extract the .so file to the app's cache directory
                            String pathname = "/data/user/0/" + app_name + "/cache/libxposedmenu.so";
                            File soFile = new File(pathname);

                            InputStream soFileStream = resourceStream("lib/" + target_abi + "/libxposedmenu.so");
                            if (soFileStream != null) {
                                byte[] soFileContent = new byte[soFileStream.available()];
                                soFileStream.read(soFileContent);
                                
                                if (!soFile.exists()) {
                                    soFile.createNewFile();
                                }
                                
                                FileOutputStream out = new FileOutputStream(soFile);
                                out.write(soFileContent);
                                out.flush();
                                out.close();
                                soFileStream.close();

                                // Load the library natively instead of using reflection hacks
                                System.load(pathname);
                                
                                // param.thisObject is the UnityPlayerActivity instance.
                                // Pass it to C++ so BNM has a non-null context to use.
                                startModMenu(param.thisObject);
                                
                                loaded = true;
                            }
                        }
                    }
                }
        );
    }
}
