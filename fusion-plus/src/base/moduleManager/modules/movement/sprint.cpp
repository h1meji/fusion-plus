#include "sprint.h"

#include "moduleManager/commonData.h"
#include "menu/menu.h"
#include "util/keys.h"

inline static void sendKey(WORD vkKey, bool sendDown = true)
{
    static INPUT ip{ INPUT_KEYBOARD };

    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = vkKey;
    ip.ki.dwFlags = sendDown ? 0 : KEYEVENTF_KEYUP;

    SendInput(1, &ip, sizeof(INPUT));
}

void Sprint::Update()
{
    if (!settings::S_Enabled || !CommonData::SanityCheck() || SDK::minecraft->IsInGuiState() || Menu::open)
    {
        if (m_isHoldingCtrl)
        {
            sendKey(VK_CONTROL, false);
            m_isHoldingCtrl = false;
        }
        return;
    }

    bool isPressingW = Keys::IsKeyPressed(0x57);

    if (isPressingW && !m_isHoldingCtrl)
    {
        sendKey(VK_CONTROL, true);
        m_isHoldingCtrl = true;
    }
    else if (!isPressingW && m_isHoldingCtrl)
    {
        sendKey(VK_CONTROL, false);
        m_isHoldingCtrl = false;
    }
}

void Sprint::RenderMenu()
{
    Menu::ToggleWithKeybind(&settings::S_Enabled, settings::S_Key);
}
