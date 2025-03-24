#include "clientBrandChanger.h"
#include <java/javahook.h>
#include <sdk/sdk.h>
#include <imgui/imgui.h>

#include "menu/menu.h"
#include <sdk/net/minecraft/client/ClientBrandRetriever.h>

std::once_flag setOriginalClientBrandFlag;
void ClientBrandChanger::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::CBC_Enabled, settings::CBC_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	static char clientBrand[128] = "";
	std::call_once(setOriginalClientBrandFlag, []() {
		if (settings::CBC_ClientBrand.empty())
		{
			settings::CBC_ClientBrand = SDK::Minecraft->OriginalClientBrand;
			strcpy_s(clientBrand, settings::CBC_ClientBrand.c_str());
		}
		else
		{
			strcpy_s(clientBrand, settings::CBC_ClientBrand.c_str());
		}
	});
	ImGui::SetNextItemWidth(ImGui::GetWindowSize().x + 190.f);
	ImGui::InputText("##clientBrandInput", clientBrand, IM_ARRAYSIZE(clientBrand));

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	if (Menu::Button("Reset"))
	{
		settings::CBC_ClientBrand = SDK::Minecraft->OriginalClientBrand;
		strcpy_s(clientBrand, settings::CBC_ClientBrand.c_str());
	}
	if (Menu::Button("Vanilla"))
	{
		settings::CBC_ClientBrand = "vanilla";
		strcpy_s(clientBrand, settings::CBC_ClientBrand.c_str());
	}
}

void ClientBrandChanger::onGetClientModName(JNIEnv* env, bool* cancel)
{
    try {
        if (!env || !cancel || !SDK::Minecraft) {
            *cancel = false;
            return;
        }

        std::string brandToUse;
        if (settings::CBC_Enabled && !settings::CBC_ClientBrand.empty()) {
            brandToUse = settings::CBC_ClientBrand;
        } else {
			brandToUse = SDK::Minecraft->OriginalClientBrand;
        }

        jstring new_name = env->NewStringUTF(brandToUse.c_str());
        if (new_name) {
            JavaHook::set_return_value<void*>(cancel, *(void**)new_name);
            *cancel = true;
        } else {
            *cancel = false;
        }
    } catch (...) {
        *cancel = false;
    }
}

void ClientBrandChanger::getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
    try {
        if (!thread || !cancel) return;
        
        JNIEnv* env = thread->get_env();
        if (!env) {
            *cancel = false;
            return;
        }

        JavaHook::JNIFrame jniFrame(env);
        onGetClientModName(env, cancel);
    } catch (...) {
        if (cancel) *cancel = false;
    }
}
