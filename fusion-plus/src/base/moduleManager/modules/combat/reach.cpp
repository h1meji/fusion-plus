#include "reach.h"

#include "sdk/sdk.h"
#include "java/java.h"
#include "moduleManager/commonData.h"
#include "util/logger.h"
#include "util/math/math.h"
#include "menu/menu.h"

void Reach::Update()
{
	if (!settings::Reach_Enabled) return;
	if (!CommonData::SanityCheck()) return;
}


void Reach::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::Reach_Enabled, settings::Reach_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Reach Distance", &settings::Reach_ReachDistance, 0.1f, 5.0f);
}
