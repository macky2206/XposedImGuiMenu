#pragma once

#include "Include/GlobalNamespace/PlayerController.hpp"
#include "Include/UnityEngine/Time.hpp"

namespace Features {
    namespace SpeedHack {
        int speedValue = 1;

        void hooked_ctor(void* instance) {
            // Leave empty to intercept the constructor of the AntiSpeedhack
        }

        void initHook() {
            auto ctor = BNM::Class("", "AntiSpeedhack").GetMethod(".ctor");

            BasicHook(ctor.GetOffset(), hooked_ctor, nullptr);

            BNM_LOG_INFO("[SpeedHack] Hooked AntiSpeedhack constructor");
        }
    }
}

struct PlayerController : BNM::UnityEngine::MonoBehaviour {
    BNM_CustomClass(PlayerController,
                    BNM::CompileTimeClassBuilder("", "PlayerController").Build(),
                    BNM::Defaults::Get<BNM::UnityEngine::MonoBehaviour>(), {});

    void LateUpdate() {
        auto thiz = (GlobalNamespace::PlayerController *) this;
        float currentTimeScale = UnityEngine::Time::get_timeScale();
        if (currentTimeScale != 0.0f && Features::SpeedHack::speedValue != 1) {
            float desiredTimeScale = static_cast<float>(Features::SpeedHack::speedValue);
            if (currentTimeScale != desiredTimeScale) {
                UnityEngine::Time::set_timeScale(desiredTimeScale);
            }
        }
    }

    BNM_CustomMethod(LateUpdate, false, BNM::Defaults::Get<void>(), "LateUpdate");
};