#pragma once

namespace Features {
    namespace Equipment {
        bool isEnabled = false;

        bool (*orig_Transmog)(void *instance, int val);
        bool hooked_Transmog(void *instance, int val) {
            if (isEnabled) {
                return true;
            } else {
                return orig_Transmog(instance, val);
            }
        }

        void initHook() {
            auto transmog = BNM::Class("", "EquipmentsData").GetMethod("JKPPALMJPPO");

            BasicHook(transmog.GetOffset(), hooked_Transmog, orig_Transmog);

            BNM_LOG_INFO("[EquipmentsData] Hooked EquipmentsData.JKPPALMJPPO");
        }
    }// namespace Equipment
}// namespace Features
