#pragma once
namespace CompPlus_ZoneSpecifics
{
    extern bool IsInternalStage(const char* CurrentScene);

    extern bool IsManiaStage(const char* CurrentScene);

    extern bool IsEncoreStage(const char* CurrentScene);

    extern bool IsCustomStage(const char* CurrentScene);

    extern bool IsExecutorStage(const char* CurrentScene);

    extern bool IsChaotixStage(const char* CurrentScene);

    extern bool IsChaotixEncoreStage(const char* CurrentScene);

    extern void UpdateSpecifics(const char* CurrentScene, int LevelID);
}