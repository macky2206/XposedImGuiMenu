#pragma once

namespace Features {
    namespace Expedition {
        bool isEnabled = false;
        int value = 1;

        int (*orig_expTime)(void *instance);
        int hook_exTime(void *instance) {
            if (isEnabled) {
                return value;
            } else {
                return orig_expTime(instance);
            }
        }

        void initHook() {
            auto expTimeMethod = BNM::Class("", "ExpeditionManager").GetMethod("LCCGPGCHLGK");

            BasicHook(expTimeMethod.GetOffset(), hook_exTime, orig_expTime);
            BNM_LOG_INFO("[ExpeditionManager] Hooked ExpeditionManager.LCCGPGCHLGK successfully");
        }
    }// namespace Expedition
}// namespace Features