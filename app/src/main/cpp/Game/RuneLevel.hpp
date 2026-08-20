#pragma once

namespace Features {
    namespace RuneLevel {
        bool isEnabled = false;
        int value = 1;

        // int PDCGPOMMPJH(RuneContent LNDJFPKFLCC, int JGBHFMMFCNB, bool BFMCDJCLKAP = True) {}
        int (*orig_GetRuneLevel)(void *instance, void* RuneContent, int param1, bool param2);
        int hook_GetRuneLevel(void *instance, void* RuneContent, int param1, bool param2 = true) {
            if (isEnabled) {
                return value;
            } else {
                return orig_GetRuneLevel(instance, RuneContent, param1, param2);
            }
        }

        void initHook() {
            auto getRuneLevelMethod = BNM::Class("", "RuneData").GetMethod("PDCGPOMMPJH");

            BasicHook(getRuneLevelMethod.GetOffset(), hook_GetRuneLevel, orig_GetRuneLevel);
            BNM_LOG_INFO("[RuneLevel] Hooked RuneData.PDCGPOMMPJH");
        }
    }// namespace RuneLevel
}// namespace Features