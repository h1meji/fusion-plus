#pragma once

#include <string>

struct settings {
	// Menu
	inline static float Menu_AccentColor[4]{ 0, 0.4, 0.4, 1.0f };
	inline static bool Menu_Watermark = true;
	inline static bool Menu_DisableAllRendering = false;

	// ESP
	inline static bool ESP_Enabled = false;
	inline static bool ESP_Text = true;
	inline static float ESP_TextSize = 18;
	inline static float ESP_TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	inline static bool ESP_TextOutline = true;
	inline static float ESP_TextOutlineColor[4]{ 0, 0, 0, 1.0f };
	inline static float ESP_TextUnrenderDistance = 14.0f;
	inline static float ESP_FadeDistance = 3.0f;
	inline static bool ESP_HealthBar = true;
	inline static int ESP_BoxType = 0;
	inline static const char* ESP_BoxTypeList[4]{ "Dynamic 2D Box", "3D Box" };
	inline static float ESP_3DBoxColor[4]{ 0, 0, 0, 1 };
	inline static float ESP_3DBoxThickness = 1.0f;
	inline static bool ESP_Box = true;
	inline static float ESP_BoxColor[4]{ 0, 0, 0, 1 };
	inline static bool ESP_FilledBox = true;
	inline static float ESP_FilledBoxColor[4]{ 0, 0, 0, 0.15f };
	inline static float ESP_SecondFilledBoxColor[4]{ 0, 0, 0, 0.15f };
	inline static bool ESP_Outline = true;
	inline static float ESP_OutlineColor[4]{ 0, 0, 0, 0.25 };

	// Array List
	inline static bool AL_Enabled = false;
	inline static int AL_renderPosition = 1;
	inline static const char* AL_renderPositionList[4]{ "Top Left", "Top Right", "Bottom Left", "Bottom Right" };
	inline static float AL_textSize = 18;
	inline static float AL_textColor[4]{ 1, 1, 1, 1 };
	inline static float AL_backgroundPadding = 5;
	inline static float AL_backgroundColor[4]{ 0, 0, 0, 0.5 };

	// Radar
	inline static bool Radar_Enabled = false;
	inline static float Radar_Radius = 50.0f;
	inline static bool Radar_RotateWithPlayer = true;
	inline static bool Radar_ShowNames = false;
	inline static float Radar_Size = 200.0f;
	inline static bool Radar_Square = true;
	inline static float Radar_Position[2]{ 10, 10 };
	inline static float Radar_LocalPlayerColor[4]{ 1, 0.5, 0, 1 };
	inline static float Radar_PlayerColor[4]{ 1, 1, 1, 1 };
	inline static float Radar_BackgroundColor[4]{ 0, 0, 0, 0.5 };

	// Block ESP
	inline static bool BlockESP_Enabled = false;
	inline static int BlockESP_TargetID = 35;

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

	// WTap
	inline static bool WTap_Enabled = false;
	inline static int WTap_DelayBetween = 50;
	inline static int WTap_LetGoDelay = 10;

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

	// Bridge Assist
	inline static bool BA_Enabled = false;
	inline static bool BA_OnlyOnShift = true;
	inline static float BA_PitchCheck = 61.0f;
	inline static int BA_BlockCheck = 1;
};