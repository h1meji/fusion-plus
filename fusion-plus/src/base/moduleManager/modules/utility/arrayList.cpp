#include "arrayList.h"

#include <imgui/imgui.h>
#include "menu/menu.h"
#include "moduleManager/commonData.h"

// Modules
#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/visual/radar.h"
#include "moduleManager/modules/visual/blockEsp.h"
#include "moduleManager/modules/combat/aimAssist.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/combat/leftAutoClicker.h"
#include "moduleManager/modules/combat/rightAutoClicker.h"
#include "moduleManager/modules/movement/bridgeAssist.h"
#include "moduleManager/modules/movement/velocity.h"
#include "moduleManager/modules/movement/sprintReset.h"
#include "moduleManager/modules/inventory/chestStealer.h"
#include "moduleManager/modules/inventory/inventorySorter.h"
#include "moduleManager/modules/utility/clientBrandChanger.h"
#include "moduleManager/modules/tnt-tag/tagBack.h"
#include "moduleManager/modules/tnt-tag/ITEsp.h"

#define M_PI 3.14159265358979323846

// Forward declarations and helper functions
ImVec2 GetPointOnRoundedRect(const ImVec2& min, const ImVec2& max, float radius, float t);
inline float ImMin(float a, float b) { return a < b ? a : b; }

// TimeManager class to control time
class TimeManager {
private:
    static float lastTime;
    static float pausedTime;
    static bool isPaused;

public:
    static float GetTime() {
        if (IsIconic(Menu::HandleWindow)) {
            if (!isPaused) {
                isPaused = true;
                pausedTime = lastTime;
            }
            return pausedTime;
        }
        
        isPaused = false;
        lastTime = ImGui::GetTime();
        return lastTime;
    }
};

float TimeManager::lastTime = 0.0f;
float TimeManager::pausedTime = 0.0f;
bool TimeManager::isPaused = false;

// Forward declarations
ImVec4 LerpColors(const ImVec4& a, const ImVec4& b, float t);

// Helper functions for color interpolation
ImU32 ImLerp(ImU32 c1, ImU32 c2, float t)
{
    ImVec4 col1 = ImGui::ColorConvertU32ToFloat4(c1);
    ImVec4 col2 = ImGui::ColorConvertU32ToFloat4(c2);
    return ImGui::ColorConvertFloat4ToU32(LerpColors(col1, col2, t));
}

// Main color interpolation function
ImVec4 LerpColors(const ImVec4& a, const ImVec4& b, float t) {
    return ImVec4(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t,
        a.w + (b.w - a.w) * t
    );
}

// Get color for module based on selected mode and index
ImVec4 GetColorForModule(int index, float rawTime) {
    if (!settings::AL_rgbEnabled)
        return ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);
        
    float time = TimeManager::GetTime();
    float hue = 0.0f;
    float r, g, b;
    float t = fmodf(time * settings::AL_rgbSpeed + (index * 0.1f), 2.0f * M_PI);
    float smoothT = (sinf(t) + 1.0f) * 0.5f;
    
    switch (settings::AL_colorMode) {
        case 1: // RGB Wave (original version)
            hue = smoothT;
            ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, r, g, b);
            return ImVec4(r, g, b, 1.0f);
            
        case 2: // Purple Rain Enhanced
        {
            float hue = 0.75f + sinf(t) * 0.08f;
            float sat = 0.8f + sinf(t * 1.5f) * 0.2f;
            float val = 0.9f + sinf(t * 2.0f) * 0.1f;
            ImGui::ColorConvertHSVtoRGB(hue, sat, val, r, g, b);
            return ImVec4(r, g, b, 1.0f);
        }
            
        case 3: // Golden Luxury
        {
            ImVec4 gold1 = ImVec4(1.0f, 0.84f, 0.0f, 1.0f);    // Bright gold
            ImVec4 gold2 = ImVec4(0.83f, 0.68f, 0.21f, 1.0f);  // Antique gold
            ImVec4 gold3 = ImVec4(0.91f, 0.75f, 0.1f, 1.0f);   // Shining gold
            
            float t1 = fmodf(smoothT * 3.0f, 1.0f);
            if(t1 < 0.33f)
                return LerpColors(gold1, gold2, t1 * 3.0f);
            else if(t1 < 0.66f)
                return LerpColors(gold2, gold3, (t1 - 0.33f) * 3.0f);
            else
                return LerpColors(gold3, gold1, (t1 - 0.66f) * 3.0f);
        }
            
        case 4: // Red Flow Enhanced
        {
            ImVec4 red1 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);      // Pure red
            ImVec4 red2 = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);      // Dark red
            ImVec4 red3 = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);      // Light red
            return LerpColors(
                LerpColors(red1, red2, sinf(t)),
                red3,
                (sinf(t * 1.5f) + 1.0f) * 0.5f
            );
        }
            
        case 5: // Neon Pulse
        {
            ImVec4 neon1 = ImVec4(1.0f, 0.0f, 0.89f, 1.0f);    // Neon pink
            ImVec4 neon2 = ImVec4(0.0f, 1.0f, 0.89f, 1.0f);    // Neon cyan
            ImVec4 neon3 = ImVec4(0.89f, 1.0f, 0.0f, 1.0f);    // Neon yellow
            
            float t1 = fmodf(smoothT * 3.0f, 1.0f);
            if(t1 < 0.33f)
                return LerpColors(neon1, neon2, t1 * 3.0f);
            else if(t1 < 0.66f)
                return LerpColors(neon2, neon3, (t1 - 0.33f) * 3.0f);
            else
                return LerpColors(neon3, neon1, (t1 - 0.66f) * 3.0f);
        }
            
        case 6: // Ocean Depths
        {
            ImVec4 water1 = ImVec4(0.0f, 0.47f, 0.95f, 1.0f);   // Light blue
            ImVec4 water2 = ImVec4(0.0f, 0.32f, 0.65f, 1.0f);   // Medium blue
            ImVec4 water3 = ImVec4(0.0f, 0.18f, 0.38f, 1.0f);   // Deep blue
            
            float t1 = (sinf(t * 0.5f) + 1.0f) * 0.5f;
            return LerpColors(
                LerpColors(water1, water2, t1),
                water3,
                (sinf(t * 0.7f) + 1.0f) * 0.5f
            );
        }
            
        case 7: // Forest Mystical
        {
            ImVec4 forest1 = ImVec4(0.0f, 0.5f, 0.0f, 1.0f);    // Forest green
            ImVec4 forest2 = ImVec4(0.13f, 0.55f, 0.13f, 1.0f); // Grass green
            ImVec4 forest3 = ImVec4(0.0f, 0.39f, 0.0f, 1.0f);   // Dark green
            ImVec4 forest4 = ImVec4(0.56f, 0.93f, 0.56f, 1.0f); // Light green
            
            float t1 = fmodf(smoothT * 4.0f, 1.0f);
            if(t1 < 0.25f)
                return LerpColors(forest1, forest2, t1 * 4.0f);
            else if(t1 < 0.5f)
                return LerpColors(forest2, forest3, (t1 - 0.25f) * 4.0f);
            else if(t1 < 0.75f)
                return LerpColors(forest3, forest4, (t1 - 0.5f) * 4.0f);
            else
                return LerpColors(forest4, forest1, (t1 - 0.75f) * 4.0f);
        }
            
        case 8: // Sunset Dreams
        {
            ImVec4 sunset1 = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);    // Orange
            ImVec4 sunset2 = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);    // Soft pink
            ImVec4 sunset3 = ImVec4(0.6f, 0.0f, 0.4f, 1.0f);    // Purple
            
            float t1 = fmodf(smoothT * 3.0f, 1.0f);
            if(t1 < 0.33f)
                return LerpColors(sunset1, sunset2, t1 * 3.0f);
            else if(t1 < 0.66f)
                return LerpColors(sunset2, sunset3, (t1 - 0.33f) * 3.0f);
            else
                return LerpColors(sunset3, sunset1, (t1 - 0.66f) * 3.0f);
        }
            
        case 9: // Cotton Candy
        {
            ImVec4 candy1 = ImVec4(1.0f, 0.7f, 0.75f, 1.0f);    // Pastel pink
            ImVec4 candy2 = ImVec4(0.7f, 0.85f, 1.0f, 1.0f);    // Pastel blue
            ImVec4 candy3 = ImVec4(0.85f, 0.7f, 1.0f, 1.0f);    // Pastel lilac
            
            float t1 = fmodf(smoothT * 3.0f, 1.0f);
            if(t1 < 0.33f)
                return LerpColors(candy1, candy2, t1 * 3.0f);
            else if(t1 < 0.66f)
                return LerpColors(candy2, candy3, (t1 - 0.33f) * 3.0f);
            else
                return LerpColors(candy3, candy1, (t1 - 0.66f) * 3.0f);
        }
            
        case 10: // Magma Flow
        {
            ImVec4 magma1 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);     // Lava red
            ImVec4 magma2 = ImVec4(1.0f, 0.4f, 0.0f, 1.0f);     // Fire orange
            ImVec4 magma3 = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);     // Fire yellow
            ImVec4 magma4 = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);     // Dark red
            
            float t1 = fmodf(smoothT * 4.0f, 1.0f);
            if(t1 < 0.25f)
                return LerpColors(magma1, magma2, t1 * 4.0f);
            else if(t1 < 0.5f)
                return LerpColors(magma2, magma3, (t1 - 0.25f) * 4.0f);
            else if(t1 < 0.75f)
                return LerpColors(magma3, magma4, (t1 - 0.5f) * 4.0f);
            else
                return LerpColors(magma4, magma1, (t1 - 0.75f) * 4.0f);
        }

        case 11: // Aqua Breeze
        {
            ImVec4 aqua1 = ImVec4(0.0f, 0.75f, 0.8f, 1.0f);     // Light aqua
            ImVec4 aqua2 = ImVec4(0.0f, 0.6f, 0.7f, 1.0f);      // Medium aqua
            ImVec4 aqua3 = ImVec4(0.2f, 0.8f, 0.8f, 1.0f);      // Turquoise
            ImVec4 aqua4 = ImVec4(0.0f, 0.5f, 0.6f, 1.0f);      // Deep aqua
            
            float t1 = fmodf(smoothT * 4.0f, 1.0f);
            if(t1 < 0.25f)
                return LerpColors(aqua1, aqua2, t1 * 4.0f);
            else if(t1 < 0.5f)
                return LerpColors(aqua2, aqua3, (t1 - 0.25f) * 4.0f);
            else if(t1 < 0.75f)
                return LerpColors(aqua3, aqua4, (t1 - 0.5f) * 4.0f);
            else
                return LerpColors(aqua4, aqua1, (t1 - 0.75f) * 4.0f);
        }

        case 12: // Cosmic Wave
        {
            ImVec4 space1 = ImVec4(0.5f, 0.0f, 1.0f, 1.0f);     // Space purple
            ImVec4 space2 = ImVec4(0.2f, 0.0f, 0.4f, 1.0f);     // Dark purple
            ImVec4 space3 = ImVec4(0.8f, 0.0f, 0.8f, 1.0f);     // Bright magenta
            float t1 = (sinf(t * 0.7f) + 1.0f) * 0.5f;
            float t2 = (sinf(t * 0.5f + 1.0f) + 1.0f) * 0.5f;
            
            ImVec4 color1 = LerpColors(space1, space2, t1);
            ImVec4 color2 = LerpColors(space2, space3, t2);
            return LerpColors(color1, color2, (sinf(t) + 1.0f) * 0.5f);
        }

        case 13: // Cherry Blossom
        {
            ImVec4 cherry1 = ImVec4(1.0f, 0.7f, 0.8f, 1.0f);    // Soft pink
            ImVec4 cherry2 = ImVec4(1.0f, 0.9f, 0.9f, 1.0f);    // Pinkish white
            ImVec4 cherry3 = ImVec4(0.9f, 0.6f, 0.7f, 1.0f);    // Medium pink
            
            float t1 = (sinf(t * 0.8f) + 1.0f) * 0.5f;
            float t2 = (sinf(t * 1.2f) + 1.0f) * 0.5f;
            
            ImVec4 blend1 = LerpColors(cherry1, cherry2, t1);
            ImVec4 blend2 = LerpColors(cherry2, cherry3, t2);
            return LerpColors(blend1, blend2, smoothT);
        }

        case 14: // Cyberpunk
        {
            ImVec4 cyber1 = ImVec4(1.0f, 0.0f, 0.7f, 1.0f);     // Neon pink
            ImVec4 cyber2 = ImVec4(0.0f, 1.0f, 0.7f, 1.0f);     // Neon green
            ImVec4 cyber3 = ImVec4(0.0f, 0.7f, 1.0f, 1.0f);     // Neon blue
            ImVec4 cyber4 = ImVec4(1.0f, 0.7f, 0.0f, 1.0f);     // Neon yellow
            
            float t1 = fmodf(time * settings::AL_rgbSpeed * 2.0f + (index * 0.1f), 4.0f);
            if(t1 < 1.0f)
                return LerpColors(cyber1, cyber2, t1);
            else if(t1 < 2.0f)
                return LerpColors(cyber2, cyber3, t1 - 1.0f);
            else if(t1 < 3.0f)
                return LerpColors(cyber3, cyber4, t1 - 2.0f);
            else
                return LerpColors(cyber4, cyber1, t1 - 3.0f);
        }
    }
    return ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);
}

void ArrayList::RenderUpdate()
{
    if (!settings::AL_Enabled) return;

    std::vector<std::string> enabledModules;

    if (Esp().IsEnabled()) enabledModules.push_back(Esp().GetName());
    if (Radar().IsEnabled()) enabledModules.push_back(Radar().GetName());
    if (BlockEsp().IsEnabled()) enabledModules.push_back(BlockEsp().GetName());
    if (AimAssist().IsEnabled()) enabledModules.push_back(AimAssist().GetName());
    if (Reach().IsEnabled()) enabledModules.push_back(Reach().GetName());
    if (LeftAutoClicker().IsEnabled()) enabledModules.push_back(LeftAutoClicker().GetName());
    if (RightAutoClicker().IsEnabled()) enabledModules.push_back(RightAutoClicker().GetName());
    if (BridgeAssist().IsEnabled()) enabledModules.push_back(BridgeAssist().GetName());
    if (Velocity().IsEnabled()) enabledModules.push_back(Velocity().GetName());
    if (SprintReset().IsEnabled()) enabledModules.push_back(SprintReset().GetName());
    if (ChestStealer().IsEnabled()) enabledModules.push_back(ChestStealer().GetName());
    if (InventorySorter().IsEnabled()) enabledModules.push_back(InventorySorter().GetName());
    if (ClientBrandChanger().IsEnabled()) enabledModules.push_back(ClientBrandChanger().GetName());
    if (TagBack().IsEnabled()) enabledModules.push_back(TagBack().GetName());
    if (ITEsp().IsEnabled()) enabledModules.push_back(ITEsp().GetName());

    if (enabledModules.empty()) return;

    // sort string length
    std::sort(enabledModules.begin(), enabledModules.end(), [](const std::string& a, const std::string& b) { return Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, a.c_str()).x > Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, b.c_str()).x; });

    // render
    float textHeight = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, enabledModules[0].c_str()).y + (2 * settings::AL_backgroundPadding);
    switch (settings::AL_renderPosition)
    {
    case 0: // Top Left
        for (int i = 0; i < enabledModules.size(); i++)
        {
            const char* name = enabledModules[i].c_str();
            ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);

            ImVec2 pos_min = ImVec2(0, (textHeight * i));
            ImVec2 pos_max = ImVec2(textSize.x + (2 * settings::AL_backgroundPadding), textSize.y + (2 * settings::AL_backgroundPadding) + pos_min.y);
            
            // Draw background without rounding to avoid crashes
            ImGui::GetWindowDrawList()->AddRectFilled(
                pos_min, 
                pos_max, 
                ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], 
                       settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]),
                0.0f
            );

            // Draw text
            ImVec4 textColor = GetColorForModule(i, ImGui::GetTime());
            ImGui::GetWindowDrawList()->AddText(
                Menu::Font, 
                settings::AL_textSize, 
                ImVec2(settings::AL_backgroundPadding, settings::AL_backgroundPadding + (textHeight * i)), 
                ImColor(textColor.x, textColor.y, textColor.z, textColor.w), 
                name
            );
        }
        break;

    case 1: // Top Right
        for (int i = 0; i < enabledModules.size(); i++)
        {
            const char* name = enabledModules[i].c_str();
            ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);
            float windowWidth = ImGui::GetWindowSize().x;

            ImVec2 pos_min = ImVec2(windowWidth - textSize.x - (2 * settings::AL_backgroundPadding), (textHeight * i));
            ImVec2 pos_max = ImVec2(windowWidth, textSize.y + (2 * settings::AL_backgroundPadding) + pos_min.y);
            
            // Draw background
            ImGui::GetWindowDrawList()->AddRectFilled(
                pos_min, 
                pos_max, 
                ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], 
                       settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]),
                0.0f
            );

            // Draw text
            ImVec4 textColor = GetColorForModule(i, ImGui::GetTime());
            ImGui::GetWindowDrawList()->AddText(
                Menu::Font, 
                settings::AL_textSize, 
                ImVec2(windowWidth - textSize.x - settings::AL_backgroundPadding, 
                       settings::AL_backgroundPadding + (textHeight * i)), 
                ImColor(textColor.x, textColor.y, textColor.z, textColor.w), 
                name
            );
        }
        break;

    case 2: // Bottom Left
        for (int i = 0; i < enabledModules.size(); i++)
        {
            const char* name = enabledModules[i].c_str();
            ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);
            float windowHeight = ImGui::GetWindowSize().y;

            ImVec2 pos_min = ImVec2(0, windowHeight - textSize.y - (2 * settings::AL_backgroundPadding) - (textHeight * i));
            ImVec2 pos_max = ImVec2(textSize.x + (2 * settings::AL_backgroundPadding), windowHeight - (textHeight * i));
            
            // Draw background
            ImGui::GetWindowDrawList()->AddRectFilled(
                pos_min, 
                pos_max, 
                ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], 
                       settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]),
                0.0f
            );

            // Draw text
            ImVec4 textColor = GetColorForModule(i, ImGui::GetTime());
            ImGui::GetWindowDrawList()->AddText(
                Menu::Font, 
                settings::AL_textSize, 
                ImVec2(settings::AL_backgroundPadding, windowHeight - textSize.y - 
                       settings::AL_backgroundPadding - (textHeight * i)), 
                ImColor(textColor.x, textColor.y, textColor.z, textColor.w), 
                name
            );
        }
        break;

    case 3: // Bottom Right
        for (int i = 0; i < enabledModules.size(); i++)
        {
            const char* name = enabledModules[i].c_str();
            ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);
            float windowWidth = ImGui::GetWindowSize().x;
            float windowHeight = ImGui::GetWindowSize().y;

            ImVec2 pos_min = ImVec2(windowWidth - textSize.x - (2 * settings::AL_backgroundPadding), 
                                   windowHeight - textSize.y - (2 * settings::AL_backgroundPadding) - (textHeight * i));
            ImVec2 pos_max = ImVec2(windowWidth, windowHeight - (textHeight * i));
            
            // Draw background
            ImGui::GetWindowDrawList()->AddRectFilled(
                pos_min, 
                pos_max, 
                ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], 
                       settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]),
                0.0f
            );

            // Draw text
            ImVec4 textColor = GetColorForModule(i, ImGui::GetTime());
            ImGui::GetWindowDrawList()->AddText(
                Menu::Font, 
                settings::AL_textSize, 
                ImVec2(windowWidth - textSize.x - settings::AL_backgroundPadding, 
                       windowHeight - textSize.y - settings::AL_backgroundPadding - (textHeight * i)), 
                ImColor(textColor.x, textColor.y, textColor.z, textColor.w), 
                name
            );
        }
        break;
    }
}

void ArrayList::RenderMenu()
{
    static bool renderSettings = false;

    ImGui::BeginGroup();

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

    if (ImGui::BeginChild("al_header", ImVec2(425.f, renderSettings ? 185.f : 35.f), false))
    {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
        ImGui::BeginGroup();

        // Title in normal position
        Menu::ToggleButton(80, ("Toggle " + this->GetName()).c_str(), ImVec2(367, 0), &settings::AL_Enabled);
        
        // Modern warning symbol with tooltip
        ImGui::SameLine(350);
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 0.0f);
            ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.15f, 0.15f, 0.15f, 0.98f));
            
            ImGui::BeginTooltip();
            
            // Warning title
            ImGui::PushFont(Menu::Font); // Assuming you have a font system
            ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Warning");
            ImGui::PopFont();
            
            ImGui::Separator();
            ImGui::Spacing();
            
            // Warning content
            ImGui::PushTextWrapPos(450.0f);
            ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.9f, 1.0f), 
                "This module is currently in development and may cause instability or crashes.\n\n"
                "Use with caution.");
            ImGui::PopTextWrapPos();
            
            ImGui::EndTooltip();
            
            ImGui::PopStyleColor();
            ImGui::PopStyleVar(3);
        }

        ImGui::EndGroup();
        
        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            renderSettings = !renderSettings;
        }

        ImGui::PopStyleColor();
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.0));

        if (renderSettings)
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            ImGui::Separator();
            if (ImGui::BeginChild("al_settings", ImVec2(425, 140), false))
            {
                Menu::ComboBox(81, "Position", ImVec2(270, 0), &settings::AL_renderPosition, settings::AL_renderPositionList, 4);
                Menu::Slider(82, "Text Size", ImVec2(225, 0), &settings::AL_textSize, 1, 50);
                Menu::ColorPicker(83, "Text Color", ImVec2(374, 0), settings::AL_textColor);
                Menu::Slider(84, "Background Padding", ImVec2(225, 0), &settings::AL_backgroundPadding, 0, 20);
                Menu::ColorPicker(85, "Background Color", ImVec2(374, 0), settings::AL_backgroundColor);
                Menu::ToggleButton(87, "RGB Effect", ImVec2(368, 0), &settings::AL_rgbEnabled);
                if (settings::AL_rgbEnabled)
                {
                    Menu::ComboBox(88, "Color Mode", ImVec2(270, 0), &settings::AL_colorMode, settings::AL_colorModeList, 12);
                    Menu::Slider(89, "RGB Speed", ImVec2(225, 0), &settings::AL_rgbSpeed, 0.1f, 5.0f, "%.1f");
                }
            }
            ImGui::EndChild();
            ImGui::Spacing();
        }
    }
    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    ImGui::EndGroup();
}

// Enhanced function for calculating Bézier curve points
ImVec2 BezierPoint(const ImVec2& p0, const ImVec2& p1, const ImVec2& p2, float t) {
    float mt = 1.0f - t;
    return ImVec2(
        mt * mt * p0.x + 2.0f * mt * t * p1.x + t * t * p2.x,
        mt * mt * p0.y + 2.0f * mt * t * p1.y + t * t * p2.y
    );
}

ImVec2 GetPointOnRoundedRect(const ImVec2& min, const ImVec2& max, float radius, float t)
{
    // Adjust radius if too large
    radius = ImMin(radius, ImMin((max.x - min.x) * 0.5f, (max.y - min.y) * 0.5f));
    
    float right = max.x - radius;
    float bottom = max.y - radius;
    float left = min.x + radius;
    float top = min.y + radius;
    
    // Calculate total perimeter length
    float straightLength = 2.0f * ((max.x - min.x - 2.0f * radius) + (max.y - min.y - 2.0f * radius));
    float curveLength = 2.0f * M_PI * radius;
    float totalLength = straightLength + curveLength;
    
    float distance = t * totalLength;
    
    // Control points for corners
    const ImVec2 corners[4] = {
        ImVec2(right, min.y), // Top right
        ImVec2(max.x, top),   // Right top
        ImVec2(max.x, bottom),// Right bottom
        ImVec2(right, max.y)  // Bottom right
    };
    
    // If we're on a straight section
    if (distance < right - min.x)
        return ImVec2(min.x + distance, min.y);
    distance -= right - min.x;
    
    // First corner (top right)
    if (distance < (M_PI * 0.5f * radius)) {
        float angle = distance / radius;
        ImVec2 center(right, top);
        ImVec2 control(right + radius * 0.552284f, top - radius * 0.552284f);
        return BezierPoint(
            ImVec2(right, min.y),
            control,
            ImVec2(max.x, top),
            angle / (M_PI * 0.5f)
        );
    }
    distance -= M_PI * 0.5f * radius;

    float angle = M_PI * 2.0f * (distance / (M_PI * 2.0f * radius));
    return ImVec2(
        left + radius * cosf(angle),
        top + radius * sinf(angle)
    );
}
