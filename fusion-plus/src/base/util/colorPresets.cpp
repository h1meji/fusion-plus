#include "colorPresets.h"
#include <cmath>
#include "timeManager.h"

ImVec4 ColorPresets::GetPreset(int preset, float t, float smoothT, float time) {
    switch (preset) {
        case 1: return RGBWave(smoothT);
        case 2: return PurpleRain(t);
        case 3: return GoldenLuxury(smoothT);
        case 4: return RedFlow(t);
        case 5: return NeonPulse(smoothT);
        case 6: return OceanDepths(t);
        case 7: return ForestMystical(smoothT);
        case 8: return SunsetDreams(smoothT);
        case 9: return CottonCandy(smoothT);
        case 10: return MagmaFlow(smoothT);
        case 11: return AquaBreeze(smoothT);
        case 12: return CosmicWave(t);
        case 13: return CherryBlossom(t, smoothT);
        case 14: return Cyberpunk(time);
        default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

ImVec4 ColorPresets::RGBWave(float smoothT) {
    float r, g, b;
    ImGui::ColorConvertHSVtoRGB(smoothT, 1.0f, 1.0f, r, g, b);
    return ImVec4(r, g, b, 1.0f);
}

ImVec4 ColorPresets::PurpleRain(float t) {
    float r, g, b;
    float hue = 0.75f + sinf(t) * 0.08f;
    float sat = 0.8f + sinf(t * 1.5f) * 0.2f;
    float val = 0.9f + sinf(t * 2.0f) * 0.1f;
    ImGui::ColorConvertHSVtoRGB(hue, sat, val, r, g, b);
    return ImVec4(r, g, b, 1.0f);
}

ImVec4 ColorPresets::GoldenLuxury(float smoothT) {
    ImVec4 gold1(1.0f, 0.84f, 0.0f, 1.0f);    // Bright gold
    ImVec4 gold2(0.83f, 0.68f, 0.21f, 1.0f);  // Antique gold
    ImVec4 gold3(0.91f, 0.75f, 0.1f, 1.0f);   // Shining gold
    
    float t1 = fmodf(smoothT * 3.0f, 1.0f);
    if(t1 < 0.33f)
        return LerpColors(gold1, gold2, t1 * 3.0f);
    else if(t1 < 0.66f)
        return LerpColors(gold2, gold3, (t1 - 0.33f) * 3.0f);
    return LerpColors(gold3, gold1, (t1 - 0.66f) * 3.0f);
}

ImVec4 ColorPresets::RedFlow(float t) {
    ImVec4 red1(1.0f, 0.0f, 0.0f, 1.0f);      // Pure red
    ImVec4 red2(0.8f, 0.0f, 0.0f, 1.0f);      // Dark red
    ImVec4 red3(1.0f, 0.2f, 0.2f, 1.0f);      // Light red
    return LerpColors(
        LerpColors(red1, red2, sinf(t)),
        red3,
        (sinf(t * 1.5f) + 1.0f) * 0.5f
    );
}

ImVec4 ColorPresets::NeonPulse(float smoothT) {
    ImVec4 neon1(1.0f, 0.0f, 0.89f, 1.0f);    // Neon pink
    ImVec4 neon2(0.0f, 1.0f, 0.89f, 1.0f);    // Neon cyan
    ImVec4 neon3(0.89f, 1.0f, 0.0f, 1.0f);    // Neon yellow
    
    float t1 = fmodf(smoothT * 3.0f, 1.0f);
    if(t1 < 0.33f)
        return LerpColors(neon1, neon2, t1 * 3.0f);
    else if(t1 < 0.66f)
        return LerpColors(neon2, neon3, (t1 - 0.33f) * 3.0f);
    return LerpColors(neon3, neon1, (t1 - 0.66f) * 3.0f);
}

ImVec4 ColorPresets::OceanDepths(float t) {
    ImVec4 water1(0.0f, 0.47f, 0.95f, 1.0f);   // Light blue
    ImVec4 water2(0.0f, 0.32f, 0.65f, 1.0f);   // Medium blue
    ImVec4 water3(0.0f, 0.18f, 0.38f, 1.0f);   // Deep blue
    
    float t1 = (sinf(t * 0.5f) + 1.0f) * 0.5f;
    return LerpColors(
        LerpColors(water1, water2, t1),
        water3,
        (sinf(t * 0.7f) + 1.0f) * 0.5f
    );
}

ImVec4 ColorPresets::ForestMystical(float smoothT) {
    ImVec4 forest1(0.0f, 0.5f, 0.0f, 1.0f);    // Forest green
    ImVec4 forest2(0.13f, 0.55f, 0.13f, 1.0f); // Grass green
    ImVec4 forest3(0.0f, 0.39f, 0.0f, 1.0f);   // Dark green
    ImVec4 forest4(0.56f, 0.93f, 0.56f, 1.0f); // Light green
    
    float t1 = fmodf(smoothT * 4.0f, 1.0f);
    if(t1 < 0.25f)
        return LerpColors(forest1, forest2, t1 * 4.0f);
    else if(t1 < 0.5f)
        return LerpColors(forest2, forest3, (t1 - 0.25f) * 4.0f);
    else if(t1 < 0.75f)
        return LerpColors(forest3, forest4, (t1 - 0.5f) * 4.0f);
    return LerpColors(forest4, forest1, (t1 - 0.75f) * 4.0f);
}

ImVec4 ColorPresets::SunsetDreams(float smoothT) {
    ImVec4 sunset1(1.0f, 0.6f, 0.0f, 1.0f);    // Orange
    ImVec4 sunset2(1.0f, 0.4f, 0.4f, 1.0f);    // Soft pink
    ImVec4 sunset3(0.6f, 0.0f, 0.4f, 1.0f);    // Purple
    
    float t1 = fmodf(smoothT * 3.0f, 1.0f);
    if(t1 < 0.33f)
        return LerpColors(sunset1, sunset2, t1 * 3.0f);
    else if(t1 < 0.66f)
        return LerpColors(sunset2, sunset3, (t1 - 0.33f) * 3.0f);
    return LerpColors(sunset3, sunset1, (t1 - 0.66f) * 3.0f);
}

ImVec4 ColorPresets::CottonCandy(float smoothT) {
    ImVec4 candy1(1.0f, 0.7f, 0.75f, 1.0f);    // Pastel pink
    ImVec4 candy2(0.7f, 0.85f, 1.0f, 1.0f);    // Pastel blue
    ImVec4 candy3(0.85f, 0.7f, 1.0f, 1.0f);    // Pastel lilac
    
    float t1 = fmodf(smoothT * 3.0f, 1.0f);
    if(t1 < 0.33f)
        return LerpColors(candy1, candy2, t1 * 3.0f);
    else if(t1 < 0.66f)
        return LerpColors(candy2, candy3, (t1 - 0.33f) * 3.0f);
    return LerpColors(candy3, candy1, (t1 - 0.66f) * 3.0f);
}

ImVec4 ColorPresets::MagmaFlow(float smoothT) {
    ImVec4 magma1(1.0f, 0.0f, 0.0f, 1.0f);     // Lava red
    ImVec4 magma2(1.0f, 0.4f, 0.0f, 1.0f);     // Fire orange
    ImVec4 magma3(1.0f, 0.6f, 0.0f, 1.0f);     // Fire yellow
    ImVec4 magma4(0.6f, 0.0f, 0.0f, 1.0f);     // Dark red
    
    float t1 = fmodf(smoothT * 4.0f, 1.0f);
    if(t1 < 0.25f)
        return LerpColors(magma1, magma2, t1 * 4.0f);
    else if(t1 < 0.5f)
        return LerpColors(magma2, magma3, (t1 - 0.25f) * 4.0f);
    else if(t1 < 0.75f)
        return LerpColors(magma3, magma4, (t1 - 0.5f) * 4.0f);
    return LerpColors(magma4, magma1, (t1 - 0.75f) * 4.0f);
}

ImVec4 ColorPresets::AquaBreeze(float smoothT) {
    ImVec4 aqua1(0.0f, 0.75f, 0.8f, 1.0f);     // Light aqua
    ImVec4 aqua2(0.0f, 0.6f, 0.7f, 1.0f);      // Medium aqua
    ImVec4 aqua3(0.2f, 0.8f, 0.8f, 1.0f);      // Turquoise
    ImVec4 aqua4(0.0f, 0.5f, 0.6f, 1.0f);      // Deep aqua
    
    float t1 = fmodf(smoothT * 4.0f, 1.0f);
    if(t1 < 0.25f)
        return LerpColors(aqua1, aqua2, t1 * 4.0f);
    else if(t1 < 0.5f)
        return LerpColors(aqua2, aqua3, (t1 - 0.25f) * 4.0f);
    else if(t1 < 0.75f)
        return LerpColors(aqua3, aqua4, (t1 - 0.5f) * 4.0f);
    return LerpColors(aqua4, aqua1, (t1 - 0.75f) * 4.0f);
}

ImVec4 ColorPresets::CosmicWave(float t) {
    ImVec4 space1(0.5f, 0.0f, 1.0f, 1.0f);     // Space purple
    ImVec4 space2(0.2f, 0.0f, 0.4f, 1.0f);     // Dark purple
    ImVec4 space3(0.8f, 0.0f, 0.8f, 1.0f);     // Bright magenta
    
    float t1 = (sinf(t * 0.7f) + 1.0f) * 0.5f;
    float t2 = (sinf(t * 0.5f + 1.0f) + 1.0f) * 0.5f;
    
    ImVec4 color1 = LerpColors(space1, space2, t1);
    ImVec4 color2 = LerpColors(space2, space3, t2);
    return LerpColors(color1, color2, (sinf(t) + 1.0f) * 0.5f);
}

ImVec4 ColorPresets::CherryBlossom(float t, float smoothT) {
    ImVec4 cherry1(1.0f, 0.7f, 0.8f, 1.0f);    // Soft pink
    ImVec4 cherry2(1.0f, 0.9f, 0.9f, 1.0f);    // Pinkish white
    ImVec4 cherry3(0.9f, 0.6f, 0.7f, 1.0f);    // Medium pink
    
    float t1 = (sinf(t * 0.8f) + 1.0f) * 0.5f;
    float t2 = (sinf(t * 1.2f) + 1.0f) * 0.5f;
    
    ImVec4 blend1 = LerpColors(cherry1, cherry2, t1);
    ImVec4 blend2 = LerpColors(cherry2, cherry3, t2);
    return LerpColors(blend1, blend2, smoothT);
}

ImVec4 ColorPresets::Cyberpunk(float time) {
    ImVec4 cyber1(1.0f, 0.0f, 0.7f, 1.0f);     // Neon pink
    ImVec4 cyber2(0.0f, 1.0f, 0.7f, 1.0f);     // Neon green
    ImVec4 cyber3(0.0f, 0.7f, 1.0f, 1.0f);     // Neon blue
    ImVec4 cyber4(1.0f, 0.7f, 0.0f, 1.0f);     // Neon yellow
    
    float t1 = fmodf(time * 2.0f, 4.0f);
    if(t1 < 1.0f)
        return LerpColors(cyber1, cyber2, t1);
    else if(t1 < 2.0f)
        return LerpColors(cyber2, cyber3, t1 - 1.0f);
    else if(t1 < 3.0f)
        return LerpColors(cyber3, cyber4, t1 - 2.0f);
    return LerpColors(cyber4, cyber1, t1 - 3.0f);
}

ImVec4 ColorPresets::LerpColors(const ImVec4& a, const ImVec4& b, float t) {
    return ImVec4(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t,
        a.w + (b.w - a.w) * t
    );
}
