#pragma once

#include <string>
#include <vector>

struct settings {
	inline static std::vector<std::string> friends;

	// Menu
	inline static float Menu_AccentColor[4]{ 0, 0.4f, 0.4f, 1.0f };
	inline static bool Menu_GUIMovement = false;
	inline static bool Menu_Watermark = true;
	inline static bool Menu_DisableAllRendering = false;
	inline static bool Menu_ShowHiddenCategories = false;
	inline static std::vector<std::string> Menu_HiddenCategoriesList{ "TnT Tag" };

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
	inline static bool ESP_HighlightFriends = true;
	inline static float ESP_Friend3DBoxColor[4]{ 0, 1, 0, 1 };
	inline static float ESP_FriendBoxColor[4]{ 0, 1, 0, 1 };
	inline static float ESP_FriendFilledBoxColor[4]{ 0, 1, 0, 0.15f };
	inline static float ESP_FriendSecondFilledBoxColor[4]{ 0, 1, 0, 0.15f };
	inline static float ESP_FriendOutlineColor[4]{ 0, 1, 0, 0.25 };

	// Array List
	inline static bool AL_Enabled = false;
	inline static int AL_renderPosition = 1;
	inline static const char* AL_renderPositionList[4]{ "Top Left", "Top Right", "Bottom Left", "Bottom Right" };
	inline static float AL_textSize = 11;
	inline static float AL_textColor[4]{ 1.f, 1.f, 1.f, 1.f };
	inline static float AL_backgroundPadding = 5;
	inline static float AL_backgroundColor[4]{ 0.f, 0.f, 0.f, 0.8f };
	inline static float AL_backgroundRoundness = 5.f;

	// New Settings for array list
    inline static bool AL_rgbEnabled = false;
    inline static int AL_colorMode = 0;
    inline static const char* AL_colorModeList[16]{ 
	    "Static", "RGB Wave", "Purple Rain", "Golden Luxury", "Red Flow", "Neon Pulse",
	    "Ocean Depth", "Forest Mystical", "Sunset Dream", "Cotton Candy", "Magma Flow",
        "Aqua Breeze", "Cosmic Wave", "Cherry Blossom", "Cyberpunk"
    };
    inline static float AL_rgbSpeed = 1.0f;
    inline static bool AL_gradientEnabled = false;
    inline static float AL_gradientStartColor[4]{ 1.0f, 0.0f, 0.0f, 1.0f };
    inline static float AL_gradientEndColor[4]{ 0.0f, 0.0f, 1.0f, 1.0f };
	inline static bool AL_outlineEnabled = false;
    inline static float AL_outlineThickness = 1.0f;
    inline static float AL_outlineColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline static bool AL_outlineRGB = true;
	
	// Radar
	inline static bool Radar_Enabled = false;
	inline static float Radar_Radius = 50.0f;
	inline static bool Radar_RotateWithPlayer = true;
	inline static bool Radar_ShowNames = false;
	inline static float Radar_Size = 200.0f;
	inline static float Radar_SquareRoundness = 10.0f;
	inline static float Radar_Position[2]{ 10, 10 };
	inline static float Radar_LocalPlayerColor[4]{ 1, 0.5, 0, 1 };
	inline static float Radar_PlayerColor[4]{ 1, 1, 1, 1 };
	inline static float Radar_FriendColor[4]{ 0, 1, 0, 1 };
	inline static float Radar_BackgroundColor[4]{ 0.f, 0.f, 0.f, 0.8f };

	// Block ESP
	inline static bool BlockESP_Enabled = false;
	inline static int BlockESP_TargetID = 35;

	// Aim Assist
	inline static bool AA_Enabled = false;
	inline static bool AA_visibilityCheck = true;
	inline static bool AA_sprintCheck = false;
	inline static bool AA_blockBreakCheck = true;
	inline static bool AA_weaponOnly = true;
	inline static bool AA_invisibleCheck = true;
	inline static bool AA_mousePressCheck = true;
	inline static bool AA_mouseMoveCheck = false;
	inline static bool AA_aimAssistFeedback = true;
	inline static float AA_aimAssistFeedbackColor[4]{ 1.f, 1.f, 1.f, 1.f };
	inline static bool AA_fovCircle = true;
	inline static float AA_fovCircleColor[4]{ 1.f, 1.f, 1.f, 1.f };
	inline static bool AA_adaptive = true;
	inline static float AA_adaptiveOffset = 3.f;
	inline static float AA_fov = 35.0f;
	inline static float AA_smooth = 15.f;
	inline static float AA_aimDistance = 4.f;
	inline static float AA_randomYaw = 2;
	inline static float AA_randomPitch = .075f;
	inline static int AA_targetPriority = 2;
	inline static const char* AA_targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
	inline static bool AA_ignoreFriends = true;

	// Reach
	inline static bool Reach_Enabled = false;
	inline static float Reach_ReachDistance = 3.0f;

	// Sprint Reset
	inline static bool SR_Enabled = false;
	inline static float SR_DelayBetween = .5f;
	inline static float SR_LetGoDelay = .05f;

	// Sprint
	inline static bool S_Enabled = false;

	// Left Auto Clicker
	inline static bool LAC_Enabled = false;
	inline static float LAC_leftMaxCps = 18;
	inline static float LAC_leftMinCps = 13;
	inline static bool LAC_ignoreBlocks = true;
	inline static bool LAC_swordBlock = true;
	inline static bool LAC_weaponOnly = false;

	// Right Auto Clicker
	inline static bool RAC_Enabled = false;
	inline static float RAC_rightMaxCps = 15;
	inline static float RAC_rightMinCps = 12;
	inline static bool RAC_blocksOnly = true;

	// Bridge Assist
	inline static bool BA_Enabled = false;
	inline static bool BA_OnlyOnShift = true;
	inline static bool BA_IgnoreForwardsMovement = true;
	inline static bool BA_AutoSwap = false;
	inline static float BA_PitchCheck = 61.0f;
	inline static int BA_BlockCheck = 1;

	// Velocity
	inline static bool Velocity_Enabled = false;
	inline static int Velocity_Mode = 0;
	inline static const char* Velocity_ModeList[0]{ "Jump Reset" };
	inline static float Velocity_JRReactionTime = 0.1f;
	inline static int Velocity_JRChange = 80;

	// Chest Stealer
	inline static bool CS_Enabled = false;
	inline static int CS_Key = 0x58; // X
	inline static int CS_Delay = 50;
	inline static std::vector<std::pair<int, int>> CS_Items{ };

	// Inventory Sorter
	inline static bool IS_Enabled = false;
	inline static int IS_Key = 0x5A; // Z
	inline static int IS_Delay = 50;

	// Client Brand Changer
	inline static bool CBC_Enabled = false;
	inline static std::string CBC_ClientBrand;

	// Block Reach
	inline static bool BR_Enabled = false;
	inline static float BR_ReachDistance = 4.5f;

	// Weapon
	inline static bool Weapon_Sword = true;
	inline static bool Weapon_Axe = false;
	inline static bool Weapon_Stick = false;
	inline static bool Weapon_Fist = false;

	// Tag Back
	inline static bool TB_Enabled = false;
	inline static bool TB_visibilityCheck = true;
	inline static bool TB_aimAssistFeedback = true;
	inline static float TB_aimAssistFeedbackColor[4]{ 1, 1, 1, 1 };
	inline static bool TB_fovCircle = true;
	inline static float TB_fovCircleColor[4]{ 1, 1, 1, 1 };
	inline static bool TB_adaptive = true;
	inline static float TB_adaptiveOffset = 3;
	inline static float TB_fov = 35.0f;
	inline static float TB_smooth = 15.f;
	inline static float TB_randomYaw = 2;
	inline static float TB_randomPitch = .075f;
	inline static int TB_targetPriority = 2;
	inline static const char* TB_targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
	inline static bool TB_ignoreFriends = true;
	inline static bool TB_autoClick = true;
	inline static int TB_maxCps = 15;
	inline static int TB_minCps = 10;

	// IT Esp
	inline static bool ITESP_Enabled = false;
	inline static bool ITESP_Text = true;
	inline static float ITESP_TextSize = 18;
	inline static float ITESP_TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	inline static bool ITESP_TextOutline = true;
	inline static float ITESP_TextOutlineColor[4]{ 0, 0, 0, 1.0f };
	inline static float ITESP_TextUnrenderDistance = 14.0f;
	inline static float ITESP_FadeDistance = 3.0f;
	inline static bool ITESP_HealthBar = true;
	inline static int ITESP_BoxType = 0;
	inline static const char* ITESP_BoxTypeList[4]{ "Dynamic 2D Box", "3D Box" };
	inline static float ITESP_3DBoxColor[4]{ 1, 0, 0, 1 };
	inline static float ITESP_3DBoxThickness = 1.0f;
	inline static bool ITESP_Box = true;
	inline static float ITESP_BoxColor[4]{ 1, 0, 0, 1 };
	inline static bool ITESP_FilledBox = true;
	inline static float ITESP_FilledBoxColor[4]{ 1, 0, 0, 0.15f };
	inline static float ITESP_SecondFilledBoxColor[4]{ 1, 0, 0, 0.15f };
	inline static bool ITESP_Outline = true;
	inline static float ITESP_OutlineColor[4]{ 1, 0, 0, 0.25 };
	inline static bool ITESP_HighlightFriends = true;
	inline static float ITESP_Friend3DBoxColor[4]{ 0, 1, 0, 1 };
	inline static float ITESP_FriendBoxColor[4]{ 0, 1, 0, 1 };
	inline static float ITESP_FriendFilledBoxColor[4]{ 0, 1, 0, 0.15f };
	inline static float ITESP_FriendSecondFilledBoxColor[4]{ 0, 1, 0, 0.15f };
	inline static float ITESP_FriendOutlineColor[4]{ 0, 1, 0, 0.25 };
};
