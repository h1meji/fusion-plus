#include "wTap.h"
#include "moduleManager/commonData.h"
#include "menu/menu.h"

inline void send_key(WORD vk_key, bool send_down = true)
{
	static INPUT ip{ INPUT_KEYBOARD };

	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = vk_key;
	ip.ki.dwFlags = send_down ? 0 : KEYEVENTF_KEYUP;

	SendInput(1, &ip, sizeof(INPUT));
}

void WTap::Update()
{
    timeSinceLetGoW++;
    if (timeSinceLetGoW > settings::WTap_DelayBetween)
    {
        can_wtap = true;
    }

    if (timeSinceLetGoW > settings::WTap_LetGoDelay && wTapInAction)
    {
        send_key(0x57, true);
        wTapInAction = false;
    }

    if (!settings::WTap_Enabled || !CommonData::SanityCheck() || SDK::Minecraft->IsInGuiState() || Menu::Open)
    {
        lastHurtResistantTime = 0;
        timeSinceLetGoW = 0;
        wTapInAction = false;
        return;
    }

    bool isPressingW = GetAsyncKeyState(0x57);
    bool attackedInput = GetAsyncKeyState(0x01);
    if (!isPressingW || !attackedInput)
    {
        lastHurtResistantTime = 0;
        return;
    }

    CEntity entity = SDK::Minecraft->GetMouseOver().GetEntityHit();

    if (entity.GetInstance() == nullptr)
    {
        lastHurtResistantTime = 0;
        return;
    }

    int currentHurtResistantTime = entity.GetHurtResistantTime();

    if (currentHurtResistantTime > 0)
    {
        lastHurtResistantTime = currentHurtResistantTime;

        if (!wTapInAction && can_wtap)
        {
            send_key(0x57, false);

            wTapInAction = true;
            can_wtap = false;
            timeSinceLetGoW = 0;
        }
    }
}


void WTap::RenderMenu()
{
    static bool renderSettings = false;

    ImGui::BeginGroup();

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

    if (ImGui::BeginChild("wtap_header", ImVec2(425, renderSettings ? 99 : 35), false))
    {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
        ImGui::BeginGroup();
        Menu::ToggleButton(18, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::WTap_Enabled);
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
            if (ImGui::BeginChild("wtap_settings", ImVec2(425, 54), false))
            {
                Menu::Slider(19, "Delay Between W-Taps", ImVec2(225, 0), &settings::WTap_DelayBetween, 0, 100);
                Menu::Slider(20, "Let Go Delay", ImVec2(225, 0), &settings::WTap_LetGoDelay, 0, 100);
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
