#pragma once

#include "Include/GlobalNamespace/SkillAttribute.hpp"
#include "Include/GlobalNamespace/SkillContent.hpp"
#include "Include/GlobalNamespace/SkillDirectory.hpp"
#include "Include/GlobalNamespace/GameDirectory.hpp"
#include "SkillEnum.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Features {
    namespace SkillsHack {
        bool noCooldown = false;
        bool unliMana = false;
        bool isEnabled = false;
        
        inline std::vector<GlobalNamespace::SkillAttribute *> skillInstances;

        inline size_t capturedCount = 0;

        inline const size_t EXPECTED_SKILL_COUNT = 28;

        inline std::unordered_map<int, std::pair<double, double>> defaultSkillValues;// id -> (baseValue, valueIncrement)

        inline bool skillsCaptured = false;

        inline const char *GetSkillName(int skillId) {
            switch ((GlobalNamespace::SKILL) skillId) {
                case GlobalNamespace::SKILL::Damage:
                    return "Damage";
                case GlobalNamespace::SKILL::Firerate:
                    return "Firerate";
                case GlobalNamespace::SKILL::Health_Regen:
                    return "Health_Regen";
                case GlobalNamespace::SKILL::Critical_Chance:
                    return "Critical_Chance";
                case GlobalNamespace::SKILL::Mob_Damage_Multiplier:
                    return "Mob_Damage_Multiplier";
                case GlobalNamespace::SKILL::Boss_Damage_Multiplier:
                    return "Boss_Damage_Multiplier";
                case GlobalNamespace::SKILL::Critical_Damage:
                    return "Critical_Damage";
                case GlobalNamespace::SKILL::Health:
                    return "Health";
                case GlobalNamespace::SKILL::Hero_Damage:
                    return "Hero_Damage";
                case GlobalNamespace::SKILL::Gold_Multiplier:
                    return "Gold_Multiplier";
                case GlobalNamespace::SKILL::Elixir_Multiplier:
                    return "Elixir_Multiplier";
                case GlobalNamespace::SKILL::Stage_Retention:
                    return "Stage_Retention";
                case GlobalNamespace::SKILL::Spell_Damage:
                    return "Spell_Damage";
                case GlobalNamespace::SKILL::Mana:
                    return "Mana";
                case GlobalNamespace::SKILL::Mana_Regen:
                    return "Mana_Regen";
                case GlobalNamespace::SKILL::Spell_Cooldown_Reduction:
                    return "Spell_Cooldown_Reduction";
                case GlobalNamespace::SKILL::Idle_Damage:
                    return "Idle_Damage";
                case GlobalNamespace::SKILL::Idle_Speed:
                    return "Idle_Speed";
                case GlobalNamespace::SKILL::Weapon_Stat_Multiplier:
                    return "Weapon_Stat_Multiplier";
                case GlobalNamespace::SKILL::Stat_Upgrade_Discount:
                    return "Stat_Upgrade_Discount";
                case GlobalNamespace::SKILL::Mob_HP_Reduction:
                    return "Mob_HP_Reduction";
                case GlobalNamespace::SKILL::Boss_HP_Reduction:
                    return "Boss_HP_Reduction";
                case GlobalNamespace::SKILL::Rune_Effect_Multiplier:
                    return "Rune_Effect_Multiplier";
                case GlobalNamespace::SKILL::Critical_Damage_Multiplier:
                    return "Critical_Damage_Multiplier";
                case GlobalNamespace::SKILL::Stat_Retention:
                    return "Stat_Retention";
                case GlobalNamespace::SKILL::Siege_HP_Reduction:
                    return "Siege_HP_Reduction";
                case GlobalNamespace::SKILL::Damage_Per_Projectile:
                    return "Damage_Per_Projectile";
                case GlobalNamespace::SKILL::Flat_Damage:
                    return "Flat_Damage";
                case GlobalNamespace::SKILL::Null:
                    return "Null";
                default:
                    return "Unknown";
            }
        }

        inline std::unordered_set<void *> capturedPointers;

        void (*orig_Awake)(void *instance);
        void hooked_Awake(void *instance) {
            orig_Awake(instance);

            if (Features::SkillsHack::skillsCaptured) return;

            try {
                auto gameDir = (GlobalNamespace::GameDirectory *) instance;
                if (!gameDir) {
                    BNM_LOG_WARN("[SkillsHack] GameDirectory instance is null");
                    return;
                }

                auto skillDir = (GlobalNamespace::SkillDirectory *) gameDir->skillDirectory();
                if (!skillDir) {
                    BNM_LOG_WARN("[SkillsHack] SkillDirectory is null");
                    return;
                }

                // Iterate through all skills using MOFCOMDKLOH(skillId) method
                for (int skillId = 0; skillId < (int) Features::SkillsHack::EXPECTED_SKILL_COUNT; skillId++) {
                    try {
                        auto attr = (GlobalNamespace::SkillAttribute *) skillDir->MOFCOMDKLOH(skillId);
                        if (!attr) {
                            BNM_LOG_WARN("[SkillsHack] Skill ID %d returned null SkillAttribute", skillId);
                            continue;
                        }

                        // Check if we already captured this pointer
                        if (Features::SkillsHack::capturedPointers.find((void *) attr) != Features::SkillsHack::capturedPointers.end()) {
                            continue;// Already captured
                        }

                        int attrId = attr->id();
                        double baseVal = attr->baseValue();
                        double incVal = attr->valueIncrement();
                        const char *skillName = GetSkillName(attrId);

                        BNM_LOG_INFO("[SkillsHack] Captured SkillAttribute #%zu: id=%d name=%s baseValue=%.6f valueIncrement=%.6f (attr=%p)",
                                     Features::SkillsHack::capturedCount + 1, attrId, skillName, baseVal, incVal, attr);

                        Features::SkillsHack::skillInstances.push_back(attr);
                        Features::SkillsHack::capturedPointers.insert((void *) attr);
                        Features::SkillsHack::capturedCount++;

                    } catch (...) {
                        BNM_LOG_WARN("[SkillsHack] Exception getting SkillAttribute for skill ID %d", skillId);
                    }
                }

                if (Features::SkillsHack::capturedCount == Features::SkillsHack::EXPECTED_SKILL_COUNT) {
                    BNM_LOG_INFO("[SkillsHack] All %zu SkillAttribute instances captured!", Features::SkillsHack::EXPECTED_SKILL_COUNT);
                    Features::SkillsHack::skillsCaptured = true;
                } else {
                    BNM_LOG_WARN("[SkillsHack] Only captured %zu/%zu skills", Features::SkillsHack::capturedCount, Features::SkillsHack::EXPECTED_SKILL_COUNT);
                }

            } catch (...) {
                BNM_LOG_WARN("[SkillsHack] Exception in hooked_Awake (ptr=%p)", instance);
            }
        }

        void (*orig_FixedUpdate)(void *instance);
        void hooked_FixedUpdate(void *instance) {
            for (auto attr: Features::SkillsHack::skillInstances) {
                if (!attr) continue;

                try {
                    int skillId = attr->id();

                    // Save default values
                    if (Features::SkillsHack::defaultSkillValues.find(skillId) == Features::SkillsHack::defaultSkillValues.end()) {
                        Features::SkillsHack::defaultSkillValues[skillId] = std::make_pair(
                                attr->baseValue(),
                                attr->valueIncrement());
                    }

                    if (skillId == static_cast<int>(GlobalNamespace::SKILL::Spell_Cooldown_Reduction)) {
                        if (noCooldown) {
                            attr->set_baseValue(100.0);
                            attr->set_valueIncrement(0.0);
                        } else {
                            auto it = Features::SkillsHack::defaultSkillValues.find(skillId);
                            if (it != Features::SkillsHack::defaultSkillValues.end()) {
                                attr->set_baseValue(it->second.first);
                                attr->set_valueIncrement(it->second.second);
                            }
                        }
                    }

                    if (skillId == static_cast<int>(GlobalNamespace::SKILL::Mana_Regen)) {
                        if (unliMana) {
                            attr->set_baseValue(100000.0);
                            attr->set_valueIncrement(0.0);
                        } else {
                            auto it = Features::SkillsHack::defaultSkillValues.find(skillId);
                            if (it != Features::SkillsHack::defaultSkillValues.end()) {
                                attr->set_baseValue(it->second.first);
                                attr->set_valueIncrement(it->second.second);
                            }
                        }
                    }

                } catch (...) {
                    BNM_LOG_WARN("[SkillsHack] Exception modifying SkillAttribute (ptr=%p)", attr);
                }
            }

            orig_FixedUpdate(instance);
        }

        void initHook() {
            auto awake = BNM::Class("", "GameDirectory").GetMethod("Awake");
            auto fixedUpdate = BNM::Class("", "SkillUI").GetMethod("FixedUpdate");

            BasicHook(awake.GetOffset(), hooked_Awake, orig_Awake);
            BasicHook(fixedUpdate.GetOffset(), hooked_FixedUpdate, orig_FixedUpdate);

            BNM_LOG_INFO("[SkillsHack] Hooked GameDirectory.Awake and SkillUI.FixedUpdate");
        }
    }// namespace SkillsHack
}// namespace Features