#pragma once

#include "SDK/CostAttribute.h"
#include "SDK/SkillAttribute.h"
#include "SDK/SkillContent.h"
#include "SDK/SkillUI.h"
#include "SDK/StatContent.h"
#include "SDK/StatUI.h"
#include "SDK/UnityEngine/Object.h"

#include <vector>

#include <unordered_map>

namespace Features {
    namespace set0Prices {
        bool isEnabled = false;

        struct DefaultCost {
            double baseValue;
            double valueIncrement;
        };
        inline std::unordered_map<GlobalNamespace::CostAttribute *, DefaultCost> defaultValues;
        // Store original values for SkillAttribute instances (e.g. Spell_Cooldown_Reduction)
        inline std::unordered_map<GlobalNamespace::SkillAttribute *, DefaultCost> defaultSkillValues;
        // Collected SkillAttribute instances (active or inactive)
        inline std::vector<GlobalNamespace::SkillAttribute *> skillAttributes;

        // RuneDirectory.GKMCFIBOLDE(int MBHCFFAKMAI, int JHJMOMGKGCI)
    	// private int GKMCFIBOLDE(int MBHCFFAKMAI, int JHJMOMGKGCI) { }
        int (*orig_RuneFusionCosts_1)(void *instance, int param1, int param2);
        int hook_RuneFusionCosts_1(void *instance, int param1, int param2) {
            if (isEnabled) {
                return 0;
            } else {
                return orig_RuneFusionCosts_1(instance, param1, param2);
            }
        }

        // RuneDirectory.BPLFGPOHEBN(int MBHCFFAKMAI, int JHJMOMGKGCI)
        // public int BPLFGPOHEBN(int MBHCFFAKMAI, int JHJMOMGKGCI) { }
        int (*orig_RuneFusionCosts_2)(void *instance, int param1, int param2);
        int hook_RuneFusionCosts_2(void *instance, int param1, int param2) {
            if (isEnabled) {
                return 0;
            } else {
                return orig_RuneFusionCosts_2(instance, param1, param2);
            }
        }

        // RuneDirectory.KNOFHCMOIMF(int JHJMOMGKGCI)
        // public double KNOFHCMOIMF(int JHJMOMGKGCI) { }
        double (*orig_RuneCloneCosts)(void* instance, int param1);
        double hook_RuneCloneCosts(void* instance, int param1) {
            if (isEnabled) {
                return 0;
            } else {
                return orig_RuneCloneCosts(instance, param1);
            }
        }

        // HeroDirectory.PIICFHCDDOA(int CBBDKGHICNF, int IFONINODIOP = 0)
        // public int PIICFHCDDOA(int CBBDKGHICNF, int IFONINODIOP = 0) { }
        int (*orig_HeroAscensionCosts)(void *instance, int param1, int param2);
        int hook_HeroAscensionCosts(void *instance, int param1, int param2 = 0) {
            if (isEnabled) {
                return 0;
            } else {
                return orig_HeroAscensionCosts(instance, param1, param2);
            }
        }

        // HeroSkillTree.ACJLHOLNJKP()
        // private int ACJLHOLNJKP() { }
        int (*orig_HeroSkillsCosts)(void* instance);
        int hook_HeroSkillsCosts(void *instance) {
            if (isEnabled) {
                return 0;
            } else {
                return orig_HeroSkillsCosts(instance);
            }
        }

        void initHook() {
            auto FirstRuneFusionMethod = BNM::Class("", "RuneDirectory").GetMethod("GKMCFIBOLDE");
            auto SecondRuneFusionMethod = BNM::Class("", "RuneDirectory").GetMethod("BPLFGPOHEBN");
            auto RuneCloneMethod = BNM::Class("", "RuneDirectory").GetMethod("KNOFHCMOIMF");
            auto HeroAscensionMethod = BNM::Class("", "HeroDirectory").GetMethod("PIICFHCDDOA");
            auto HeroSkillsMethod = BNM::Class("", "HeroSkillTree").GetMethod("ACJLHOLNJKP");

            auto firstRuneFusionHook = BasicHook(FirstRuneFusionMethod.GetOffset(), hook_RuneFusionCosts_1, orig_RuneFusionCosts_1);
            if (firstRuneFusionHook) {
                BNM_LOG_INFO("[Set0Prices] Hooked RuneDirectory.GKMCFIBOLDE successfully.");
            } else {
                BNM_LOG_INFO("[Set0Prices] Failed to hook RuneDirectory.GKMCFIBOLDE.");
            }
            auto secondRuneFusionHook = BasicHook(SecondRuneFusionMethod.GetOffset(), hook_RuneFusionCosts_2, orig_RuneFusionCosts_2);
            if (secondRuneFusionHook) {
                BNM_LOG_INFO("[Set0Prices] Hooked RuneDirectory.BPLFGPOHEBN successfully.");
            } else {
                BNM_LOG_INFO("[Set0Prices] Failed to hook RuneDirectory.BPLFGPOHEBN.");
            }

            auto runeCloneHook = BasicHook(RuneCloneMethod.GetOffset(), hook_RuneCloneCosts, orig_RuneCloneCosts);
            if (runeCloneHook) {
                BNM_LOG_INFO("[Set0Prices] Hooked RuneDirectory.KNOFHCMOIMF (RuneCloneCosts) successfully.");
            } else {
                BNM_LOG_INFO("[Set0Prices] Failed to hook RuneDirectory.KNOFHCMOIMF (RuneCloneCosts).");
            }

            auto heroAscensionHook = BasicHook(HeroAscensionMethod.GetOffset(), hook_HeroAscensionCosts, orig_HeroAscensionCosts);
            if (heroAscensionHook) {
                BNM_LOG_INFO("[Set0Prices] Hooked HeroDirectory.PIICFHCDDOA (HeroAscensionCosts) successfully.");
            } else {
                BNM_LOG_INFO("[Set0Prices] Failed to hook HeroDirectory.PIICFHCDDOA (HeroAscensionCosts).");
            }

            auto heroSkillsHook = BasicHook(HeroSkillsMethod.GetOffset(), hook_HeroSkillsCosts, orig_HeroSkillsCosts);
            if (heroSkillsHook) {
                BNM_LOG_INFO("[Set0Prices] Hooked HeroSkillTree.ACJLHOLNJKP (HeroSkillsCosts) successfully.");
            } else {
                BNM_LOG_INFO("[Set0Prices] Failed to hook HeroSkillTree.ACJLHOLNJKP (HeroSkillsCosts).");
            }
        }
    }// namespace set0Prices
}// namespace Features

struct StatUI : BNM::UnityEngine::MonoBehaviour {
    BNM_CustomClass(StatUI,
                    BNM::CompileTimeClassBuilder("", "StatUI").Build(),
                    BNM::Defaults::Get<BNM::UnityEngine::MonoBehaviour>(), {});

    void LateUpdate() {
        auto thiz = (GlobalNamespace::StatUI *) this;
        auto content = (GlobalNamespace::StatContent *) thiz->content();
        if (content != nullptr) {
            auto cost = (GlobalNamespace::CostAttribute *) content->cost();
            if (cost != nullptr) {
                auto &map = Features::set0Prices::defaultValues;
                if (map.find(cost) == map.end()) {
                    map[cost] = Features::set0Prices::DefaultCost{
                            cost->baseValue(),
                            cost->valueIncrement()};
                }
                if (Features::set0Prices::isEnabled) {
                    cost->set_baseValue(0.0);
                    cost->set_valueIncrement(0.0);
                } else {
                    auto it = map.find(cost);
                    if (it != map.end()) {
                        cost->set_baseValue(it->second.baseValue);
                        cost->set_valueIncrement(it->second.valueIncrement);
                    }
                }
            }
        }
    }

    BNM_CustomMethod(LateUpdate, false, BNM::Defaults::Get<void>(), "LateUpdate");
};

struct SkillUI : BNM::UnityEngine::MonoBehaviour {
    BNM_CustomClass(SkillUI,
                    BNM::CompileTimeClassBuilder("", "SkillUI").Build(),
                    BNM::Defaults::Get<BNM::UnityEngine::MonoBehaviour>(), {});

    void LateUpdate() {
        auto thiz = (GlobalNamespace::SkillUI *) this;
        auto content = (GlobalNamespace::SkillContent *) thiz->content();
        if (content != nullptr) {
            auto cost = (GlobalNamespace::CostAttribute *) content->cost();
            if (cost != nullptr) {
                auto &map = Features::set0Prices::defaultValues;
                if (map.find(cost) == map.end()) {
                    map[cost] = Features::set0Prices::DefaultCost{
                            cost->baseValue(),
                            cost->valueIncrement()};
                }
                if (Features::set0Prices::isEnabled) {
                    cost->set_baseValue(0.0);
                    cost->set_valueIncrement(0.0);
                } else {
                    auto it = map.find(cost);
                    if (it != map.end()) {
                        cost->set_baseValue(it->second.baseValue);
                        cost->set_valueIncrement(it->second.valueIncrement);
                    }
                }
            }
        }
        // auto attr = (GlobalNamespace::SkillAttribute *) content->$value();
        // if (attr != nullptr) {
        //     if (attr->id() == 15) {
        //         auto &skillMap = Features::set0Prices::defaultSkillValues;
        //         // Save original values the first time we see this attribute
        //         if (skillMap.find(attr) == skillMap.end()) {
        //             skillMap[attr] = Features::set0Prices::DefaultCost{
        //                     attr->baseValue(),
        //                     attr->valueIncrement()};
        //         }

        //         if (Features::set0Prices::noCooldown) {
        //             attr->set_baseValue(100.0);
        //             attr->set_valueIncrement(0.0);
        //         } else {
        //             // Restore saved original values when toggled off
        //             auto it = skillMap.find(attr);
        //             if (it != skillMap.end()) {
        //                 attr->set_baseValue(it->second.baseValue);
        //                 attr->set_valueIncrement(it->second.valueIncrement);
        //             }
        //         }
        //     }
        // }
    }

    void FixedUpdate() {

    }

    BNM_CustomMethod(LateUpdate, false, BNM::Defaults::Get<void>(), "LateUpdate");
    BNM_CustomMethod(FixedUpdate, false, BNM::Defaults::Get<void>(), "FixedUpdate");
};