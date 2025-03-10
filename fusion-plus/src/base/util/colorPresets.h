#pragma once
#include <imgui/imgui.h>

class ColorPresets {
public:
    static ImVec4 GetPreset(int preset, float t, float smoothT, float time);
    static ImVec4 LerpColors(const ImVec4& a, const ImVec4& b, float t);

private:
    static ImVec4 RGBWave(float smoothT);
    static ImVec4 PurpleRain(float t);
    static ImVec4 GoldenLuxury(float smoothT);
    static ImVec4 RedFlow(float t);
    static ImVec4 NeonPulse(float smoothT);
    static ImVec4 OceanDepths(float t);
    static ImVec4 ForestMystical(float smoothT);
    static ImVec4 SunsetDreams(float smoothT);
    static ImVec4 CottonCandy(float smoothT);
    static ImVec4 MagmaFlow(float smoothT);
    static ImVec4 AquaBreeze(float smoothT);
    static ImVec4 CosmicWave(float t);
    static ImVec4 CherryBlossom(float t, float smoothT);
    static ImVec4 Cyberpunk(float time);
};
