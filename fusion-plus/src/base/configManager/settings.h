#pragma once

#include <string>

struct settings {
	// Menu
	inline static float Menu_AccentColor[4]{ 0, 0.4, 0.4, 1.0f };

	// ESP
	inline static bool ESP_Enabled = false;
	inline static bool ESP_Box = true;
	inline static float ESP_BoxColor[4]{ 0, 0, 0, 1 };
	inline static bool ESP_FilledBox = true;
	inline static float ESP_FilledBoxColor[4]{ 0, 0, 0, 0.15f };
	inline static float ESP_SecondFilledBoxColor[4]{ 0, 0, 0, 0.15f };
	inline static bool ESP_Outline = true;
	inline static float ESP_OutlineColor[4]{ 0, 0, 0, 0.25 };
	inline static bool ESP_Text = true;
	inline static float ESP_TextSize = 18;
	inline static float ESP_TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	inline static bool ESP_TextOutline = true;
	inline static float ESP_TextOutlineColor[4]{ 0, 0, 0, 1.0f };
	inline static float ESP_TextUnrenderDistance = 14.0f;
	inline static float ESP_FadeDistance = 3.0f;
	inline static bool ESP_HealthBar = true;

	// Array List
	inline static bool AL_Enabled = false;
	inline static int AL_renderPosition = 1;
	inline static const char* AL_renderPositionList[4]{ "Top Left", "Top Right", "Bottom Left", "Bottom Right" };
	inline static float AL_textSize = 18;
	inline static float AL_textColor[4]{ 1, 1, 1, 1 };
	inline static float AL_backgroundPadding = 5;
	inline static float AL_backgroundColor[4]{ 0, 0, 0, 0.5 };

	// Aim Assist
	inline static bool AA_Enabled = false;
	inline static bool AA_visibilityCheck = true;
	inline static bool AA_aimAssistFeedback = true;
	inline static float AA_aimAssistFeedbackColor[4]{ 1, 1, 1, 1 };
	inline static bool AA_fovCircle = true;
	inline static float AA_fovCircleColor[4]{ 1, 1, 1, 1 };
	inline static bool AA_aimKey = true;
	inline static bool AA_adaptive = true;
	inline static float AA_adaptiveOffset = 3;
	inline static float AA_fov = 35.0f;
	inline static float AA_smooth = 15.f;
	inline static float AA_aimDistance = 4.f;
	inline static float AA_randomYaw = 2;
	inline static float AA_randomPitch = .075f;
	inline static int AA_targetPriority = 2;
	inline static const char* AA_targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };

	// Reach
	inline static bool Reach_Enabled = false;
	inline static float Reach_ReachDistance = 3.0f;

	// Left Auto Clicker
	inline static bool LAC_Enabled = false;
	inline static float LAC_leftMaxCps = 18;
	inline static float LAC_leftMinCps = 13;
	inline static bool LAC_ignoreBlocks = true;

	// Right Auto Clicker
	inline static bool RAC_Enabled = false;
	inline static float RAC_rightMaxCps = 15;
	inline static float RAC_rightMinCps = 12;
	inline static bool RAC_blocksOnly = true;
};