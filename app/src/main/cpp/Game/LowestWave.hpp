#pragma once

namespace Features {
    namespace LowestWave {
        bool isEnabled = false;

        int (*orig_WaveCounts)(void *instance, int val);
        int hooked_WaveCounts(void *instance, int val) {
            if (isEnabled) {
                return 1;
            } else {
                return orig_WaveCounts(instance, val);
            }
        }

        void initHook() {
            auto waveCounts = BNM::Class("", "StageGeneratorCampaign").GetMethod("DHGMIEAOFHE");

            BasicHook(waveCounts.GetOffset(), hooked_WaveCounts, orig_WaveCounts);

            BNM_LOG_INFO("[LowestWave] Hooked StageGeneratorCampaign.DHGMIEAOFHE");
        }
    } // namespace LowestWave
} // namespace Features