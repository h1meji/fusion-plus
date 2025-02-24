#include "blockReach.h"
#include <imgui/imgui.h>
#include <menu/menu.h>

void BlockReach::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("br_header", ImVec2(425, renderSettings ? 166 : 35), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(138, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::BR_Enabled);
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
			if (ImGui::BeginChild("br_settings", ImVec2(425, 121), false))
			{
				Menu::Slider(139, "Reach Distance", ImVec2(225, 0), &settings::BR_ReachDistance, 0.0f, 10.0f, "%.1f");
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

void BlockReach::onGetBlockReachDistance(JNIEnv* env, bool* cancel)
{
	if (settings::BR_Enabled)
	{
		JavaHook::set_return_value<float>(cancel, settings::BR_ReachDistance);
		*cancel = true;
		return;
	}
	*cancel = false;
}

void BlockReach::getBlockReachDistance_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Java::Env) return;
	JNIEnv* env = thread->get_env();
	JavaHook::JNIFrame jniFrame(env);
	BlockReach::onGetBlockReachDistance(env, cancel);
	return;
}
