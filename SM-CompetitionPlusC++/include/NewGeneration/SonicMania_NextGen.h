#pragma once
#define _USE_MATH_DEFINES
#include "MemAccess.h"
#include <cmath>

// #region PreprocessorDefines
#define BitFlag(type, enumType) inline type operator|(type a, type b) { return (type)((enumType)a | (enumType)b); }
#define ALIGN(x) __declspec(align(x))

#define DataTruePointer(type, name, address) \
	static type* name = (type *)(baseAddress + address)

typedef signed char Sint8;
typedef unsigned char Uint8;
typedef signed short Sint16;
typedef unsigned short Uint16;
typedef signed int Sint32;
typedef unsigned int Uint32;
typedef void* VoidPtr;
// #endregion

namespace SonicMania
{
// #region TypesDefs
typedef void(__cdecl *Ability)();
typedef void(__cdecl *PlayerStatus)();
typedef void(__cdecl *InputStatus)();
// #endregion

// #region Enums
enum Scene : Uint16 {
    // Presentation
    Scene_Logo,
    Scene_Title,
    Scene_MainMenu,
    Scene_ThanksForPlaying,
    Scene_LevelSelect,
    Scene_Credits,
    Scene_Continue,
    Scene_Summary,
    Scene_Summary_e,
    // Mania Mode
    Scene_GHZ1,
    Scene_GHZ2,
    Scene_CPZ1,
    Scene_CPZ2,
    Scene_SPZ1,
    Scene_SPZ2,
    Scene_FBZ1,
    Scene_FBZ2,
    Scene_PSZ1,
    Scene_PSZ2,
    Scene_SSZ1,
    Scene_SSZ2,
    Scene_SSZ2M,
    Scene_HCZ1,
    Scene_HCZ2,
    Scene_MSZ1,
    Scene_MSZ1K,
    Scene_MSZ2,
    Scene_OOZ1,
    Scene_OOZ2,
    Scene_LFZ1,
    Scene_LFZ2,
    Scene_LFZ3,
    Scene_MMZ1,
    Scene_MMZ2,
    Scene_TMZ1,
    Scene_TMZ2,
    Scene_TMZ3,
    Scene_ERZ,
    // Encore Mode
    Scene_GHZ1_e,
    Scene_GHZ2_e,
    Scene_CPZ1_e,
    Scene_CPZ2_e,
    Scene_SPZ1_e,
    Scene_SPZ2_e,
    Scene_FBZ1_e,
    Scene_FBZ2_e,
    Scene_PSZ1_e,
    Scene_PSZ2_e,
    Scene_SSZ1_e,
    Scene_SSZ2_e,
    Scene_SSZ2M_e,
    Scene_HCZ1_e,
    Scene_HCZ2_e,
    Scene_MSZ1_e,
    Scene_MSZ2_e,
    Scene_OOZ1_e,
    Scene_OOZ2_e,
    Scene_LFZ1_e,
    Scene_LFZ2_e,
    Scene_LFZ3_e,
    Scene_MMZ1_e,
    Scene_MMZ2_e,
    Scene_TMZ1_e,
    Scene_TMZ2_e,
    Scene_TMZ3_e,
    // Special Stage
    Scene_SpecialStage1,
    Scene_SpecialStage2,
    Scene_SpecialStage3,
    Scene_SpecialStage4,
    Scene_SpecialStage5,
    Scene_SpecialStage6,
    Scene_SpecialStage7,
    Scene_SpecialStage1_e,
    Scene_SpecialStage2_e,
    Scene_SpecialStage3_e,
    Scene_SpecialStage4_e,
    Scene_SpecialStage5_e,
    Scene_SpecialStage6_e,
    Scene_SpecialStage7_e,
    // Blue Sphere (+0 - +31)
    Scene_BlueSphere,
    Scene_BlueSphere_Random = Scene_BlueSphere + 32,
    Scene_BlueSphere_Random2,
    // Pinball
    Scene_Pinball,
    // Extras
    Scene_PuyoPuyo,
    Scene_DAGarden,
    Scene_DAGarden_e,
    // Cutscene
    Scene_Cutscene_AngelIsland,
    Scene_Cutscene_AngelIsland_e,
    Scene_Cutscene_GreenHillZone,
    Scene_Cutscene_GreenHillZone2,
    Scene_Cutscene_MirageSaloonKnucklesIntro,
    Scene_Cutscene_StardustSpeedwayTimeTravel,
    Scene_TryAgain,
    Scene_Cutscene_MirageSaloonEnd_e,
    Scene_TryAgain_e,
    // Video
    Scene_BadEnd_Sonic,
    Scene_BadEnd_Sonic2,
    Scene_BadEnd_Tails,
    Scene_BadEnd_Knux,
    Scene_BadEnd_Mighty,
    Scene_BadEnd_Ray,
    Scene_GoodEnd,
    Scene_TrueEnd
};
enum GameMode : Uint32 {
    GameMode_ManiaMode,
    GameMode_EncoreMode,
    GameMode_TimeAttack,
    GameMode_Competition
};
enum Filter : Uint8 {
    Filter_None = 0b0000,
    Filter_ManiaMode = 0b0001,
    Filter_Unknown = 0b0010,
    Filter_EncoreMode = 0b0100
};
BitFlag(Filter, Uint8);
enum GameStates : Uint8 {
    GameState_NotRunning = 0b0000,
    GameState_Running = 0b0001,
    GameState_SoftPause = 0b0010,
    GameState_HardPause = 0b0100,
    GameState_DevMenu = 0b1000
};
BitFlag(GameStates, Uint8);

// TODO: needs updating
enum ObjectType {
    // General
    ObjectType_Ring             = 0x00AC67E0,
    ObjectType_SSRing           = 0x00AC686C,
    ObjectType_ItemBox          = 0x00AC6F00,
    ObjectType_Spring           = 0x00AC6BD8,
    ObjectType_Animal           = 0x00AC6D78,
    ObjectType_ScoreOnHitNumber = 0x00AC6D80,
    ObjectType_Explosion        = 0x00AC6D84,
    ObjectType_Spikes           = 0x00AC67BC,
    ObjectType_Player           = 0x00AC6838,
    ObjectType_Zone             = 0x00AC690C,
    // Green Hill Zone
    ObjectType_Motobug          = 0x00AC6B60,
    ObjectType_CrabMeat         = 0x00AC6F9C,
    ObjectType_Chopper          = 0x00AC6A8C,
    ObjectType_BuzzBomber       = 0x00AC6F2C,
    ObjectType_NewTron          = 0x00AC6F84,
    ObjectType_BatBrain         = 0x00AC6F90,
    ObjectType_Splats           = 0x00AC6900,
    ObjectType_DDWrecker        = 0x00AC67F0,
    ObjectType_DERobot          = 0x00AC6D70,
    ObjectType_CheckerBall      = 0x00AC66B8,
    // Chemical Plant Zone
    ObjectType_Grabber          = 0x00AC6C18,
    ObjectType_Spiny            = 0x00AC6DAC,
    ObjectType_AmoebaDroid      = 0x00AC67F0,
    ObjectType_CatakillerJR     = 0x00AC6798,
    // Studiopolis Zone
    ObjectType_MicDrop          = 0x00AC6DA8,
    ObjectType_ShutterBug       = 0x00AC6E58,
    ObjectType_Tubinaut         = 0x00AC6AD0,
    ObjectType_WallCrawl        = 0x00AC6B14,
    ObjectType_HeavyGunner      = 0x00AC6C2C,
    ObjectType_WeatherMobile    = 0x00AC6A80,
    ObjectType_CircleBumper     = 0x00AC6904,
    // Flying Battery
    ObjectType_TechnoSqueek     = 0x00AC69FC,
    ObjectType_Blaster          = 0x00AC6A6C,
    ObjectType_Clucker          = 0x00AC6C88,
    // Press Garden Zone
    ObjectType_Dragonfly        = 0x00AC6928,
    ObjectType_Jugglesaw        = 0x00AC6688,
    ObjectType_SplatsJar        = 0x00AC6CB4,
    ObjectType_Woodrow          = 0x00AC67FC,
    ObjectType_IceBomba         = 0x00AC66EC,
    ObjectType_HeavyShinobi     = 0x00AC6B08,
    // StarDust Speed Way
    ObjectType_Hotaru           = 0x00AC6808,
    ObjectType_Dango            = 0x00AC6C7C,
    ObjectType_Kanabun          = 0x00AC67FC,
    ObjectType_Kabasira         = 0x00AC6CB4,
    ObjectType_SilverSonic      = 0x00AC679C,
    ObjectType_MetalSonic       = 0x00AC6B34,
    // HydroCity Zone
    ObjectType_Jellygnite       = 0x00AC6B9C,
    ObjectType_Pointdexter      = 0x00AC6A2C,
    ObjectType_Blastoid         = 0x00AC66F4,
    ObjectType_Jawz             = 0x00AC6D10,
    ObjectType_MegaChopper      = 0x00AC6DB8,
    ObjectType_TurboSpiker      = 0x00AC6DF0,
    ObjectType_Buggernaut       = 0x00AC6728,
    //MirageSaloonZone
    ObjectType_Vultron          = 0x00AC67CC,
    ObjectType_Cactula          = 0x00AC6EC4,
    ObjectType_Bumpalo          = 0x00AC66A4,
    ObjectType_Rattlekiller     = 0x00AC6748,
    ObjectType_BallHog          = 0x00AC69A0,
    ObjectType_Armadiloid       = 0x00AC68A4,
    //Oil Ocean Zone
    ObjectType_Aquis            = 0x00AC6EE4,
    ObjectType_Octus            = 0x00AC6DC4,
    ObjectType_Sol              = 0x00AC6778,
    // Lave Reef Zone
    ObjectType_Toxomister       = 0x00AC6FA0, // 0x004DC320 // ID: 0x0051
    ObjectType_Fireworm         = 0x00AC6A40,
    ObjectType_Iwamodoki        = 0x00AC6638,
    ObjectType_Rexon            = 0x00AC6DD4,
    ObjectType_BuckwildBall     = 0x00AC6980, // 0x004DD028 // ID: 0x003E // dword_EC68D0
    // Metallic Madness Zone
    ObjectType_MechaBu          = 0x00AC6888,
    ObjectType_MatryoshkaBom    = 0x00AC6C30,
    ObjectType_Scarab           = 0x00AC69A8,
    ObjectType_PohBee           = 0x00AC6950,
    // Titanic Monarch Zone
    ObjectType_SentryBug        = 0x00AC6E70,
    ObjectType_TurboTurtle      = 0x00AC683C,
    ObjectType_FlasherMkII      = 0x00AC670C,
    ObjectType_BallHog2         = 0x00AC6678,

    // Angel Island Zone
    ObjectType_MonkeyDude       = 0x00AC6784,
    ObjectType_Rhinobot         = 0x00AC6C24,
    ObjectType_Bloominator      = 0x00AC6F48,

    ObjectType_Water            = 0x00AC6E3C
};
enum AttributeType {
    AttributeType_UInt8 = 0,
    AttributeType_UInt16 = 1,
    AttributeType_UInt32 = 2,
    AttributeType_Int8 = 3,
    AttributeType_Int16 = 4,
    AttributeType_Int32 = 5,
    AttributeType_Var = 6, // 4
    AttributeType_Bool = 7, // 4
    AttributeType_String = 8,
    AttributeType_Position = 9,
    AttributeType_Unknown = 10,
    AttributeType_Color = 11,
};

// Entity Enums
enum Scope {
    Scope_None,
    Scope_Global,
    Scope_Stage
};
enum TransparencyFlag : BYTE {
    TransparencyFlag_Opaque,
    TransparencyFlag_HalfTransparent,
    TransparencyFlag_Transparent
};

// EntityPlayer Enums
enum Character : int {
    Character_None = 0b00000,
    Character_Sonic = 0b00001, // 1 << 0
    Character_Tails = 0b00010, // 1 << 1
    Character_Knux = 0b00100, // 1 << 2
    Character_Mighty = 0b01000, // 1 << 3
    Character_Ray = 0b10000  // 1 << 4
};
enum ShieldType : int {
    ShieldType_None,
    ShieldType_Normal,
    ShieldType_Water,
    ShieldType_Flame,
    ShieldType_Lightning
};
enum SuperState : int {
    SuperState_NotActive,
    SuperState_Activate,
    SuperState_Active,
    SuperState_Deactive
};

// EntityItemBox Enums
enum ItemBoxItem : BYTE  {
    ItemBoxItem_Ring,
    ItemBoxItem_ShieldNormal,
    ItemBoxItem_ShieldWater,
    ItemBoxItem_ShieldFlame,
    ItemBoxItem_ShieldLightning,
    ItemBoxItem_Invincibility,
    ItemBoxItem_SpeedShoes,
    ItemBoxItem_LifeSonic,
    ItemBoxItem_LifeTails,
    ItemBoxItem_LifeKnuckles,
    ItemBoxItem_Eggman,
    ItemBoxItem_CombineRing,
    ItemBoxItem_TeamSwap,
    ItemBoxItem_Random,
    ItemBoxItem_Super,
    ItemBoxItem_LifeMighty,
    ItemBoxItem_LifeRay
};
// #endregion

// #region Constants
// Player Status
#define InputStatus_None                    (SonicMania::PlayerStatus)(0x00000000)
#define InputStatus_PlayerInput             (SonicMania::PlayerStatus)(baseAddress + 0x000C3E00)
#define InputStatus_AI                      (SonicMania::PlayerStatus)(baseAddress + 0x000C4340)

// Player Status
#define PlayerStatus_None                   (SonicMania::PlayerStatus)(0x00000000)
#define PlayerStatus_Standing               (SonicMania::PlayerStatus)(baseAddress + 0x000CAD80)
#define PlayerStatus_Jumping                (SonicMania::PlayerStatus)(baseAddress + 0x000CB6C0)
#define PlayerStatus_LookingDown            (SonicMania::PlayerStatus)(baseAddress + 0x000CBBD0)
#define PlayerStatus_LookingUp              (SonicMania::PlayerStatus)(baseAddress + 0x000CBAA0)
#define PlayerStatus_SpinDash               (SonicMania::PlayerStatus)(baseAddress + 0x000CBD80)
#define PlayerStatus_Roll                   (SonicMania::PlayerStatus)(baseAddress + 0x000CB850)
#define PlayerStatus_Hurt                   (SonicMania::PlayerStatus)(baseAddress + 0x004CCA00) // TODO: needs updating
#define PlayerStatus_Dead                   (SonicMania::PlayerStatus)(baseAddress + 0x000CCAC0)
#define PlayerStatus_Gimmick                (SonicMania::PlayerStatus)(baseAddress + 0x000CAD70)
#define PlayerStatus_Gimmick2               (SonicMania::PlayerStatus)(baseAddress + 0x004CBA90) // TODO: needs updating
#define PlayerStatus_Hanging                (SonicMania::PlayerStatus)(baseAddress + 0x004CAD70) // TODO: needs updating
#define PlayerStatus_SpiningTube_PGZ        (SonicMania::PlayerStatus)(baseAddress + 0x0041F7F0) // TODO: needs updating
#define PlayerStatus_Frozen_PGZ             (SonicMania::PlayerStatus)(baseAddress + 0x004A3410) // TODO: needs updating
#define PlayerStatus_Sliding_OOZ            (SonicMania::PlayerStatus)(baseAddress + 0x0042EB10) // TODO: needs updating
#define PlayerStatus_SwitchingToBG_MMZ      (SonicMania::PlayerStatus)(baseAddress + 0x004304A0) // TODO: needs updating
#define PlayerStatus_SwitchingToFG_MMZ      (SonicMania::PlayerStatus)(baseAddress + 0x004305B0) // TODO: needs updating
#define PlayerStatus_TurningSmall_MMZ       (SonicMania::PlayerStatus)(baseAddress + 0x00431560) // TODO: needs updating
#define PlayerStatus_TurningBig_MMZ         (SonicMania::PlayerStatus)(baseAddress + 0x00431690) // TODO: needs updating
#define PlayerStatus_FlyingIn               (SonicMania::PlayerStatus)(baseAddress + 0x004CD150) // TODO: needs updating
#define PlayerStatus_JumpingIn              (SonicMania::PlayerStatus)(baseAddress + 0x004CD560) // TODO: needs updating
#define PlayerStatus_SpringBasic            (SonicMania::PlayerStatus)(baseAddress + 0x000CB6C0)
#define PlayerStatus_ScoreCard              (SonicMania::PlayerStatus)(baseAddress + 0x000CCD30)
#define PlayerStatus_TransportTube_CPZ      (SonicMania::PlayerStatus)(baseAddress + 0x000CBA90)
#define PlayerStatus_Null                    (SonicMania::PlayerStatus)(baseAddress + 0x000CAD70)

// Sonic
#define PlayerStatus_Sonic_DropDash         (SonicMania::PlayerStatus)(baseAddress + 0x004CC1F0) // TODO: needs updating
#define PlayerStatus_Sonic_Peelout          (SonicMania::PlayerStatus)(baseAddress + 0x004CBF70) // TODO: needs updating

// Tails
#define PlayerStatus_Tails_Flying           (SonicMania::PlayerStatus)(baseAddress + 0x000CCF30)
#define PlayerStatus_Tails_Hanging          (SonicMania::PlayerStatus)(baseAddress + 0x004CDA60) // TODO: needs updating

// Knuckles
#define PlayerStatus_Knuckles_GlidingLeft   (SonicMania::PlayerStatus)(baseAddress + 0x000CDB10)
#define PlayerStatus_Knuckles_GlidingRight  (SonicMania::PlayerStatus)(baseAddress + 0x000CDE10)
#define PlayerStatus_Knuckles_Sliding       (SonicMania::PlayerStatus)(baseAddress + 0x004CE230) // TODO: needs updating
#define PlayerStatus_Knuckles_Climbing      (SonicMania::PlayerStatus)(baseAddress + 0x000CE380)
#define PlayerStatus_Knuckles_GettingUp     (SonicMania::PlayerStatus)(baseAddress + 0x004CE6F0) // TODO: needs updating
#define PlayerStatus_Knuckles_Falling       (SonicMania::PlayerStatus)(baseAddress + 0x000CE110)

// Mighty
#define PlayerStatus_Mighty_HammerDrop      (SonicMania::PlayerStatus)(baseAddress + 0x000CC580)

// Ray
#define PlayerStatus_Ray_Flying             (SonicMania::PlayerStatus)(baseAddress + 0x000CD660)

// Move Sets
#define MOVESET_NONE    (SonicMania::Ability)(0x00000000)
#define MOVESET_SONIC   (SonicMania::Ability)(baseAddress + 0x000C8630)
#define MOVESET_TAILS   (SonicMania::Ability)(baseAddress + 0x000C8990)
#define MOVESET_KNUX    (SonicMania::Ability)(baseAddress + 0x000C8A70)
#define MOVESET_MIGHTY  (SonicMania::Ability)(baseAddress + 0x000C8B70)
#define MOVESET_RAY     (SonicMania::Ability)(baseAddress + 0x000C8DF0)
#define MOVESET_ERSS    (SonicMania::Ability)(baseAddress + 0x000C2340) // Egg Reverie Super Sonic

#define PLAYERID1 0
#define PLAYERID2 1
#define PLAYERID3 2
#define PLAYERID4 3
// #endregion

// #region Structs
struct Vector2 {
    private:
        Uint16 SubX;
    public:
        Sint16 X = 0;
    private:
        Uint16 SubY;
    public:
        Sint16 Y = 0;

    Vector2() {

    }
    Vector2(int x) : Vector2() {
        X = x;
        Y = x;
    }
    Vector2(int x, int y) : Vector2() {
        X = x;
        Y = y;
    }

    Vector2* Add(Vector2 &vec) {
        X += vec.X;
        Y += vec.Y;
        return this;
    }
    Vector2* Sub(Vector2 &vec) {
        X -= vec.X;
        Y -= vec.Y;
        return this;
    }
    Vector2* Mul(Vector2 &vec) {
        X *= vec.X;
        Y *= vec.Y;
        return this;
    }
    Vector2* Div(Vector2 &vec) {
        X /= vec.X;
        Y /= vec.Y;
        return this;
    }
    Vector2* Abs() {
        if (X < 0)
            X = -X;
        if (Y < 0)
            Y = -Y;
    }

    Vector2 operator+(const Vector2& vec2) {
        Vector2 vec;
        vec.Add(*this);
        vec.Add(*(Vector2*)&vec2);
        return vec;
    }
    Vector2 operator+=(const Vector2& vec2) {
        Add(*(Vector2*)&vec2);
        return *this;
    }
    Vector2 operator-(const Vector2& vec2) {
        Vector2 vec;
        vec.Add(*this);
        vec.Sub(*(Vector2*)&vec2);
        return vec;
    }
    Vector2 operator-=(const Vector2& vec2) {
        Sub(*(Vector2*)&vec2);
        return *this;
    }
    Vector2 operator*(const Vector2& vec2) {
        Vector2 vec;
        vec.Add(*this);
        vec.Mul(*(Vector2*)&vec2);
        return vec;
    }
    Vector2 operator*=(const Vector2& vec2) {
        Mul(*(Vector2*)&vec2);
        return *this;
    }
    Vector2 operator/(const Vector2& vec2) {
        Vector2 vec;
        vec.Add(*this);
        vec.Div(*(Vector2*)&vec2);
        return vec;
    }
    Vector2 operator/=(const Vector2& vec2) {
        Div(*(Vector2*)&vec2);
        return *this;
    }

    /** Calculates the Angle to the target vector
        Vector2 target: Location to the target.
        double Return: Angle between the main and target in Radians.
    **/
    double CalculateAngle(Vector2 target) {
        double theta = atan2(target.X - X, Y - target.Y);
        if (theta < 0.0)
            theta += 6.2831853071795865;
        return theta;
    }

    /** Calculates the Distance between to the target vector and the main vector
        Vector2 target: Location to the target.
        double Return: The Distance between the main and target.
    **/
    double inline CalculateDistance(Vector2 target) {
        return sqrt((X - target.X) * (X - target.X) + (Y - target.Y) * (Y - target.Y));
    }

    bool inline IsNull() {
        return X == 0 && Y == 0;
    }
};
struct Color {
    BYTE Red;
    BYTE Green;
    BYTE Blue;

    inline int  ToRGB565() {
        return ((Red & 0b11111000) << 8) | ((Green & 0b11111100) << 3) | (Blue >> 3);
    }
    inline void ToRGB888(SHORT RGB454) {
        Red   = (RGB454 & 0b1111100000000000) >> 8;
        Green = (RGB454 & 0b0000011111100000) >> 3;
        Blue  = (RGB454 & 0b0000000000011111) << 3;
    }
};

struct ControllerInput {
    /* 0x00000000 */ ALIGN(4) bool Down;
    /* 0x00000004 */ ALIGN(4) bool Press;
    /* 0x00000008 */ ALIGN(4) bool Unknown;
};
struct Controller {
    /* 0x00000000 */ ControllerInput Up;
    /* 0x0000000C */ ControllerInput Down;
    /* 0x00000018 */ ControllerInput Left;
    /* 0x00000024 */ ControllerInput Right;
    /* 0x00000030 */ ControllerInput A;
    /* 0x0000003C */ ControllerInput B;
    /* 0x00000048 */ ControllerInput C;
    /* 0x00000054 */ ControllerInput X;
    /* 0x00000060 */ ControllerInput Y;
    /* 0x0000006C */ ControllerInput Z;
    /* 0x00000078 */ ControllerInput Start;
    /* 0x00000084 */ ControllerInput Select;
};
// __declspec(align(4))
struct EntityAnimationData {
    /* 0x00000000 */ void* Animationptr;
    /* 0x00000004 */ Uint32 FrameID;
    /* 0x00000008 */ Uint16 AnimationID;
    /* 0x0000000A */ Uint16 PrevAnimationID;
    /* 0x0000000C */ Uint16 FrameDuration;
    /* 0x0000000E */ Uint16 PrevFrameID;
    /* 0x00000010 */ Uint16 Unk_0x10;
    /* 0x00000012 */ Uint16 FrameCount;
    /* 0x00000014 */ Uint8  Unk_0x14;
    /* 0x00000015 */ Uint8  Unk_0x15;
    /* 0x00000016 */ Uint8  Unk_0x16;
    /* 0x00000017 */ Uint8  Unk_0x17;
};

// Not a proper struct, I just want the timer
struct struct_Timer {
    /* 0x00000000 */ bool Enabled;
    /* 0x00000001 */ BYTE Other[7];
    /* 0x00000008 */ BYTE TimerCentisecond;
    /* 0x00000009 */ BYTE TimerSecond;
    /* 0x0000000A */ BYTE TimerMinute;

    void ResetTimer() {
        TimerMinute = TimerSecond = TimerCentisecond = 0;
    }
    void AddTime(BYTE centiseconds = 0, BYTE seconds = 0, BYTE minutes = 0) {
        TimerMinute += minutes;
        TimerSecond += seconds;
        TimerCentisecond += centiseconds;
        while (TimerCentisecond > 100) {
            TimerCentisecond -= 100;
            ++TimerSecond;
        }
        while (TimerSecond > 60) {
            TimerSecond -= 60;
            ++TimerMinute;
        }
    }
};

struct RegistryObject_Item {
    Uint32 HashA;
    Uint32 HashB;
    Uint32 HashC;
    Uint32 HashD;
    Uint32 Unk_0x10;
    Uint32 Unk_0x14;
    Uint32 Unk_0x18;
    Uint32 Unk_0x1C;
    Uint32 Unk_0x20;
    Uint32 LoadFunc;
    Uint32 Unk_0x28;
    Uint32 Unk_0x2C;
    Uint32 PropertyFunc;
    short** ObjectTypeInfo;
    Uint32 ObjectMemSize;
    Uint32 ObjectTypeInfoSize;
};
// #define RegistryObjectCount *(Uint16*)(baseAddress + 0x83D56C - 0x400000)


// Entities
struct Entity;
struct EntityPlayer;
struct EntityItemBox;
struct EntityRing;
struct EntityUIText;

typedef Entity* EntityPtr;
typedef EntityPlayer* EntityPlayerPtr;
// #endregion

// #region Functions
// Audio
FastcallFunctionPointer(void, SetupMusic, (int slot, const char* filePath, int loopStart), 0x00002AD0);
FunctionPointer(int, PlayMusic, (const char* filePath, int slot, int a3, int loopstart, bool loop), 0x001BC640);
FunctionPointer(int, PlaySoundFX_, (short SoundFXID, signed int a2, unsigned __int8 a3), 0x001BC390);
FunctionPointer(short, GetSoundFXID, (const char *path), 0x001BC2F0);
FunctionPointer(void, ChangeMusicSpeed_OLD, (int slot, float volume, float Channelbalance, float PlaybackSpeed), 0x001BC830);
OffsetFunctionPointer(void, ChangeMusicSpeed, (int slot, float volume, float Channelbalance, float PlaybackSpeed), 0x00A78ED8);

// Entity
FunctionPointer(bool, SetSpriteAnimation, (short spriteIndex, short animationID, EntityAnimationData* animationData, bool forceApply, short frameID), 0x001B35E0);
FastcallFunctionPointer(void, FastChangeCharacter, (EntityPlayer* player, Character character), 0x000C7920);
FastcallFunctionPointer(void, ApplyShieldEffect, (EntityPtr entity), 0x000C5910);
FunctionPointer(int, FindNextObjectOfType, (short objectID, Entity** ent), 0x001C8430);
FunctionPointer(EntityPtr, SpawnObject_Internal, (short, short, Uint32, Uint32), 0x001D3E00);
FunctionPointer(void, DespawnEntity_Internal, (Entity*, Uint32, Uint32), 0x001D3CF0);

// Graphics
FunctionPointer(void, DrawRect, (short XPos, short YPos, short SizeY, short SizeX, BYTE R, BYTE G, BYTE B, BYTE Alpha), 0x001DAC10);
// #endregion

// #region DataPointers
// Players
DataTruePointer(EntityPlayer, Player1, 0x00469A10);
DataTruePointer(EntityPlayer, Player2, 0x00469E68);
DataTruePointer(EntityPlayer, Player3, 0x0046A2C0);
DataTruePointer(EntityPlayer, Player4, 0x0046A718);
DataTruePointer(EntityPlayerPtr, ActivePlayer, 0x00AA7634);

// Other
char* SceneDirectory = (char*)(baseAddress + 0xA5359C);

DataPointer(Scene, CurrentScene, 0x00A535C4);
DataPointer(INT, CurrentSceneInt, 0x00A535C4);
DataPointer(struct_Timer, Timer, 0x00A535DC);
DataPointer(GameStates, GameState, 0x00A535E2);
DataArray(Controller, PlayerControllers, 0x004416D8, 5);

// Palettes
DataArray(SHORT, Palette0, 0x00945B58, 256);
DataArray(SHORT, Palette1, 0x00945D58, 256);
DataArray(SHORT, Palette2, 0x00945F58, 256);
DataArray(SHORT, Palette3, 0x00946158, 256);
DataArray(SHORT, Palette4, 0x00946358, 256);
DataArray(SHORT, Palette5, 0x00946558, 256);
DataArray(SHORT, Palette6, 0x00946758, 256);
DataArray(SHORT, Palette7, 0x00946958, 256);
// #endregion

// #region Entity
struct Entity {
    Vector2 Position;
    Uint32 SpriteSizeX;
    Uint32 SpriteSizeY;
    Sint32 XSpeed;
    Sint32 YSpeed;
    Uint32 Unk_0x18;
    Uint32 Unk_0x1C;
    Uint32 Angle;
    Uint32 Unk_0x24;
    Uint32 Rotation;
    Sint32 GroundSpeed;
    Uint32 Unk_0x30;
    Uint16 Unk_0x34;
    Uint16 ObjectID;
    Uint32 IsOnScreen;
    Uint32 Unk_0x3C;
    Uint32 Unk_0x40;
    Uint32 Unk_0x44;
    Uint32 OnGround;
    Uint8  Unk_0x4C;
    Uint8  Unk_0x4D;
    Uint8  IsFacingLeft;
    Uint8  DrawGroup; // The layer the Sprite Draws on (0-14)
    Uint8  Unk_0x50;
    Uint8  PlaneIndex;
    Uint8  AngleMode;
    Uint8  SizeState;
    TransparencyFlag Transparency;
    Uint8  Unk_0x55;
    Uint8  Unk_0x56;
    Uint8  Unk_0x57;
    PlayerStatus Status;

    void Move(Sint16 x, Sint16 y) {
        this->Position.X = x;
        this->Position.Y = y;
    }
    void AddVelocity(Sint32 x, Sint32 y) {
        this->XSpeed += x;
        this->YSpeed += y;
        this->GroundSpeed += x;
    }
    void SetVelocity(Sint32 x, Sint32 y) {
        this->XSpeed = x;
        this->YSpeed = y;
        this->GroundSpeed = x;
    }
    void MultiplyVelocity(float x, float y)  {
        this->XSpeed      = (Sint32)(XSpeed * x);
        this->YSpeed      = (Sint32)(YSpeed * y);
        this->GroundSpeed = (Sint32)(GroundSpeed * x);
    }
};
struct EntityPlayer : Entity {
    Sint32 Unk_0x5C;
    Uint32 Unk_0x60;
    Uint32 CameraPtr;
    EntityAnimationData Animation;
    Uint32 Unk_0x80;
    Uint32 Unk_0x84;
    Uint32 Unk_0x88;
    Uint32 Unk_0x8C;
    Uint32 Unk_0x90;
    Uint32 Unk_0x94;
    Uint32 Unk_0x98;
    Uint32 Unk_0x9C;
    Uint32 Unk_0xA0;
    Uint32 Unk_0xA4;
    Uint32 Unk_0xA8;
    Uint32 Unk_0xAC;
    Sint16 SpriteIndex;
    Sint16 SpriteIndexTails;
    Sint16 Unk_0xB4;
    Uint16 PlayerID;
    Uint32 Unk_0xB8;
    Uint32 Unk_0xBC;
    Character Character;
    Uint32 RingCount;
    Uint32 RingsToNextLife;
    ShieldType Shield;
    Uint32 LifeCount;
    Uint32 Score;
    Uint32 Unk_0xD8;
    Uint32 CombineRing;
    Uint32 WaitTimer;
    Uint32 OuttaHereTimer;
    Uint32 Unk_0xE8;
    Uint32 Unk_0xEC;
    Uint32 Unk_0xF0;
    Uint32 AirLeft;
    Uint32 Invincibility;
    Uint32 SpeedShoesTimer;
    Uint32 InvincibilityFrames;
    Uint32 field_104;
    Uint32 field_108;
    Uint32 PushingTimer;
    Uint32 UnderwaterFlag;
    Uint32 field_114;
    Uint32 IsUpSideDown;
    Uint32 field_11C;
    Uint32 IsTransforming;
    SuperState SuperState;
    char field_128[12];
    Uint32 DoNotDropRings; // MightyInShell?
    BYTE gap138[4];
    Uint32 dword13C;
    Uint32 Unk0x140;
    Uint32 Unk0x144;
    Uint32 TopSpeed; // 148
    Uint32 Acceleration; // 14C
    Uint32 Friction; // 150
    Uint32 AirAcceleration; // 154
    Uint32 Unk0x158;
    Uint32 Deceleration;
    Uint32 Unk0x160;
    Uint32 Unk0x164;
    Uint32 Gravity;
    Uint32 GlideSpeedStore;
    Uint32 JumpHeight;
    Uint32 JumpReleaseSpeed;
    Uint32 Unk0x178;
    Uint32 dword17C;
    Uint32 dword180;
    Uint32 dword184;
    Uint32 dword188;
    Uint32 dword18C;
    Uint32 dword190;
    BYTE gap194[8];
    Uint32 dword19C;
    InputStatus InputStatus;
    Uint32 ControllerID;
    Uint32 InputLockTimer;
    Uint32 Up;
    Uint32 Down;
    Uint32 Left;
    Uint32 Right;
    Uint32 Jump;
    Uint32 JumpAbilityFlag;
    int JumpAbility;
    int AbilityTimer;
    Ability Moveset;
    Ability UpAbility;
    Uint32 dword1D4;
    Uint32 dword1D8;
    Uint32 dword1DC;
    Uint32 dword1E0;
    Uint32 dword1E4;
    Uint32 KillFlag;
    Uint32 dword1EC;
    Uint32 IsGhost;
    Uint32 dword1F4;
    Uint32 dword1F8;
    Uint32 dword1FC;
    float dword200;
    Uint32 dword204;
    Uint32 dword208;
    Uint32 dword20C;
    Uint32 dword210;
    Uint32 dword214;
    Uint32 dword218;
    Uint32 dword21C;

    void Kill() {
        KillFlag = 1;
    }
    Controller& GetController() {
        if (ControllerID < 0 && ControllerID > 4)
            return PlayerControllers[0];
        return PlayerControllers[ControllerID];
    }
};
struct EntityItemBox : Entity {
    Sint32 Type;
    Uint32 dword60;
    Uint32 dword64;
    Uint32 dword68;
    Uint32 dword6C;
    Uint32 dword70;
    Uint32 dword74;
    Uint32 dword78;
    Uint32 dword7C;
    Uint32 dword80;
    Uint32 dword84;
    Uint32 dword88;
    Uint32 dword8C;
    EntityAnimationData Animation;
    EntityAnimationData AnimationInner;
    BYTE gapC0[128];
};
struct EntityRing : Entity {
    /* 0x0000005C */ Uint32 dword5C;
    /* 0x00000060 */ Uint32 Type;
    /* 0x00000064 */ Uint32 PlaneFilter;
    /* 0x00000068 */ Uint32 dword68;
    /* 0x0000006C */ Uint32 dword6C;
    /* 0x00000070 */ Uint32 dword70;
    /* 0x00000074 */ Uint32 dword74;
    /* 0x00000078 */ Uint32 dword78;
    /* 0x0000007C */ Uint32 MoveType;
    /* 0x00000080 */ Uint32 Amplitude;
    /* 0x00000084 */ Uint32 dword84;
    /* 0x00000088 */ Uint32 Speed;
    /* 0x0000008C */ Uint32 dword8C;
    /* 0x00000090 */ Uint32 dword90;
    /* 0x00000094 */ EntityAnimationData Animation;
};
struct EntitySpikes : Entity {
    Uint32 Type;
    Uint32 Moving;
    Uint8  Count;
    Uint8  Stagger;
    Uint8  Timer;
    Uint8  Unk_0x67;
    Uint32 PlaneFilter;
    Uint32 Unk_0x6C;
    Uint32 Unk_0x70;
    Uint32 Unk_0x74;
    Uint32 Unk_0x78;
    Uint32 MoveType;
    Uint32 Amplitude;
    Uint32 Unk_0x84;
    EntityAnimationData Animation;
};
struct EntityBuckwildBall : Entity {
    /* 0x0000005C */ Uint32 Amplitude;
    /* 0x00000060 */ Uint8  Mode;
    /* 0x00000061 */ Uint8  Unk61;
    /* 0x00000062 */ Uint8  Unk62;
    /* 0x00000063 */ Uint8  Unk63;
    /* 0x00000064 */ Uint32 Speed;
    /* 0x00000068 */ Uint32 DetectOffset1;
    /* 0x0000006C */ Uint32 DetectOffset2;
    /* 0x00000070 */ Uint32 DetectSize1;
    /* 0x00000074 */ Uint32 DetectSize2;
    /* 0x00000078 */ Uint32 Respawn;
    /* 0x0000007C */ Uint32 dword7C;
    /* 0x00000080 */ Uint32 StartX;
    /* 0x00000084 */ Uint32 StartY;
    /* 0x00000088 */ Uint32 DetectBoxX;
    /* 0x0000008C */ Uint32 DetectBoxY;
    /* 0x00000090 */ Uint32 dword90;
    /* 0x00000094 */ Uint32 dword94;
    /* 0x00000098 */ Uint32 dword98;
    /* 0x0000009C */ Uint32 dword9C;
    /* 0x000000A0 */ EntityAnimationData Animation;
};
struct EntityUIText : Entity {
    /* 0x0000005C */ Uint32 dword5C;
    /* 0x00000060 */ char* Text;
    /* 0x00000064 */ Uint32 dword64;
    /* 0x00000068 */ Uint32 dword68;
    /* 0x0000006C */ Uint32 dword6C;
    /* 0x00000070 */ Uint32 dword70;
    /* 0x00000074 */ Uint32 dword74;
    /* 0x00000078 */ Uint32 dword78;
    /* 0x0000007C */ Uint32 dword7C;
    /* 0x00000080 */ Uint32 dword80;
    /* 0x00000084 */ Uint32 dword84;
    /* 0x00000088 */ Uint32 dword88;
    /* 0x0000008C */ Uint32 dword8C;
    /* 0x00000090 */ Uint32 dword90;
};
struct EntityMotoBug : Entity {
    /* 0x0000005C */ Uint32 dword5C;
    /* 0x00000060 */ Uint32 dword60;
    /* 0x00000064 */ Uint32 dword64;
    /* 0x00000068 */ Uint32 dword68;
    /* 0x0000006C */ Uint32 dword6C;
    /* 0x00000070 */ Uint32 dword70;
    /* 0x00000074 */ EntityAnimationData Animation;
    /* 0x00000088 */ Uint32 dword88;
    /* 0x0000008C */ Uint32 dword8C;
    /* 0x00000090 */ Uint32 dword90;

};
struct EntityFXFade : Entity {
    /* 0x0000005C */ int Timer;
    /* 0x00000060 */ int SpeedIn;
    /* 0x00000064 */ int Wait;
    /* 0x00000068 */ int SpeedOut;
    /* 0x0000006C */ Uint32 Color;
    /* 0x00000070 */ bool OneWay;
    /* 0x00000074 */ bool EventOnly;
    /* 0x00000078 */ bool Overhud;
    /* 0x0000007C */ bool FadeOutBlack;
    /* 0x00000080 */ Uint32 dword80;
    /* 0x00000084 */ Uint32 dword84;
    /* 0x00000088 */ Uint32 Speed;
    /* 0x0000008C */ Uint32 dword8C;
    /* 0x00000090 */ Uint32 dword90;
    /* 0x00000094 */ EntityAnimationData Animation;
};
// #endregion

// #region Pointer Functions
static BYTE GetChaosEmeraldBits() {
    int* pointer = (int*)(baseAddress + 0x00AC6A20);
    if (!*pointer)
        return 0;
    pointer = (int*)(*pointer + 0x10);
    if (!*pointer)
        return 0;
    pointer = (int*)(*pointer + 0x70);
    if (!*pointer)
        return 0;
    return *pointer;
}
static BYTE GetChaosEmeraldCount() {
    int CECount = 0;
    BYTE CE = GetChaosEmeraldBits();
    if (CE == 0)
        return 0;
    for (int i = 0; i < 7; ++i)
        if (CE & (1 << i))
            ++CECount;
    return CECount;
}
// #endregion

// #region HelperFunctions
// Written by Sajid
inline int ToRGB565(BYTE R, BYTE G, BYTE B) {
    return ((R & 0b11111000) << 8) | ((G & 0b11111100) << 3) | (B >> 3);
}
inline void ToRGB888(SHORT val, BYTE &R, BYTE &G, BYTE &B) {
    R = (val & 0b1111100000000000) >> 8;
    G = (val & 0b0000011111100000) >> 3;
    B = (val & 0b0000000000011111) << 3;
}
inline void WriteRGB888ToRGB565Array(SHORT* writeAddress, BYTE* colors, int colorCount) {
    for (int i = 0; i < colorCount; ++i)
        writeAddress[i] = ToRGB565(colors[(i * 3) + 0], colors[(i * 3) + 1], colors[(i * 3) + 2]);
}
inline SHORT* GetColour(SHORT* Palette, int x, int y) {
    return Palette + x + 16 * y;
}
inline int* GetAddress(int baseAddress, int offset1) {
    return (int*)((*(int*)baseAddress) + offset1);
}
inline int* GetAddress(int baseAddress, int offset1, int offset2) {
    return (int*)(*(int*)GetAddress(baseAddress, offset1) + offset2);
}
static BYTE GetSpritePointer(int SpritePointer, int offset) {
    int* pointer = (int*)(baseAddress + SpritePointer);
    if (!*pointer)
        return 0;
    pointer = (int*)(*pointer + offset);
    if (!*pointer)
        return 0;
    return *pointer;
}
static INT GetPointer(int SpritePointer, int offset) {
    int* pointer = (int*)(baseAddress + SpritePointer);
    if (!*pointer)
        return 0;
    pointer = (int*)(*pointer + offset);
    if (!*pointer)
        return 0;
    return *pointer;
}
// #endregion

// #region ManiaHelperFunctions
inline Character  GetCharacter(int playerId) {
    return *((Character*)GetAddress((baseAddress + 0x00AA763C), 4 + playerId));
}
inline Character* GetCharacter_ptr(int playerId) {
    return ((Character*)GetAddress((baseAddress + 0x00AA763C), 4 + playerId));
}

template <typename T>
inline T* GetActiveEntity() {
    return (T*)ActivePlayer;
}
template <typename T>
inline T* GetEntityFromSceneSlot(int slot) {
    return (T*)((baseAddress + 0x0047B010) + (slot * 0x458));
}

template <typename T>
static T*      GetAbsAddress(int jmp) {
    int r = *(int*)(jmp + 1);
    int abs = jmp + r + 5;
    return (T*)abs;
}
inline short   GetObjectIDFromType(ObjectType type) {
    if (*((int*)(baseAddress + type)) == 0)
        return 0;
    return *(short*)GetAddress((int)(baseAddress + type), 0);
}
inline Ability GetMoveSetByCharacter(Character character) {
    switch (character) {
        case Character_Sonic:
            return MOVESET_SONIC;
        case Character_Tails:
            return MOVESET_TAILS;
        case Character_Knux:
            return MOVESET_KNUX;
        case Character_Mighty:
            return MOVESET_MIGHTY;
        case Character_Ray:
            return MOVESET_RAY;
        default:
            return MOVESET_SONIC;
    }
}

inline void    RestartScene() {
    // Setting GameState to NotRunning restarts the scene
    GameState = GameState_NotRunning;
}
inline void    ChangeScene(Scene scene) {
    CurrentScene = scene;
    GameState = GameState_NotRunning;
}
inline Entity* SpawnObject(short objectID, short subObject, short x, short y) {
    return SpawnObject_Internal(objectID, subObject, ((int)x) << 16, ((int)y) << 16);
}
inline Entity* SpawnObject(short objectID, short subObject, Vector2 position) {
    return SpawnObject(objectID, subObject, position.X, position.Y);
}
inline void    DespawnEntity(Entity* entity) {
    DespawnEntity_Internal(entity, 0, 0);
}
inline void    PlaySong(const char* filePath, int loopstart, bool loop) {
    int* addr = GetAddress(0x00AC6E08, 0x248);
    if ((int)addr > 0x248)
        *addr = PlayMusic(filePath, 0, 0, loopstart, loop ? 1 : 0);
    else
        PlayMusic(filePath, 0, 0, loopstart, loop ? 1 : 0);
}
inline int     PlaySoundFXS(const char *path) {
    return PlaySoundFX_(GetSoundFXID(path), 0, 0xFF);
}

static int loc_LoadSoundFX = baseAddress + 0x001BBA00;
static _declspec(naked) short LoadSoundFX(const char* path, Scope scope) {
    __asm {
        mov dl, 1
        mov ecx, [ESP + 4]
        push[ESP + 8]
        call loc_LoadSoundFX
        add esp, 4
        ret
    };
}
static short TryLoadSoundFX(const char* path, Scope scope) {
    if (GetSoundFXID(path) == (short)-1)
        return LoadSoundFX(path, scope);
    return -1;
}


static int loc_HitEntity = (baseAddress + 0x001C9380);
inline __declspec(naked) bool HitEntity(Entity* attacker, Entity* target, Uint32 a3) {
    __asm {
        mov edx, [ESP + 4]
        mov ecx, [ESP + 8]
        push[ESP + 12]
        call loc_HitEntity
        add esp, 4
        ret
    };
}
inline void SetCharacterPallette(Character Character, int RGB1, int RGB2, int RGB3, int RGB4, int RGB5, int RGB6) {
    SHORT* ptr;
    switch (Character) {
        case Character_Sonic:
            ptr = GetColour(Palette0, 0, 4);
            break;
        case Character_Tails:
            ptr = GetColour(Palette0, 6, 4);
            break;
        case Character_Knux:
            ptr = GetColour(Palette0, 0, 5);
            break;
        case Character_Mighty:
            ptr = GetColour(Palette0, 0, 6);
            break;
        case Character_Ray:
            ptr = GetColour(Palette0, 0, 7);
            break;
        default:
            ptr = GetColour(Palette0, 0, 4);
            break;
    }

    ptr[0] = ToRGB565(RGB1 >> 16, RGB1 >> 8, RGB1);
    ptr[1] = ToRGB565(RGB2 >> 16, RGB2 >> 8, RGB2);
    ptr[2] = ToRGB565(RGB3 >> 16, RGB3 >> 8, RGB3);
    ptr[3] = ToRGB565(RGB4 >> 16, RGB4 >> 8, RGB4);
    ptr[4] = ToRGB565(RGB4 >> 16, RGB4 >> 8, RGB5);
    ptr[5] = ToRGB565(RGB4 >> 16, RGB4 >> 8, RGB6);
}
// #endregion

// #region ManiaPatches
inline void BindLBAndRB() {
    // LB
    BYTE LBPatch[6]{ (BYTE)0x09, (BYTE)0x42, (BYTE)0x4C, (BYTE)0x90, (BYTE)0x90, (BYTE)0x90 };
    WriteData((BYTE*)(baseAddress + 0x001E6358), LBPatch, 6);
    // RB
    BYTE RBPatch[6]{ (BYTE)0x09, (BYTE)0x42, (BYTE)0x70, (BYTE)0x90, (BYTE)0x90, (BYTE)0x90 };
    WriteData((BYTE*)(baseAddress + 0x001E6362), RBPatch, 6);
}
// #endregion

// #region DevMenu
    DataPointer(int, ScreenOffsetX, 0x479F34);
    DataPointer(int, ScreenOffsetY, 0x479F38);
    DataPointer(bool, DevMenu_Enabled, 0x002FC867);
    DataPointer(VoidPtr, DevMenu_Address, 0x002FBB40);
    DataPointer(int, DevMenu_Option, 0x002FBB44);
    DataPointer(int, DevMenu_Scroll, 0x002FBB48);
    FunctionPointer(int, DevMenu_DrawRect, (int x, int y, signed int width, int height, int color, signed int a6, int a7, int a8), 0x001D8870);
    DataPointer(Uint32, dword_D3CC00, 0x947C6C);

    FunctionPointer(char, Devmenu_MainMenu, (), 0x001C2500);
    FunctionPointer(char, Devmenu_StageSelect, (), 0x001C2B60);
    FunctionPointer(char, Devmenu_SceneSelect, (), 0x001C2DB0);
    FunctionPointer(char, Devmenu_Options, (), 0x001C3090);

    enum DevMenu_Alignment : int {
        Alignment_Left,
        Alignment_Centre,
        Alignment_Right
    };

    static int loc_DrawText = baseAddress + 0x1D58C0;
    static __declspec(naked) WORD DevMenu_DrawText(int XPosition, const char* text, int YPosition, DevMenu_Alignment alignment, int color) {
        __asm {
            mov edx, [ESP + 4]
            mov ecx, [ESP + 8]
            push[ESP + 20]
            push[ESP + 20]
            push[ESP + 20]
            call loc_DrawText
            add esp, 12
            ret
        };
    }

// #endregion
}
