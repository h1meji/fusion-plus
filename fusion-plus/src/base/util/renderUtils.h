#pragma once
#include <imgui/imgui.h>
#include <vector>
#include <string>

class RenderUtils {
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
