#include "configManager.h"

bool ConfigManager::LoadConfig(const char* name)
{
	std::ifstream file(ConfigManager::GetDocumentsPath() + name + FILE_SUFFIX);

	if (!file.is_open())
		return false;

	json j;
	file >> j;
	file.close();

	if (!JsonToSettings(j))
		return false;

	return true;
}

bool ConfigManager::SaveConfig(const char* name)
{
	json j;

	if (!SettingsToJson(j))
		return false;

	std::ofstream file(ConfigManager::GetDocumentsPath() + name + FILE_SUFFIX);

	if (!file.is_open())
		return false;

	file << j.dump();
	file.close();

	return true;
}

std::vector<std::string> ConfigManager::GetConfigList()
{
	std::vector<std::string> configs;

	// check if the directory exists, if not create it
	if (!std::filesystem::exists(ConfigManager::GetDocumentsPath()))
		std::filesystem::create_directory(ConfigManager::GetDocumentsPath());

	for (const auto& entry : std::filesystem::directory_iterator(ConfigManager::GetDocumentsPath()))
	{
		if (entry.path().extension() == FILE_SUFFIX/* || entry.path().extension() == ".json"*/)
			configs.push_back(entry.path().filename().replace_extension("").string());
	}

	return configs;
}

bool ConfigManager::SettingsToJson(json& j)
{
	// Menu
	j["Menu_AccentColor"] = settings::Menu_AccentColor;
	j["Menu_Watermark"] = settings::Menu_Watermark;
	j["Menu_DisableAllRendering"] = settings::Menu_DisableAllRendering;

	// ESP
	j["ESP_Enabled"] = settings::ESP_Enabled;
	j["ESP_Text"] = settings::ESP_Text;
	j["ESP_TextSize"] = settings::ESP_TextSize;
	j["ESP_TextColor"] = settings::ESP_TextColor;
	j["ESP_TextOutline"] = settings::ESP_TextOutline;
	j["ESP_TextOutlineColor"] = settings::ESP_TextOutlineColor;
	j["ESP_TextUnrenderDistance"] = settings::ESP_TextUnrenderDistance;
	j["ESP_FadeDistance"] = settings::ESP_FadeDistance;
	j["ESP_HealthBar"] = settings::ESP_HealthBar;
	j["ESP_BoxType"] = settings::ESP_BoxType;
	j["ESP_3DBoxColor"] = settings::ESP_3DBoxColor;
	j["ESP_3DBoxThickness"] = settings::ESP_3DBoxThickness;
	j["ESP_Box"] = settings::ESP_Box;
	j["ESP_BoxColor"] = settings::ESP_BoxColor;
	j["ESP_FilledBox"] = settings::ESP_FilledBox;
	j["ESP_FilledBoxColor"] = settings::ESP_FilledBoxColor;
	j["ESP_SecondFilledBoxColor"] = settings::ESP_SecondFilledBoxColor;
	j["ESP_Outline"] = settings::ESP_Outline;
	j["ESP_OutlineColor"] = settings::ESP_OutlineColor;

	// Array List
	j["AL_Enabled"] = settings::AL_Enabled;
	j["AL_renderPosition"] = settings::AL_renderPosition;
	j["AL_textSize"] = settings::AL_textSize;
	j["AL_textColor"] = settings::AL_textColor;
	j["AL_backgroundPadding"] = settings::AL_backgroundPadding;
	j["AL_backgroundColor"] = settings::AL_backgroundColor;

	// Radar
	j["Radar_Enabled"] = settings::Radar_Enabled;
	j["Radar_Radius"] = settings::Radar_Radius;
	j["Radar_RotateWithPlayer"] = settings::Radar_RotateWithPlayer;
	j["Radar_ShowNames"] = settings::Radar_ShowNames;
	j["Radar_Size"] = settings::Radar_Size;
	j["Radar_Square"] = settings::Radar_Square;
	j["Radar_Position"] = settings::Radar_Position;
	j["Radar_LocalPlayerColor"] = settings::Radar_LocalPlayerColor;
	j["Radar_PlayerColor"] = settings::Radar_PlayerColor;
	j["Radar_BackgroundColor"] = settings::Radar_BackgroundColor;

	// Aim Assist
	j["AA_Enabled"] = settings::AA_Enabled;
	j["AA_visibilityCheck"] = settings::AA_visibilityCheck;
	j["AA_aimAssistFeedback"] = settings::AA_aimAssistFeedback;
	j["AA_aimAssistFeedbackColor"] = settings::AA_aimAssistFeedbackColor;
	j["AA_fovCircle"] = settings::AA_fovCircle;
	j["AA_fovCircleColor"] = settings::AA_fovCircleColor;
	j["AA_aimKey"] = settings::AA_aimKey;
	j["AA_adaptive"] = settings::AA_adaptive;
	j["AA_adaptiveOffset"] = settings::AA_adaptiveOffset;
	j["AA_fov"] = settings::AA_fov;
	j["AA_smooth"] = settings::AA_smooth;
	j["AA_aimDistance"] = settings::AA_aimDistance;
	j["AA_randomYaw"] = settings::AA_randomYaw;
	j["AA_randomPitch"] = settings::AA_randomPitch;
	j["AA_targetPriority"] = settings::AA_targetPriority;

	// Reach
	j["Reach_Enabled"] = settings::Reach_Enabled;
	j["Reach_ReachDistance"] = settings::Reach_ReachDistance;

	// WTap
	j["WTap_Enabled"] = settings::WTap_Enabled;
	j["WTap_DelayBetween"] = settings::WTap_DelayBetween;
	j["WTap_LetGoDelay"] = settings::WTap_LetGoDelay;

	// Left Auto Clicker
	j["LAC_Enabled"] = settings::LAC_Enabled;
	j["LAC_leftMaxCps"] = settings::LAC_leftMaxCps;
	j["LAC_leftMinCps"] = settings::LAC_leftMinCps;
	j["LAC_ignoreBlocks"] = settings::LAC_ignoreBlocks;

	// Right Auto Clicker
	j["RAC_Enabled"] = settings::RAC_Enabled;
	j["RAC_rightMaxCps"] = settings::RAC_rightMaxCps;
	j["RAC_rightMinCps"] = settings::RAC_rightMinCps;
	j["RAC_blocksOnly"] = settings::RAC_blocksOnly;

	// Bridge Assist
	j["BA_Enabled"] = settings::BA_Enabled;
	j["BA_OnlyOnShift"] = settings::BA_OnlyOnShift;
	j["BA_PitchCheck"] = settings::BA_PitchCheck;
	j["BA_BlockCheck"] = settings::BA_BlockCheck;

	return true;
}

bool ConfigManager::JsonToSettings(const json& j)
{
	// Menu
	ConfigManager::GetJsonValue(j, settings::Menu_AccentColor, "Menu_AccentColor");
	ConfigManager::GetJsonValue(j, settings::Menu_Watermark, "Menu_Watermark");
	ConfigManager::GetJsonValue(j, settings::Menu_DisableAllRendering, "Menu_DisableAllRendering");

	// ESP
	ConfigManager::GetJsonValue(j, settings::ESP_Enabled, "ESP_Enabled");
	ConfigManager::GetJsonValue(j, settings::ESP_Text, "ESP_Text");
	ConfigManager::GetJsonValue(j, settings::ESP_TextSize, "ESP_TextSize");
	ConfigManager::GetJsonValue(j, settings::ESP_TextColor, "ESP_TextColor");
	ConfigManager::GetJsonValue(j, settings::ESP_TextOutline, "ESP_TextOutline");
	ConfigManager::GetJsonValue(j, settings::ESP_TextOutlineColor, "ESP_TextOutlineColor");
	ConfigManager::GetJsonValue(j, settings::ESP_TextUnrenderDistance, "ESP_TextUnrenderDistance");
	ConfigManager::GetJsonValue(j, settings::ESP_FadeDistance, "ESP_FadeDistance");
	ConfigManager::GetJsonValue(j, settings::ESP_HealthBar, "ESP_HealthBar");
	ConfigManager::GetJsonValue(j, settings::ESP_BoxType, "ESP_BoxType");
	ConfigManager::GetJsonValue(j, settings::ESP_3DBoxColor, "ESP_3DBoxColor");
	ConfigManager::GetJsonValue(j, settings::ESP_3DBoxThickness, "ESP_3DBoxThickness");
	ConfigManager::GetJsonValue(j, settings::ESP_Box, "ESP_Box");
	ConfigManager::GetJsonValue(j, settings::ESP_BoxColor, "ESP_BoxColor");
	ConfigManager::GetJsonValue(j, settings::ESP_FilledBox, "ESP_FilledBox");
	ConfigManager::GetJsonValue(j, settings::ESP_FilledBoxColor, "ESP_FilledBoxColor");
	ConfigManager::GetJsonValue(j, settings::ESP_SecondFilledBoxColor, "ESP_SecondFilledBoxColor");
	ConfigManager::GetJsonValue(j, settings::ESP_Outline, "ESP_Outline");
	ConfigManager::GetJsonValue(j, settings::ESP_OutlineColor, "ESP_OutlineColor");

	// Array List
	ConfigManager::GetJsonValue(j, settings::AL_Enabled, "AL_Enabled");
	ConfigManager::GetJsonValue(j, settings::AL_renderPosition, "AL_renderPosition");
	ConfigManager::GetJsonValue(j, settings::AL_textSize, "AL_textSize");
	ConfigManager::GetJsonValue(j, settings::AL_textColor, "AL_textColor");
	ConfigManager::GetJsonValue(j, settings::AL_backgroundPadding, "AL_backgroundPadding");
	ConfigManager::GetJsonValue(j, settings::AL_backgroundColor, "AL_backgroundColor");

	// Radar
	ConfigManager::GetJsonValue(j, settings::Radar_Enabled, "Radar_Enabled");
	ConfigManager::GetJsonValue(j, settings::Radar_Radius, "Radar_Radius");
	ConfigManager::GetJsonValue(j, settings::Radar_RotateWithPlayer, "Radar_RotateWithPlayer");
	ConfigManager::GetJsonValue(j, settings::Radar_ShowNames, "Radar_ShowNames");
	ConfigManager::GetJsonValue(j, settings::Radar_Size, "Radar_Size");
	ConfigManager::GetJsonValue(j, settings::Radar_Square, "Radar_Square");
	ConfigManager::GetJsonValue(j, settings::Radar_Position, "Radar_Position");
	ConfigManager::GetJsonValue(j, settings::Radar_LocalPlayerColor, "Radar_LocalPlayerColor");
	ConfigManager::GetJsonValue(j, settings::Radar_PlayerColor, "Radar_PlayerColor");
	ConfigManager::GetJsonValue(j, settings::Radar_BackgroundColor, "Radar_BackgroundColor");

	// Aim Assist
	ConfigManager::GetJsonValue(j, settings::AA_Enabled, "AA_Enabled");
	ConfigManager::GetJsonValue(j, settings::AA_visibilityCheck, "AA_visibilityCheck");
	ConfigManager::GetJsonValue(j, settings::AA_aimAssistFeedback, "AA_aimAssistFeedback");
	ConfigManager::GetJsonValue(j, settings::AA_aimAssistFeedbackColor, "AA_aimAssistFeedbackColor");
	ConfigManager::GetJsonValue(j, settings::AA_fovCircle, "AA_fovCircle");
	ConfigManager::GetJsonValue(j, settings::AA_fovCircleColor, "AA_fovCircleColor");
	ConfigManager::GetJsonValue(j, settings::AA_aimKey, "AA_aimKey");
	ConfigManager::GetJsonValue(j, settings::AA_adaptive, "AA_adaptive");
	ConfigManager::GetJsonValue(j, settings::AA_adaptiveOffset, "AA_adaptiveOffset");
	ConfigManager::GetJsonValue(j, settings::AA_fov, "AA_fov");
	ConfigManager::GetJsonValue(j, settings::AA_smooth, "AA_smooth");
	ConfigManager::GetJsonValue(j, settings::AA_aimDistance, "AA_aimDistance");
	ConfigManager::GetJsonValue(j, settings::AA_randomYaw, "AA_randomYaw");
	ConfigManager::GetJsonValue(j, settings::AA_randomPitch, "AA_randomPitch");
	ConfigManager::GetJsonValue(j, settings::AA_targetPriority, "AA_targetPriority");

	// Reach
	ConfigManager::GetJsonValue(j, settings::Reach_Enabled, "Reach_Enabled");
	ConfigManager::GetJsonValue(j, settings::Reach_ReachDistance, "Reach_ReachDistance");

	// WTap
	ConfigManager::GetJsonValue(j, settings::WTap_Enabled, "WTap_Enabled");
	ConfigManager::GetJsonValue(j, settings::WTap_DelayBetween, "WTap_DelayBetween");
	ConfigManager::GetJsonValue(j, settings::WTap_LetGoDelay, "WTap_LetGoDelay");

	// Left Auto Clicker
	ConfigManager::GetJsonValue(j, settings::LAC_Enabled, "LAC_Enabled");
	ConfigManager::GetJsonValue(j, settings::LAC_leftMaxCps, "LAC_leftMaxCps");
	ConfigManager::GetJsonValue(j, settings::LAC_leftMinCps, "LAC_leftMinCps");
	ConfigManager::GetJsonValue(j, settings::LAC_ignoreBlocks, "LAC_ignoreBlocks");

	// Right Auto Clicker
	ConfigManager::GetJsonValue(j, settings::RAC_Enabled, "RAC_Enabled");
	ConfigManager::GetJsonValue(j, settings::RAC_rightMaxCps, "RAC_rightMaxCps");
	ConfigManager::GetJsonValue(j, settings::RAC_rightMinCps, "RAC_rightMinCps");
	ConfigManager::GetJsonValue(j, settings::RAC_blocksOnly, "RAC_blocksOnly");

	// Bridge Assist
	ConfigManager::GetJsonValue(j, settings::BA_Enabled, "BA_Enabled");
	ConfigManager::GetJsonValue(j, settings::BA_OnlyOnShift, "BA_OnlyOnShift");
	ConfigManager::GetJsonValue(j, settings::BA_PitchCheck, "BA_PitchCheck");
	ConfigManager::GetJsonValue(j, settings::BA_BlockCheck, "BA_BlockCheck");

	return true;
}

std::string ConfigManager::GetDocumentsPath()
{
	char path[MAX_PATH];

	// Get the path to the Documents folder (CSIDL_PERSONAL refers to "My Documents")
	if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path) == S_OK) {
		return std::string(path) + "/Fusion+/";  // Add your specific subfolder
	}
	else {
		std::cerr << "Failed to get Documents folder." << std::endl;
		return "";
	}
}

bool ConfigManager::LoadFriends()
{
	std::ifstream file(ConfigManager::GetDocumentsPath() + "friends.json");

	if (!file.is_open())
		return false;

	json j;
	file >> j;

	if (!j.is_array())
		return false;

	settings::friends.clear();

	for (const auto& friendName : j)
	{
		settings::friends.push_back(friendName.get<std::string>());
	}

	return true;
}

bool ConfigManager::SaveFriends()
{
	json j;

	for (const auto& friendName : settings::friends)
	{
		j.push_back(friendName);
	}

	std::ofstream file(ConfigManager::GetDocumentsPath() + "friends.json");

	if (!file.is_open())
		return false;

	file << j.dump();
	file.close();

	return true;
}

bool ConfigManager::AddFriend(const std::string& name)
{
	if (IsFriend(name))
		return false;

	settings::friends.push_back(name);

	return SaveFriends();
}

bool ConfigManager::RemoveFriend(const std::string& name)
{
	auto it = std::find(settings::friends.begin(), settings::friends.end(), name);

	if (it == settings::friends.end())
		return false;

	settings::friends.erase(it);

	return SaveFriends();
}

bool ConfigManager::IsFriend(const std::string& name)
{
	return std::find(settings::friends.begin(), settings::friends.end(), name) != settings::friends.end();
}
