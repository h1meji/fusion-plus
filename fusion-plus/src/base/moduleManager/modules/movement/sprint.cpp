#include "sprint.h"
#include "moduleManager/commonData.h"
#include "menu/menu.h"

inline static void send_key(WORD vk_key, bool send_down = true) {
    unsigned long dwFlags = send_down ? 0 : KEYEVENTF_KEYUP;
    static INPUT ip{ INPUT_KEYBOARD };
    ip.ki = {
        vk_key,
        0,
        dwFlags,
        0,
        0
    };
    SendInput(1, &ip, sizeof(INPUT));
}

bool isHoldingCtrl = false;

void Sprint::Update()
{
    if (!settings::S_Enabled || !CommonData::SanityCheck() || SDK::Minecraft->IsInGuiState() || Menu::Open)
    {
        if (isHoldingCtrl)
        {
            send_key(VK_CONTROL, false);
            isHoldingCtrl = false;
        }
        return;
    }

    bool isPressingW = GetAsyncKeyState(0x57) & 0x8000;

    if (isPressingW && !isHoldingCtrl)
    {
        send_key(VK_CONTROL, true);
        isHoldingCtrl = true;
    }
    else if (!isPressingW && isHoldingCtrl)
    {
        send_key(VK_CONTROL, false);
        isHoldingCtrl = false;
    }
}

void Sprint::RenderMenu()
{
    ImGui::BeginGroup();

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

    if (ImGui::BeginChild("s_header", ImVec2(425.f, 35.f), false))
    {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
        ImGui::BeginGroup();
        Menu::ToggleButton(140, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::S_Enabled);
        ImGui::EndGroup();
    }
    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    ImGui::EndGroup();
}
