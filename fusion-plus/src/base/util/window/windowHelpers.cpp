#include "windowHelpers.h"
#include "util/logger/logger.h"

#include "imgui/imgui.h"
#include <imgui/imgui_internal.h>

struct AspectRatioData {
    float xRatio;
    float yRatio;
    float ratio;
    ImVec2 lastStableSize;
    bool isFirstUpdate;
};

void WindowHelpers::SetFixedAspectRatio(float xRatio, float yRatio)
{
    // Use static storage for the callback data
    static AspectRatioData data;
    data.xRatio = xRatio;
    data.yRatio = yRatio;
    data.ratio = xRatio / yRatio;
    data.isFirstUpdate = true;

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(10, 10),
        ImVec2(FLT_MAX, FLT_MAX),
        [](ImGuiSizeCallbackData* callback_data)
        {
            AspectRatioData* aspectData = (AspectRatioData*)callback_data->UserData;

            if (aspectData->isFirstUpdate) {
                aspectData->lastStableSize = callback_data->CurrentSize;
                aspectData->isFirstUpdate = false;
            }

            float widthFromHeight = callback_data->DesiredSize.y * aspectData->ratio;
            float heightFromWidth = callback_data->DesiredSize.x / aspectData->ratio;

            if (widthFromHeight * callback_data->DesiredSize.y <=
                callback_data->DesiredSize.x * heightFromWidth) {
                callback_data->DesiredSize.x = widthFromHeight;
            }
            else {
                callback_data->DesiredSize.y = heightFromWidth;
            }

            aspectData->lastStableSize = callback_data->DesiredSize;
        },
        (void*)&data
    );
}