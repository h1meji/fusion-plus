#pragma once

#include <vector>
#include <string>

#include <imgui/imgui.h>

#include "configManager/settings.h"

struct Render
{
    static void DrawOutlinedText(ImFont* font, float textSize, ImVec2 pos, ImColor color, ImColor outlineColor, const char* text)
    {
        ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x + 1, pos.y), outlineColor, text);
        ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x - 1, pos.y), outlineColor, text);
        ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x, pos.y + 1), outlineColor, text);
        ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x, pos.y - 1), outlineColor, text);

        ImGui::GetWindowDrawList()->AddText(font, textSize, pos, color, text);
    }

    static void DrawLine(int x, int height, int padding)
    {
        ImVec2 lineStart = ImVec2(x, settings::Hud_WatermarkPosition[1] + (padding * 1.5));
        ImVec2 lineEnd = ImVec2(x, settings::Hud_WatermarkPosition[1] + height - (padding * 1.5));
        ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(155, 155, 155, 255), 2);
    }

public:
    static void RenderModuleList(const std::vector<std::string>& modules, 
                               int position, float textSize, 
                               float padding, ImVec4 bgColor,
                               const ImFont* font,
                               bool useRGB, int colorMode, float rgbSpeed);

private:
    static void RenderTopLeft(const std::vector<std::string>& modules, float textHeight, 
                            float padding, ImVec4 bgColor, const ImFont* font,
                            bool useRGB, int colorMode, float rgbSpeed);
    
    static void RenderTopRight(const std::vector<std::string>& modules, float textHeight, 
                             float padding, ImVec4 bgColor, const ImFont* font,
                             bool useRGB, int colorMode, float rgbSpeed);
    
    static void RenderBottomLeft(const std::vector<std::string>& modules, float textHeight, 
                               float padding, ImVec4 bgColor, const ImFont* font,
                               bool useRGB, int colorMode, float rgbSpeed);
    
    static void RenderBottomRight(const std::vector<std::string>& modules, float textHeight, 
                                float padding, ImVec4 bgColor, const ImFont* font,
                                bool useRGB, int colorMode, float rgbSpeed);
};
