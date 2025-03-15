#include "arrayList.h"
#include "util/render/renderUtils.h"
#include "util/render/colorPresets.h"
#include "util/time/timeManager.h"

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
        return ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], 
                     settings::AL_textColor[2], settings::AL_textColor[3]);
        
    float time = TimeManager::GetTime();
    float t = fmodf(time * settings::AL_rgbSpeed + (index * 0.1f), 2.0f * M_PI);
    float smoothT = (sinf(t) + 1.0f) * 0.5f;
    
    return ColorPresets::GetPreset(settings::AL_colorMode, t, smoothT, time);
}

void ArrayList::RenderHud() {
    if (!settings::AL_Enabled) return;

    std::vector<std::string> enabledModules;
    
    // Collect enabled modules
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

    // Sort modules by length
    std::sort(enabledModules.begin(), enabledModules.end(), 
        [](const std::string& a, const std::string& b) { 
            return Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, a.c_str()).x > 
                   Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, b.c_str()).x; 
        });

    ImVec4 bgColor(
        settings::AL_backgroundColor[0],
        settings::AL_backgroundColor[1],
        settings::AL_backgroundColor[2],
        settings::AL_backgroundColor[3]
    );

    RenderUtils::RenderModuleList(
        enabledModules,
        settings::AL_renderPosition,
        settings::AL_textSize,
        settings::AL_backgroundPadding,
        bgColor,
        Menu::Font,
        settings::AL_rgbEnabled,
        settings::AL_colorMode,
        settings::AL_rgbSpeed
    );
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
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "( ? )");
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
                Menu::KeybindButton(176, "Keybind", ImVec2(297, 0), settings::AL_Key);
                Menu::ComboBox(81, "Position", ImVec2(270, 0), &settings::AL_renderPosition, settings::AL_renderPositionList, 4);
                Menu::ToggleButton(148, "RGB Effect", ImVec2(368, 0), &settings::AL_rgbEnabled);
                if (settings::AL_rgbEnabled)
                {
                    Menu::ComboBox(149, "Color Mode", ImVec2(270, 0), &settings::AL_colorMode, settings::AL_colorModeList, 12);
                    Menu::Slider(150, "RGB Speed", ImVec2(225, 0), &settings::AL_rgbSpeed, 0.1f, 5.0f, "%.1f");
                }
                Menu::Slider(82, "Text Size", ImVec2(225, 0), &settings::AL_textSize, 1, 50);
                Menu::ColorPicker(83, "Text Color", ImVec2(374, 0), settings::AL_textColor);
                Menu::Slider(84, "Background Padding", ImVec2(225, 0), &settings::AL_backgroundPadding, 0, 20);
                Menu::ColorPicker(85, "Background Color", ImVec2(374, 0), settings::AL_backgroundColor);
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
