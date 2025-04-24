#include "sprintReset.h"

#include "moduleManager/commonData.h"
#include "menu/menu.h"
#include "util/keys.h"

void SprintReset::Update()
{
	std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> sinceStart = currentTime - m_startTime;
	if (sinceStart.count() > settings::SR_LetGoDelay && m_sprintResetInAction)
	{
		Keys::SendKey(0x53, false);

		m_sprintResetInAction = false;
		m_pauseTime = std::chrono::steady_clock::now();
		return;
	}
	std::chrono::duration<double> sincePause = currentTime - m_pauseTime;
	if (sincePause.count() > settings::SR_DelayBetween && !m_canSprintReset)
	{
		m_canSprintReset = true;
		return;
	}

	if (!settings::SR_Enabled || !CommonData::SanityCheck() || SDK::minecraft->IsInGuiState() || Menu::open)
	{
		return;
	}

	bool isPressingW = GetAsyncKeyState(0x57);
	bool attackedInput = GetAsyncKeyState(0x01);
	if (!isPressingW || !attackedInput || !SDK::minecraft->thePlayer->IsSprinting())
	{
		return;
	}

	CEntity entity = SDK::minecraft->GetMouseOver().GetEntityHit();
	if (entity.GetInstance() == nullptr)
	{
		return;
	}

	int currentHurtResistantTime = entity.GetHurtResistantTime();
	if (currentHurtResistantTime > 10)
	{
		if (!m_sprintResetInAction && m_canSprintReset)
		{
			Keys::SendKey(0x53, true);

			m_sprintResetInAction = true;
			m_canSprintReset = false;
			m_startTime = std::chrono::steady_clock::now();
		}
	}
}

void SprintReset::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::SR_Enabled, settings::SR_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Delay Between S-Taps", &settings::SR_DelayBetween, 0.1f, 3.f);
	Menu::Slider("Let Go Delay", &settings::SR_LetGoDelay, .01f, .3f, ImVec2(0,0), "%.3f");
}
