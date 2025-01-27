#pragma once

class Settings
{
public:
    static Settings* GetSingleton();

    void LoadSettings();
    void LoadForms();
    void AdjustWeaponStaggerVals();
    void GetIngameData();
    void SetGlobalsAndGameSettings();  
    void LoadMCMSettings();
    void ReadColorStringSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, uint32_t& a_setting);

    // Spells
    RE::SpellItem* IsAttackingSpell;
    RE::SpellItem* IsBlockingSpell;
    RE::SpellItem* IsSneakingSpell;
    RE::SpellItem* IsSprintingSpell;
    RE::SpellItem* MountSprintingSpell;
    RE::SpellItem* BowStaminaSpell;
    RE::SpellItem* XbowStaminaSpell;
    RE::SpellItem* IsCastingSpell;
    RE::SpellItem* MAGParryStaggerSpell;
    RE::SpellItem* MAGParryControllerSpell;
    RE::SpellItem* MAGCrossbowStaminaDrainSpell;
    RE::SpellItem* APOParryBuffSPell;
    RE::SpellItem* jumpSpell;
    RE::SpellItem* PowerAttackStopSpell;
    RE::SpellItem* ArrowRainCooldownSpell;
    RE::SpellItem* MultiShotCooldownSpell;

    RE::SpellItem* DodgeRuneSpell;
    // Perks
    RE::BGSPerk* BashStaminaPerk;
    RE::BGSPerk* BlockStaminaPerk;
    RE::BGSPerk* ArrowRainPerk;
    RE::BGSPerk* MultiShotPerk;
    RE::BGSPerk* PitFighterPerk;
    // Explosions (Sparks)
    RE::BGSExplosion* APOSparks;
    RE::BGSExplosion* APOSparksPhysics;
    RE::BGSExplosion* APOSparksFlash;
    RE::BGSExplosion* APOSparksShieldFlash;
    // Globals
    RE::TESGlobal* StaminaCostGlobal;
    RE::TESGlobal* NPCStaminaCostGlobal;
    RE::TESGlobal* DualBlockKey;
    // Effects
    RE::EffectSetting* MAG_ParryWindowEffect;
    RE::EffectSetting* ArrowRainCooldownEffect;
    RE::EffectSetting* MultiShotCooldownEffect;
    RE::EffectSetting* StaminaPenaltyEffect;
    RE::EffectSetting* StaminaPenEffectNPC;
    // Conditions
    RE::TESCondition* IsPowerAttacking;

    //tests
    RE::SpellItem* fireBolt;

    // bools
    bool               enableSneakStaminaCost;
    bool               enableLevelDifficulty;
    bool               zeroAllWeapStagger;
    bool               armorScalingEnabled;
    bool               IsBlockingWeaponSpellCasted = false;
    bool               wasPowerAttacking           = false;
    inline static bool debug_logging{};
    // floats
    inline static float BonusXPPerLevel;
    inline static float BaseXP;
    float               blockAngleSetting;
    float               surroundingActorsRange;
    // int
    inline static uint32_t blockingKey[RE::INPUT_DEVICE::kFlatTotal] = { 0xFF, 0xFF, 0xFF };
    inline static uint32_t blockKeyMouse{ 0xFF };
    inline static uint32_t blockKeyKeyboard{ 0xFF };
    inline static uint32_t blockKeyGamePad{ 0xFF };
    int                    maxFrameCheck = 6;
    static inline uint32_t               dualBlockKey;
    static inline std::string colorCodeStaminaPenalty;
    static inline uint32_t uColorCodeStamBar = 0xDF2020;
    static inline float dmgModifierMaxEnemy = 1.5f;
    static inline float dmgModifierMidEnemy = 1.3f;
    static inline float dmgModifierMinEnemy = 1.15f;
    static inline bool TrueHudAPI_Obtained;

    // tests
    RE::BGSPerk* dummyPerkDodge;

    static RE::FormID ParseFormID(const std::string& str);

    std::string FileName;
};
