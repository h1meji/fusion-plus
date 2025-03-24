#include "renderUtils.h"
#include "colorPresets.h"
#include "util/time/timeManager.h"
#include "configManager/settings.h" // Add this include
#include <cmath>

void RenderUtils::RenderModuleList(const std::vector<std::string>& modules, 
                                 int position, float textSize, 
                                 float padding, ImVec4 bgColor,
                                 const ImFont* font,
                                 bool useRGB, int colorMode, float rgbSpeed) 
{
    if (modules.empty()) return;

    float textHeight = font->CalcTextSizeA(textSize, FLT_MAX, 0.0f, modules[0].c_str()).y + (2 * padding);

    switch (position) {
        case 0: RenderTopLeft(modules, textHeight, padding, bgColor, font, useRGB, colorMode, rgbSpeed); break;
        case 1: RenderTopRight(modules, textHeight, padding, bgColor, font, useRGB, colorMode, rgbSpeed); break;
        case 2: RenderBottomLeft(modules, textHeight, padding, bgColor, font, useRGB, colorMode, rgbSpeed); break;
        case 3: RenderBottomRight(modules, textHeight, padding, bgColor, font, useRGB, colorMode, rgbSpeed); break;
    }
}

void RenderUtils::RenderTopLeft(const std::vector<std::string>& modules, float textHeight, 
                              float padding, ImVec4 bgColor, const ImFont* font,
                              bool useRGB, int colorMode, float rgbSpeed)
{
    float currentY = 0;
    const float moduleSpacing = 0.5f;
    
    for (int i = 0; i < modules.size(); i++) {
        const char* name = modules[i].c_str();
        ImVec2 textSize = font->CalcTextSizeA(textHeight, FLT_MAX, 0.0f, name);

        ImVec2 pos_min = ImVec2(0, currentY);
        ImVec2 pos_max = ImVec2(textSize.x + (2 * padding), currentY + textSize.y + (2 * padding));

        ImDrawFlags cornerFlags = ImDrawFlags_None;
        if (i < modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersBottomRight;
        if (i == modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersRight;

        if (i > 0) {
            ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(pos_min.x, pos_min.y - 1),
                ImVec2(pos_max.x, pos_min.y + 1),
                ImGui::ColorConvertFloat4ToU32(bgColor)
            );
        }

        // Draw outline if enabled
        if (settings::AL_outlineEnabled) {
            ImVec4 outlineColor = settings::AL_outlineRGB ? 
                ColorPresets::GetPreset(colorMode, 
                                      TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                      (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                      TimeManager::GetTime()) :
                ImVec4(settings::AL_outlineColor[0], settings::AL_outlineColor[1],
                      settings::AL_outlineColor[2], settings::AL_outlineColor[3]);

            // Draw outline
            ImGui::GetWindowDrawList()->AddRect(
                pos_min, pos_max,
                ImGui::ColorConvertFloat4ToU32(outlineColor),
                (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
                cornerFlags,
                settings::AL_outlineThickness
            );
        }

        ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, 
            ImGui::ColorConvertFloat4ToU32(bgColor), 
            (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
            cornerFlags);

        ImVec4 textColor = useRGB ? 
            ColorPresets::GetPreset(colorMode, 
                                  TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                  (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                  TimeManager::GetTime()) :
            ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);

        ImGui::GetWindowDrawList()->AddText(font, textHeight,
            ImVec2(padding, currentY + padding),
            ImGui::ColorConvertFloat4ToU32(textColor), name);

        currentY = pos_max.y - moduleSpacing;
    }
}

void RenderUtils::RenderTopRight(const std::vector<std::string>& modules, float textHeight, 
                               float padding, ImVec4 bgColor, const ImFont* font,
                               bool useRGB, int colorMode, float rgbSpeed)
{
    float windowWidth = ImGui::GetWindowSize().x;
    float currentY = 0;
    const float moduleSpacing = 0.5f;
    
    for (int i = 0; i < modules.size(); i++) {
        const char* name = modules[i].c_str();
        ImVec2 textSize = font->CalcTextSizeA(textHeight, FLT_MAX, 0.0f, name);

        ImVec2 pos_min = ImVec2(windowWidth - textSize.x - (2 * padding), currentY);
        ImVec2 pos_max = ImVec2(windowWidth, currentY + textSize.y + (2 * padding));

        ImDrawFlags cornerFlags = ImDrawFlags_None;
        if (i < modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersBottomLeft;
        if (i == modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersLeft;

        if (i > 0) {
            ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(pos_min.x, pos_min.y - 1),
                ImVec2(pos_max.x, pos_min.y + 1),
                ImGui::ColorConvertFloat4ToU32(bgColor)
            );
        }

        // Draw outline if enabled
        if (settings::AL_outlineEnabled) {
            ImVec4 outlineColor = settings::AL_outlineRGB ? 
                ColorPresets::GetPreset(colorMode, 
                                      TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                      (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                      TimeManager::GetTime()) :
                ImVec4(settings::AL_outlineColor[0], settings::AL_outlineColor[1],
                      settings::AL_outlineColor[2], settings::AL_outlineColor[3]);

            // Draw outline
            ImGui::GetWindowDrawList()->AddRect(
                pos_min, pos_max,
                ImGui::ColorConvertFloat4ToU32(outlineColor),
                (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
                cornerFlags,
                settings::AL_outlineThickness
            );
        }

        ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, 
            ImGui::ColorConvertFloat4ToU32(bgColor), 
            (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
            cornerFlags);

        ImVec4 textColor = useRGB ? 
            ColorPresets::GetPreset(colorMode, 
                                  TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                  (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                  TimeManager::GetTime()) :
            ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);

        ImGui::GetWindowDrawList()->AddText(font, textHeight,
            ImVec2(windowWidth - textSize.x - padding, currentY + padding),
            ImGui::ColorConvertFloat4ToU32(textColor), name);

        currentY = pos_max.y - moduleSpacing;
    }
}

void RenderUtils::RenderBottomLeft(const std::vector<std::string>& modules, float textHeight, 
                                 float padding, ImVec4 bgColor, const ImFont* font,
                                 bool useRGB, int colorMode, float rgbSpeed)
{
    float windowHeight = ImGui::GetWindowSize().y;
    float totalHeight = 0;
    const float moduleSpacing = 0.5f;

    for (int i = 0; i < modules.size(); i++) {
        const char* name = modules[i].c_str();
        ImVec2 textSize = font->CalcTextSizeA(textHeight, FLT_MAX, 0.0f, name);
        totalHeight += ceilf(textSize.y + (2 * padding)) - (i > 0 ? 1.0f : 0.0f);
        if (i < modules.size() - 1) totalHeight += moduleSpacing;
    }

    float currentY = floorf(windowHeight - totalHeight);

    for (int i = 0; i < modules.size(); i++) {
        const char* name = modules[i].c_str();
        ImVec2 textSize = font->CalcTextSizeA(textHeight, FLT_MAX, 0.0f, name);

        ImVec2 pos_min = ImVec2(0, floorf(currentY));
        ImVec2 pos_max = ImVec2(textSize.x + (2 * padding), ceilf(currentY + textSize.y + (2 * padding)));
        
        ImDrawFlags cornerFlags = ImDrawFlags_None;
        if (i == 0) cornerFlags |= ImDrawFlags_RoundCornersTopRight;
        if (i == modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersBottomRight;
        if (i > 0 && i < modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersBottomRight;
        if (modules.size() == 1) cornerFlags |= ImDrawFlags_RoundCornersRight;

        if (i > 0) pos_min.y -= 1.0f;

        // Draw outline if enabled
        if (settings::AL_outlineEnabled) {
            ImVec4 outlineColor = settings::AL_outlineRGB ? 
                ColorPresets::GetPreset(colorMode, 
                                      TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                      (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                      TimeManager::GetTime()) :
                ImVec4(settings::AL_outlineColor[0], settings::AL_outlineColor[1],
                      settings::AL_outlineColor[2], settings::AL_outlineColor[3]);

            // Draw outline
            ImGui::GetWindowDrawList()->AddRect(
                pos_min, pos_max,
                ImGui::ColorConvertFloat4ToU32(outlineColor),
                (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
                cornerFlags,
                settings::AL_outlineThickness
            );
        }

        ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, 
            ImGui::ColorConvertFloat4ToU32(bgColor), 
            (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
            cornerFlags);

        ImVec4 textColor = useRGB ? 
            ColorPresets::GetPreset(colorMode, 
                                  TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                  (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                  TimeManager::GetTime()) :
            ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);

        ImGui::GetWindowDrawList()->AddText(font, textHeight,
            ImVec2(padding, currentY + padding),
            ImGui::ColorConvertFloat4ToU32(textColor), name);

        currentY = pos_max.y - moduleSpacing;
    }
}

void RenderUtils::RenderBottomRight(const std::vector<std::string>& modules, float textHeight, 
                                  float padding, ImVec4 bgColor, const ImFont* font,
                                  bool useRGB, int colorMode, float rgbSpeed)
{
    float windowWidth = ImGui::GetWindowSize().x;
    float windowHeight = ImGui::GetWindowSize().y;
    float totalHeight = 0;
    const float moduleSpacing = 0.5f;

    for (int i = 0; i < modules.size(); i++) {
        const char* name = modules[i].c_str();
        ImVec2 textSize = font->CalcTextSizeA(textHeight, FLT_MAX, 0.0f, name);
        totalHeight += ceilf(textSize.y + (2 * padding)) - (i > 0 ? 1.0f : 0.0f);
        if (i < modules.size() - 1) totalHeight += moduleSpacing;
    }

    float currentY = floorf(windowHeight - totalHeight);

    for (int i = 0; i < modules.size(); i++) {
        const char* name = modules[i].c_str();
        ImVec2 textSize = font->CalcTextSizeA(textHeight, FLT_MAX, 0.0f, name);

        ImVec2 pos_min = ImVec2(windowWidth - textSize.x - (2 * padding), floorf(currentY));
        ImVec2 pos_max = ImVec2(windowWidth, ceilf(currentY + textSize.y + (2 * padding)));
        
        ImDrawFlags cornerFlags = ImDrawFlags_None;
        if (i == 0) cornerFlags |= ImDrawFlags_RoundCornersTopLeft;
        if (i == modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersBottomLeft;
        if (i > 0 && i < modules.size() - 1) cornerFlags |= ImDrawFlags_RoundCornersBottomLeft;
        if (modules.size() == 1) cornerFlags |= ImDrawFlags_RoundCornersLeft;

        if (i > 0) pos_min.y -= 1.0f;

        // Draw outline if enabled
        if (settings::AL_outlineEnabled) {
            ImVec4 outlineColor = settings::AL_outlineRGB ? 
                ColorPresets::GetPreset(colorMode, 
                                      TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                      (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                      TimeManager::GetTime()) :
                ImVec4(settings::AL_outlineColor[0], settings::AL_outlineColor[1],
                      settings::AL_outlineColor[2], settings::AL_outlineColor[3]);

            // Draw outline
            ImGui::GetWindowDrawList()->AddRect(
                pos_min, pos_max,
                ImGui::ColorConvertFloat4ToU32(outlineColor),
                (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
                cornerFlags,
                settings::AL_outlineThickness
            );
        }

        ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, 
            ImGui::ColorConvertFloat4ToU32(bgColor), 
            (cornerFlags == ImDrawFlags_None) ? 0.0f : 3.0f,
            cornerFlags);

        ImVec4 textColor = useRGB ? 
            ColorPresets::GetPreset(colorMode, 
                                  TimeManager::GetTime() * rgbSpeed + (i * 0.1f),
                                  (sinf(TimeManager::GetTime() * rgbSpeed + (i * 0.1f)) + 1.0f) * 0.5f,
                                  TimeManager::GetTime()) :
            ImVec4(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]);

        ImGui::GetWindowDrawList()->AddText(font, textHeight,
            ImVec2(windowWidth - textSize.x - padding, currentY + padding),
            ImGui::ColorConvertFloat4ToU32(textColor), name);

        currentY = pos_max.y - moduleSpacing;
    }
}
