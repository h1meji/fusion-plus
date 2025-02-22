#include "clientBrandChanger.h"
#include <java/javahook.h>
#include <sdk/sdk.h>
#include <imgui/imgui.h>

#include "menu/menu.h"

void ClientBrandChanger::Update()
{
}

std::once_flag setOriginalClientBrandFlag;
void ClientBrandChanger::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("cbc_header", ImVec2(425, renderSettings ? 166 : 35), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(134, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::CBC_Enabled);
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
			if (ImGui::BeginChild("cbc_settings", ImVec2(425, 121), false))
			{
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

				if (Menu::TextInput(135, "Client Name", ImVec2(614, 0), clientBrand, sizeof(clientBrand)))
				{
					settings::CBC_ClientBrand = clientBrand;
				}

				Menu::TextInputButton(1350, "Client Name", ImVec2(614, 0), clientBrand, sizeof(clientBrand));

				if (Menu::Button(136, "Reset", ImVec2(384, 0)))
				{
					settings::CBC_ClientBrand = SDK::Minecraft->OriginalClientBrand;
					strcpy_s(clientBrand, settings::CBC_ClientBrand.c_str());
				}

				if (Menu::Button(137, "Vanilla", ImVec2(384, 0)))
				{
					settings::CBC_ClientBrand = "vanilla";
					strcpy_s(clientBrand, settings::CBC_ClientBrand.c_str());
				}
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

void ClientBrandChanger::onGetClientModName(JNIEnv* env, bool* cancel)
{
	jobject new_name = env->NewStringUTF("vanilla");
	if (!settings::CBC_Enabled || settings::CBC_ClientBrand == "")
	{
		new_name = env->NewStringUTF(SDK::Minecraft->OriginalClientBrand.c_str());
	}
	else
	{
		new_name = env->NewStringUTF(settings::CBC_ClientBrand.c_str());
	}

	JavaHook::set_return_value<void*>(cancel, *(void**)new_name);
	*cancel = true;
}

void ClientBrandChanger::getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Java::Env) return;
	JNIEnv* env = thread->get_env();
	JavaHook::JNIFrame jniFrame(env);
	onGetClientModName(env, cancel);
	return;
}
