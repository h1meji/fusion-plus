#include "windowHelpers.h"

#include "util/logger.h"

void WindowHelpers::SetFixedAspectRatio(AspectRatioData* aspectData)
{
	aspectData->isFirstUpdate = true;
    ImGui::SetNextWindowSizeConstraints(
        ImVec2(10, 10),
        ImVec2(FLT_MAX, FLT_MAX),
        [](ImGuiSizeCallbackData* callback_data)
        {
            AspectRatioData* aspectData = (AspectRatioData*)callback_data->UserData;

            if (aspectData->isFirstUpdate)
            {
                aspectData->lastStableSize = callback_data->CurrentSize;
                aspectData->isFirstUpdate = false;
            }

            float widthFromHeight = callback_data->DesiredSize.y * aspectData->ratio;
            float heightFromWidth = callback_data->DesiredSize.x / aspectData->ratio;

            if (widthFromHeight * callback_data->DesiredSize.y <=
                callback_data->DesiredSize.x * heightFromWidth)
            {
                callback_data->DesiredSize.x = widthFromHeight;
            }
            else
            {
                callback_data->DesiredSize.y = heightFromWidth;
            }

            aspectData->lastStableSize = callback_data->DesiredSize;
        },
        aspectData
    );
}