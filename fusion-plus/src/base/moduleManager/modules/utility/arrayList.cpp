#include "arrayList.h"
#include "util/render/renderUtils.h"
#include "util/render/colorPresets.h"
#include "util/time/timeManager.h"

#include <imgui/imgui.h>
#include "menu/menu.h"
#include "moduleManager/commonData.h"

#include <moduleManager/moduleManager.h>

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
    if (settings::AL_colorMode == 0)
        return ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);
        
    float time = TimeManager::GetTime();
    float t = fmodf(time * settings::AL_rgbSpeed + (index * 0.1f), 2.0f * M_PI);
    float smoothT = (sinf(t) + 1.0f) * 0.5f;
    
    return ColorPresets::GetPreset(settings::AL_colorMode, t, smoothT, time);
}

void ArrayList::RenderHud() {
    if (!settings::AL_Enabled) return;

    std::vector<std::string> enabledModules;
    
    // Collect enabled modules
	for (std::unique_ptr<ModuleBase>& module : g_ModuleManager->GetModules()) {
        if (module->IsEnabled()) {
            enabledModules.push_back(module->GetName());
        }
	}

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
        settings::AL_colorMode != 0,
        settings::AL_colorMode,
        settings::AL_rgbSpeed
    );
}

void ArrayList::RenderMenu()
{
	Menu::TextColored("This module is currently in development and may cause instability or crashes. Use with caution.", ImVec4(1.0f, 0.8f, 0.0f, 1.0f), FontSize::SIZE_16);

    Menu::ToggleWithKeybind(&settings::AL_Enabled, settings::AL_Key);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
    Menu::HorizontalSeparator("Sep1");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Dropdown("Position", settings::AL_renderPositionList, &settings::AL_renderPosition, 4);
	Menu::Slider("Text Size", &settings::AL_textSize, 1, 50);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
    Menu::HorizontalSeparator("Sep2");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Dropdown("Color Mode", settings::AL_colorModeList, &settings::AL_colorMode, 12);
	if (settings::AL_colorMode == 0)
	{
		Menu::ColorEdit("Color", settings::AL_textColor);
	}
    else
    {
		Menu::Slider("RGB Speed", &settings::AL_rgbSpeed, 0.1f, 5.0f, ImVec2(0,0), "%.1f");
    }
	Menu::Slider("Background Padding", &settings::AL_backgroundPadding, 0, 20);
	Menu::ColorEdit("Background Color", settings::AL_backgroundColor);
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
