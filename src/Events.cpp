#include "Events.h"

inline void AnimationGraphEventHandler::StaminaCost(RE::Actor* actor, double cost)
{
    // logger::debug("stamina for attacks is {}", cost);
    RE::PlayerCharacter* player = Cache::GetPlayerSingleton();
    if (actor == player && !player->IsGodMode()) {
        actor->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, cost * -1.0f);
        logger::debug("attacks costs {} stamina", cost);
    }
    else
        actor->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, cost * -1.0f);
}

inline void AnimationGraphEventHandler::ProcessJump(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event,
                                                    RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
{
    const char* jumpAnimEventString = "JumpUp";

    if (!a_event) {
        return;
    }
    if (!a_event->tag.empty() && a_event->holder && a_event->holder->As<RE::Actor>()) {
        if (std::strcmp(a_event->tag.c_str(), jumpAnimEventString) == 0) {
            HandleJumpAnim();
        }
    }
    return;
};

inline void AnimationGraphEventHandler::ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event,
                                                     RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
{
    const char* HitString   = "HitFrame";
    const char* DodgeString = "TKDR_DodgeStart"; // Test to make stuff while dodging
    const char* BFCORec = "MCO_Recovery";
    const char* BowShoot = "BowRelease";
    Settings* settings = Settings::GetSingleton();
    if (!a_event) {
        return;
    }
    // DOES NOT WORK YET
    /*if (!a_event->tag.empty() && a_event->holder && a_event->holder->As<RE::Actor>())
    {
        if (std::strcmp(a_event->tag.c_str(), BowShoot) == 0) {
            logger::debug("Bow Shoot event");
            RE::Actor* shooter = const_cast<RE::TESObjectREFR*>(a_event->holder)->As<RE::Actor>();
            if (shooter->HasPerk(settings->dummyPerkDodge)) {
                if (auto targ = shooter->GetActorRuntimeData().currentCombatTarget.get().get(); targ) {
                    dlog("target is {}", targ->GetDisplayFullName());
                }
                
                Conditions::LaunchExtraArrow(shooter, shooter->GetCurrentAmmo(), Conditions::getWieldingWeapon(shooter), "", -1, shooter->GetActorRuntimeData().currentCombatTarget.get().get(), nullptr);
            }            
        }
    }*/

    if (!a_event->tag.empty() && a_event->holder && a_event->holder->As<RE::Actor>()) {
        // debug logging to catch any animation event. used for potential new events
        //dlog("--- [ANIMATION EVENT] --- Animation Event is {} \n \n ", a_event->tag);
        if (std::strcmp(a_event->tag.c_str(), HitString) == 0) {
            if (a_event->holder->As<RE::Actor>()) {
                RE::PlayerCharacter* player         = Cache::GetPlayerSingleton();
                auto                 actor          = const_cast<RE::TESObjectREFR*>(a_event->holder)->As<RE::Actor>();
                auto                 wieldedWeap    = Conditions::getWieldingWeapon(actor);
                const Settings*      settings       = Settings::GetSingleton();
                RE::TESGlobal*       stamGlob       = settings->StaminaCostGlobal;
                auto                 global         = stamGlob->value;
                auto                 npc_glob       = settings->NPCStaminaCostGlobal->value;
                double               stam_cost      = 10.0;
                double               dual_wield_mod = 1.2;

                if (actor == player) {
                    if (wieldedWeap && wieldedWeap->IsWeapon() && wieldedWeap->IsMelee()) {
                        bool dagger     = wieldedWeap->IsOneHandedDagger();
                        bool sword      = wieldedWeap->IsOneHandedSword();
                        bool mace       = wieldedWeap->IsOneHandedMace();
                        bool axe        = wieldedWeap->IsOneHandedAxe();
                        bool greatsword = wieldedWeap->IsTwoHandedSword();
                        bool greataxe   = wieldedWeap->IsTwoHandedAxe();

                        if (sword || axe || mace) {
                            if (Conditions::IsDualWielding(actor)) {
                                stam_cost = global * dual_wield_mod;
                            }
                            else
                                stam_cost = global;
                        }
                        else if (greatsword || greataxe) {
                            stam_cost = global * 1.5;
                        }
                        else if (dagger || wieldedWeap->IsHandToHandMelee()) {
                            if (dagger && Conditions::IsDualWielding(actor)) {
                                stam_cost = global * 0.8 * dual_wield_mod;
                            }
                            else
                                stam_cost = global * 0.8;
                        }
                    }
                    if (player->IsGodMode()) {
                        stam_cost = 0.0;
                    }
                }
                else {
                    if (actor != player) {
                        if (wieldedWeap && wieldedWeap->IsWeapon() && wieldedWeap->IsMelee()) {
                            bool dagger     = wieldedWeap->IsOneHandedDagger();
                            bool sword      = wieldedWeap->IsOneHandedSword();
                            bool mace       = wieldedWeap->IsOneHandedMace();
                            bool axe        = wieldedWeap->IsOneHandedAxe();
                            bool greatsword = wieldedWeap->IsTwoHandedSword();
                            bool greataxe   = wieldedWeap->IsTwoHandedAxe();

                            if (sword || axe || mace) {
                                if (Conditions::IsDualWielding(actor)) {
                                    stam_cost = npc_glob * dual_wield_mod;
                                }
                                stam_cost = npc_glob;
                            }
                            else if (greatsword || greataxe) {
                                stam_cost = npc_glob * 1.5;
                            }
                            else if (dagger || wieldedWeap->IsHandToHandMelee()) {
                                if (dagger && Conditions::IsDualWielding(actor)) {
                                    stam_cost = npc_glob * 0.8 * dual_wield_mod;
                                }
                                stam_cost = npc_glob * 0.8;
                            }
                        }
                    }
                }
                if (!Conditions::IsPowerAttacking(actor)) {
                    StaminaCost(actor, stam_cost);
                }
            }
        }
    }
    if (!a_event->tag.empty() && a_event->holder && a_event->holder->As<RE::Actor>()) {
        if (std::strcmp(a_event->tag.c_str(), DodgeString) == 0) {
            if (a_event->holder->As<RE::Actor>()) {
                const Settings* settings = Settings::GetSingleton();
                if (a_event->holder->As<RE::Actor>()->HasPerk(settings->dummyPerkDodge)) {
                    logger::debug("Dodge happened");
                    RE::PlayerCharacter* player   = Cache::GetPlayerSingleton();
                    RE::NiPoint3         playerPos;
                    playerPos.x = player->GetPositionX();
                    playerPos.y = player->GetPositionY();
                    playerPos.z = player->GetPositionZ();
                    Conditions::CastSpellFromPointToPoint(player, settings->DodgeRuneSpell, playerPos.x, playerPos.y, playerPos.z + 10, playerPos.x, playerPos.y,
                                                          playerPos.z - 150);
                }
            }
        }
    }
    return;
}

EventResult AnimationGraphEventHandler::ProcessEvent_NPC(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event,
                                                         RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
{
    ProcessEvent(a_sink, a_event, a_eventSource);
    return _ProcessEvent_NPC(a_sink, a_event, a_eventSource);
}

EventResult AnimationGraphEventHandler::ProcessEvent_PC(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event,
                                                        RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
{
    ProcessEvent(a_sink, a_event, a_eventSource);
    return _ProcessEvent_PC(a_sink, a_event, a_eventSource);
}
