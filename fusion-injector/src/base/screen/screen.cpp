#include "screen.h"

#include <string>
#include <windows.h>

#include "process/process.h"
#include "folder/folder.h"
#include "update/update.h"
#include "base.h"
#include <iostream>

#include <thread>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 400

void Screen::SetupStyle()
{
	// Deep Dark style by janekb04 from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 7.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(10.0f, 4.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
	style.CellPadding = ImVec2(6.0f, 6.0f);
	style.IndentSpacing = 25.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.9200000166893005f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.2899999916553497f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.239999994635582f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.3600000143051147f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 0.3300000131130219f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3600000143051147f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.3499999940395355f);
}

std::atomic<bool> dllUpdating(false);
std::atomic<bool> injectorUpdating(false);
std::atomic<bool> updateFinished(false);

std::string updateStatus = "";

static void UpdateDllThread()
{
	dllUpdating = true;
	updateStatus = "Updating DLL...";
	if (BaseUtils::UpdateDll(Update::oldDllPath)) {
		updateStatus = "DLL Updated!";
	}
	else {
		updateStatus = "DLL Update Failed!";
	}
	dllUpdating = false;
}

static void UpdateInjectorThread()
{
	injectorUpdating = true;
	updateStatus = "Updating Injector...";
	if (BaseUtils::UpdateInjector()) {
		updateStatus = "Injector Updated! Launching...";
		std::this_thread::sleep_for(std::chrono::seconds(2)); 
		std::string path = FolderManager::GetCurrentDir() + "fusion-plus_v" + BaseUtils::new_injetor_version + ".exe";
		std::wstring wpath = std::wstring(path.begin(), path.end());
		ShellExecute(NULL, L"open", wpath.c_str(), NULL, NULL, SW_SHOWNORMAL);
		PostMessage(HWND_BROADCAST, WM_CLOSE, 0, 0);
	}
	else {
		updateStatus = "Injector Update Failed!";
	}
	injectorUpdating = false;
}

static void AnimateUpdateStatus()
{
	static int dotCount = 3;
	static int lastUpdateTime = 0;
	int currentTime = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count() / 1000000000);

	// Update every 500 milliseconds (for example)
	if (currentTime - lastUpdateTime >= 1)
	{
		dotCount = (dotCount + 1) % 4;  // 0, 1, 2, 3 dots
		lastUpdateTime = currentTime;
	}

	// Generate the status message based on the update state
	std::string dotStr(dotCount, '.');

	if (dllUpdating && injectorUpdating)
	{
		updateStatus = "Updating DLL and Injector" + dotStr;
	}
	else if (dllUpdating)
	{
		updateStatus = "Updating DLL" + dotStr;
	}
	else if (injectorUpdating)
	{
		updateStatus = "Updating Injector" + dotStr;
	}
	else
	{
		updateStatus = "Update Finished!";
	}
}

#include <iostream>

bool Screen::Render()
{
	static bool update = BaseUtils::IsInjectorUpdated();
	static bool dllUpdated = false;

	static std::vector<ProcessManager::WindowInfo> processes;
	static int selectedProcess = 0;

	static int renderUpdates = 99;
	renderUpdates++;
	if (renderUpdates % 100 == 0)
	{
		ProcessManager::GetMinecraftProcesses(processes);
		if (selectedProcess >= processes.size())
		{
			selectedProcess = 0;
		}
	}

	std::string dllVersion = FolderManager::GetVersionStringDll();
	std::string injectorVersion = INJECTOR_VERSION;

	bool minecraft_running = processes.size() > 0;
	bool multiple_minecraft_instances = processes.size() > 1;

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::Begin("Fusion Injector", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
	ImGui::PopStyleVar();

	if (!update)
	{
		if (ImGui::Button("Update Available"))
		{
			std::thread injectorUpdateThread(UpdateInjectorThread);
			injectorUpdateThread.detach();
			update = false;
		}
	}

	std::string text = "Inject | " + (processes.size() > 0 ? processes[selectedProcess].processName : "NONE");
	float stringWidth = ImGui::CalcTextSize(text.c_str()).x + 40;
	float stringHeight = ImGui::CalcTextSize(text.c_str()).y + 40;
	ImGui::SetCursorPosY((ImGui::GetWindowHeight() / 2) - (stringHeight / 2));
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2) - (stringWidth / 2));

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
	if (ImGui::Button(text.c_str()))
	{
		if (minecraft_running)
		{
			if (ProcessManager::InjectDLL(processes[selectedProcess].processId, FolderManager::GetDllPath().c_str()))
			{
			}
			else
			{
				MessageBoxA(NULL, "Failed to inject!", "Fusion Injector", MB_OK | MB_ICONERROR);
			}
		}
		else
		{
			MessageBoxA(NULL, "Minecraft is not running!", "Fusion Injector", MB_OK | MB_ICONERROR);
		}
	}
	ImGui::PopStyleVar();

	if (multiple_minecraft_instances)
	{
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 93);
		if (ImGui::Button("Switch Minecraft Instance"))
		{
			selectedProcess++;
			if (selectedProcess >= processes.size())
			{
				selectedProcess = 0;
			}
		}
	}

	AnimateUpdateStatus();
	if (dllUpdating || injectorUpdating)
	{
		int textWidth = ImGui::CalcTextSize(updateStatus.c_str()).x;
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - textWidth / 2.0f);
		ImGui::SetCursorPosY(10);
		ImGui::Text("%s", updateStatus.c_str());
	}

	// Final Buttons
	ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 36);
	if (ImGui::Button("Discord"))
	{
		ShellExecute(0, L"open", L"https://discord.gg/EWkhAPRdwb", 0, 0, SW_SHOWNORMAL);
	}
	ImGui::SameLine();
	if (ImGui::Button("Github"))
	{
		ShellExecute(0, L"open", L"https://github.com/h1meji/fusion-plus", 0, 0, SW_SHOWNORMAL);
	}

	std::string version = " Fusion+ v" + dllVersion + " | Injector v" + injectorVersion;
	ImGui::SetCursorPosY(ImGui::GetWindowHeight() - ImGui::CalcTextSize(version.c_str()).y - 8);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - ImGui::CalcTextSize(version.c_str()).x - 5);
	ImGui::Text(version.c_str());

	ImGui::End();

	if (!BaseUtils::IsDllUpdated() && !dllUpdated)
	{
		Update::oldDllPath = FolderManager::GetDllPath();
		std::thread dllUpdateThread(UpdateDllThread);
		dllUpdateThread.detach();
		dllUpdated = true;
	}
	else
	{
		dllUpdated = true;
	}

	return true;
}