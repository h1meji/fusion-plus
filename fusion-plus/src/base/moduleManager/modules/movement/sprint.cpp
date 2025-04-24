#include "sprint.h"

#include "moduleManager/commonData.h"
#include "menu/menu.h"
#include "util/keys.h"

void Sprint::Update()
{
    if (!settings::S_Enabled || !CommonData::SanityCheck() || SDK::minecraft->IsInGuiState() || Menu::open)
    {
        if (m_isHoldingCtrl)
        {
            Keys::SendKey(VK_CONTROL, false);
            m_isHoldingCtrl = false;
        }
        return;
    }

    bool isPressingW = Keys::IsKeyPressed(0x57);

    if (isPressingW && !m_isHoldingCtrl)
    {
        Keys::SendKey(VK_CONTROL, true);
        m_isHoldingCtrl = true;
    }
    else if (!isPressingW && m_isHoldingCtrl)
    {
        Keys::SendKey(VK_CONTROL, false);
        m_isHoldingCtrl = false;
    }
}

void Sprint::RenderMenu()
{
    Menu::ToggleWithKeybind(&settings::S_Enabled, settings::S_Key);
}
