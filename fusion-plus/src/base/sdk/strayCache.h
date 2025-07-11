#pragma once
#include "java/java.h"

#include "util/logger.h"

struct StrayCache
{

	inline static bool initialized;

	// MINECRAFT CLASS
	inline static jclass minecraft_class;
	inline static jmethodID minecraft_getMinecraft;
	inline static jmethodID minecraft_getNetHandler;
	inline static jmethodID minecraft_clickMouse;
	inline static jfieldID minecraft_thePlayer;
	inline static jfieldID minecraft_playerController;
	inline static jfieldID minecraft_theWorld;
	inline static jfieldID minecraft_renderManager;
	inline static jfieldID minecraft_renderViewEntity;
	inline static jfieldID minecraft_timer;
	inline static jfieldID minecraft_gameSettings;
	inline static jfieldID minecraft_currentScreen;
	inline static jfieldID minecraft_objectMouseOver;
	inline static jfieldID minecraft_launchedVersion;
	inline static jfieldID minecraft_debugFPS;

	// CLIENT BRAND RETRIEVER CLASS
	inline static jclass clientBrandRetriever_class;
	inline static jmethodID clientBrandRetriever_getClientModName;

	// WORLD CLIENT CLASS
	inline static jclass worldClient_class;
	inline static jfieldID worldClient_entityList;

	// PLAYER CONTROLLER M P CLASS
	inline static jclass playerControllerMP_class;
	inline static jmethodID playerControllerMP_windowClick;
	inline static jmethodID playerControllerMP_getBlockReachDistance;

	// ACTIVE RENDER INFO CLASS
	inline static jclass activeRenderInfo_class;
	inline static jfieldID activeRenderInfo_PROJECTION;
	inline static jfieldID activeRenderInfo_MODELVIEW;

	// RENDER MANAGER CLASS
	inline static jclass renderManager_class;
	inline static jfieldID renderManager_instance;
	inline static jfieldID renderManager_renderPosX;
	inline static jfieldID renderManager_renderPosY;
	inline static jfieldID renderManager_renderPosZ;
	inline static jfieldID renderManager_viewerPosX;
	inline static jfieldID renderManager_viewerPosY;
	inline static jfieldID renderManager_viewerPosZ;

	// GAME SETTINGS CLASS
	inline static jclass gameSettings_class;
	inline static jmethodID gameSettings_setOptionKeyBinding;
	inline static jfieldID gameSettings_thirdPersonView;
	inline static jfieldID gameSettings_fovSetting;
	inline static jfieldID gameSettings_keyBindFullscreen;

	// ENTITY PLAYER S P CLASS
	inline static jclass entityPlayerSP_class;

	// GUI CONTAINER CLASS
	inline static jclass guiContainer_class;
	inline static jfieldID guiContainer_inventorySlots;

	// GUI CHEST CLASS
	inline static jclass guiChest_class;
	inline static jfieldID guiChest_upperChestInventory;
	inline static jfieldID guiChest_lowerChestInventory;
	inline static jfieldID guiChest_inventoryRows;

	// ENTITY CLASS
	inline static jclass entity_class;
	inline static jmethodID entity_getName;
	inline static jmethodID entity_isSneaking;
	inline static jmethodID entity_isSprinting;
	inline static jmethodID entity_setSprinting;
	inline static jmethodID entity_isInvisibleToPlayer;
	inline static jmethodID entity_getEyeHeight;
	inline static jfieldID entity_posX;
	inline static jfieldID entity_posY;
	inline static jfieldID entity_posZ;
	inline static jfieldID entity_lastTickPosX;
	inline static jfieldID entity_lastTickPosY;
	inline static jfieldID entity_lastTickPosZ;
	inline static jfieldID entity_width;
	inline static jfieldID entity_height;
	inline static jfieldID entity_distanceWalkedModified;
	inline static jfieldID entity_prevDistanceWalkedModified;
	inline static jfieldID entity_rotationYaw;
	inline static jfieldID entity_rotationPitch;
	inline static jfieldID entity_prevRotationYaw;
	inline static jfieldID entity_prevRotationPitch;
	inline static jfieldID entity_boundingBox;
	inline static jfieldID entity_motionX;
	inline static jfieldID entity_motionY;
	inline static jfieldID entity_motionZ;
	inline static jfieldID entity_hurtResistantTime;

	// ENTITY LIVING BASE CLASS
	inline static jclass entityLivingBase_class;
	inline static jmethodID entityLivingBase_getHealth;
	inline static jmethodID entityLivingBase_getMaxHealth;
	inline static jmethodID entityLivingBase_canEntityBeSeen;

	// ENTITY PLAYER M P CLASS
	inline static jclass entityPlayerMP_class;

	// ENTITY PLAYER CLASS
	inline static jclass entityPlayer_class;
	inline static jfieldID entityPlayer_inventory;

	// INVENTORY PLAYER CLASS
	inline static jclass inventoryPlayer_class;
	inline static jmethodID inventoryPlayer_getCurrentItem;
	inline static jfieldID inventoryPlayer_mainInventory;
	inline static jfieldID inventoryPlayer_armorInventory;
	inline static jfieldID inventoryPlayer_currentItem;

	// WORLD CLASS
	inline static jclass world_class;
	inline static jmethodID world_rayTraceBlocks;
	inline static jmethodID world_getBlockState;
	inline static jmethodID world_getBlock;
	inline static jfieldID world_playerEntities;

	// ITEM CLASS
	inline static jclass item_class;
	inline static jmethodID item_getIdFromItem;
	inline static jmethodID item_getUnlocalizedName;
	inline static jmethodID item_getItemStackLimit;

	// ITEM STACK CLASS
	inline static jclass itemStack_class;
	inline static jmethodID itemStack_getItem;
	inline static jmethodID itemStack_getMetadata;
	inline static jmethodID itemStack_getMaxDamage;
	inline static jfieldID itemStack_stackSize;

	// I INVENTORY CLASS
	inline static jclass iInventory_class;
	inline static jmethodID iInventory_getSizeInventory;
	inline static jmethodID iInventory_getStackInSlot;

	// CONTAINER CLASS
	inline static jclass container_class;
	inline static const char* container_windowId_name;
	// ENCHANTMENT HELPER CLASS
	inline static jclass enchantmentHelper_class;
	inline static jmethodID enchantmentHelper_getEnchantments;

	// BLOCK CLASS
	inline static jclass block_class;
	inline static jmethodID block_getIdFromBlock;

	// I BLOCK STATE CLASS
	inline static jclass iBlockState_class;
	inline static jmethodID iBlockState_getBlock;

	// AXIS ALIGNED B B CLASS
	inline static jclass axisAlignedBB_class;
	inline static jfieldID axisAlignedBB_minX;
	inline static jfieldID axisAlignedBB_minY;
	inline static jfieldID axisAlignedBB_minZ;
	inline static jfieldID axisAlignedBB_maxX;
	inline static jfieldID axisAlignedBB_maxY;
	inline static jfieldID axisAlignedBB_maxZ;

	// TIMER CLASS
	inline static jclass timer_class;
	inline static jfieldID timer_renderPartialTicks;

	// MOVING OBJECT POSITION CLASS
	inline static jclass movingObjectPosition_class;
	inline static jfieldID movingObjectPosition_hitVec;
	inline static jfieldID movingObjectPosition_entityHit;
	inline static jfieldID movingObjectPosition_typeOfHit;
	inline static jfieldID movingObjectPosition_BLOCK;

	// BLOCK POS CLASS
	inline static jclass blockPos_class;
	inline static jmethodID blockPos_constructorDouble;
	inline static jmethodID blockPos_constructorInt;

	// VEC3 CLASS
	inline static jclass vec3_class;
	inline static jfieldID vec3_xCoord;
	inline static jfieldID vec3_yCoord;
	inline static jfieldID vec3_zCoord;

	// NET HANDLER PLAY CLIENT CLASS
	inline static jclass netHandlerPlayClient_class;
	inline static jmethodID netHandlerPlayClient_getPlayerInfo;
	inline static jfieldID netHandlerPlayClient_playerInfoList;

	// NETWORK PLAYER INFO CLASS
	inline static jclass networkPlayerInfo_class;
	inline static jmethodID networkPlayerInfo_getResponseTime;

	// GUI PLAYER INFO CLASS
	inline static jclass guiPlayerInfo_class;
	inline static jfieldID guiPlayerInfo_responseTime;
	inline static jfieldID guiPlayerInfo_name;

	// STRINGS
	inline static const char* inventory_class_name;
	inline static const char* chest_gui_class_name;
	inline static const char* vec3_class_name;

	static void Init()
	{
		if (Java::version == MinecraftVersion::UNKNOWN) { return; }
		if (initialized) { return; }

		if (Java::version == MinecraftVersion::LUNAR_1_8_9)
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			if (!minecraft_class) LOG_INFO("minecraft_class: %p", minecraft_class);
			else if (minecraft_class)
			{
				minecraft_getMinecraft = Java::env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
				if (!minecraft_getMinecraft) LOG_INFO("minecraft_getMinecraft: %p", minecraft_getMinecraft);
				minecraft_getNetHandler = Java::env->GetMethodID(minecraft_class, "getNetHandler", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
				if (!minecraft_getNetHandler) LOG_INFO("minecraft_getNetHandler: %p", minecraft_getNetHandler);
				minecraft_clickMouse = Java::env->GetMethodID(minecraft_class, "clickMouse", "()V");
				if (!minecraft_clickMouse) LOG_INFO("minecraft_clickMouse: %p", minecraft_clickMouse);
				minecraft_thePlayer = Java::env->GetFieldID(minecraft_class, "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
				if (!minecraft_thePlayer) LOG_INFO("minecraft_thePlayer: %p", minecraft_thePlayer);
				minecraft_playerController = Java::env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
				if (!minecraft_playerController) LOG_INFO("minecraft_playerController: %p", minecraft_playerController);
				minecraft_theWorld = Java::env->GetFieldID(minecraft_class, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
				if (!minecraft_theWorld) LOG_INFO("minecraft_theWorld: %p", minecraft_theWorld);
				minecraft_renderManager = Java::env->GetFieldID(minecraft_class, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
				if (!minecraft_renderManager) LOG_INFO("minecraft_renderManager: %p", minecraft_renderManager);
				minecraft_renderViewEntity = Java::env->GetFieldID(minecraft_class, "renderViewEntity", "Lnet/minecraft/entity/Entity;");
				if (!minecraft_renderViewEntity) LOG_INFO("minecraft_renderViewEntity: %p", minecraft_renderViewEntity);
				minecraft_timer = Java::env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
				if (!minecraft_timer) LOG_INFO("minecraft_timer: %p", minecraft_timer);
				minecraft_gameSettings = Java::env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
				if (!minecraft_gameSettings) LOG_INFO("minecraft_gameSettings: %p", minecraft_gameSettings);
				minecraft_currentScreen = Java::env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
				if (!minecraft_currentScreen) LOG_INFO("minecraft_currentScreen: %p", minecraft_currentScreen);
				minecraft_objectMouseOver = Java::env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
				if (!minecraft_objectMouseOver) LOG_INFO("minecraft_objectMouseOver: %p", minecraft_objectMouseOver);
				minecraft_launchedVersion = Java::env->GetFieldID(minecraft_class, "launchedVersion", "Ljava/lang/String;");
				if (!minecraft_launchedVersion) LOG_INFO("minecraft_launchedVersion: %p", minecraft_launchedVersion);
				minecraft_debugFPS = Java::env->GetStaticFieldID(minecraft_class, "debugFPS", "I");
				if (!minecraft_debugFPS) LOG_INFO("minecraft_debugFPS: %p", minecraft_debugFPS);
			}

			Java::AssignClass("net.minecraft.client.ClientBrandRetriever", clientBrandRetriever_class);
			if (!clientBrandRetriever_class) LOG_INFO("clientBrandRetriever_class: %p", clientBrandRetriever_class);
			else if (clientBrandRetriever_class)
			{
				clientBrandRetriever_getClientModName = Java::env->GetStaticMethodID(clientBrandRetriever_class, "getClientModName", "()Ljava/lang/String;");
				if (!clientBrandRetriever_getClientModName) LOG_INFO("clientBrandRetriever_getClientModName: %p", clientBrandRetriever_getClientModName);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			if (!worldClient_class) LOG_INFO("worldClient_class: %p", worldClient_class);
			else if (worldClient_class)
			{
				worldClient_entityList = Java::env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");
				if (!worldClient_entityList) LOG_INFO("worldClient_entityList: %p", worldClient_entityList);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			if (!playerControllerMP_class) LOG_INFO("playerControllerMP_class: %p", playerControllerMP_class);
			else if (playerControllerMP_class)
			{
				playerControllerMP_windowClick = Java::env->GetMethodID(playerControllerMP_class, "windowClick", "(IIIILnet/minecraft/entity/player/EntityPlayer;)Lnet/minecraft/item/ItemStack;");
				if (!playerControllerMP_windowClick) LOG_INFO("playerControllerMP_windowClick: %p", playerControllerMP_windowClick);
				playerControllerMP_getBlockReachDistance = Java::env->GetMethodID(playerControllerMP_class, "getBlockReachDistance", "()F");
				if (!playerControllerMP_getBlockReachDistance) LOG_INFO("playerControllerMP_getBlockReachDistance: %p", playerControllerMP_getBlockReachDistance);
			}

			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			if (!activeRenderInfo_class) LOG_INFO("activeRenderInfo_class: %p", activeRenderInfo_class);
			else if (activeRenderInfo_class)
			{
				activeRenderInfo_PROJECTION = Java::env->GetStaticFieldID(activeRenderInfo_class, "PROJECTION", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_PROJECTION) LOG_INFO("activeRenderInfo_PROJECTION: %p", activeRenderInfo_PROJECTION);
				activeRenderInfo_MODELVIEW = Java::env->GetStaticFieldID(activeRenderInfo_class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_MODELVIEW) LOG_INFO("activeRenderInfo_MODELVIEW: %p", activeRenderInfo_MODELVIEW);
			}

			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			if (!renderManager_class) LOG_INFO("renderManager_class: %p", renderManager_class);
			else if (renderManager_class)
			{
				renderManager_instance = Java::env->GetStaticFieldID(renderManager_class, "", "");
				if (!renderManager_instance) LOG_INFO("renderManager_instance: %p", renderManager_instance);
				renderManager_renderPosX = Java::env->GetFieldID(renderManager_class, "renderPosX", "D");
				if (!renderManager_renderPosX) LOG_INFO("renderManager_renderPosX: %p", renderManager_renderPosX);
				renderManager_renderPosY = Java::env->GetFieldID(renderManager_class, "renderPosY", "D");
				if (!renderManager_renderPosY) LOG_INFO("renderManager_renderPosY: %p", renderManager_renderPosY);
				renderManager_renderPosZ = Java::env->GetFieldID(renderManager_class, "renderPosZ", "D");
				if (!renderManager_renderPosZ) LOG_INFO("renderManager_renderPosZ: %p", renderManager_renderPosZ);
				renderManager_viewerPosX = Java::env->GetFieldID(renderManager_class, "viewerPosX", "D");
				if (!renderManager_viewerPosX) LOG_INFO("renderManager_viewerPosX: %p", renderManager_viewerPosX);
				renderManager_viewerPosY = Java::env->GetFieldID(renderManager_class, "viewerPosY", "D");
				if (!renderManager_viewerPosY) LOG_INFO("renderManager_viewerPosY: %p", renderManager_viewerPosY);
				renderManager_viewerPosZ = Java::env->GetFieldID(renderManager_class, "viewerPosZ", "D");
				if (!renderManager_viewerPosZ) LOG_INFO("renderManager_viewerPosZ: %p", renderManager_viewerPosZ);
			}

			Java::AssignClass("net.minecraft.client.settings.GameSettings", gameSettings_class);
			if (!gameSettings_class) LOG_INFO("gameSettings_class: %p", gameSettings_class);
			else if (gameSettings_class)
			{
				gameSettings_setOptionKeyBinding = Java::env->GetMethodID(gameSettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
				if (!gameSettings_setOptionKeyBinding) LOG_INFO("gameSettings_setOptionKeyBinding: %p", gameSettings_setOptionKeyBinding);
				gameSettings_thirdPersonView = Java::env->GetFieldID(gameSettings_class, "thirdPersonView", "I");
				if (!gameSettings_thirdPersonView) LOG_INFO("gameSettings_thirdPersonView: %p", gameSettings_thirdPersonView);
				gameSettings_fovSetting = Java::env->GetFieldID(gameSettings_class, "fovSetting", "F");
				if (!gameSettings_fovSetting) LOG_INFO("gameSettings_fovSetting: %p", gameSettings_fovSetting);
				gameSettings_keyBindFullscreen = Java::env->GetFieldID(gameSettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
				if (!gameSettings_keyBindFullscreen) LOG_INFO("gameSettings_keyBindFullscreen: %p", gameSettings_keyBindFullscreen);
			}

			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			if (!entityPlayerSP_class) LOG_INFO("entityPlayerSP_class: %p", entityPlayerSP_class);
			else if (entityPlayerSP_class)
			{
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiContainer", guiContainer_class);
			if (!guiContainer_class) LOG_INFO("guiContainer_class: %p", guiContainer_class);
			else if (guiContainer_class)
			{
				guiContainer_inventorySlots = Java::env->GetFieldID(guiContainer_class, "inventorySlots", "Lnet/minecraft/inventory/Container;");
				if (!guiContainer_inventorySlots) LOG_INFO("guiContainer_inventorySlots: %p", guiContainer_inventorySlots);
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiChest", guiChest_class);
			if (!guiChest_class) LOG_INFO("guiChest_class: %p", guiChest_class);
			else if (guiChest_class)
			{
				guiChest_upperChestInventory = Java::env->GetFieldID(guiChest_class, "upperChestInventory", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_upperChestInventory) LOG_INFO("guiChest_upperChestInventory: %p", guiChest_upperChestInventory);
				guiChest_lowerChestInventory = Java::env->GetFieldID(guiChest_class, "lowerChestInventory", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_lowerChestInventory) LOG_INFO("guiChest_lowerChestInventory: %p", guiChest_lowerChestInventory);
				guiChest_inventoryRows = Java::env->GetFieldID(guiChest_class, "inventoryRows", "I");
				if (!guiChest_inventoryRows) LOG_INFO("guiChest_inventoryRows: %p", guiChest_inventoryRows);
			}

			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			if (!entity_class) LOG_INFO("entity_class: %p", entity_class);
			else if (entity_class)
			{
				entity_getName = Java::env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
				if (!entity_getName) LOG_INFO("entity_getName: %p", entity_getName);
				entity_isSneaking = Java::env->GetMethodID(entity_class, "isSneaking", "()Z");
				if (!entity_isSneaking) LOG_INFO("entity_isSneaking: %p", entity_isSneaking);
				entity_isSprinting = Java::env->GetMethodID(entity_class, "isSprinting", "()Z");
				if (!entity_isSprinting) LOG_INFO("entity_isSprinting: %p", entity_isSprinting);
				entity_setSprinting = Java::env->GetMethodID(entity_class, "setSprinting", "(Z)V");
				if (!entity_setSprinting) LOG_INFO("entity_setSprinting: %p", entity_setSprinting);
				entity_isInvisibleToPlayer = Java::env->GetMethodID(entity_class, "isInvisibleToPlayer", "(Lnet/minecraft/entity/player/EntityPlayer;)Z");
				if (!entity_isInvisibleToPlayer) LOG_INFO("entity_isInvisibleToPlayer: %p", entity_isInvisibleToPlayer);
				entity_getEyeHeight = Java::env->GetMethodID(entity_class, "getEyeHeight", "()F");
				if (!entity_getEyeHeight) LOG_INFO("entity_getEyeHeight: %p", entity_getEyeHeight);
				entity_posX = Java::env->GetFieldID(entity_class, "posX", "D");
				if (!entity_posX) LOG_INFO("entity_posX: %p", entity_posX);
				entity_posY = Java::env->GetFieldID(entity_class, "posY", "D");
				if (!entity_posY) LOG_INFO("entity_posY: %p", entity_posY);
				entity_posZ = Java::env->GetFieldID(entity_class, "posZ", "D");
				if (!entity_posZ) LOG_INFO("entity_posZ: %p", entity_posZ);
				entity_lastTickPosX = Java::env->GetFieldID(entity_class, "lastTickPosX", "D");
				if (!entity_lastTickPosX) LOG_INFO("entity_lastTickPosX: %p", entity_lastTickPosX);
				entity_lastTickPosY = Java::env->GetFieldID(entity_class, "lastTickPosY", "D");
				if (!entity_lastTickPosY) LOG_INFO("entity_lastTickPosY: %p", entity_lastTickPosY);
				entity_lastTickPosZ = Java::env->GetFieldID(entity_class, "lastTickPosZ", "D");
				if (!entity_lastTickPosZ) LOG_INFO("entity_lastTickPosZ: %p", entity_lastTickPosZ);
				entity_width = Java::env->GetFieldID(entity_class, "width", "F");
				if (!entity_width) LOG_INFO("entity_width: %p", entity_width);
				entity_height = Java::env->GetFieldID(entity_class, "height", "F");
				if (!entity_height) LOG_INFO("entity_height: %p", entity_height);
				entity_distanceWalkedModified = Java::env->GetFieldID(entity_class, "distanceWalkedModified", "F");
				if (!entity_distanceWalkedModified) LOG_INFO("entity_distanceWalkedModified: %p", entity_distanceWalkedModified);
				entity_prevDistanceWalkedModified = Java::env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
				if (!entity_prevDistanceWalkedModified) LOG_INFO("entity_prevDistanceWalkedModified: %p", entity_prevDistanceWalkedModified);
				entity_rotationYaw = Java::env->GetFieldID(entity_class, "rotationYaw", "F");
				if (!entity_rotationYaw) LOG_INFO("entity_rotationYaw: %p", entity_rotationYaw);
				entity_rotationPitch = Java::env->GetFieldID(entity_class, "rotationPitch", "F");
				if (!entity_rotationPitch) LOG_INFO("entity_rotationPitch: %p", entity_rotationPitch);
				entity_prevRotationYaw = Java::env->GetFieldID(entity_class, "prevRotationYaw", "F");
				if (!entity_prevRotationYaw) LOG_INFO("entity_prevRotationYaw: %p", entity_prevRotationYaw);
				entity_prevRotationPitch = Java::env->GetFieldID(entity_class, "prevRotationPitch", "F");
				if (!entity_prevRotationPitch) LOG_INFO("entity_prevRotationPitch: %p", entity_prevRotationPitch);
				entity_boundingBox = Java::env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
				if (!entity_boundingBox) LOG_INFO("entity_boundingBox: %p", entity_boundingBox);
				entity_motionX = Java::env->GetFieldID(entity_class, "motionX", "D");
				if (!entity_motionX) LOG_INFO("entity_motionX: %p", entity_motionX);
				entity_motionY = Java::env->GetFieldID(entity_class, "motionY", "D");
				if (!entity_motionY) LOG_INFO("entity_motionY: %p", entity_motionY);
				entity_motionZ = Java::env->GetFieldID(entity_class, "motionZ", "D");
				if (!entity_motionZ) LOG_INFO("entity_motionZ: %p", entity_motionZ);
				entity_hurtResistantTime = Java::env->GetFieldID(entity_class, "hurtResistantTime", "I");
				if (!entity_hurtResistantTime) LOG_INFO("entity_hurtResistantTime: %p", entity_hurtResistantTime);
			}

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			if (!entityLivingBase_class) LOG_INFO("entityLivingBase_class: %p", entityLivingBase_class);
			else if (entityLivingBase_class)
			{
				entityLivingBase_getHealth = Java::env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
				if (!entityLivingBase_getHealth) LOG_INFO("entityLivingBase_getHealth: %p", entityLivingBase_getHealth);
				entityLivingBase_getMaxHealth = Java::env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
				if (!entityLivingBase_getMaxHealth) LOG_INFO("entityLivingBase_getMaxHealth: %p", entityLivingBase_getMaxHealth);
				entityLivingBase_canEntityBeSeen = Java::env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
				if (!entityLivingBase_canEntityBeSeen) LOG_INFO("entityLivingBase_canEntityBeSeen: %p", entityLivingBase_canEntityBeSeen);
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayerMP", entityPlayerMP_class);
			if (!entityPlayerMP_class) LOG_INFO("entityPlayerMP_class: %p", entityPlayerMP_class);
			else if (entityPlayerMP_class)
			{
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			if (!entityPlayer_class) LOG_INFO("entityPlayer_class: %p", entityPlayer_class);
			else if (entityPlayer_class)
			{
				entityPlayer_inventory = Java::env->GetFieldID(entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
				if (!entityPlayer_inventory) LOG_INFO("entityPlayer_inventory: %p", entityPlayer_inventory);
			}

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			if (!inventoryPlayer_class) LOG_INFO("inventoryPlayer_class: %p", inventoryPlayer_class);
			else if (inventoryPlayer_class)
			{
				inventoryPlayer_getCurrentItem = Java::env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_getCurrentItem) LOG_INFO("inventoryPlayer_getCurrentItem: %p", inventoryPlayer_getCurrentItem);
				inventoryPlayer_mainInventory = Java::env->GetFieldID(inventoryPlayer_class, "mainInventory", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_mainInventory) LOG_INFO("inventoryPlayer_mainInventory: %p", inventoryPlayer_mainInventory);
				inventoryPlayer_armorInventory = Java::env->GetFieldID(inventoryPlayer_class, "armorInventory", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_armorInventory) LOG_INFO("inventoryPlayer_armorInventory: %p", inventoryPlayer_armorInventory);
				inventoryPlayer_currentItem = Java::env->GetFieldID(inventoryPlayer_class, "currentItem", "I");
				if (!inventoryPlayer_currentItem) LOG_INFO("inventoryPlayer_currentItem: %p", inventoryPlayer_currentItem);
			}

			Java::AssignClass("net.minecraft.world.World", world_class);
			if (!world_class) LOG_INFO("world_class: %p", world_class);
			else if (world_class)
			{
				world_rayTraceBlocks = Java::env->GetMethodID(world_class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
				if (!world_rayTraceBlocks) LOG_INFO("world_rayTraceBlocks: %p", world_rayTraceBlocks);
				world_getBlockState = Java::env->GetMethodID(world_class, "getBlockState", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
				if (!world_getBlockState) LOG_INFO("world_getBlockState: %p", world_getBlockState);
				world_getBlock = Java::env->GetMethodID(world_class, "", "");
				if (!world_getBlock) LOG_INFO("world_getBlock: %p", world_getBlock);
				world_playerEntities = Java::env->GetFieldID(world_class, "playerEntities", "Ljava/util/List;");
				if (!world_playerEntities) LOG_INFO("world_playerEntities: %p", world_playerEntities);
			}

			Java::AssignClass("net.minecraft.item.Item", item_class);
			if (!item_class) LOG_INFO("item_class: %p", item_class);
			else if (item_class)
			{
				item_getIdFromItem = Java::env->GetStaticMethodID(item_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");
				if (!item_getIdFromItem) LOG_INFO("item_getIdFromItem: %p", item_getIdFromItem);
				item_getUnlocalizedName = Java::env->GetMethodID(item_class, "getUnlocalizedName", "()Ljava/lang/String;");
				if (!item_getUnlocalizedName) LOG_INFO("item_getUnlocalizedName: %p", item_getUnlocalizedName);
				item_getItemStackLimit = Java::env->GetMethodID(item_class, "getItemStackLimit", "()I");
				if (!item_getItemStackLimit) LOG_INFO("item_getItemStackLimit: %p", item_getItemStackLimit);
			}

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			if (!itemStack_class) LOG_INFO("itemStack_class: %p", itemStack_class);
			else if (itemStack_class)
			{
				itemStack_getItem = Java::env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
				if (!itemStack_getItem) LOG_INFO("itemStack_getItem: %p", itemStack_getItem);
				itemStack_getMetadata = Java::env->GetMethodID(itemStack_class, "getMetadata", "()I");
				if (!itemStack_getMetadata) LOG_INFO("itemStack_getMetadata: %p", itemStack_getMetadata);
				itemStack_getMaxDamage = Java::env->GetMethodID(itemStack_class, "getMaxDamage", "()I");
				if (!itemStack_getMaxDamage) LOG_INFO("itemStack_getMaxDamage: %p", itemStack_getMaxDamage);
				itemStack_stackSize = Java::env->GetFieldID(itemStack_class, "stackSize", "I");
				if (!itemStack_stackSize) LOG_INFO("itemStack_stackSize: %p", itemStack_stackSize);
			}

			Java::AssignClass("net.minecraft.inventory.IInventory", iInventory_class);
			if (!iInventory_class) LOG_INFO("iInventory_class: %p", iInventory_class);
			else if (iInventory_class)
			{
				iInventory_getSizeInventory = Java::env->GetMethodID(iInventory_class, "getSizeInventory", "()I");
				if (!iInventory_getSizeInventory) LOG_INFO("iInventory_getSizeInventory: %p", iInventory_getSizeInventory);
				iInventory_getStackInSlot = Java::env->GetMethodID(iInventory_class, "getStackInSlot", "(I)Lnet/minecraft/item/ItemStack;");
				if (!iInventory_getStackInSlot) LOG_INFO("iInventory_getStackInSlot: %p", iInventory_getStackInSlot);
			}

			Java::AssignClass("net.minecraft.inventory.Container", container_class);
			if (!container_class) LOG_INFO("container_class: %p", container_class);
			else if (container_class)
			{
				container_windowId_name = "windowId";
			}

			Java::AssignClass("net.minecraft.enchantment.EnchantmentHelper", enchantmentHelper_class);
			if (!enchantmentHelper_class) LOG_INFO("enchantmentHelper_class: %p", enchantmentHelper_class);
			else if (enchantmentHelper_class)
			{
				enchantmentHelper_getEnchantments = Java::env->GetStaticMethodID(enchantmentHelper_class, "getEnchantments", "(Lnet/minecraft/item/ItemStack;)Ljava/util/Map;");
				if (!enchantmentHelper_getEnchantments) LOG_INFO("enchantmentHelper_getEnchantments: %p", enchantmentHelper_getEnchantments);
			}

			Java::AssignClass("net.minecraft.block.Block", block_class);
			if (!block_class) LOG_INFO("block_class: %p", block_class);
			else if (block_class)
			{
				block_getIdFromBlock = Java::env->GetStaticMethodID(block_class, "getIdFromBlock", "(Lnet/minecraft/block/Block;)I");
				if (!block_getIdFromBlock) LOG_INFO("block_getIdFromBlock: %p", block_getIdFromBlock);
			}

			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			if (!iBlockState_class) LOG_INFO("iBlockState_class: %p", iBlockState_class);
			else if (iBlockState_class)
			{
				iBlockState_getBlock = Java::env->GetMethodID(iBlockState_class, "getBlock", "()Lnet/minecraft/block/Block;");
				if (!iBlockState_getBlock) LOG_INFO("iBlockState_getBlock: %p", iBlockState_getBlock);
			}

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			if (!axisAlignedBB_class) LOG_INFO("axisAlignedBB_class: %p", axisAlignedBB_class);
			else if (axisAlignedBB_class)
			{
				axisAlignedBB_minX = Java::env->GetFieldID(axisAlignedBB_class, "minX", "D");
				if (!axisAlignedBB_minX) LOG_INFO("axisAlignedBB_minX: %p", axisAlignedBB_minX);
				axisAlignedBB_minY = Java::env->GetFieldID(axisAlignedBB_class, "minY", "D");
				if (!axisAlignedBB_minY) LOG_INFO("axisAlignedBB_minY: %p", axisAlignedBB_minY);
				axisAlignedBB_minZ = Java::env->GetFieldID(axisAlignedBB_class, "minZ", "D");
				if (!axisAlignedBB_minZ) LOG_INFO("axisAlignedBB_minZ: %p", axisAlignedBB_minZ);
				axisAlignedBB_maxX = Java::env->GetFieldID(axisAlignedBB_class, "maxX", "D");
				if (!axisAlignedBB_maxX) LOG_INFO("axisAlignedBB_maxX: %p", axisAlignedBB_maxX);
				axisAlignedBB_maxY = Java::env->GetFieldID(axisAlignedBB_class, "maxY", "D");
				if (!axisAlignedBB_maxY) LOG_INFO("axisAlignedBB_maxY: %p", axisAlignedBB_maxY);
				axisAlignedBB_maxZ = Java::env->GetFieldID(axisAlignedBB_class, "maxZ", "D");
				if (!axisAlignedBB_maxZ) LOG_INFO("axisAlignedBB_maxZ: %p", axisAlignedBB_maxZ);
			}

			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			if (!timer_class) LOG_INFO("timer_class: %p", timer_class);
			else if (timer_class)
			{
				timer_renderPartialTicks = Java::env->GetFieldID(timer_class, "renderPartialTicks", "F");
				if (!timer_renderPartialTicks) LOG_INFO("timer_renderPartialTicks: %p", timer_renderPartialTicks);
			}

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			if (!movingObjectPosition_class) LOG_INFO("movingObjectPosition_class: %p", movingObjectPosition_class);
			else if (movingObjectPosition_class)
			{
				movingObjectPosition_hitVec = Java::env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/Vec3;");
				if (!movingObjectPosition_hitVec) LOG_INFO("movingObjectPosition_hitVec: %p", movingObjectPosition_hitVec);
				movingObjectPosition_entityHit = Java::env->GetFieldID(movingObjectPosition_class, "entityHit", "Lnet/minecraft/entity/Entity;");
				if (!movingObjectPosition_entityHit) LOG_INFO("movingObjectPosition_entityHit: %p", movingObjectPosition_entityHit);
				movingObjectPosition_typeOfHit = Java::env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_typeOfHit) LOG_INFO("movingObjectPosition_typeOfHit: %p", movingObjectPosition_typeOfHit);
				movingObjectPosition_BLOCK = Java::env->GetStaticFieldID(movingObjectPosition_class, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_BLOCK) LOG_INFO("movingObjectPosition_BLOCK: %p", movingObjectPosition_BLOCK);
			}

			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			if (!blockPos_class) LOG_INFO("blockPos_class: %p", blockPos_class);
			else if (blockPos_class)
			{
				blockPos_constructorDouble = Java::env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
				if (!blockPos_constructorDouble) LOG_INFO("blockPos_constructorDouble: %p", blockPos_constructorDouble);
				blockPos_constructorInt = Java::env->GetMethodID(blockPos_class, "<init>", "(III)V");
				if (!blockPos_constructorInt) LOG_INFO("blockPos_constructorInt: %p", blockPos_constructorInt);
			}

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			if (!vec3_class) LOG_INFO("vec3_class: %p", vec3_class);
			else if (vec3_class)
			{
				vec3_xCoord = Java::env->GetFieldID(vec3_class, "xCoord", "D");
				if (!vec3_xCoord) LOG_INFO("vec3_xCoord: %p", vec3_xCoord);
				vec3_yCoord = Java::env->GetFieldID(vec3_class, "yCoord", "D");
				if (!vec3_yCoord) LOG_INFO("vec3_yCoord: %p", vec3_yCoord);
				vec3_zCoord = Java::env->GetFieldID(vec3_class, "zCoord", "D");
				if (!vec3_zCoord) LOG_INFO("vec3_zCoord: %p", vec3_zCoord);
			}

			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			if (!netHandlerPlayClient_class) LOG_INFO("netHandlerPlayClient_class: %p", netHandlerPlayClient_class);
			else if (netHandlerPlayClient_class)
			{
				netHandlerPlayClient_getPlayerInfo = Java::env->GetMethodID(netHandlerPlayClient_class, "getPlayerInfo", "(Ljava/lang/String;)Lnet/minecraft/client/network/NetworkPlayerInfo;");
				if (!netHandlerPlayClient_getPlayerInfo) LOG_INFO("netHandlerPlayClient_getPlayerInfo: %p", netHandlerPlayClient_getPlayerInfo);
				netHandlerPlayClient_playerInfoList = Java::env->GetFieldID(netHandlerPlayClient_class, "", "");
				if (!netHandlerPlayClient_playerInfoList) LOG_INFO("netHandlerPlayClient_playerInfoList: %p", netHandlerPlayClient_playerInfoList);
			}

			Java::AssignClass("net.minecraft.client.network.NetworkPlayerInfo", networkPlayerInfo_class);
			if (!networkPlayerInfo_class) LOG_INFO("networkPlayerInfo_class: %p", networkPlayerInfo_class);
			else if (networkPlayerInfo_class)
			{
				networkPlayerInfo_getResponseTime = Java::env->GetMethodID(networkPlayerInfo_class, "getResponseTime", "()I");
				if (!networkPlayerInfo_getResponseTime) LOG_INFO("networkPlayerInfo_getResponseTime: %p", networkPlayerInfo_getResponseTime);
			}

			Java::AssignClass("", guiPlayerInfo_class);
			if (!guiPlayerInfo_class) LOG_INFO("guiPlayerInfo_class: %p", guiPlayerInfo_class);
			else if (guiPlayerInfo_class)
			{
				guiPlayerInfo_responseTime = Java::env->GetFieldID(guiPlayerInfo_class, "", "");
				if (!guiPlayerInfo_responseTime) LOG_INFO("guiPlayerInfo_responseTime: %p", guiPlayerInfo_responseTime);
				guiPlayerInfo_name = Java::env->GetFieldID(guiPlayerInfo_class, "", "");
				if (!guiPlayerInfo_name) LOG_INFO("guiPlayerInfo_name: %p", guiPlayerInfo_name);
			}

			inventory_class_name = "net.minecraft.client.gui.inventory.GuiInventory";
			chest_gui_class_name = "net.minecraft.client.gui.inventory.GuiChest";
			vec3_class_name = "net.minecraft.util.Vec3";
		}
		else if (Java::version == MinecraftVersion::LUNAR_1_7_10)
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			if (!minecraft_class) LOG_INFO("minecraft_class: %p", minecraft_class);
			else if (minecraft_class)
			{
				minecraft_getMinecraft = Java::env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
				if (!minecraft_getMinecraft) LOG_INFO("minecraft_getMinecraft: %p", minecraft_getMinecraft);
				minecraft_getNetHandler = Java::env->GetMethodID(minecraft_class, "getNetHandler", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
				if (!minecraft_getNetHandler) LOG_INFO("minecraft_getNetHandler: %p", minecraft_getNetHandler);
				minecraft_clickMouse = Java::env->GetMethodID(minecraft_class, "clickMouse", "()V");
				if (!minecraft_clickMouse) LOG_INFO("minecraft_clickMouse: %p", minecraft_clickMouse);
				minecraft_thePlayer = Java::env->GetFieldID(minecraft_class, "thePlayer", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
				if (!minecraft_thePlayer) LOG_INFO("minecraft_thePlayer: %p", minecraft_thePlayer);
				minecraft_playerController = Java::env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
				if (!minecraft_playerController) LOG_INFO("minecraft_playerController: %p", minecraft_playerController);
				minecraft_theWorld = Java::env->GetFieldID(minecraft_class, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
				if (!minecraft_theWorld) LOG_INFO("minecraft_theWorld: %p", minecraft_theWorld);
				minecraft_renderManager = Java::env->GetFieldID(minecraft_class, "", "");
				if (!minecraft_renderManager) LOG_INFO("minecraft_renderManager: %p", minecraft_renderManager);
				minecraft_renderViewEntity = Java::env->GetFieldID(minecraft_class, "renderViewEntity", "Lnet/minecraft/entity/EntityLivingBase;");
				if (!minecraft_renderViewEntity) LOG_INFO("minecraft_renderViewEntity: %p", minecraft_renderViewEntity);
				minecraft_timer = Java::env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
				if (!minecraft_timer) LOG_INFO("minecraft_timer: %p", minecraft_timer);
				minecraft_gameSettings = Java::env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
				if (!minecraft_gameSettings) LOG_INFO("minecraft_gameSettings: %p", minecraft_gameSettings);
				minecraft_currentScreen = Java::env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
				if (!minecraft_currentScreen) LOG_INFO("minecraft_currentScreen: %p", minecraft_currentScreen);
				minecraft_objectMouseOver = Java::env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
				if (!minecraft_objectMouseOver) LOG_INFO("minecraft_objectMouseOver: %p", minecraft_objectMouseOver);
				minecraft_launchedVersion = Java::env->GetFieldID(minecraft_class, "launchedVersion", "Ljava/lang/String;");
				if (!minecraft_launchedVersion) LOG_INFO("minecraft_launchedVersion: %p", minecraft_launchedVersion);
				minecraft_debugFPS = Java::env->GetStaticFieldID(minecraft_class, "debugFPS", "I");
				if (!minecraft_debugFPS) LOG_INFO("minecraft_debugFPS: %p", minecraft_debugFPS);
			}

			Java::AssignClass("net.minecraft.client.ClientBrandRetriever", clientBrandRetriever_class);
			if (!clientBrandRetriever_class) LOG_INFO("clientBrandRetriever_class: %p", clientBrandRetriever_class);
			else if (clientBrandRetriever_class)
			{
				clientBrandRetriever_getClientModName = Java::env->GetStaticMethodID(clientBrandRetriever_class, "getClientModName", "()Ljava/lang/String;");
				if (!clientBrandRetriever_getClientModName) LOG_INFO("clientBrandRetriever_getClientModName: %p", clientBrandRetriever_getClientModName);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			if (!worldClient_class) LOG_INFO("worldClient_class: %p", worldClient_class);
			else if (worldClient_class)
			{
				worldClient_entityList = Java::env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");
				if (!worldClient_entityList) LOG_INFO("worldClient_entityList: %p", worldClient_entityList);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			if (!playerControllerMP_class) LOG_INFO("playerControllerMP_class: %p", playerControllerMP_class);
			else if (playerControllerMP_class)
			{
				playerControllerMP_windowClick = Java::env->GetMethodID(playerControllerMP_class, "windowClick", "(IIIILnet/minecraft/entity/player/EntityPlayer;)Lnet/minecraft/item/ItemStack;");
				if (!playerControllerMP_windowClick) LOG_INFO("playerControllerMP_windowClick: %p", playerControllerMP_windowClick);
				playerControllerMP_getBlockReachDistance = Java::env->GetMethodID(playerControllerMP_class, "getBlockReachDistance", "()F");
				if (!playerControllerMP_getBlockReachDistance) LOG_INFO("playerControllerMP_getBlockReachDistance: %p", playerControllerMP_getBlockReachDistance);
			}

			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			if (!activeRenderInfo_class) LOG_INFO("activeRenderInfo_class: %p", activeRenderInfo_class);
			else if (activeRenderInfo_class)
			{
				activeRenderInfo_PROJECTION = Java::env->GetStaticFieldID(activeRenderInfo_class, "projection", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_PROJECTION) LOG_INFO("activeRenderInfo_PROJECTION: %p", activeRenderInfo_PROJECTION);
				activeRenderInfo_MODELVIEW = Java::env->GetStaticFieldID(activeRenderInfo_class, "modelview", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_MODELVIEW) LOG_INFO("activeRenderInfo_MODELVIEW: %p", activeRenderInfo_MODELVIEW);
			}

			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			if (!renderManager_class) LOG_INFO("renderManager_class: %p", renderManager_class);
			else if (renderManager_class)
			{
				renderManager_instance = Java::env->GetStaticFieldID(renderManager_class, "instance", "Lnet/minecraft/client/renderer/entity/RenderManager;");
				if (!renderManager_instance) LOG_INFO("renderManager_instance: %p", renderManager_instance);
				renderManager_renderPosX = Java::env->GetStaticFieldID(renderManager_class, "renderPosX", "D");
				if (!renderManager_renderPosX) LOG_INFO("renderManager_renderPosX: %p", renderManager_renderPosX);
				renderManager_renderPosY = Java::env->GetStaticFieldID(renderManager_class, "renderPosY", "D");
				if (!renderManager_renderPosY) LOG_INFO("renderManager_renderPosY: %p", renderManager_renderPosY);
				renderManager_renderPosZ = Java::env->GetStaticFieldID(renderManager_class, "renderPosZ", "D");
				if (!renderManager_renderPosZ) LOG_INFO("renderManager_renderPosZ: %p", renderManager_renderPosZ);
				renderManager_viewerPosX = Java::env->GetFieldID(renderManager_class, "viewerPosX", "D");
				if (!renderManager_viewerPosX) LOG_INFO("renderManager_viewerPosX: %p", renderManager_viewerPosX);
				renderManager_viewerPosY = Java::env->GetFieldID(renderManager_class, "viewerPosY", "D");
				if (!renderManager_viewerPosY) LOG_INFO("renderManager_viewerPosY: %p", renderManager_viewerPosY);
				renderManager_viewerPosZ = Java::env->GetFieldID(renderManager_class, "viewerPosZ", "D");
				if (!renderManager_viewerPosZ) LOG_INFO("renderManager_viewerPosZ: %p", renderManager_viewerPosZ);
			}

			Java::AssignClass("net.minecraft.client.settings.GameSettings", gameSettings_class);
			if (!gameSettings_class) LOG_INFO("gameSettings_class: %p", gameSettings_class);
			else if (gameSettings_class)
			{
				gameSettings_setOptionKeyBinding = Java::env->GetMethodID(gameSettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
				if (!gameSettings_setOptionKeyBinding) LOG_INFO("gameSettings_setOptionKeyBinding: %p", gameSettings_setOptionKeyBinding);
				gameSettings_thirdPersonView = Java::env->GetFieldID(gameSettings_class, "thirdPersonView", "I");
				if (!gameSettings_thirdPersonView) LOG_INFO("gameSettings_thirdPersonView: %p", gameSettings_thirdPersonView);
				gameSettings_fovSetting = Java::env->GetFieldID(gameSettings_class, "fovSetting", "F");
				if (!gameSettings_fovSetting) LOG_INFO("gameSettings_fovSetting: %p", gameSettings_fovSetting);
				gameSettings_keyBindFullscreen = Java::env->GetFieldID(gameSettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
				if (!gameSettings_keyBindFullscreen) LOG_INFO("gameSettings_keyBindFullscreen: %p", gameSettings_keyBindFullscreen);
			}

			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			if (!entityPlayerSP_class) LOG_INFO("entityPlayerSP_class: %p", entityPlayerSP_class);
			else if (entityPlayerSP_class)
			{
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiContainer", guiContainer_class);
			if (!guiContainer_class) LOG_INFO("guiContainer_class: %p", guiContainer_class);
			else if (guiContainer_class)
			{
				guiContainer_inventorySlots = Java::env->GetFieldID(guiContainer_class, "inventorySlots", "Lnet/minecraft/inventory/Container;");
				if (!guiContainer_inventorySlots) LOG_INFO("guiContainer_inventorySlots: %p", guiContainer_inventorySlots);
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiChest", guiChest_class);
			if (!guiChest_class) LOG_INFO("guiChest_class: %p", guiChest_class);
			else if (guiChest_class)
			{
				guiChest_upperChestInventory = Java::env->GetFieldID(guiChest_class, "upperChestInventory", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_upperChestInventory) LOG_INFO("guiChest_upperChestInventory: %p", guiChest_upperChestInventory);
				guiChest_lowerChestInventory = Java::env->GetFieldID(guiChest_class, "lowerChestInventory", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_lowerChestInventory) LOG_INFO("guiChest_lowerChestInventory: %p", guiChest_lowerChestInventory);
				guiChest_inventoryRows = Java::env->GetFieldID(guiChest_class, "inventoryRows", "I");
				if (!guiChest_inventoryRows) LOG_INFO("guiChest_inventoryRows: %p", guiChest_inventoryRows);
			}

			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			if (!entity_class) LOG_INFO("entity_class: %p", entity_class);
			else if (entity_class)
			{
				entity_getName = Java::env->GetMethodID(entity_class, "getCommandSenderName", "()Ljava/lang/String;");
				if (!entity_getName) LOG_INFO("entity_getName: %p", entity_getName);
				entity_isSneaking = Java::env->GetMethodID(entity_class, "isSneaking", "()Z");
				if (!entity_isSneaking) LOG_INFO("entity_isSneaking: %p", entity_isSneaking);
				entity_isSprinting = Java::env->GetMethodID(entity_class, "isSprinting", "()Z");
				if (!entity_isSprinting) LOG_INFO("entity_isSprinting: %p", entity_isSprinting);
				entity_setSprinting = Java::env->GetMethodID(entity_class, "setSprinting", "(Z)V");
				if (!entity_setSprinting) LOG_INFO("entity_setSprinting: %p", entity_setSprinting);
				entity_isInvisibleToPlayer = Java::env->GetMethodID(entity_class, "isInvisibleToPlayer", "(Lnet/minecraft/entity/player/EntityPlayer;)Z");
				if (!entity_isInvisibleToPlayer) LOG_INFO("entity_isInvisibleToPlayer: %p", entity_isInvisibleToPlayer);
				entity_getEyeHeight = Java::env->GetMethodID(entity_class, "getEyeHeight", "()F");
				if (!entity_getEyeHeight) LOG_INFO("entity_getEyeHeight: %p", entity_getEyeHeight);
				entity_posX = Java::env->GetFieldID(entity_class, "posX", "D");
				if (!entity_posX) LOG_INFO("entity_posX: %p", entity_posX);
				entity_posY = Java::env->GetFieldID(entity_class, "posY", "D");
				if (!entity_posY) LOG_INFO("entity_posY: %p", entity_posY);
				entity_posZ = Java::env->GetFieldID(entity_class, "posZ", "D");
				if (!entity_posZ) LOG_INFO("entity_posZ: %p", entity_posZ);
				entity_lastTickPosX = Java::env->GetFieldID(entity_class, "lastTickPosX", "D");
				if (!entity_lastTickPosX) LOG_INFO("entity_lastTickPosX: %p", entity_lastTickPosX);
				entity_lastTickPosY = Java::env->GetFieldID(entity_class, "lastTickPosY", "D");
				if (!entity_lastTickPosY) LOG_INFO("entity_lastTickPosY: %p", entity_lastTickPosY);
				entity_lastTickPosZ = Java::env->GetFieldID(entity_class, "lastTickPosZ", "D");
				if (!entity_lastTickPosZ) LOG_INFO("entity_lastTickPosZ: %p", entity_lastTickPosZ);
				entity_width = Java::env->GetFieldID(entity_class, "width", "F");
				if (!entity_width) LOG_INFO("entity_width: %p", entity_width);
				entity_height = Java::env->GetFieldID(entity_class, "height", "F");
				if (!entity_height) LOG_INFO("entity_height: %p", entity_height);
				entity_distanceWalkedModified = Java::env->GetFieldID(entity_class, "distanceWalkedModified", "F");
				if (!entity_distanceWalkedModified) LOG_INFO("entity_distanceWalkedModified: %p", entity_distanceWalkedModified);
				entity_prevDistanceWalkedModified = Java::env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
				if (!entity_prevDistanceWalkedModified) LOG_INFO("entity_prevDistanceWalkedModified: %p", entity_prevDistanceWalkedModified);
				entity_rotationYaw = Java::env->GetFieldID(entity_class, "rotationYaw", "F");
				if (!entity_rotationYaw) LOG_INFO("entity_rotationYaw: %p", entity_rotationYaw);
				entity_rotationPitch = Java::env->GetFieldID(entity_class, "rotationPitch", "F");
				if (!entity_rotationPitch) LOG_INFO("entity_rotationPitch: %p", entity_rotationPitch);
				entity_prevRotationYaw = Java::env->GetFieldID(entity_class, "prevRotationYaw", "F");
				if (!entity_prevRotationYaw) LOG_INFO("entity_prevRotationYaw: %p", entity_prevRotationYaw);
				entity_prevRotationPitch = Java::env->GetFieldID(entity_class, "prevRotationPitch", "F");
				if (!entity_prevRotationPitch) LOG_INFO("entity_prevRotationPitch: %p", entity_prevRotationPitch);
				entity_boundingBox = Java::env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
				if (!entity_boundingBox) LOG_INFO("entity_boundingBox: %p", entity_boundingBox);
				entity_motionX = Java::env->GetFieldID(entity_class, "motionX", "D");
				if (!entity_motionX) LOG_INFO("entity_motionX: %p", entity_motionX);
				entity_motionY = Java::env->GetFieldID(entity_class, "motionY", "D");
				if (!entity_motionY) LOG_INFO("entity_motionY: %p", entity_motionY);
				entity_motionZ = Java::env->GetFieldID(entity_class, "motionZ", "D");
				if (!entity_motionZ) LOG_INFO("entity_motionZ: %p", entity_motionZ);
				entity_hurtResistantTime = Java::env->GetFieldID(entity_class, "hurtResistantTime", "I");
				if (!entity_hurtResistantTime) LOG_INFO("entity_hurtResistantTime: %p", entity_hurtResistantTime);
			}

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			if (!entityLivingBase_class) LOG_INFO("entityLivingBase_class: %p", entityLivingBase_class);
			else if (entityLivingBase_class)
			{
				entityLivingBase_getHealth = Java::env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
				if (!entityLivingBase_getHealth) LOG_INFO("entityLivingBase_getHealth: %p", entityLivingBase_getHealth);
				entityLivingBase_getMaxHealth = Java::env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
				if (!entityLivingBase_getMaxHealth) LOG_INFO("entityLivingBase_getMaxHealth: %p", entityLivingBase_getMaxHealth);
				entityLivingBase_canEntityBeSeen = Java::env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
				if (!entityLivingBase_canEntityBeSeen) LOG_INFO("entityLivingBase_canEntityBeSeen: %p", entityLivingBase_canEntityBeSeen);
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayerMP_class);
			if (!entityPlayerMP_class) LOG_INFO("entityPlayerMP_class: %p", entityPlayerMP_class);
			else if (entityPlayerMP_class)
			{
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			if (!entityPlayer_class) LOG_INFO("entityPlayer_class: %p", entityPlayer_class);
			else if (entityPlayer_class)
			{
				entityPlayer_inventory = Java::env->GetFieldID(entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
				if (!entityPlayer_inventory) LOG_INFO("entityPlayer_inventory: %p", entityPlayer_inventory);
			}

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			if (!inventoryPlayer_class) LOG_INFO("inventoryPlayer_class: %p", inventoryPlayer_class);
			else if (inventoryPlayer_class)
			{
				inventoryPlayer_getCurrentItem = Java::env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_getCurrentItem) LOG_INFO("inventoryPlayer_getCurrentItem: %p", inventoryPlayer_getCurrentItem);
				inventoryPlayer_mainInventory = Java::env->GetFieldID(inventoryPlayer_class, "mainInventory", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_mainInventory) LOG_INFO("inventoryPlayer_mainInventory: %p", inventoryPlayer_mainInventory);
				inventoryPlayer_armorInventory = Java::env->GetFieldID(inventoryPlayer_class, "armorInventory", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_armorInventory) LOG_INFO("inventoryPlayer_armorInventory: %p", inventoryPlayer_armorInventory);
				inventoryPlayer_currentItem = Java::env->GetFieldID(inventoryPlayer_class, "currentItem", "I");
				if (!inventoryPlayer_currentItem) LOG_INFO("inventoryPlayer_currentItem: %p", inventoryPlayer_currentItem);
			}

			Java::AssignClass("net.minecraft.world.World", world_class);
			if (!world_class) LOG_INFO("world_class: %p", world_class);
			else if (world_class)
			{
				world_rayTraceBlocks = Java::env->GetMethodID(world_class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
				if (!world_rayTraceBlocks) LOG_INFO("world_rayTraceBlocks: %p", world_rayTraceBlocks);
				world_getBlockState = Java::env->GetMethodID(world_class, "", "");
				if (!world_getBlockState) LOG_INFO("world_getBlockState: %p", world_getBlockState);
				world_getBlock = Java::env->GetMethodID(world_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
				if (!world_getBlock) LOG_INFO("world_getBlock: %p", world_getBlock);
				world_playerEntities = Java::env->GetFieldID(world_class, "playerEntities", "Ljava/util/List;");
				if (!world_playerEntities) LOG_INFO("world_playerEntities: %p", world_playerEntities);
			}

			Java::AssignClass("net.minecraft.item.Item", item_class);
			if (!item_class) LOG_INFO("item_class: %p", item_class);
			else if (item_class)
			{
				item_getIdFromItem = Java::env->GetStaticMethodID(item_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");
				if (!item_getIdFromItem) LOG_INFO("item_getIdFromItem: %p", item_getIdFromItem);
				item_getUnlocalizedName = Java::env->GetMethodID(item_class, "getUnlocalizedName", "()Ljava/lang/String;");
				if (!item_getUnlocalizedName) LOG_INFO("item_getUnlocalizedName: %p", item_getUnlocalizedName);
				item_getItemStackLimit = Java::env->GetMethodID(item_class, "getItemStackLimit", "()I");
				if (!item_getItemStackLimit) LOG_INFO("item_getItemStackLimit: %p", item_getItemStackLimit);
			}

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			if (!itemStack_class) LOG_INFO("itemStack_class: %p", itemStack_class);
			else if (itemStack_class)
			{
				itemStack_getItem = Java::env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
				if (!itemStack_getItem) LOG_INFO("itemStack_getItem: %p", itemStack_getItem);
				itemStack_getMetadata = Java::env->GetMethodID(itemStack_class, "getMetadata", "()I");
				if (!itemStack_getMetadata) LOG_INFO("itemStack_getMetadata: %p", itemStack_getMetadata);
				itemStack_getMaxDamage = Java::env->GetMethodID(itemStack_class, "getMaxDurability", "()I");
				if (!itemStack_getMaxDamage) LOG_INFO("itemStack_getMaxDamage: %p", itemStack_getMaxDamage);
				itemStack_stackSize = Java::env->GetFieldID(itemStack_class, "stackSize", "I");
				if (!itemStack_stackSize) LOG_INFO("itemStack_stackSize: %p", itemStack_stackSize);
			}

			Java::AssignClass("net.minecraft.inventory.IInventory", iInventory_class);
			if (!iInventory_class) LOG_INFO("iInventory_class: %p", iInventory_class);
			else if (iInventory_class)
			{
				iInventory_getSizeInventory = Java::env->GetMethodID(iInventory_class, "getSizeInventory", "()I");
				if (!iInventory_getSizeInventory) LOG_INFO("iInventory_getSizeInventory: %p", iInventory_getSizeInventory);
				iInventory_getStackInSlot = Java::env->GetMethodID(iInventory_class, "getStackInSlot", "(I)Lnet/minecraft/item/ItemStack;");
				if (!iInventory_getStackInSlot) LOG_INFO("iInventory_getStackInSlot: %p", iInventory_getStackInSlot);
			}

			Java::AssignClass("net.minecraft.inventory.Container", container_class);
			if (!container_class) LOG_INFO("container_class: %p", container_class);
			else if (container_class)
			{
				container_windowId_name = "windowId";
			}

			Java::AssignClass("net.minecraft.enchantment.EnchantmentHelper", enchantmentHelper_class);
			if (!enchantmentHelper_class) LOG_INFO("enchantmentHelper_class: %p", enchantmentHelper_class);
			else if (enchantmentHelper_class)
			{
				enchantmentHelper_getEnchantments = Java::env->GetStaticMethodID(enchantmentHelper_class, "getEnchantments", "(Lnet/minecraft/item/ItemStack;)Ljava/util/Map;");
				if (!enchantmentHelper_getEnchantments) LOG_INFO("enchantmentHelper_getEnchantments: %p", enchantmentHelper_getEnchantments);
			}

			Java::AssignClass("net.minecraft.block.Block", block_class);
			if (!block_class) LOG_INFO("block_class: %p", block_class);
			else if (block_class)
			{
				block_getIdFromBlock = Java::env->GetStaticMethodID(block_class, "getIdFromBlock", "(Lnet/minecraft/block/Block;)I");
				if (!block_getIdFromBlock) LOG_INFO("block_getIdFromBlock: %p", block_getIdFromBlock);
			}

			Java::AssignClass("", iBlockState_class);
			if (!iBlockState_class) LOG_INFO("iBlockState_class: %p", iBlockState_class);
			else if (iBlockState_class)
			{
				iBlockState_getBlock = Java::env->GetMethodID(iBlockState_class, "", "");
				if (!iBlockState_getBlock) LOG_INFO("iBlockState_getBlock: %p", iBlockState_getBlock);
			}

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			if (!axisAlignedBB_class) LOG_INFO("axisAlignedBB_class: %p", axisAlignedBB_class);
			else if (axisAlignedBB_class)
			{
				axisAlignedBB_minX = Java::env->GetFieldID(axisAlignedBB_class, "minX", "D");
				if (!axisAlignedBB_minX) LOG_INFO("axisAlignedBB_minX: %p", axisAlignedBB_minX);
				axisAlignedBB_minY = Java::env->GetFieldID(axisAlignedBB_class, "minY", "D");
				if (!axisAlignedBB_minY) LOG_INFO("axisAlignedBB_minY: %p", axisAlignedBB_minY);
				axisAlignedBB_minZ = Java::env->GetFieldID(axisAlignedBB_class, "minZ", "D");
				if (!axisAlignedBB_minZ) LOG_INFO("axisAlignedBB_minZ: %p", axisAlignedBB_minZ);
				axisAlignedBB_maxX = Java::env->GetFieldID(axisAlignedBB_class, "maxX", "D");
				if (!axisAlignedBB_maxX) LOG_INFO("axisAlignedBB_maxX: %p", axisAlignedBB_maxX);
				axisAlignedBB_maxY = Java::env->GetFieldID(axisAlignedBB_class, "maxY", "D");
				if (!axisAlignedBB_maxY) LOG_INFO("axisAlignedBB_maxY: %p", axisAlignedBB_maxY);
				axisAlignedBB_maxZ = Java::env->GetFieldID(axisAlignedBB_class, "maxZ", "D");
				if (!axisAlignedBB_maxZ) LOG_INFO("axisAlignedBB_maxZ: %p", axisAlignedBB_maxZ);
			}

			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			if (!timer_class) LOG_INFO("timer_class: %p", timer_class);
			else if (timer_class)
			{
				timer_renderPartialTicks = Java::env->GetFieldID(timer_class, "renderPartialTicks", "F");
				if (!timer_renderPartialTicks) LOG_INFO("timer_renderPartialTicks: %p", timer_renderPartialTicks);
			}

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			if (!movingObjectPosition_class) LOG_INFO("movingObjectPosition_class: %p", movingObjectPosition_class);
			else if (movingObjectPosition_class)
			{
				movingObjectPosition_hitVec = Java::env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/Vec3;");
				if (!movingObjectPosition_hitVec) LOG_INFO("movingObjectPosition_hitVec: %p", movingObjectPosition_hitVec);
				movingObjectPosition_entityHit = Java::env->GetFieldID(movingObjectPosition_class, "entityHit", "Lnet/minecraft/entity/Entity;");
				if (!movingObjectPosition_entityHit) LOG_INFO("movingObjectPosition_entityHit: %p", movingObjectPosition_entityHit);
				movingObjectPosition_typeOfHit = Java::env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_typeOfHit) LOG_INFO("movingObjectPosition_typeOfHit: %p", movingObjectPosition_typeOfHit);
				movingObjectPosition_BLOCK = Java::env->GetStaticFieldID(movingObjectPosition_class, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_BLOCK) LOG_INFO("movingObjectPosition_BLOCK: %p", movingObjectPosition_BLOCK);
			}

			Java::AssignClass("", blockPos_class);
			if (!blockPos_class) LOG_INFO("blockPos_class: %p", blockPos_class);
			else if (blockPos_class)
			{
				blockPos_constructorDouble = Java::env->GetMethodID(blockPos_class, "", "");
				if (!blockPos_constructorDouble) LOG_INFO("blockPos_constructorDouble: %p", blockPos_constructorDouble);
				blockPos_constructorInt = Java::env->GetMethodID(blockPos_class, "", "");
				if (!blockPos_constructorInt) LOG_INFO("blockPos_constructorInt: %p", blockPos_constructorInt);
			}

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			if (!vec3_class) LOG_INFO("vec3_class: %p", vec3_class);
			else if (vec3_class)
			{
				vec3_xCoord = Java::env->GetFieldID(vec3_class, "xCoord", "D");
				if (!vec3_xCoord) LOG_INFO("vec3_xCoord: %p", vec3_xCoord);
				vec3_yCoord = Java::env->GetFieldID(vec3_class, "yCoord", "D");
				if (!vec3_yCoord) LOG_INFO("vec3_yCoord: %p", vec3_yCoord);
				vec3_zCoord = Java::env->GetFieldID(vec3_class, "zCoord", "D");
				if (!vec3_zCoord) LOG_INFO("vec3_zCoord: %p", vec3_zCoord);
			}

			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			if (!netHandlerPlayClient_class) LOG_INFO("netHandlerPlayClient_class: %p", netHandlerPlayClient_class);
			else if (netHandlerPlayClient_class)
			{
				netHandlerPlayClient_getPlayerInfo = Java::env->GetMethodID(netHandlerPlayClient_class, "", "");
				if (!netHandlerPlayClient_getPlayerInfo) LOG_INFO("netHandlerPlayClient_getPlayerInfo: %p", netHandlerPlayClient_getPlayerInfo);
				netHandlerPlayClient_playerInfoList = Java::env->GetFieldID(netHandlerPlayClient_class, "playerInfoList", "Ljava/util/List;");
				if (!netHandlerPlayClient_playerInfoList) LOG_INFO("netHandlerPlayClient_playerInfoList: %p", netHandlerPlayClient_playerInfoList);
			}

			Java::AssignClass("", networkPlayerInfo_class);
			if (!networkPlayerInfo_class) LOG_INFO("networkPlayerInfo_class: %p", networkPlayerInfo_class);
			else if (networkPlayerInfo_class)
			{
				networkPlayerInfo_getResponseTime = Java::env->GetMethodID(networkPlayerInfo_class, "", "");
				if (!networkPlayerInfo_getResponseTime) LOG_INFO("networkPlayerInfo_getResponseTime: %p", networkPlayerInfo_getResponseTime);
			}

			Java::AssignClass("net.minecraft.client.gui.GuiPlayerInfo", guiPlayerInfo_class);
			if (!guiPlayerInfo_class) LOG_INFO("guiPlayerInfo_class: %p", guiPlayerInfo_class);
			else if (guiPlayerInfo_class)
			{
				guiPlayerInfo_responseTime = Java::env->GetFieldID(guiPlayerInfo_class, "responseTime", "I");
				if (!guiPlayerInfo_responseTime) LOG_INFO("guiPlayerInfo_responseTime: %p", guiPlayerInfo_responseTime);
				guiPlayerInfo_name = Java::env->GetFieldID(guiPlayerInfo_class, "name", "Ljava/lang/String;");
				if (!guiPlayerInfo_name) LOG_INFO("guiPlayerInfo_name: %p", guiPlayerInfo_name);
			}

			inventory_class_name = "net.minecraft.client.gui.inventory.GuiInventory";
			chest_gui_class_name = "net.minecraft.client.gui.inventory.GuiChest";
			vec3_class_name = "net.minecraft.util.Vec3";
		}
		else if (Java::version == MinecraftVersion::VANILLA_1_8_9)
		{
			Java::AssignClass("ave", minecraft_class);
			if (!minecraft_class) LOG_INFO("minecraft_class: %p", minecraft_class);
			else if (minecraft_class)
			{
				minecraft_getMinecraft = Java::env->GetStaticMethodID(minecraft_class, "A", "()Lave;");
				if (!minecraft_getMinecraft) LOG_INFO("minecraft_getMinecraft: %p", minecraft_getMinecraft);
				minecraft_getNetHandler = Java::env->GetMethodID(minecraft_class, "u", "()Lbcy;");
				if (!minecraft_getNetHandler) LOG_INFO("minecraft_getNetHandler: %p", minecraft_getNetHandler);
				minecraft_clickMouse = Java::env->GetMethodID(minecraft_class, "aw", "()V");
				if (!minecraft_clickMouse) LOG_INFO("minecraft_clickMouse: %p", minecraft_clickMouse);
				minecraft_thePlayer = Java::env->GetFieldID(minecraft_class, "h", "Lbew;");
				if (!minecraft_thePlayer) LOG_INFO("minecraft_thePlayer: %p", minecraft_thePlayer);
				minecraft_playerController = Java::env->GetFieldID(minecraft_class, "c", "Lbda;");
				if (!minecraft_playerController) LOG_INFO("minecraft_playerController: %p", minecraft_playerController);
				minecraft_theWorld = Java::env->GetFieldID(minecraft_class, "f", "Lbdb;");
				if (!minecraft_theWorld) LOG_INFO("minecraft_theWorld: %p", minecraft_theWorld);
				minecraft_renderManager = Java::env->GetFieldID(minecraft_class, "aa", "Lbiu;");
				if (!minecraft_renderManager) LOG_INFO("minecraft_renderManager: %p", minecraft_renderManager);
				minecraft_renderViewEntity = Java::env->GetFieldID(minecraft_class, "ad", "Lpk;");
				if (!minecraft_renderViewEntity) LOG_INFO("minecraft_renderViewEntity: %p", minecraft_renderViewEntity);
				minecraft_timer = Java::env->GetFieldID(minecraft_class, "Y", "Lavl;");
				if (!minecraft_timer) LOG_INFO("minecraft_timer: %p", minecraft_timer);
				minecraft_gameSettings = Java::env->GetFieldID(minecraft_class, "t", "Lavh;");
				if (!minecraft_gameSettings) LOG_INFO("minecraft_gameSettings: %p", minecraft_gameSettings);
				minecraft_currentScreen = Java::env->GetFieldID(minecraft_class, "m", "Laxu;");
				if (!minecraft_currentScreen) LOG_INFO("minecraft_currentScreen: %p", minecraft_currentScreen);
				minecraft_objectMouseOver = Java::env->GetFieldID(minecraft_class, "s", "Lauh;");
				if (!minecraft_objectMouseOver) LOG_INFO("minecraft_objectMouseOver: %p", minecraft_objectMouseOver);
				minecraft_launchedVersion = Java::env->GetFieldID(minecraft_class, "al", "Ljava/lang/String;");
				if (!minecraft_launchedVersion) LOG_INFO("minecraft_launchedVersion: %p", minecraft_launchedVersion);
				minecraft_debugFPS = Java::env->GetStaticFieldID(minecraft_class, "ao", "I");
				if (!minecraft_debugFPS) LOG_INFO("minecraft_debugFPS: %p", minecraft_debugFPS);
			}

			Java::AssignClass("net/minecraft/client/ClientBrandRetriever", clientBrandRetriever_class);
			if (!clientBrandRetriever_class) LOG_INFO("clientBrandRetriever_class: %p", clientBrandRetriever_class);
			else if (clientBrandRetriever_class)
			{
				clientBrandRetriever_getClientModName = Java::env->GetStaticMethodID(clientBrandRetriever_class, "getClientModName", "()Ljava/lang/String;");
				if (!clientBrandRetriever_getClientModName) LOG_INFO("clientBrandRetriever_getClientModName: %p", clientBrandRetriever_getClientModName);
			}

			Java::AssignClass("bdb", worldClient_class);
			if (!worldClient_class) LOG_INFO("worldClient_class: %p", worldClient_class);
			else if (worldClient_class)
			{
				worldClient_entityList = Java::env->GetFieldID(worldClient_class, "c", "Ljava/util/Set;");
				if (!worldClient_entityList) LOG_INFO("worldClient_entityList: %p", worldClient_entityList);
			}

			Java::AssignClass("bda", playerControllerMP_class);
			if (!playerControllerMP_class) LOG_INFO("playerControllerMP_class: %p", playerControllerMP_class);
			else if (playerControllerMP_class)
			{
				playerControllerMP_windowClick = Java::env->GetMethodID(playerControllerMP_class, "a", "(IIIILwn;)Lzx;");
				if (!playerControllerMP_windowClick) LOG_INFO("playerControllerMP_windowClick: %p", playerControllerMP_windowClick);
				playerControllerMP_getBlockReachDistance = Java::env->GetMethodID(playerControllerMP_class, "d", "()F");
				if (!playerControllerMP_getBlockReachDistance) LOG_INFO("playerControllerMP_getBlockReachDistance: %p", playerControllerMP_getBlockReachDistance);
			}

			Java::AssignClass("auz", activeRenderInfo_class);
			if (!activeRenderInfo_class) LOG_INFO("activeRenderInfo_class: %p", activeRenderInfo_class);
			else if (activeRenderInfo_class)
			{
				activeRenderInfo_PROJECTION = Java::env->GetStaticFieldID(activeRenderInfo_class, "c", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_PROJECTION) LOG_INFO("activeRenderInfo_PROJECTION: %p", activeRenderInfo_PROJECTION);
				activeRenderInfo_MODELVIEW = Java::env->GetStaticFieldID(activeRenderInfo_class, "b", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_MODELVIEW) LOG_INFO("activeRenderInfo_MODELVIEW: %p", activeRenderInfo_MODELVIEW);
			}

			Java::AssignClass("biu", renderManager_class);
			if (!renderManager_class) LOG_INFO("renderManager_class: %p", renderManager_class);
			else if (renderManager_class)
			{
				renderManager_instance = Java::env->GetStaticFieldID(renderManager_class, "", "");
				if (!renderManager_instance) LOG_INFO("renderManager_instance: %p", renderManager_instance);
				renderManager_renderPosX = Java::env->GetFieldID(renderManager_class, "o", "D");
				if (!renderManager_renderPosX) LOG_INFO("renderManager_renderPosX: %p", renderManager_renderPosX);
				renderManager_renderPosY = Java::env->GetFieldID(renderManager_class, "p", "D");
				if (!renderManager_renderPosY) LOG_INFO("renderManager_renderPosY: %p", renderManager_renderPosY);
				renderManager_renderPosZ = Java::env->GetFieldID(renderManager_class, "q", "D");
				if (!renderManager_renderPosZ) LOG_INFO("renderManager_renderPosZ: %p", renderManager_renderPosZ);
				renderManager_viewerPosX = Java::env->GetFieldID(renderManager_class, "h", "D");
				if (!renderManager_viewerPosX) LOG_INFO("renderManager_viewerPosX: %p", renderManager_viewerPosX);
				renderManager_viewerPosY = Java::env->GetFieldID(renderManager_class, "i", "D");
				if (!renderManager_viewerPosY) LOG_INFO("renderManager_viewerPosY: %p", renderManager_viewerPosY);
				renderManager_viewerPosZ = Java::env->GetFieldID(renderManager_class, "j", "D");
				if (!renderManager_viewerPosZ) LOG_INFO("renderManager_viewerPosZ: %p", renderManager_viewerPosZ);
			}

			Java::AssignClass("avh", gameSettings_class);
			if (!gameSettings_class) LOG_INFO("gameSettings_class: %p", gameSettings_class);
			else if (gameSettings_class)
			{
				gameSettings_setOptionKeyBinding = Java::env->GetMethodID(gameSettings_class, "a", "(Lavb;I)V");
				if (!gameSettings_setOptionKeyBinding) LOG_INFO("gameSettings_setOptionKeyBinding: %p", gameSettings_setOptionKeyBinding);
				gameSettings_thirdPersonView = Java::env->GetFieldID(gameSettings_class, "aB", "I");
				if (!gameSettings_thirdPersonView) LOG_INFO("gameSettings_thirdPersonView: %p", gameSettings_thirdPersonView);
				gameSettings_fovSetting = Java::env->GetFieldID(gameSettings_class, "aI", "F");
				if (!gameSettings_fovSetting) LOG_INFO("gameSettings_fovSetting: %p", gameSettings_fovSetting);
				gameSettings_keyBindFullscreen = Java::env->GetFieldID(gameSettings_class, "aq", "Lavb;");
				if (!gameSettings_keyBindFullscreen) LOG_INFO("gameSettings_keyBindFullscreen: %p", gameSettings_keyBindFullscreen);
			}

			Java::AssignClass("bew", entityPlayerSP_class);
			if (!entityPlayerSP_class) LOG_INFO("entityPlayerSP_class: %p", entityPlayerSP_class);
			else if (entityPlayerSP_class)
			{
			}

			Java::AssignClass("ayl", guiContainer_class);
			if (!guiContainer_class) LOG_INFO("guiContainer_class: %p", guiContainer_class);
			else if (guiContainer_class)
			{
				guiContainer_inventorySlots = Java::env->GetFieldID(guiContainer_class, "h", "Lxi;");
				if (!guiContainer_inventorySlots) LOG_INFO("guiContainer_inventorySlots: %p", guiContainer_inventorySlots);
			}

			Java::AssignClass("ayr", guiChest_class);
			if (!guiChest_class) LOG_INFO("guiChest_class: %p", guiChest_class);
			else if (guiChest_class)
			{
				guiChest_upperChestInventory = Java::env->GetFieldID(guiChest_class, "v", "Log;");
				if (!guiChest_upperChestInventory) LOG_INFO("guiChest_upperChestInventory: %p", guiChest_upperChestInventory);
				guiChest_lowerChestInventory = Java::env->GetFieldID(guiChest_class, "w", "Log;");
				if (!guiChest_lowerChestInventory) LOG_INFO("guiChest_lowerChestInventory: %p", guiChest_lowerChestInventory);
				guiChest_inventoryRows = Java::env->GetFieldID(guiChest_class, "x", "I");
				if (!guiChest_inventoryRows) LOG_INFO("guiChest_inventoryRows: %p", guiChest_inventoryRows);
			}

			Java::AssignClass("pk", entity_class);
			if (!entity_class) LOG_INFO("entity_class: %p", entity_class);
			else if (entity_class)
			{
				entity_getName = Java::env->GetMethodID(entity_class, "e_", "()Ljava/lang/String;");
				if (!entity_getName) LOG_INFO("entity_getName: %p", entity_getName);
				entity_isSneaking = Java::env->GetMethodID(entity_class, "av", "()Z");
				if (!entity_isSneaking) LOG_INFO("entity_isSneaking: %p", entity_isSneaking);
				entity_isSprinting = Java::env->GetMethodID(entity_class, "aw", "()Z");
				if (!entity_isSprinting) LOG_INFO("entity_isSprinting: %p", entity_isSprinting);
				entity_setSprinting = Java::env->GetMethodID(entity_class, "d", "(Z)V");
				if (!entity_setSprinting) LOG_INFO("entity_setSprinting: %p", entity_setSprinting);
				entity_isInvisibleToPlayer = Java::env->GetMethodID(entity_class, "f", "(Lwn;)Z");
				if (!entity_isInvisibleToPlayer) LOG_INFO("entity_isInvisibleToPlayer: %p", entity_isInvisibleToPlayer);
				entity_getEyeHeight = Java::env->GetMethodID(entity_class, "aS", "()F");
				if (!entity_getEyeHeight) LOG_INFO("entity_getEyeHeight: %p", entity_getEyeHeight);
				entity_posX = Java::env->GetFieldID(entity_class, "s", "D");
				if (!entity_posX) LOG_INFO("entity_posX: %p", entity_posX);
				entity_posY = Java::env->GetFieldID(entity_class, "t", "D");
				if (!entity_posY) LOG_INFO("entity_posY: %p", entity_posY);
				entity_posZ = Java::env->GetFieldID(entity_class, "u", "D");
				if (!entity_posZ) LOG_INFO("entity_posZ: %p", entity_posZ);
				entity_lastTickPosX = Java::env->GetFieldID(entity_class, "P", "D");
				if (!entity_lastTickPosX) LOG_INFO("entity_lastTickPosX: %p", entity_lastTickPosX);
				entity_lastTickPosY = Java::env->GetFieldID(entity_class, "Q", "D");
				if (!entity_lastTickPosY) LOG_INFO("entity_lastTickPosY: %p", entity_lastTickPosY);
				entity_lastTickPosZ = Java::env->GetFieldID(entity_class, "R", "D");
				if (!entity_lastTickPosZ) LOG_INFO("entity_lastTickPosZ: %p", entity_lastTickPosZ);
				entity_width = Java::env->GetFieldID(entity_class, "J", "F");
				if (!entity_width) LOG_INFO("entity_width: %p", entity_width);
				entity_height = Java::env->GetFieldID(entity_class, "K", "F");
				if (!entity_height) LOG_INFO("entity_height: %p", entity_height);
				entity_distanceWalkedModified = Java::env->GetFieldID(entity_class, "M", "F");
				if (!entity_distanceWalkedModified) LOG_INFO("entity_distanceWalkedModified: %p", entity_distanceWalkedModified);
				entity_prevDistanceWalkedModified = Java::env->GetFieldID(entity_class, "L", "F");
				if (!entity_prevDistanceWalkedModified) LOG_INFO("entity_prevDistanceWalkedModified: %p", entity_prevDistanceWalkedModified);
				entity_rotationYaw = Java::env->GetFieldID(entity_class, "y", "F");
				if (!entity_rotationYaw) LOG_INFO("entity_rotationYaw: %p", entity_rotationYaw);
				entity_rotationPitch = Java::env->GetFieldID(entity_class, "z", "F");
				if (!entity_rotationPitch) LOG_INFO("entity_rotationPitch: %p", entity_rotationPitch);
				entity_prevRotationYaw = Java::env->GetFieldID(entity_class, "A", "F");
				if (!entity_prevRotationYaw) LOG_INFO("entity_prevRotationYaw: %p", entity_prevRotationYaw);
				entity_prevRotationPitch = Java::env->GetFieldID(entity_class, "B", "F");
				if (!entity_prevRotationPitch) LOG_INFO("entity_prevRotationPitch: %p", entity_prevRotationPitch);
				entity_boundingBox = Java::env->GetFieldID(entity_class, "f", "Laug;");
				if (!entity_boundingBox) LOG_INFO("entity_boundingBox: %p", entity_boundingBox);
				entity_motionX = Java::env->GetFieldID(entity_class, "v", "D");
				if (!entity_motionX) LOG_INFO("entity_motionX: %p", entity_motionX);
				entity_motionY = Java::env->GetFieldID(entity_class, "w", "D");
				if (!entity_motionY) LOG_INFO("entity_motionY: %p", entity_motionY);
				entity_motionZ = Java::env->GetFieldID(entity_class, "x", "D");
				if (!entity_motionZ) LOG_INFO("entity_motionZ: %p", entity_motionZ);
				entity_hurtResistantTime = Java::env->GetFieldID(entity_class, "Z", "I");
				if (!entity_hurtResistantTime) LOG_INFO("entity_hurtResistantTime: %p", entity_hurtResistantTime);
			}

			Java::AssignClass("pr", entityLivingBase_class);
			if (!entityLivingBase_class) LOG_INFO("entityLivingBase_class: %p", entityLivingBase_class);
			else if (entityLivingBase_class)
			{
				entityLivingBase_getHealth = Java::env->GetMethodID(entityLivingBase_class, "bn", "()F");
				if (!entityLivingBase_getHealth) LOG_INFO("entityLivingBase_getHealth: %p", entityLivingBase_getHealth);
				entityLivingBase_getMaxHealth = Java::env->GetMethodID(entityLivingBase_class, "bu", "()F");
				if (!entityLivingBase_getMaxHealth) LOG_INFO("entityLivingBase_getMaxHealth: %p", entityLivingBase_getMaxHealth);
				entityLivingBase_canEntityBeSeen = Java::env->GetMethodID(entityLivingBase_class, "t", "(Lpk;)Z");
				if (!entityLivingBase_canEntityBeSeen) LOG_INFO("entityLivingBase_canEntityBeSeen: %p", entityLivingBase_canEntityBeSeen);
			}

			Java::AssignClass("", entityPlayerMP_class);
			if (!entityPlayerMP_class) LOG_INFO("entityPlayerMP_class: %p", entityPlayerMP_class);
			else if (entityPlayerMP_class)
			{
			}

			Java::AssignClass("wn", entityPlayer_class);
			if (!entityPlayer_class) LOG_INFO("entityPlayer_class: %p", entityPlayer_class);
			else if (entityPlayer_class)
			{
				entityPlayer_inventory = Java::env->GetFieldID(entityPlayer_class, "bi", "Lwm;");
				if (!entityPlayer_inventory) LOG_INFO("entityPlayer_inventory: %p", entityPlayer_inventory);
			}

			Java::AssignClass("wm", inventoryPlayer_class);
			if (!inventoryPlayer_class) LOG_INFO("inventoryPlayer_class: %p", inventoryPlayer_class);
			else if (inventoryPlayer_class)
			{
				inventoryPlayer_getCurrentItem = Java::env->GetMethodID(inventoryPlayer_class, "h", "()Lzx;");
				if (!inventoryPlayer_getCurrentItem) LOG_INFO("inventoryPlayer_getCurrentItem: %p", inventoryPlayer_getCurrentItem);
				inventoryPlayer_mainInventory = Java::env->GetFieldID(inventoryPlayer_class, "a", "[Lzx;");
				if (!inventoryPlayer_mainInventory) LOG_INFO("inventoryPlayer_mainInventory: %p", inventoryPlayer_mainInventory);
				inventoryPlayer_armorInventory = Java::env->GetFieldID(inventoryPlayer_class, "b", "[Lzx;");
				if (!inventoryPlayer_armorInventory) LOG_INFO("inventoryPlayer_armorInventory: %p", inventoryPlayer_armorInventory);
				inventoryPlayer_currentItem = Java::env->GetFieldID(inventoryPlayer_class, "c", "I");
				if (!inventoryPlayer_currentItem) LOG_INFO("inventoryPlayer_currentItem: %p", inventoryPlayer_currentItem);
			}

			Java::AssignClass("adm", world_class);
			if (!world_class) LOG_INFO("world_class: %p", world_class);
			else if (world_class)
			{
				world_rayTraceBlocks = Java::env->GetMethodID(world_class, "a", "(Laui;Laui;ZZZ)Lauh;");
				if (!world_rayTraceBlocks) LOG_INFO("world_rayTraceBlocks: %p", world_rayTraceBlocks);
				world_getBlockState = Java::env->GetMethodID(world_class, "p", "(Lcj;)Lalz;");
				if (!world_getBlockState) LOG_INFO("world_getBlockState: %p", world_getBlockState);
				world_getBlock = Java::env->GetMethodID(world_class, "", ";");
				if (!world_getBlock) LOG_INFO("world_getBlock: %p", world_getBlock);
				world_playerEntities = Java::env->GetFieldID(world_class, "j", "Ljava/util/List;");
				if (!world_playerEntities) LOG_INFO("world_playerEntities: %p", world_playerEntities);
			}

			Java::AssignClass("zw", item_class);
			if (!item_class) LOG_INFO("item_class: %p", item_class);
			else if (item_class)
			{
				item_getIdFromItem = Java::env->GetStaticMethodID(item_class, "b", "(Lzw;)I");
				if (!item_getIdFromItem) LOG_INFO("item_getIdFromItem: %p", item_getIdFromItem);
				item_getUnlocalizedName = Java::env->GetMethodID(item_class, "a", "()Ljava/lang/String;");
				if (!item_getUnlocalizedName) LOG_INFO("item_getUnlocalizedName: %p", item_getUnlocalizedName);
				item_getItemStackLimit = Java::env->GetMethodID(item_class, "j", "()I");
				if (!item_getItemStackLimit) LOG_INFO("item_getItemStackLimit: %p", item_getItemStackLimit);
			}

			Java::AssignClass("zx", itemStack_class);
			if (!itemStack_class) LOG_INFO("itemStack_class: %p", itemStack_class);
			else if (itemStack_class)
			{
				itemStack_getItem = Java::env->GetMethodID(itemStack_class, "b", "()Lzw;");
				if (!itemStack_getItem) LOG_INFO("itemStack_getItem: %p", itemStack_getItem);
				itemStack_getMetadata = Java::env->GetMethodID(itemStack_class, "i", "()I");
				if (!itemStack_getMetadata) LOG_INFO("itemStack_getMetadata: %p", itemStack_getMetadata);
				itemStack_getMaxDamage = Java::env->GetMethodID(itemStack_class, "j", "()I");
				if (!itemStack_getMaxDamage) LOG_INFO("itemStack_getMaxDamage: %p", itemStack_getMaxDamage);
				itemStack_stackSize = Java::env->GetFieldID(itemStack_class, "b", "I");
				if (!itemStack_stackSize) LOG_INFO("itemStack_stackSize: %p", itemStack_stackSize);
			}

			Java::AssignClass("og", iInventory_class);
			if (!iInventory_class) LOG_INFO("iInventory_class: %p", iInventory_class);
			else if (iInventory_class)
			{
				iInventory_getSizeInventory = Java::env->GetMethodID(iInventory_class, "o_", "()I");
				if (!iInventory_getSizeInventory) LOG_INFO("iInventory_getSizeInventory: %p", iInventory_getSizeInventory);
				iInventory_getStackInSlot = Java::env->GetMethodID(iInventory_class, "a", "(I)Lzx;");
				if (!iInventory_getStackInSlot) LOG_INFO("iInventory_getStackInSlot: %p", iInventory_getStackInSlot);
			}

			Java::AssignClass("xi", container_class);
			if (!container_class) LOG_INFO("container_class: %p", container_class);
			else if (container_class)
			{
				container_windowId_name = "d";
			}

			Java::AssignClass("ack", enchantmentHelper_class);
			if (!enchantmentHelper_class) LOG_INFO("enchantmentHelper_class: %p", enchantmentHelper_class);
			else if (enchantmentHelper_class)
			{
				enchantmentHelper_getEnchantments = Java::env->GetStaticMethodID(enchantmentHelper_class, "a", "(Lzx;)Ljava/util/Map;");
				if (!enchantmentHelper_getEnchantments) LOG_INFO("enchantmentHelper_getEnchantments: %p", enchantmentHelper_getEnchantments);
			}

			Java::AssignClass("afh", block_class);
			if (!block_class) LOG_INFO("block_class: %p", block_class);
			else if (block_class)
			{
				block_getIdFromBlock = Java::env->GetStaticMethodID(block_class, "a", "(Lafh;)I");
				if (!block_getIdFromBlock) LOG_INFO("block_getIdFromBlock: %p", block_getIdFromBlock);
			}

			Java::AssignClass("ama", iBlockState_class);
			if (!iBlockState_class) LOG_INFO("iBlockState_class: %p", iBlockState_class);
			else if (iBlockState_class)
			{
				iBlockState_getBlock = Java::env->GetMethodID(iBlockState_class, "c", "()Lafh;");
				if (!iBlockState_getBlock) LOG_INFO("iBlockState_getBlock: %p", iBlockState_getBlock);
			}

			Java::AssignClass("aug", axisAlignedBB_class);
			if (!axisAlignedBB_class) LOG_INFO("axisAlignedBB_class: %p", axisAlignedBB_class);
			else if (axisAlignedBB_class)
			{
				axisAlignedBB_minX = Java::env->GetFieldID(axisAlignedBB_class, "a", "D");
				if (!axisAlignedBB_minX) LOG_INFO("axisAlignedBB_minX: %p", axisAlignedBB_minX);
				axisAlignedBB_minY = Java::env->GetFieldID(axisAlignedBB_class, "b", "D");
				if (!axisAlignedBB_minY) LOG_INFO("axisAlignedBB_minY: %p", axisAlignedBB_minY);
				axisAlignedBB_minZ = Java::env->GetFieldID(axisAlignedBB_class, "c", "D");
				if (!axisAlignedBB_minZ) LOG_INFO("axisAlignedBB_minZ: %p", axisAlignedBB_minZ);
				axisAlignedBB_maxX = Java::env->GetFieldID(axisAlignedBB_class, "d", "D");
				if (!axisAlignedBB_maxX) LOG_INFO("axisAlignedBB_maxX: %p", axisAlignedBB_maxX);
				axisAlignedBB_maxY = Java::env->GetFieldID(axisAlignedBB_class, "e", "D");
				if (!axisAlignedBB_maxY) LOG_INFO("axisAlignedBB_maxY: %p", axisAlignedBB_maxY);
				axisAlignedBB_maxZ = Java::env->GetFieldID(axisAlignedBB_class, "f", "D");
				if (!axisAlignedBB_maxZ) LOG_INFO("axisAlignedBB_maxZ: %p", axisAlignedBB_maxZ);
			}

			Java::AssignClass("avl", timer_class);
			if (!timer_class) LOG_INFO("timer_class: %p", timer_class);
			else if (timer_class)
			{
				timer_renderPartialTicks = Java::env->GetFieldID(timer_class, "c", "F");
				if (!timer_renderPartialTicks) LOG_INFO("timer_renderPartialTicks: %p", timer_renderPartialTicks);
			}

			Java::AssignClass("auh", movingObjectPosition_class);
			if (!movingObjectPosition_class) LOG_INFO("movingObjectPosition_class: %p", movingObjectPosition_class);
			else if (movingObjectPosition_class)
			{
				movingObjectPosition_hitVec = Java::env->GetFieldID(movingObjectPosition_class, "c", "Laui;");
				if (!movingObjectPosition_hitVec) LOG_INFO("movingObjectPosition_hitVec: %p", movingObjectPosition_hitVec);
				movingObjectPosition_entityHit = Java::env->GetFieldID(movingObjectPosition_class, "d", "Lpk;");
				if (!movingObjectPosition_entityHit) LOG_INFO("movingObjectPosition_entityHit: %p", movingObjectPosition_entityHit);
				movingObjectPosition_typeOfHit = Java::env->GetFieldID(movingObjectPosition_class, "a", "Lauh$a;");
				if (!movingObjectPosition_typeOfHit) LOG_INFO("movingObjectPosition_typeOfHit: %p", movingObjectPosition_typeOfHit);
				movingObjectPosition_BLOCK = Java::env->GetStaticFieldID(movingObjectPosition_class, "b", "Lauh$a;");
				if (!movingObjectPosition_BLOCK) LOG_INFO("movingObjectPosition_BLOCK: %p", movingObjectPosition_BLOCK);
			}

			Java::AssignClass("cj", blockPos_class);
			if (!blockPos_class) LOG_INFO("blockPos_class: %p", blockPos_class);
			else if (blockPos_class)
			{
				blockPos_constructorDouble = Java::env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
				if (!blockPos_constructorDouble) LOG_INFO("blockPos_constructorDouble: %p", blockPos_constructorDouble);
				blockPos_constructorInt = Java::env->GetMethodID(blockPos_class, "<init>", "(III)V");
				if (!blockPos_constructorInt) LOG_INFO("blockPos_constructorInt: %p", blockPos_constructorInt);
			}

			Java::AssignClass("aui", vec3_class);
			if (!vec3_class) LOG_INFO("vec3_class: %p", vec3_class);
			else if (vec3_class)
			{
				vec3_xCoord = Java::env->GetFieldID(vec3_class, "a", "D");
				if (!vec3_xCoord) LOG_INFO("vec3_xCoord: %p", vec3_xCoord);
				vec3_yCoord = Java::env->GetFieldID(vec3_class, "b", "D");
				if (!vec3_yCoord) LOG_INFO("vec3_yCoord: %p", vec3_yCoord);
				vec3_zCoord = Java::env->GetFieldID(vec3_class, "c", "D");
				if (!vec3_zCoord) LOG_INFO("vec3_zCoord: %p", vec3_zCoord);
			}

			Java::AssignClass("bcy", netHandlerPlayClient_class);
			if (!netHandlerPlayClient_class) LOG_INFO("netHandlerPlayClient_class: %p", netHandlerPlayClient_class);
			else if (netHandlerPlayClient_class)
			{
				netHandlerPlayClient_getPlayerInfo = Java::env->GetMethodID(netHandlerPlayClient_class, "a", "(Ljava/lang/String;)Lbdc;");
				if (!netHandlerPlayClient_getPlayerInfo) LOG_INFO("netHandlerPlayClient_getPlayerInfo: %p", netHandlerPlayClient_getPlayerInfo);
				netHandlerPlayClient_playerInfoList = Java::env->GetFieldID(netHandlerPlayClient_class, "", "");
				if (!netHandlerPlayClient_playerInfoList) LOG_INFO("netHandlerPlayClient_playerInfoList: %p", netHandlerPlayClient_playerInfoList);
			}

			Java::AssignClass("bdc", networkPlayerInfo_class);
			if (!networkPlayerInfo_class) LOG_INFO("networkPlayerInfo_class: %p", networkPlayerInfo_class);
			else if (networkPlayerInfo_class)
			{
				networkPlayerInfo_getResponseTime = Java::env->GetMethodID(networkPlayerInfo_class, "c", "()I");
				if (!networkPlayerInfo_getResponseTime) LOG_INFO("networkPlayerInfo_getResponseTime: %p", networkPlayerInfo_getResponseTime);
			}

			Java::AssignClass("", guiPlayerInfo_class);
			if (!guiPlayerInfo_class) LOG_INFO("guiPlayerInfo_class: %p", guiPlayerInfo_class);
			else if (guiPlayerInfo_class)
			{
				guiPlayerInfo_responseTime = Java::env->GetFieldID(guiPlayerInfo_class, "", "");
				if (!guiPlayerInfo_responseTime) LOG_INFO("guiPlayerInfo_responseTime: %p", guiPlayerInfo_responseTime);
				guiPlayerInfo_name = Java::env->GetFieldID(guiPlayerInfo_class, "", "");
				if (!guiPlayerInfo_name) LOG_INFO("guiPlayerInfo_name: %p", guiPlayerInfo_name);
			}

			inventory_class_name = "azc";
			chest_gui_class_name = "ayr";
			vec3_class_name = "aui";
		}
		else if (Java::version == MinecraftVersion::VANILLA_1_7_10)
		{
			Java::AssignClass("bao", minecraft_class);
			if (!minecraft_class) LOG_INFO("minecraft_class: %p", minecraft_class);
			else if (minecraft_class)
			{
				minecraft_getMinecraft = Java::env->GetStaticMethodID(minecraft_class, "B", "()Lbao;");
				if (!minecraft_getMinecraft) LOG_INFO("minecraft_getMinecraft: %p", minecraft_getMinecraft);
				minecraft_getNetHandler = Java::env->GetMethodID(minecraft_class, "v", "()Lbjb;");
				if (!minecraft_getNetHandler) LOG_INFO("minecraft_getNetHandler: %p", minecraft_getNetHandler);
				minecraft_clickMouse = Java::env->GetMethodID(minecraft_class, "al", "()V");
				if (!minecraft_clickMouse) LOG_INFO("minecraft_clickMouse: %p", minecraft_clickMouse);
				minecraft_thePlayer = Java::env->GetFieldID(minecraft_class, "h", "Lbjk;");
				if (!minecraft_thePlayer) LOG_INFO("minecraft_thePlayer: %p", minecraft_thePlayer);
				minecraft_playerController = Java::env->GetFieldID(minecraft_class, "c", "Lbje;");
				if (!minecraft_playerController) LOG_INFO("minecraft_playerController: %p", minecraft_playerController);
				minecraft_theWorld = Java::env->GetFieldID(minecraft_class, "f", "Lbjf;");
				if (!minecraft_theWorld) LOG_INFO("minecraft_theWorld: %p", minecraft_theWorld);
				minecraft_renderManager = Java::env->GetFieldID(minecraft_class, "", "");
				if (!minecraft_renderManager) LOG_INFO("minecraft_renderManager: %p", minecraft_renderManager);
				minecraft_renderViewEntity = Java::env->GetFieldID(minecraft_class, "i", "Lsv;");
				if (!minecraft_renderViewEntity) LOG_INFO("minecraft_renderViewEntity: %p", minecraft_renderViewEntity);
				minecraft_timer = Java::env->GetFieldID(minecraft_class, "Q", "Lbbr;");
				if (!minecraft_timer) LOG_INFO("minecraft_timer: %p", minecraft_timer);
				minecraft_gameSettings = Java::env->GetFieldID(minecraft_class, "u", "Lbbj;");
				if (!minecraft_gameSettings) LOG_INFO("minecraft_gameSettings: %p", minecraft_gameSettings);
				minecraft_currentScreen = Java::env->GetFieldID(minecraft_class, "n", "Lbdw;");
				if (!minecraft_currentScreen) LOG_INFO("minecraft_currentScreen: %p", minecraft_currentScreen);
				minecraft_objectMouseOver = Java::env->GetFieldID(minecraft_class, "t", "Lazu;");
				if (!minecraft_objectMouseOver) LOG_INFO("minecraft_objectMouseOver: %p", minecraft_objectMouseOver);
				minecraft_launchedVersion = Java::env->GetFieldID(minecraft_class, "Z", "Ljava/lang/String;");
				if (!minecraft_launchedVersion) LOG_INFO("minecraft_launchedVersion: %p", minecraft_launchedVersion);
				minecraft_debugFPS = Java::env->GetStaticFieldID(minecraft_class, "ac", "I");
				if (!minecraft_debugFPS) LOG_INFO("minecraft_debugFPS: %p", minecraft_debugFPS);
			}

			Java::AssignClass("net/minecraft/client/ClientBrandRetriever", clientBrandRetriever_class);
			if (!clientBrandRetriever_class) LOG_INFO("clientBrandRetriever_class: %p", clientBrandRetriever_class);
			else if (clientBrandRetriever_class)
			{
				clientBrandRetriever_getClientModName = Java::env->GetStaticMethodID(clientBrandRetriever_class, "getClientModName", "()Ljava/lang/String;");
				if (!clientBrandRetriever_getClientModName) LOG_INFO("clientBrandRetriever_getClientModName: %p", clientBrandRetriever_getClientModName);
			}

			Java::AssignClass("bjf", worldClient_class);
			if (!worldClient_class) LOG_INFO("worldClient_class: %p", worldClient_class);
			else if (worldClient_class)
			{
				worldClient_entityList = Java::env->GetFieldID(worldClient_class, "J", "Ljava/util/Set;");
				if (!worldClient_entityList) LOG_INFO("worldClient_entityList: %p", worldClient_entityList);
			}

			Java::AssignClass("bje", playerControllerMP_class);
			if (!playerControllerMP_class) LOG_INFO("playerControllerMP_class: %p", playerControllerMP_class);
			else if (playerControllerMP_class)
			{
				playerControllerMP_windowClick = Java::env->GetMethodID(playerControllerMP_class, "a", "(IIIILyz;)Ladd;");
				if (!playerControllerMP_windowClick) LOG_INFO("playerControllerMP_windowClick: %p", playerControllerMP_windowClick);
				playerControllerMP_getBlockReachDistance = Java::env->GetMethodID(playerControllerMP_class, "d", "()F");
				if (!playerControllerMP_getBlockReachDistance) LOG_INFO("playerControllerMP_getBlockReachDistance: %p", playerControllerMP_getBlockReachDistance);
			}

			Java::AssignClass("baj", activeRenderInfo_class);
			if (!activeRenderInfo_class) LOG_INFO("activeRenderInfo_class: %p", activeRenderInfo_class);
			else if (activeRenderInfo_class)
			{
				activeRenderInfo_PROJECTION = Java::env->GetStaticFieldID(activeRenderInfo_class, "k", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_PROJECTION) LOG_INFO("activeRenderInfo_PROJECTION: %p", activeRenderInfo_PROJECTION);
				activeRenderInfo_MODELVIEW = Java::env->GetStaticFieldID(activeRenderInfo_class, "j", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_MODELVIEW) LOG_INFO("activeRenderInfo_MODELVIEW: %p", activeRenderInfo_MODELVIEW);
			}

			Java::AssignClass("bnn", renderManager_class);
			if (!renderManager_class) LOG_INFO("renderManager_class: %p", renderManager_class);
			else if (renderManager_class)
			{
				renderManager_instance = Java::env->GetStaticFieldID(renderManager_class, "a", "Lbnn;");
				if (!renderManager_instance) LOG_INFO("renderManager_instance: %p", renderManager_instance);
				renderManager_renderPosX = Java::env->GetStaticFieldID(renderManager_class, "b", "D");
				if (!renderManager_renderPosX) LOG_INFO("renderManager_renderPosX: %p", renderManager_renderPosX);
				renderManager_renderPosY = Java::env->GetStaticFieldID(renderManager_class, "c", "D");
				if (!renderManager_renderPosY) LOG_INFO("renderManager_renderPosY: %p", renderManager_renderPosY);
				renderManager_renderPosZ = Java::env->GetStaticFieldID(renderManager_class, "d", "D");
				if (!renderManager_renderPosZ) LOG_INFO("renderManager_renderPosZ: %p", renderManager_renderPosZ);
				renderManager_viewerPosX = Java::env->GetFieldID(renderManager_class, "m", "D");
				if (!renderManager_viewerPosX) LOG_INFO("renderManager_viewerPosX: %p", renderManager_viewerPosX);
				renderManager_viewerPosY = Java::env->GetFieldID(renderManager_class, "n", "D");
				if (!renderManager_viewerPosY) LOG_INFO("renderManager_viewerPosY: %p", renderManager_viewerPosY);
				renderManager_viewerPosZ = Java::env->GetFieldID(renderManager_class, "o", "D");
				if (!renderManager_viewerPosZ) LOG_INFO("renderManager_viewerPosZ: %p", renderManager_viewerPosZ);
			}

			Java::AssignClass("bbj", gameSettings_class);
			if (!gameSettings_class) LOG_INFO("gameSettings_class: %p", gameSettings_class);
			else if (gameSettings_class)
			{
				gameSettings_setOptionKeyBinding = Java::env->GetMethodID(gameSettings_class, "a", "(Lbal;I)V");
				if (!gameSettings_setOptionKeyBinding) LOG_INFO("gameSettings_setOptionKeyBinding: %p", gameSettings_setOptionKeyBinding);
				gameSettings_thirdPersonView = Java::env->GetFieldID(gameSettings_class, "aw", "I");
				if (!gameSettings_thirdPersonView) LOG_INFO("gameSettings_thirdPersonView: %p", gameSettings_thirdPersonView);
				gameSettings_fovSetting = Java::env->GetFieldID(gameSettings_class, "aF", "F");
				if (!gameSettings_fovSetting) LOG_INFO("gameSettings_fovSetting: %p", gameSettings_fovSetting);
				gameSettings_keyBindFullscreen = Java::env->GetFieldID(gameSettings_class, "am", "Lbal;");
				if (!gameSettings_keyBindFullscreen) LOG_INFO("gameSettings_keyBindFullscreen: %p", gameSettings_keyBindFullscreen);
			}

			Java::AssignClass("blk", entityPlayerSP_class);
			if (!entityPlayerSP_class) LOG_INFO("entityPlayerSP_class: %p", entityPlayerSP_class);
			else if (entityPlayerSP_class)
			{
			}

			Java::AssignClass("bex", guiContainer_class);
			if (!guiContainer_class) LOG_INFO("guiContainer_class: %p", guiContainer_class);
			else if (guiContainer_class)
			{
				guiContainer_inventorySlots = Java::env->GetFieldID(guiContainer_class, "h", "Lzs;");
				if (!guiContainer_inventorySlots) LOG_INFO("guiContainer_inventorySlots: %p", guiContainer_inventorySlots);
			}

			Java::AssignClass("bfi", guiChest_class);
			if (!guiChest_class) LOG_INFO("guiChest_class: %p", guiChest_class);
			else if (guiChest_class)
			{
				guiChest_upperChestInventory = Java::env->GetFieldID(guiChest_class, "v", "Lrb;");
				if (!guiChest_upperChestInventory) LOG_INFO("guiChest_upperChestInventory: %p", guiChest_upperChestInventory);
				guiChest_lowerChestInventory = Java::env->GetFieldID(guiChest_class, "w", "Lrb;");
				if (!guiChest_lowerChestInventory) LOG_INFO("guiChest_lowerChestInventory: %p", guiChest_lowerChestInventory);
				guiChest_inventoryRows = Java::env->GetFieldID(guiChest_class, "x", "I");
				if (!guiChest_inventoryRows) LOG_INFO("guiChest_inventoryRows: %p", guiChest_inventoryRows);
			}

			Java::AssignClass("sa", entity_class);
			if (!entity_class) LOG_INFO("entity_class: %p", entity_class);
			else if (entity_class)
			{
				entity_getName = Java::env->GetMethodID(entity_class, "b_", "()Ljava/lang/String;");
				if (!entity_getName) LOG_INFO("entity_getName: %p", entity_getName);
				entity_isSneaking = Java::env->GetMethodID(entity_class, "an", "()Z");
				if (!entity_isSneaking) LOG_INFO("entity_isSneaking: %p", entity_isSneaking);
				entity_isSprinting = Java::env->GetMethodID(entity_class, "ao", "()Z");
				if (!entity_isSprinting) LOG_INFO("entity_isSprinting: %p", entity_isSprinting);
				entity_setSprinting = Java::env->GetMethodID(entity_class, "c", "(Z)V");
				if (!entity_setSprinting) LOG_INFO("entity_setSprinting: %p", entity_setSprinting);
				entity_isInvisibleToPlayer = Java::env->GetMethodID(entity_class, "d", "(Lyz;)Z");
				if (!entity_isInvisibleToPlayer) LOG_INFO("entity_isInvisibleToPlayer: %p", entity_isInvisibleToPlayer);
				entity_getEyeHeight = Java::env->GetMethodID(entity_class, "g", "()F");
				if (!entity_getEyeHeight) LOG_INFO("entity_getEyeHeight: %p", entity_getEyeHeight);
				entity_posX = Java::env->GetFieldID(entity_class, "s", "D");
				if (!entity_posX) LOG_INFO("entity_posX: %p", entity_posX);
				entity_posY = Java::env->GetFieldID(entity_class, "t", "D");
				if (!entity_posY) LOG_INFO("entity_posY: %p", entity_posY);
				entity_posZ = Java::env->GetFieldID(entity_class, "u", "D");
				if (!entity_posZ) LOG_INFO("entity_posZ: %p", entity_posZ);
				entity_lastTickPosX = Java::env->GetFieldID(entity_class, "S", "D");
				if (!entity_lastTickPosX) LOG_INFO("entity_lastTickPosX: %p", entity_lastTickPosX);
				entity_lastTickPosY = Java::env->GetFieldID(entity_class, "T", "D");
				if (!entity_lastTickPosY) LOG_INFO("entity_lastTickPosY: %p", entity_lastTickPosY);
				entity_lastTickPosZ = Java::env->GetFieldID(entity_class, "U", "D");
				if (!entity_lastTickPosZ) LOG_INFO("entity_lastTickPosZ: %p", entity_lastTickPosZ);
				entity_width = Java::env->GetFieldID(entity_class, "M", "F");
				if (!entity_width) LOG_INFO("entity_width: %p", entity_width);
				entity_height = Java::env->GetFieldID(entity_class, "N", "F");
				if (!entity_height) LOG_INFO("entity_height: %p", entity_height);
				entity_distanceWalkedModified = Java::env->GetFieldID(entity_class, "P", "F");
				if (!entity_distanceWalkedModified) LOG_INFO("entity_distanceWalkedModified: %p", entity_distanceWalkedModified);
				entity_prevDistanceWalkedModified = Java::env->GetFieldID(entity_class, "O", "F");
				if (!entity_prevDistanceWalkedModified) LOG_INFO("entity_prevDistanceWalkedModified: %p", entity_prevDistanceWalkedModified);
				entity_rotationYaw = Java::env->GetFieldID(entity_class, "y", "F");
				if (!entity_rotationYaw) LOG_INFO("entity_rotationYaw: %p", entity_rotationYaw);
				entity_rotationPitch = Java::env->GetFieldID(entity_class, "z", "F");
				if (!entity_rotationPitch) LOG_INFO("entity_rotationPitch: %p", entity_rotationPitch);
				entity_prevRotationYaw = Java::env->GetFieldID(entity_class, "A", "F");
				if (!entity_prevRotationYaw) LOG_INFO("entity_prevRotationYaw: %p", entity_prevRotationYaw);
				entity_prevRotationPitch = Java::env->GetFieldID(entity_class, "B", "F");
				if (!entity_prevRotationPitch) LOG_INFO("entity_prevRotationPitch: %p", entity_prevRotationPitch);
				entity_boundingBox = Java::env->GetFieldID(entity_class, "C", "Lazt;");
				if (!entity_boundingBox) LOG_INFO("entity_boundingBox: %p", entity_boundingBox);
				entity_motionX = Java::env->GetFieldID(entity_class, "v", "D");
				if (!entity_motionX) LOG_INFO("entity_motionX: %p", entity_motionX);
				entity_motionY = Java::env->GetFieldID(entity_class, "w", "D");
				if (!entity_motionY) LOG_INFO("entity_motionY: %p", entity_motionY);
				entity_motionZ = Java::env->GetFieldID(entity_class, "x", "D");
				if (!entity_motionZ) LOG_INFO("entity_motionZ: %p", entity_motionZ);
				entity_hurtResistantTime = Java::env->GetFieldID(entity_class, "ad", "I");
				if (!entity_hurtResistantTime) LOG_INFO("entity_hurtResistantTime: %p", entity_hurtResistantTime);
			}

			Java::AssignClass("sv", entityLivingBase_class);
			if (!entityLivingBase_class) LOG_INFO("entityLivingBase_class: %p", entityLivingBase_class);
			else if (entityLivingBase_class)
			{
				entityLivingBase_getHealth = Java::env->GetMethodID(entityLivingBase_class, "aS", "()F");
				if (!entityLivingBase_getHealth) LOG_INFO("entityLivingBase_getHealth: %p", entityLivingBase_getHealth);
				entityLivingBase_getMaxHealth = Java::env->GetMethodID(entityLivingBase_class, "aY", "()F");
				if (!entityLivingBase_getMaxHealth) LOG_INFO("entityLivingBase_getMaxHealth: %p", entityLivingBase_getMaxHealth);
				entityLivingBase_canEntityBeSeen = Java::env->GetMethodID(entityLivingBase_class, "p", "(Lsa;)Z");
				if (!entityLivingBase_canEntityBeSeen) LOG_INFO("entityLivingBase_canEntityBeSeen: %p", entityLivingBase_canEntityBeSeen);
			}

			Java::AssignClass("", entityPlayerMP_class);
			if (!entityPlayerMP_class) LOG_INFO("entityPlayerMP_class: %p", entityPlayerMP_class);
			else if (entityPlayerMP_class)
			{
			}

			Java::AssignClass("yz", entityPlayer_class);
			if (!entityPlayer_class) LOG_INFO("entityPlayer_class: %p", entityPlayer_class);
			else if (entityPlayer_class)
			{
				entityPlayer_inventory = Java::env->GetFieldID(entityPlayer_class, "bm", "Lyx;");
				if (!entityPlayer_inventory) LOG_INFO("entityPlayer_inventory: %p", entityPlayer_inventory);
			}

			Java::AssignClass("yx", inventoryPlayer_class);
			if (!inventoryPlayer_class) LOG_INFO("inventoryPlayer_class: %p", inventoryPlayer_class);
			else if (inventoryPlayer_class)
			{
				inventoryPlayer_getCurrentItem = Java::env->GetMethodID(inventoryPlayer_class, "h", "()Ladd;");
				if (!inventoryPlayer_getCurrentItem) LOG_INFO("inventoryPlayer_getCurrentItem: %p", inventoryPlayer_getCurrentItem);
				inventoryPlayer_mainInventory = Java::env->GetFieldID(inventoryPlayer_class, "a", "[Ladd;");
				if (!inventoryPlayer_mainInventory) LOG_INFO("inventoryPlayer_mainInventory: %p", inventoryPlayer_mainInventory);
				inventoryPlayer_armorInventory = Java::env->GetFieldID(inventoryPlayer_class, "b", "[Ladd;");
				if (!inventoryPlayer_armorInventory) LOG_INFO("inventoryPlayer_armorInventory: %p", inventoryPlayer_armorInventory);
				inventoryPlayer_currentItem = Java::env->GetFieldID(inventoryPlayer_class, "c", "I");
				if (!inventoryPlayer_currentItem) LOG_INFO("inventoryPlayer_currentItem: %p", inventoryPlayer_currentItem);
			}

			Java::AssignClass("ahb", world_class);
			if (!world_class) LOG_INFO("world_class: %p", world_class);
			else if (world_class)
			{
				world_rayTraceBlocks = Java::env->GetMethodID(world_class, "a", "(Lazw;Lazw;ZZZ)Lazu;");
				if (!world_rayTraceBlocks) LOG_INFO("world_rayTraceBlocks: %p", world_rayTraceBlocks);
				world_getBlockState = Java::env->GetMethodID(world_class, "", "");
				if (!world_getBlockState) LOG_INFO("world_getBlockState: %p", world_getBlockState);
				world_getBlock = Java::env->GetMethodID(world_class, "a", "(III)Laji;");
				if (!world_getBlock) LOG_INFO("world_getBlock: %p", world_getBlock);
				world_playerEntities = Java::env->GetFieldID(world_class, "h", "Ljava/util/List;");
				if (!world_playerEntities) LOG_INFO("world_playerEntities: %p", world_playerEntities);
			}

			Java::AssignClass("adb", item_class);
			if (!item_class) LOG_INFO("item_class: %p", item_class);
			else if (item_class)
			{
				item_getIdFromItem = Java::env->GetStaticMethodID(item_class, "b", "(Ladb;)I");
				if (!item_getIdFromItem) LOG_INFO("item_getIdFromItem: %p", item_getIdFromItem);
				item_getUnlocalizedName = Java::env->GetMethodID(item_class, "a", "()Ljava/lang/String;");
				if (!item_getUnlocalizedName) LOG_INFO("item_getUnlocalizedName: %p", item_getUnlocalizedName);
				item_getItemStackLimit = Java::env->GetMethodID(item_class, "m", "()I");
				if (!item_getItemStackLimit) LOG_INFO("item_getItemStackLimit: %p", item_getItemStackLimit);
			}

			Java::AssignClass("add", itemStack_class);
			if (!itemStack_class) LOG_INFO("itemStack_class: %p", itemStack_class);
			else if (itemStack_class)
			{
				itemStack_getItem = Java::env->GetMethodID(itemStack_class, "b", "()Ladb;");
				if (!itemStack_getItem) LOG_INFO("itemStack_getItem: %p", itemStack_getItem);
				itemStack_getMetadata = Java::env->GetMethodID(itemStack_class, "k", "()I");
				if (!itemStack_getMetadata) LOG_INFO("itemStack_getMetadata: %p", itemStack_getMetadata);
				itemStack_getMaxDamage = Java::env->GetMethodID(itemStack_class, "l", "()I");
				if (!itemStack_getMaxDamage) LOG_INFO("itemStack_getMaxDamage: %p", itemStack_getMaxDamage);
				itemStack_stackSize = Java::env->GetFieldID(itemStack_class, "b", "I");
				if (!itemStack_stackSize) LOG_INFO("itemStack_stackSize: %p", itemStack_stackSize);
			}

			Java::AssignClass("rb", iInventory_class);
			if (!iInventory_class) LOG_INFO("iInventory_class: %p", iInventory_class);
			else if (iInventory_class)
			{
				iInventory_getSizeInventory = Java::env->GetMethodID(iInventory_class, "a", "()I");
				if (!iInventory_getSizeInventory) LOG_INFO("iInventory_getSizeInventory: %p", iInventory_getSizeInventory);
				iInventory_getStackInSlot = Java::env->GetMethodID(iInventory_class, "a", "(I)Ladd;");
				if (!iInventory_getStackInSlot) LOG_INFO("iInventory_getStackInSlot: %p", iInventory_getStackInSlot);
			}

			Java::AssignClass("zs", container_class);
			if (!container_class) LOG_INFO("container_class: %p", container_class);
			else if (container_class)
			{
				container_windowId_name = "d";
			}

			Java::AssignClass("afv", enchantmentHelper_class);
			if (!enchantmentHelper_class) LOG_INFO("enchantmentHelper_class: %p", enchantmentHelper_class);
			else if (enchantmentHelper_class)
			{
				enchantmentHelper_getEnchantments = Java::env->GetStaticMethodID(enchantmentHelper_class, "a", "(Ladd;)Ljava/util/Map;");
				if (!enchantmentHelper_getEnchantments) LOG_INFO("enchantmentHelper_getEnchantments: %p", enchantmentHelper_getEnchantments);
			}

			Java::AssignClass("aji", block_class);
			if (!block_class) LOG_INFO("block_class: %p", block_class);
			else if (block_class)
			{
				block_getIdFromBlock = Java::env->GetStaticMethodID(block_class, "b", "(Laji;)I");
				if (!block_getIdFromBlock) LOG_INFO("block_getIdFromBlock: %p", block_getIdFromBlock);
			}

			Java::AssignClass("", iBlockState_class);
			if (!iBlockState_class) LOG_INFO("iBlockState_class: %p", iBlockState_class);
			else if (iBlockState_class)
			{
				iBlockState_getBlock = Java::env->GetMethodID(iBlockState_class, "", "");
				if (!iBlockState_getBlock) LOG_INFO("iBlockState_getBlock: %p", iBlockState_getBlock);
			}

			Java::AssignClass("azt", axisAlignedBB_class);
			if (!axisAlignedBB_class) LOG_INFO("axisAlignedBB_class: %p", axisAlignedBB_class);
			else if (axisAlignedBB_class)
			{
				axisAlignedBB_minX = Java::env->GetFieldID(axisAlignedBB_class, "a", "D");
				if (!axisAlignedBB_minX) LOG_INFO("axisAlignedBB_minX: %p", axisAlignedBB_minX);
				axisAlignedBB_minY = Java::env->GetFieldID(axisAlignedBB_class, "b", "D");
				if (!axisAlignedBB_minY) LOG_INFO("axisAlignedBB_minY: %p", axisAlignedBB_minY);
				axisAlignedBB_minZ = Java::env->GetFieldID(axisAlignedBB_class, "c", "D");
				if (!axisAlignedBB_minZ) LOG_INFO("axisAlignedBB_minZ: %p", axisAlignedBB_minZ);
				axisAlignedBB_maxX = Java::env->GetFieldID(axisAlignedBB_class, "d", "D");
				if (!axisAlignedBB_maxX) LOG_INFO("axisAlignedBB_maxX: %p", axisAlignedBB_maxX);
				axisAlignedBB_maxY = Java::env->GetFieldID(axisAlignedBB_class, "e", "D");
				if (!axisAlignedBB_maxY) LOG_INFO("axisAlignedBB_maxY: %p", axisAlignedBB_maxY);
				axisAlignedBB_maxZ = Java::env->GetFieldID(axisAlignedBB_class, "f", "D");
				if (!axisAlignedBB_maxZ) LOG_INFO("axisAlignedBB_maxZ: %p", axisAlignedBB_maxZ);
			}

			Java::AssignClass("bbr", timer_class);
			if (!timer_class) LOG_INFO("timer_class: %p", timer_class);
			else if (timer_class)
			{
				timer_renderPartialTicks = Java::env->GetFieldID(timer_class, "c", "F");
				if (!timer_renderPartialTicks) LOG_INFO("timer_renderPartialTicks: %p", timer_renderPartialTicks);
			}

			Java::AssignClass("azu", movingObjectPosition_class);
			if (!movingObjectPosition_class) LOG_INFO("movingObjectPosition_class: %p", movingObjectPosition_class);
			else if (movingObjectPosition_class)
			{
				movingObjectPosition_hitVec = Java::env->GetFieldID(movingObjectPosition_class, "f", "Lazw;");
				if (!movingObjectPosition_hitVec) LOG_INFO("movingObjectPosition_hitVec: %p", movingObjectPosition_hitVec);
				movingObjectPosition_entityHit = Java::env->GetFieldID(movingObjectPosition_class, "g", "Lsa;");
				if (!movingObjectPosition_entityHit) LOG_INFO("movingObjectPosition_entityHit: %p", movingObjectPosition_entityHit);
				movingObjectPosition_typeOfHit = Java::env->GetFieldID(movingObjectPosition_class, "a", "Lazv;");
				if (!movingObjectPosition_typeOfHit) LOG_INFO("movingObjectPosition_typeOfHit: %p", movingObjectPosition_typeOfHit);
				movingObjectPosition_BLOCK = Java::env->GetStaticFieldID(movingObjectPosition_class, "b", "Lazv;");
				if (!movingObjectPosition_BLOCK) LOG_INFO("movingObjectPosition_BLOCK: %p", movingObjectPosition_BLOCK);
			}

			Java::AssignClass("", blockPos_class);
			if (!blockPos_class) LOG_INFO("blockPos_class: %p", blockPos_class);
			else if (blockPos_class)
			{
				blockPos_constructorDouble = Java::env->GetMethodID(blockPos_class, "", "");
				if (!blockPos_constructorDouble) LOG_INFO("blockPos_constructorDouble: %p", blockPos_constructorDouble);
				blockPos_constructorInt = Java::env->GetMethodID(blockPos_class, "", "");
				if (!blockPos_constructorInt) LOG_INFO("blockPos_constructorInt: %p", blockPos_constructorInt);
			}

			Java::AssignClass("azw", vec3_class);
			if (!vec3_class) LOG_INFO("vec3_class: %p", vec3_class);
			else if (vec3_class)
			{
				vec3_xCoord = Java::env->GetFieldID(vec3_class, "a", "D");
				if (!vec3_xCoord) LOG_INFO("vec3_xCoord: %p", vec3_xCoord);
				vec3_yCoord = Java::env->GetFieldID(vec3_class, "b", "D");
				if (!vec3_yCoord) LOG_INFO("vec3_yCoord: %p", vec3_yCoord);
				vec3_zCoord = Java::env->GetFieldID(vec3_class, "c", "D");
				if (!vec3_zCoord) LOG_INFO("vec3_zCoord: %p", vec3_zCoord);
			}

			Java::AssignClass("bjb", netHandlerPlayClient_class);
			if (!netHandlerPlayClient_class) LOG_INFO("netHandlerPlayClient_class: %p", netHandlerPlayClient_class);
			else if (netHandlerPlayClient_class)
			{
				netHandlerPlayClient_getPlayerInfo = Java::env->GetMethodID(netHandlerPlayClient_class, "", "");
				if (!netHandlerPlayClient_getPlayerInfo) LOG_INFO("netHandlerPlayClient_getPlayerInfo: %p", netHandlerPlayClient_getPlayerInfo);
				netHandlerPlayClient_playerInfoList = Java::env->GetFieldID(netHandlerPlayClient_class, "b", "Ljava/util/List;");
				if (!netHandlerPlayClient_playerInfoList) LOG_INFO("netHandlerPlayClient_playerInfoList: %p", netHandlerPlayClient_playerInfoList);
			}

			Java::AssignClass("", networkPlayerInfo_class);
			if (!networkPlayerInfo_class) LOG_INFO("networkPlayerInfo_class: %p", networkPlayerInfo_class);
			else if (networkPlayerInfo_class)
			{
				networkPlayerInfo_getResponseTime = Java::env->GetMethodID(networkPlayerInfo_class, "", "");
				if (!networkPlayerInfo_getResponseTime) LOG_INFO("networkPlayerInfo_getResponseTime: %p", networkPlayerInfo_getResponseTime);
			}

			Java::AssignClass("bjl", guiPlayerInfo_class);
			if (!guiPlayerInfo_class) LOG_INFO("guiPlayerInfo_class: %p", guiPlayerInfo_class);
			else if (guiPlayerInfo_class)
			{
				guiPlayerInfo_responseTime = Java::env->GetFieldID(guiPlayerInfo_class, "b", "I");
				if (!guiPlayerInfo_responseTime) LOG_INFO("guiPlayerInfo_responseTime: %p", guiPlayerInfo_responseTime);
				guiPlayerInfo_name = Java::env->GetFieldID(guiPlayerInfo_class, "a", "Ljava/lang/String;");
				if (!guiPlayerInfo_name) LOG_INFO("guiPlayerInfo_name: %p", guiPlayerInfo_name);
			}

			inventory_class_name = "bfu";
			chest_gui_class_name = "bfi";
			vec3_class_name = "azw";
		}
		else if (Java::version == MinecraftVersion::FORGE_1_8_9)
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			if (!minecraft_class) LOG_INFO("minecraft_class: %p", minecraft_class);
			else if (minecraft_class)
			{
				minecraft_getMinecraft = Java::env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
				if (!minecraft_getMinecraft) LOG_INFO("minecraft_getMinecraft: %p", minecraft_getMinecraft);
				minecraft_getNetHandler = Java::env->GetMethodID(minecraft_class, "func_147114_u", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
				if (!minecraft_getNetHandler) LOG_INFO("minecraft_getNetHandler: %p", minecraft_getNetHandler);
				minecraft_clickMouse = Java::env->GetMethodID(minecraft_class, "func_147116_af", "()V");
				if (!minecraft_clickMouse) LOG_INFO("minecraft_clickMouse: %p", minecraft_clickMouse);
				minecraft_thePlayer = Java::env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
				if (!minecraft_thePlayer) LOG_INFO("minecraft_thePlayer: %p", minecraft_thePlayer);
				minecraft_playerController = Java::env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
				if (!minecraft_playerController) LOG_INFO("minecraft_playerController: %p", minecraft_playerController);
				minecraft_theWorld = Java::env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
				if (!minecraft_theWorld) LOG_INFO("minecraft_theWorld: %p", minecraft_theWorld);
				minecraft_renderManager = Java::env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
				if (!minecraft_renderManager) LOG_INFO("minecraft_renderManager: %p", minecraft_renderManager);
				minecraft_renderViewEntity = Java::env->GetFieldID(minecraft_class, "field_175622_Z", "Lnet/minecraft/entity/Entity;");
				if (!minecraft_renderViewEntity) LOG_INFO("minecraft_renderViewEntity: %p", minecraft_renderViewEntity);
				minecraft_timer = Java::env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");
				if (!minecraft_timer) LOG_INFO("minecraft_timer: %p", minecraft_timer);
				minecraft_gameSettings = Java::env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
				if (!minecraft_gameSettings) LOG_INFO("minecraft_gameSettings: %p", minecraft_gameSettings);
				minecraft_currentScreen = Java::env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
				if (!minecraft_currentScreen) LOG_INFO("minecraft_currentScreen: %p", minecraft_currentScreen);
				minecraft_objectMouseOver = Java::env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
				if (!minecraft_objectMouseOver) LOG_INFO("minecraft_objectMouseOver: %p", minecraft_objectMouseOver);
				minecraft_launchedVersion = Java::env->GetFieldID(minecraft_class, "field_110447_Z", "Ljava/lang/String;");
				if (!minecraft_launchedVersion) LOG_INFO("minecraft_launchedVersion: %p", minecraft_launchedVersion);
				minecraft_debugFPS = Java::env->GetStaticFieldID(minecraft_class, "field_71470_ab", "I");
				if (!minecraft_debugFPS) LOG_INFO("minecraft_debugFPS: %p", minecraft_debugFPS);
			}

			Java::AssignClass("net.minecraft.client.ClientBrandRetriever", clientBrandRetriever_class);
			if (!clientBrandRetriever_class) LOG_INFO("clientBrandRetriever_class: %p", clientBrandRetriever_class);
			else if (clientBrandRetriever_class)
			{
				clientBrandRetriever_getClientModName = Java::env->GetStaticMethodID(clientBrandRetriever_class, "getClientModName", "()Ljava/lang/String;");
				if (!clientBrandRetriever_getClientModName) LOG_INFO("clientBrandRetriever_getClientModName: %p", clientBrandRetriever_getClientModName);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			if (!worldClient_class) LOG_INFO("worldClient_class: %p", worldClient_class);
			else if (worldClient_class)
			{
				worldClient_entityList = Java::env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");
				if (!worldClient_entityList) LOG_INFO("worldClient_entityList: %p", worldClient_entityList);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			if (!playerControllerMP_class) LOG_INFO("playerControllerMP_class: %p", playerControllerMP_class);
			else if (playerControllerMP_class)
			{
				playerControllerMP_windowClick = Java::env->GetMethodID(playerControllerMP_class, "func_78753_a", "(IIIILnet/minecraft/entity/player/EntityPlayer;)Lnet/minecraft/item/ItemStack;");
				if (!playerControllerMP_windowClick) LOG_INFO("playerControllerMP_windowClick: %p", playerControllerMP_windowClick);
				playerControllerMP_getBlockReachDistance = Java::env->GetMethodID(playerControllerMP_class, "func_78757_d", "()F");
				if (!playerControllerMP_getBlockReachDistance) LOG_INFO("playerControllerMP_getBlockReachDistance: %p", playerControllerMP_getBlockReachDistance);
			}

			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			if (!activeRenderInfo_class) LOG_INFO("activeRenderInfo_class: %p", activeRenderInfo_class);
			else if (activeRenderInfo_class)
			{
				activeRenderInfo_PROJECTION = Java::env->GetStaticFieldID(activeRenderInfo_class, "field_178813_c", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_PROJECTION) LOG_INFO("activeRenderInfo_PROJECTION: %p", activeRenderInfo_PROJECTION);
				activeRenderInfo_MODELVIEW = Java::env->GetStaticFieldID(activeRenderInfo_class, "field_178812_b", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_MODELVIEW) LOG_INFO("activeRenderInfo_MODELVIEW: %p", activeRenderInfo_MODELVIEW);
			}

			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			if (!renderManager_class) LOG_INFO("renderManager_class: %p", renderManager_class);
			else if (renderManager_class)
			{
				renderManager_instance = Java::env->GetStaticFieldID(renderManager_class, "", "");
				if (!renderManager_instance) LOG_INFO("renderManager_instance: %p", renderManager_instance);
				renderManager_renderPosX = Java::env->GetFieldID(renderManager_class, "field_78725_b", "D");
				if (!renderManager_renderPosX) LOG_INFO("renderManager_renderPosX: %p", renderManager_renderPosX);
				renderManager_renderPosY = Java::env->GetFieldID(renderManager_class, "field_78726_c", "D");
				if (!renderManager_renderPosY) LOG_INFO("renderManager_renderPosY: %p", renderManager_renderPosY);
				renderManager_renderPosZ = Java::env->GetFieldID(renderManager_class, "field_78723_d", "D");
				if (!renderManager_renderPosZ) LOG_INFO("renderManager_renderPosZ: %p", renderManager_renderPosZ);
				renderManager_viewerPosX = Java::env->GetFieldID(renderManager_class, "field_78730_l", "D");
				if (!renderManager_viewerPosX) LOG_INFO("renderManager_viewerPosX: %p", renderManager_viewerPosX);
				renderManager_viewerPosY = Java::env->GetFieldID(renderManager_class, "field_78731_m", "D");
				if (!renderManager_viewerPosY) LOG_INFO("renderManager_viewerPosY: %p", renderManager_viewerPosY);
				renderManager_viewerPosZ = Java::env->GetFieldID(renderManager_class, "field_78728_n", "D");
				if (!renderManager_viewerPosZ) LOG_INFO("renderManager_viewerPosZ: %p", renderManager_viewerPosZ);
			}

			Java::AssignClass("net.minecraft.client.settings.GameSettings", gameSettings_class);
			if (!gameSettings_class) LOG_INFO("gameSettings_class: %p", gameSettings_class);
			else if (gameSettings_class)
			{
				gameSettings_setOptionKeyBinding = Java::env->GetMethodID(gameSettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
				if (!gameSettings_setOptionKeyBinding) LOG_INFO("gameSettings_setOptionKeyBinding: %p", gameSettings_setOptionKeyBinding);
				gameSettings_thirdPersonView = Java::env->GetFieldID(gameSettings_class, "field_74320_O", "I");
				if (!gameSettings_thirdPersonView) LOG_INFO("gameSettings_thirdPersonView: %p", gameSettings_thirdPersonView);
				gameSettings_fovSetting = Java::env->GetFieldID(gameSettings_class, "field_74334_X", "F");
				if (!gameSettings_fovSetting) LOG_INFO("gameSettings_fovSetting: %p", gameSettings_fovSetting);
				gameSettings_keyBindFullscreen = Java::env->GetFieldID(gameSettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
				if (!gameSettings_keyBindFullscreen) LOG_INFO("gameSettings_keyBindFullscreen: %p", gameSettings_keyBindFullscreen);
			}

			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			if (!entityPlayerSP_class) LOG_INFO("entityPlayerSP_class: %p", entityPlayerSP_class);
			else if (entityPlayerSP_class)
			{
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiContainer", guiContainer_class);
			if (!guiContainer_class) LOG_INFO("guiContainer_class: %p", guiContainer_class);
			else if (guiContainer_class)
			{
				guiContainer_inventorySlots = Java::env->GetFieldID(guiContainer_class, "field_147002_h", "Lnet/minecraft/inventory/Container;");
				if (!guiContainer_inventorySlots) LOG_INFO("guiContainer_inventorySlots: %p", guiContainer_inventorySlots);
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiChest", guiChest_class);
			if (!guiChest_class) LOG_INFO("guiChest_class: %p", guiChest_class);
			else if (guiChest_class)
			{
				guiChest_upperChestInventory = Java::env->GetFieldID(guiChest_class, "field_147016_v", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_upperChestInventory) LOG_INFO("guiChest_upperChestInventory: %p", guiChest_upperChestInventory);
				guiChest_lowerChestInventory = Java::env->GetFieldID(guiChest_class, "field_147015_w", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_lowerChestInventory) LOG_INFO("guiChest_lowerChestInventory: %p", guiChest_lowerChestInventory);
				guiChest_inventoryRows = Java::env->GetFieldID(guiChest_class, "field_147018_x", "I");
				if (!guiChest_inventoryRows) LOG_INFO("guiChest_inventoryRows: %p", guiChest_inventoryRows);
			}

			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			if (!entity_class) LOG_INFO("entity_class: %p", entity_class);
			else if (entity_class)
			{
				entity_getName = Java::env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
				if (!entity_getName) LOG_INFO("entity_getName: %p", entity_getName);
				entity_isSneaking = Java::env->GetMethodID(entity_class, "func_70093_af", "()Z");
				if (!entity_isSneaking) LOG_INFO("entity_isSneaking: %p", entity_isSneaking);
				entity_isSprinting = Java::env->GetMethodID(entity_class, "func_70051_ag", "()Z");
				if (!entity_isSprinting) LOG_INFO("entity_isSprinting: %p", entity_isSprinting);
				entity_setSprinting = Java::env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
				if (!entity_setSprinting) LOG_INFO("entity_setSprinting: %p", entity_setSprinting);
				entity_isInvisibleToPlayer = Java::env->GetMethodID(entity_class, "func_98034_c", "(Lnet/minecraft/entity/player/EntityPlayer;)Z");
				if (!entity_isInvisibleToPlayer) LOG_INFO("entity_isInvisibleToPlayer: %p", entity_isInvisibleToPlayer);
				entity_getEyeHeight = Java::env->GetMethodID(entity_class, "func_70047_e", "()F");
				if (!entity_getEyeHeight) LOG_INFO("entity_getEyeHeight: %p", entity_getEyeHeight);
				entity_posX = Java::env->GetFieldID(entity_class, "field_70165_t", "D");
				if (!entity_posX) LOG_INFO("entity_posX: %p", entity_posX);
				entity_posY = Java::env->GetFieldID(entity_class, "field_70163_u", "D");
				if (!entity_posY) LOG_INFO("entity_posY: %p", entity_posY);
				entity_posZ = Java::env->GetFieldID(entity_class, "field_70161_v", "D");
				if (!entity_posZ) LOG_INFO("entity_posZ: %p", entity_posZ);
				entity_lastTickPosX = Java::env->GetFieldID(entity_class, "field_70142_S", "D");
				if (!entity_lastTickPosX) LOG_INFO("entity_lastTickPosX: %p", entity_lastTickPosX);
				entity_lastTickPosY = Java::env->GetFieldID(entity_class, "field_70137_T", "D");
				if (!entity_lastTickPosY) LOG_INFO("entity_lastTickPosY: %p", entity_lastTickPosY);
				entity_lastTickPosZ = Java::env->GetFieldID(entity_class, "field_70136_U", "D");
				if (!entity_lastTickPosZ) LOG_INFO("entity_lastTickPosZ: %p", entity_lastTickPosZ);
				entity_width = Java::env->GetFieldID(entity_class, "field_70130_N", "F");
				if (!entity_width) LOG_INFO("entity_width: %p", entity_width);
				entity_height = Java::env->GetFieldID(entity_class, "field_70131_O", "F");
				if (!entity_height) LOG_INFO("entity_height: %p", entity_height);
				entity_distanceWalkedModified = Java::env->GetFieldID(entity_class, "field_70140_Q", "F");
				if (!entity_distanceWalkedModified) LOG_INFO("entity_distanceWalkedModified: %p", entity_distanceWalkedModified);
				entity_prevDistanceWalkedModified = Java::env->GetFieldID(entity_class, "field_70141_P", "F");
				if (!entity_prevDistanceWalkedModified) LOG_INFO("entity_prevDistanceWalkedModified: %p", entity_prevDistanceWalkedModified);
				entity_rotationYaw = Java::env->GetFieldID(entity_class, "field_70177_z", "F");
				if (!entity_rotationYaw) LOG_INFO("entity_rotationYaw: %p", entity_rotationYaw);
				entity_rotationPitch = Java::env->GetFieldID(entity_class, "field_70125_A", "F");
				if (!entity_rotationPitch) LOG_INFO("entity_rotationPitch: %p", entity_rotationPitch);
				entity_prevRotationYaw = Java::env->GetFieldID(entity_class, "field_70126_B", "F");
				if (!entity_prevRotationYaw) LOG_INFO("entity_prevRotationYaw: %p", entity_prevRotationYaw);
				entity_prevRotationPitch = Java::env->GetFieldID(entity_class, "field_70127_C", "F");
				if (!entity_prevRotationPitch) LOG_INFO("entity_prevRotationPitch: %p", entity_prevRotationPitch);
				entity_boundingBox = Java::env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
				if (!entity_boundingBox) LOG_INFO("entity_boundingBox: %p", entity_boundingBox);
				entity_motionX = Java::env->GetFieldID(entity_class, "field_70159_w", "D");
				if (!entity_motionX) LOG_INFO("entity_motionX: %p", entity_motionX);
				entity_motionY = Java::env->GetFieldID(entity_class, "field_70181_x", "D");
				if (!entity_motionY) LOG_INFO("entity_motionY: %p", entity_motionY);
				entity_motionZ = Java::env->GetFieldID(entity_class, "field_70179_y", "D");
				if (!entity_motionZ) LOG_INFO("entity_motionZ: %p", entity_motionZ);
				entity_hurtResistantTime = Java::env->GetFieldID(entity_class, "field_70172_ad", "I");
				if (!entity_hurtResistantTime) LOG_INFO("entity_hurtResistantTime: %p", entity_hurtResistantTime);
			}

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			if (!entityLivingBase_class) LOG_INFO("entityLivingBase_class: %p", entityLivingBase_class);
			else if (entityLivingBase_class)
			{
				entityLivingBase_getHealth = Java::env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
				if (!entityLivingBase_getHealth) LOG_INFO("entityLivingBase_getHealth: %p", entityLivingBase_getHealth);
				entityLivingBase_getMaxHealth = Java::env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
				if (!entityLivingBase_getMaxHealth) LOG_INFO("entityLivingBase_getMaxHealth: %p", entityLivingBase_getMaxHealth);
				entityLivingBase_canEntityBeSeen = Java::env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
				if (!entityLivingBase_canEntityBeSeen) LOG_INFO("entityLivingBase_canEntityBeSeen: %p", entityLivingBase_canEntityBeSeen);
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayerMP_class);
			if (!entityPlayerMP_class) LOG_INFO("entityPlayerMP_class: %p", entityPlayerMP_class);
			else if (entityPlayerMP_class)
			{
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			if (!entityPlayer_class) LOG_INFO("entityPlayer_class: %p", entityPlayer_class);
			else if (entityPlayer_class)
			{
				entityPlayer_inventory = Java::env->GetFieldID(entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
				if (!entityPlayer_inventory) LOG_INFO("entityPlayer_inventory: %p", entityPlayer_inventory);
			}

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			if (!inventoryPlayer_class) LOG_INFO("inventoryPlayer_class: %p", inventoryPlayer_class);
			else if (inventoryPlayer_class)
			{
				inventoryPlayer_getCurrentItem = Java::env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_getCurrentItem) LOG_INFO("inventoryPlayer_getCurrentItem: %p", inventoryPlayer_getCurrentItem);
				inventoryPlayer_mainInventory = Java::env->GetFieldID(inventoryPlayer_class, "field_70462_a", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_mainInventory) LOG_INFO("inventoryPlayer_mainInventory: %p", inventoryPlayer_mainInventory);
				inventoryPlayer_armorInventory = Java::env->GetFieldID(inventoryPlayer_class, "field_70460_b", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_armorInventory) LOG_INFO("inventoryPlayer_armorInventory: %p", inventoryPlayer_armorInventory);
				inventoryPlayer_currentItem = Java::env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
				if (!inventoryPlayer_currentItem) LOG_INFO("inventoryPlayer_currentItem: %p", inventoryPlayer_currentItem);
			}

			Java::AssignClass("net.minecraft.world.World", world_class);
			if (!world_class) LOG_INFO("world_class: %p", world_class);
			else if (world_class)
			{
				world_rayTraceBlocks = Java::env->GetMethodID(world_class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
				if (!world_rayTraceBlocks) LOG_INFO("world_rayTraceBlocks: %p", world_rayTraceBlocks);
				world_getBlockState = Java::env->GetMethodID(world_class, "func_180495_p", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
				if (!world_getBlockState) LOG_INFO("world_getBlockState: %p", world_getBlockState);
				world_getBlock = Java::env->GetMethodID(world_class, "", "");
				if (!world_getBlock) LOG_INFO("world_getBlock: %p", world_getBlock);
				world_playerEntities = Java::env->GetFieldID(world_class, "field_73010_i", "Ljava/util/List;");
				if (!world_playerEntities) LOG_INFO("world_playerEntities: %p", world_playerEntities);
			}

			Java::AssignClass("net.minecraft.item.Item", item_class);
			if (!item_class) LOG_INFO("item_class: %p", item_class);
			else if (item_class)
			{
				item_getIdFromItem = Java::env->GetStaticMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
				if (!item_getIdFromItem) LOG_INFO("item_getIdFromItem: %p", item_getIdFromItem);
				item_getUnlocalizedName = Java::env->GetMethodID(item_class, "func_77658_a", "()Ljava/lang/String;");
				if (!item_getUnlocalizedName) LOG_INFO("item_getUnlocalizedName: %p", item_getUnlocalizedName);
				item_getItemStackLimit = Java::env->GetMethodID(item_class, "func_77639_j", "()I");
				if (!item_getItemStackLimit) LOG_INFO("item_getItemStackLimit: %p", item_getItemStackLimit);
			}

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			if (!itemStack_class) LOG_INFO("itemStack_class: %p", itemStack_class);
			else if (itemStack_class)
			{
				itemStack_getItem = Java::env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
				if (!itemStack_getItem) LOG_INFO("itemStack_getItem: %p", itemStack_getItem);
				itemStack_getMetadata = Java::env->GetMethodID(itemStack_class, "func_77960_j", "()I");
				if (!itemStack_getMetadata) LOG_INFO("itemStack_getMetadata: %p", itemStack_getMetadata);
				itemStack_getMaxDamage = Java::env->GetMethodID(itemStack_class, "func_77958_k", "()I");
				if (!itemStack_getMaxDamage) LOG_INFO("itemStack_getMaxDamage: %p", itemStack_getMaxDamage);
				itemStack_stackSize = Java::env->GetFieldID(itemStack_class, "field_77994_a", "I");
				if (!itemStack_stackSize) LOG_INFO("itemStack_stackSize: %p", itemStack_stackSize);
			}

			Java::AssignClass("net.minecraft.inventory.IInventory", iInventory_class);
			if (!iInventory_class) LOG_INFO("iInventory_class: %p", iInventory_class);
			else if (iInventory_class)
			{
				iInventory_getSizeInventory = Java::env->GetMethodID(iInventory_class, "func_70302_i_", "()I");
				if (!iInventory_getSizeInventory) LOG_INFO("iInventory_getSizeInventory: %p", iInventory_getSizeInventory);
				iInventory_getStackInSlot = Java::env->GetMethodID(iInventory_class, "func_70301_a", "(I)Lnet/minecraft/item/ItemStack;");
				if (!iInventory_getStackInSlot) LOG_INFO("iInventory_getStackInSlot: %p", iInventory_getStackInSlot);
			}

			Java::AssignClass("net.minecraft.inventory.Container", container_class);
			if (!container_class) LOG_INFO("container_class: %p", container_class);
			else if (container_class)
			{
				container_windowId_name = "field_75152_c";
			}

			Java::AssignClass("net.minecraft.enchantment.EnchantmentHelper", enchantmentHelper_class);
			if (!enchantmentHelper_class) LOG_INFO("enchantmentHelper_class: %p", enchantmentHelper_class);
			else if (enchantmentHelper_class)
			{
				enchantmentHelper_getEnchantments = Java::env->GetStaticMethodID(enchantmentHelper_class, "func_82781_a", "(Lnet/minecraft/item/ItemStack;)Ljava/util/Map;");
				if (!enchantmentHelper_getEnchantments) LOG_INFO("enchantmentHelper_getEnchantments: %p", enchantmentHelper_getEnchantments);
			}

			Java::AssignClass("net.minecraft.block.Block", block_class);
			if (!block_class) LOG_INFO("block_class: %p", block_class);
			else if (block_class)
			{
				block_getIdFromBlock = Java::env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
				if (!block_getIdFromBlock) LOG_INFO("block_getIdFromBlock: %p", block_getIdFromBlock);
			}

			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			if (!iBlockState_class) LOG_INFO("iBlockState_class: %p", iBlockState_class);
			else if (iBlockState_class)
			{
				iBlockState_getBlock = Java::env->GetMethodID(iBlockState_class, "func_177230_c", "()Lnet/minecraft/block/Block;");
				if (!iBlockState_getBlock) LOG_INFO("iBlockState_getBlock: %p", iBlockState_getBlock);
			}

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			if (!axisAlignedBB_class) LOG_INFO("axisAlignedBB_class: %p", axisAlignedBB_class);
			else if (axisAlignedBB_class)
			{
				axisAlignedBB_minX = Java::env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
				if (!axisAlignedBB_minX) LOG_INFO("axisAlignedBB_minX: %p", axisAlignedBB_minX);
				axisAlignedBB_minY = Java::env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
				if (!axisAlignedBB_minY) LOG_INFO("axisAlignedBB_minY: %p", axisAlignedBB_minY);
				axisAlignedBB_minZ = Java::env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
				if (!axisAlignedBB_minZ) LOG_INFO("axisAlignedBB_minZ: %p", axisAlignedBB_minZ);
				axisAlignedBB_maxX = Java::env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
				if (!axisAlignedBB_maxX) LOG_INFO("axisAlignedBB_maxX: %p", axisAlignedBB_maxX);
				axisAlignedBB_maxY = Java::env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
				if (!axisAlignedBB_maxY) LOG_INFO("axisAlignedBB_maxY: %p", axisAlignedBB_maxY);
				axisAlignedBB_maxZ = Java::env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
				if (!axisAlignedBB_maxZ) LOG_INFO("axisAlignedBB_maxZ: %p", axisAlignedBB_maxZ);
			}

			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			if (!timer_class) LOG_INFO("timer_class: %p", timer_class);
			else if (timer_class)
			{
				timer_renderPartialTicks = Java::env->GetFieldID(timer_class, "field_74281_c", "F");
				if (!timer_renderPartialTicks) LOG_INFO("timer_renderPartialTicks: %p", timer_renderPartialTicks);
			}

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			if (!movingObjectPosition_class) LOG_INFO("movingObjectPosition_class: %p", movingObjectPosition_class);
			else if (movingObjectPosition_class)
			{
				movingObjectPosition_hitVec = Java::env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/Vec3;");
				if (!movingObjectPosition_hitVec) LOG_INFO("movingObjectPosition_hitVec: %p", movingObjectPosition_hitVec);
				movingObjectPosition_entityHit = Java::env->GetFieldID(movingObjectPosition_class, "field_72308_g", "Lnet/minecraft/entity/Entity;");
				if (!movingObjectPosition_entityHit) LOG_INFO("movingObjectPosition_entityHit: %p", movingObjectPosition_entityHit);
				movingObjectPosition_typeOfHit = Java::env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_typeOfHit) LOG_INFO("movingObjectPosition_typeOfHit: %p", movingObjectPosition_typeOfHit);
				movingObjectPosition_BLOCK = Java::env->GetStaticFieldID(movingObjectPosition_class, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_BLOCK) LOG_INFO("movingObjectPosition_BLOCK: %p", movingObjectPosition_BLOCK);
			}

			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			if (!blockPos_class) LOG_INFO("blockPos_class: %p", blockPos_class);
			else if (blockPos_class)
			{
				blockPos_constructorDouble = Java::env->GetMethodID(blockPos_class, "<init>", "(DDD)V");
				if (!blockPos_constructorDouble) LOG_INFO("blockPos_constructorDouble: %p", blockPos_constructorDouble);
				blockPos_constructorInt = Java::env->GetMethodID(blockPos_class, "<init>", "(III)V");
				if (!blockPos_constructorInt) LOG_INFO("blockPos_constructorInt: %p", blockPos_constructorInt);
			}

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			if (!vec3_class) LOG_INFO("vec3_class: %p", vec3_class);
			else if (vec3_class)
			{
				vec3_xCoord = Java::env->GetFieldID(vec3_class, "field_72450_a", "D");
				if (!vec3_xCoord) LOG_INFO("vec3_xCoord: %p", vec3_xCoord);
				vec3_yCoord = Java::env->GetFieldID(vec3_class, "field_72448_b", "D");
				if (!vec3_yCoord) LOG_INFO("vec3_yCoord: %p", vec3_yCoord);
				vec3_zCoord = Java::env->GetFieldID(vec3_class, "field_72449_c", "D");
				if (!vec3_zCoord) LOG_INFO("vec3_zCoord: %p", vec3_zCoord);
			}

			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			if (!netHandlerPlayClient_class) LOG_INFO("netHandlerPlayClient_class: %p", netHandlerPlayClient_class);
			else if (netHandlerPlayClient_class)
			{
				netHandlerPlayClient_getPlayerInfo = Java::env->GetMethodID(netHandlerPlayClient_class, "func_175104_a", "(Ljava/lang/String;)Lnet/minecraft/client/network/NetworkPlayerInfo;");
				if (!netHandlerPlayClient_getPlayerInfo) LOG_INFO("netHandlerPlayClient_getPlayerInfo: %p", netHandlerPlayClient_getPlayerInfo);
				netHandlerPlayClient_playerInfoList = Java::env->GetFieldID(netHandlerPlayClient_class, "", "");
				if (!netHandlerPlayClient_playerInfoList) LOG_INFO("netHandlerPlayClient_playerInfoList: %p", netHandlerPlayClient_playerInfoList);
			}

			Java::AssignClass("net.minecraft.client.network.NetworkPlayerInfo", networkPlayerInfo_class);
			if (!networkPlayerInfo_class) LOG_INFO("networkPlayerInfo_class: %p", networkPlayerInfo_class);
			else if (networkPlayerInfo_class)
			{
				networkPlayerInfo_getResponseTime = Java::env->GetMethodID(networkPlayerInfo_class, "func_178853_c", "()I");
				if (!networkPlayerInfo_getResponseTime) LOG_INFO("networkPlayerInfo_getResponseTime: %p", networkPlayerInfo_getResponseTime);
			}

			Java::AssignClass("", guiPlayerInfo_class);
			if (!guiPlayerInfo_class) LOG_INFO("guiPlayerInfo_class: %p", guiPlayerInfo_class);
			else if (guiPlayerInfo_class)
			{
				guiPlayerInfo_responseTime = Java::env->GetFieldID(guiPlayerInfo_class, "", "");
				if (!guiPlayerInfo_responseTime) LOG_INFO("guiPlayerInfo_responseTime: %p", guiPlayerInfo_responseTime);
				guiPlayerInfo_name = Java::env->GetFieldID(guiPlayerInfo_class, "", "");
				if (!guiPlayerInfo_name) LOG_INFO("guiPlayerInfo_name: %p", guiPlayerInfo_name);
			}

			inventory_class_name = "net.minecraft.client.gui.inventory.GuiInventory";
			chest_gui_class_name = "net.minecraft.client.gui.inventory.GuiChest";
			vec3_class_name = "net.minecraft.util.Vec3";
		}
		else if (Java::version == MinecraftVersion::FORGE_1_7_10)
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			if (!minecraft_class) LOG_INFO("minecraft_class: %p", minecraft_class);
			else if (minecraft_class)
			{
				minecraft_getMinecraft = Java::env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
				if (!minecraft_getMinecraft) LOG_INFO("minecraft_getMinecraft: %p", minecraft_getMinecraft);
				minecraft_getNetHandler = Java::env->GetMethodID(minecraft_class, "func_147114_u", "()Lnet/minecraft/client/network/NetHandlerPlayClient;");
				if (!minecraft_getNetHandler) LOG_INFO("minecraft_getNetHandler: %p", minecraft_getNetHandler);
				minecraft_clickMouse = Java::env->GetMethodID(minecraft_class, "func_147116_af", "()V");
				if (!minecraft_clickMouse) LOG_INFO("minecraft_clickMouse: %p", minecraft_clickMouse);
				minecraft_thePlayer = Java::env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
				if (!minecraft_thePlayer) LOG_INFO("minecraft_thePlayer: %p", minecraft_thePlayer);
				minecraft_playerController = Java::env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
				if (!minecraft_playerController) LOG_INFO("minecraft_playerController: %p", minecraft_playerController);
				minecraft_theWorld = Java::env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
				if (!minecraft_theWorld) LOG_INFO("minecraft_theWorld: %p", minecraft_theWorld);
				minecraft_renderManager = Java::env->GetFieldID(minecraft_class, "", "");
				if (!minecraft_renderManager) LOG_INFO("minecraft_renderManager: %p", minecraft_renderManager);
				minecraft_renderViewEntity = Java::env->GetFieldID(minecraft_class, "field_71451_h", "Lnet/minecraft/entity/EntityLivingBase;");
				if (!minecraft_renderViewEntity) LOG_INFO("minecraft_renderViewEntity: %p", minecraft_renderViewEntity);
				minecraft_timer = Java::env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");
				if (!minecraft_timer) LOG_INFO("minecraft_timer: %p", minecraft_timer);
				minecraft_gameSettings = Java::env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
				if (!minecraft_gameSettings) LOG_INFO("minecraft_gameSettings: %p", minecraft_gameSettings);
				minecraft_currentScreen = Java::env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
				if (!minecraft_currentScreen) LOG_INFO("minecraft_currentScreen: %p", minecraft_currentScreen);
				minecraft_objectMouseOver = Java::env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
				if (!minecraft_objectMouseOver) LOG_INFO("minecraft_objectMouseOver: %p", minecraft_objectMouseOver);
				minecraft_launchedVersion = Java::env->GetFieldID(minecraft_class, "field_110447_Z", "Ljava/lang/String;");
				if (!minecraft_launchedVersion) LOG_INFO("minecraft_launchedVersion: %p", minecraft_launchedVersion);
				minecraft_debugFPS = Java::env->GetStaticFieldID(minecraft_class, "field_71470_ab", "I");
				if (!minecraft_debugFPS) LOG_INFO("minecraft_debugFPS: %p", minecraft_debugFPS);
			}

			Java::AssignClass("net.minecraft.client.ClientBrandRetriever", clientBrandRetriever_class);
			if (!clientBrandRetriever_class) LOG_INFO("clientBrandRetriever_class: %p", clientBrandRetriever_class);
			else if (clientBrandRetriever_class)
			{
				clientBrandRetriever_getClientModName = Java::env->GetStaticMethodID(clientBrandRetriever_class, "getClientModName", "()Ljava/lang/String;");
				if (!clientBrandRetriever_getClientModName) LOG_INFO("clientBrandRetriever_getClientModName: %p", clientBrandRetriever_getClientModName);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			if (!worldClient_class) LOG_INFO("worldClient_class: %p", worldClient_class);
			else if (worldClient_class)
			{
				worldClient_entityList = Java::env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");
				if (!worldClient_entityList) LOG_INFO("worldClient_entityList: %p", worldClient_entityList);
			}

			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			if (!playerControllerMP_class) LOG_INFO("playerControllerMP_class: %p", playerControllerMP_class);
			else if (playerControllerMP_class)
			{
				playerControllerMP_windowClick = Java::env->GetMethodID(playerControllerMP_class, "func_78753_a", "(IIIILnet/minecraft/entity/player/EntityPlayer;)Lnet/minecraft/item/ItemStack;");
				if (!playerControllerMP_windowClick) LOG_INFO("playerControllerMP_windowClick: %p", playerControllerMP_windowClick);
				playerControllerMP_getBlockReachDistance = Java::env->GetMethodID(playerControllerMP_class, "func_78757_d", "()F");
				if (!playerControllerMP_getBlockReachDistance) LOG_INFO("playerControllerMP_getBlockReachDistance: %p", playerControllerMP_getBlockReachDistance);
			}

			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			if (!activeRenderInfo_class) LOG_INFO("activeRenderInfo_class: %p", activeRenderInfo_class);
			else if (activeRenderInfo_class)
			{
				activeRenderInfo_PROJECTION = Java::env->GetStaticFieldID(activeRenderInfo_class, "field_74595_k", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_PROJECTION) LOG_INFO("activeRenderInfo_PROJECTION: %p", activeRenderInfo_PROJECTION);
				activeRenderInfo_MODELVIEW = Java::env->GetStaticFieldID(activeRenderInfo_class, "field_74594_j", "Ljava/nio/FloatBuffer;");
				if (!activeRenderInfo_MODELVIEW) LOG_INFO("activeRenderInfo_MODELVIEW: %p", activeRenderInfo_MODELVIEW);
			}

			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			if (!renderManager_class) LOG_INFO("renderManager_class: %p", renderManager_class);
			else if (renderManager_class)
			{
				renderManager_instance = Java::env->GetStaticFieldID(renderManager_class, "field_78727_a", "Lnet/minecraft/client/renderer/entity/RenderManager;");
				if (!renderManager_instance) LOG_INFO("renderManager_instance: %p", renderManager_instance);
				renderManager_renderPosX = Java::env->GetStaticFieldID(renderManager_class, "field_78725_b", "D");
				if (!renderManager_renderPosX) LOG_INFO("renderManager_renderPosX: %p", renderManager_renderPosX);
				renderManager_renderPosY = Java::env->GetStaticFieldID(renderManager_class, "field_78726_c", "D");
				if (!renderManager_renderPosY) LOG_INFO("renderManager_renderPosY: %p", renderManager_renderPosY);
				renderManager_renderPosZ = Java::env->GetStaticFieldID(renderManager_class, "field_78723_d", "D");
				if (!renderManager_renderPosZ) LOG_INFO("renderManager_renderPosZ: %p", renderManager_renderPosZ);
				renderManager_viewerPosX = Java::env->GetFieldID(renderManager_class, "field_78730_l", "D");
				if (!renderManager_viewerPosX) LOG_INFO("renderManager_viewerPosX: %p", renderManager_viewerPosX);
				renderManager_viewerPosY = Java::env->GetFieldID(renderManager_class, "field_78731_m", "D");
				if (!renderManager_viewerPosY) LOG_INFO("renderManager_viewerPosY: %p", renderManager_viewerPosY);
				renderManager_viewerPosZ = Java::env->GetFieldID(renderManager_class, "field_78728_n", "D");
				if (!renderManager_viewerPosZ) LOG_INFO("renderManager_viewerPosZ: %p", renderManager_viewerPosZ);
			}

			Java::AssignClass("net.minecraft.client.settings.GameSettings", gameSettings_class);
			if (!gameSettings_class) LOG_INFO("gameSettings_class: %p", gameSettings_class);
			else if (gameSettings_class)
			{
				gameSettings_setOptionKeyBinding = Java::env->GetMethodID(gameSettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
				if (!gameSettings_setOptionKeyBinding) LOG_INFO("gameSettings_setOptionKeyBinding: %p", gameSettings_setOptionKeyBinding);
				gameSettings_thirdPersonView = Java::env->GetFieldID(gameSettings_class, "field_74320_O", "I");
				if (!gameSettings_thirdPersonView) LOG_INFO("gameSettings_thirdPersonView: %p", gameSettings_thirdPersonView);
				gameSettings_fovSetting = Java::env->GetFieldID(gameSettings_class, "field_74334_X", "F");
				if (!gameSettings_fovSetting) LOG_INFO("gameSettings_fovSetting: %p", gameSettings_fovSetting);
				gameSettings_keyBindFullscreen = Java::env->GetFieldID(gameSettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
				if (!gameSettings_keyBindFullscreen) LOG_INFO("gameSettings_keyBindFullscreen: %p", gameSettings_keyBindFullscreen);
			}

			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			if (!entityPlayerSP_class) LOG_INFO("entityPlayerSP_class: %p", entityPlayerSP_class);
			else if (entityPlayerSP_class)
			{
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiContainer", guiContainer_class);
			if (!guiContainer_class) LOG_INFO("guiContainer_class: %p", guiContainer_class);
			else if (guiContainer_class)
			{
				guiContainer_inventorySlots = Java::env->GetFieldID(guiContainer_class, "field_147002_h", "Lnet/minecraft/inventory/Container;");
				if (!guiContainer_inventorySlots) LOG_INFO("guiContainer_inventorySlots: %p", guiContainer_inventorySlots);
			}

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiChest", guiChest_class);
			if (!guiChest_class) LOG_INFO("guiChest_class: %p", guiChest_class);
			else if (guiChest_class)
			{
				guiChest_upperChestInventory = Java::env->GetFieldID(guiChest_class, "field_147016_v", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_upperChestInventory) LOG_INFO("guiChest_upperChestInventory: %p", guiChest_upperChestInventory);
				guiChest_lowerChestInventory = Java::env->GetFieldID(guiChest_class, "field_147015_w", "Lnet/minecraft/inventory/IInventory;");
				if (!guiChest_lowerChestInventory) LOG_INFO("guiChest_lowerChestInventory: %p", guiChest_lowerChestInventory);
				guiChest_inventoryRows = Java::env->GetFieldID(guiChest_class, "field_147018_x", "I");
				if (!guiChest_inventoryRows) LOG_INFO("guiChest_inventoryRows: %p", guiChest_inventoryRows);
			}

			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			if (!entity_class) LOG_INFO("entity_class: %p", entity_class);
			else if (entity_class)
			{
				entity_getName = Java::env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
				if (!entity_getName) LOG_INFO("entity_getName: %p", entity_getName);
				entity_isSneaking = Java::env->GetMethodID(entity_class, "func_70093_af", "()Z");
				if (!entity_isSneaking) LOG_INFO("entity_isSneaking: %p", entity_isSneaking);
				entity_isSprinting = Java::env->GetMethodID(entity_class, "func_70051_ag", "()Z");
				if (!entity_isSprinting) LOG_INFO("entity_isSprinting: %p", entity_isSprinting);
				entity_setSprinting = Java::env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
				if (!entity_setSprinting) LOG_INFO("entity_setSprinting: %p", entity_setSprinting);
				entity_isInvisibleToPlayer = Java::env->GetMethodID(entity_class, "func_98034_c", "(Lnet/minecraft/entity/player/EntityPlayer;)Z");
				if (!entity_isInvisibleToPlayer) LOG_INFO("entity_isInvisibleToPlayer: %p", entity_isInvisibleToPlayer);
				entity_getEyeHeight = Java::env->GetMethodID(entity_class, "func_70047_e", "()F");
				if (!entity_getEyeHeight) LOG_INFO("entity_getEyeHeight: %p", entity_getEyeHeight);
				entity_posX = Java::env->GetFieldID(entity_class, "field_70165_t", "D");
				if (!entity_posX) LOG_INFO("entity_posX: %p", entity_posX);
				entity_posY = Java::env->GetFieldID(entity_class, "field_70163_u", "D");
				if (!entity_posY) LOG_INFO("entity_posY: %p", entity_posY);
				entity_posZ = Java::env->GetFieldID(entity_class, "field_70161_v", "D");
				if (!entity_posZ) LOG_INFO("entity_posZ: %p", entity_posZ);
				entity_lastTickPosX = Java::env->GetFieldID(entity_class, "field_70142_S", "D");
				if (!entity_lastTickPosX) LOG_INFO("entity_lastTickPosX: %p", entity_lastTickPosX);
				entity_lastTickPosY = Java::env->GetFieldID(entity_class, "field_70137_T", "D");
				if (!entity_lastTickPosY) LOG_INFO("entity_lastTickPosY: %p", entity_lastTickPosY);
				entity_lastTickPosZ = Java::env->GetFieldID(entity_class, "field_70136_U", "D");
				if (!entity_lastTickPosZ) LOG_INFO("entity_lastTickPosZ: %p", entity_lastTickPosZ);
				entity_width = Java::env->GetFieldID(entity_class, "field_70130_N", "F");
				if (!entity_width) LOG_INFO("entity_width: %p", entity_width);
				entity_height = Java::env->GetFieldID(entity_class, "field_70131_O", "F");
				if (!entity_height) LOG_INFO("entity_height: %p", entity_height);
				entity_distanceWalkedModified = Java::env->GetFieldID(entity_class, "field_70140_Q", "F");
				if (!entity_distanceWalkedModified) LOG_INFO("entity_distanceWalkedModified: %p", entity_distanceWalkedModified);
				entity_prevDistanceWalkedModified = Java::env->GetFieldID(entity_class, "field_70141_P", "F");
				if (!entity_prevDistanceWalkedModified) LOG_INFO("entity_prevDistanceWalkedModified: %p", entity_prevDistanceWalkedModified);
				entity_rotationYaw = Java::env->GetFieldID(entity_class, "field_70177_z", "F");
				if (!entity_rotationYaw) LOG_INFO("entity_rotationYaw: %p", entity_rotationYaw);
				entity_rotationPitch = Java::env->GetFieldID(entity_class, "field_70125_A", "F");
				if (!entity_rotationPitch) LOG_INFO("entity_rotationPitch: %p", entity_rotationPitch);
				entity_prevRotationYaw = Java::env->GetFieldID(entity_class, "field_70126_B", "F");
				if (!entity_prevRotationYaw) LOG_INFO("entity_prevRotationYaw: %p", entity_prevRotationYaw);
				entity_prevRotationPitch = Java::env->GetFieldID(entity_class, "field_70127_C", "F");
				if (!entity_prevRotationPitch) LOG_INFO("entity_prevRotationPitch: %p", entity_prevRotationPitch);
				entity_boundingBox = Java::env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
				if (!entity_boundingBox) LOG_INFO("entity_boundingBox: %p", entity_boundingBox);
				entity_motionX = Java::env->GetFieldID(entity_class, "field_70159_w", "D");
				if (!entity_motionX) LOG_INFO("entity_motionX: %p", entity_motionX);
				entity_motionY = Java::env->GetFieldID(entity_class, "field_70181_x", "D");
				if (!entity_motionY) LOG_INFO("entity_motionY: %p", entity_motionY);
				entity_motionZ = Java::env->GetFieldID(entity_class, "field_70179_y", "D");
				if (!entity_motionZ) LOG_INFO("entity_motionZ: %p", entity_motionZ);
				entity_hurtResistantTime = Java::env->GetFieldID(entity_class, "field_70172_ad", "I");
				if (!entity_hurtResistantTime) LOG_INFO("entity_hurtResistantTime: %p", entity_hurtResistantTime);
			}

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			if (!entityLivingBase_class) LOG_INFO("entityLivingBase_class: %p", entityLivingBase_class);
			else if (entityLivingBase_class)
			{
				entityLivingBase_getHealth = Java::env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
				if (!entityLivingBase_getHealth) LOG_INFO("entityLivingBase_getHealth: %p", entityLivingBase_getHealth);
				entityLivingBase_getMaxHealth = Java::env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
				if (!entityLivingBase_getMaxHealth) LOG_INFO("entityLivingBase_getMaxHealth: %p", entityLivingBase_getMaxHealth);
				entityLivingBase_canEntityBeSeen = Java::env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
				if (!entityLivingBase_canEntityBeSeen) LOG_INFO("entityLivingBase_canEntityBeSeen: %p", entityLivingBase_canEntityBeSeen);
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayerMP_class);
			if (!entityPlayerMP_class) LOG_INFO("entityPlayerMP_class: %p", entityPlayerMP_class);
			else if (entityPlayerMP_class)
			{
			}

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			if (!entityPlayer_class) LOG_INFO("entityPlayer_class: %p", entityPlayer_class);
			else if (entityPlayer_class)
			{
				entityPlayer_inventory = Java::env->GetFieldID(entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
				if (!entityPlayer_inventory) LOG_INFO("entityPlayer_inventory: %p", entityPlayer_inventory);
			}

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			if (!inventoryPlayer_class) LOG_INFO("inventoryPlayer_class: %p", inventoryPlayer_class);
			else if (inventoryPlayer_class)
			{
				inventoryPlayer_getCurrentItem = Java::env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_getCurrentItem) LOG_INFO("inventoryPlayer_getCurrentItem: %p", inventoryPlayer_getCurrentItem);
				inventoryPlayer_mainInventory = Java::env->GetFieldID(inventoryPlayer_class, "field_70462_a", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_mainInventory) LOG_INFO("inventoryPlayer_mainInventory: %p", inventoryPlayer_mainInventory);
				inventoryPlayer_armorInventory = Java::env->GetFieldID(inventoryPlayer_class, "field_70460_b", "[Lnet/minecraft/item/ItemStack;");
				if (!inventoryPlayer_armorInventory) LOG_INFO("inventoryPlayer_armorInventory: %p", inventoryPlayer_armorInventory);
				inventoryPlayer_currentItem = Java::env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
				if (!inventoryPlayer_currentItem) LOG_INFO("inventoryPlayer_currentItem: %p", inventoryPlayer_currentItem);
			}

			Java::AssignClass("net.minecraft.world.World", world_class);
			if (!world_class) LOG_INFO("world_class: %p", world_class);
			else if (world_class)
			{
				world_rayTraceBlocks = Java::env->GetMethodID(world_class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
				if (!world_rayTraceBlocks) LOG_INFO("world_rayTraceBlocks: %p", world_rayTraceBlocks);
				world_getBlockState = Java::env->GetMethodID(world_class, "", "");
				if (!world_getBlockState) LOG_INFO("world_getBlockState: %p", world_getBlockState);
				world_getBlock = Java::env->GetMethodID(world_class, "func_147439_a", "(III)Lnet/minecraft/block/Block;");
				if (!world_getBlock) LOG_INFO("world_getBlock: %p", world_getBlock);
				world_playerEntities = Java::env->GetFieldID(world_class, "field_73010_i", "Ljava/util/List;");
				if (!world_playerEntities) LOG_INFO("world_playerEntities: %p", world_playerEntities);
			}

			Java::AssignClass("net.minecraft.item.Item", item_class);
			if (!item_class) LOG_INFO("item_class: %p", item_class);
			else if (item_class)
			{
				item_getIdFromItem = Java::env->GetStaticMethodID(item_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
				if (!item_getIdFromItem) LOG_INFO("item_getIdFromItem: %p", item_getIdFromItem);
				item_getUnlocalizedName = Java::env->GetMethodID(item_class, "func_77658_a", "()Ljava/lang/String;");
				if (!item_getUnlocalizedName) LOG_INFO("item_getUnlocalizedName: %p", item_getUnlocalizedName);
				item_getItemStackLimit = Java::env->GetMethodID(item_class, "func_77639_j", "()I");
				if (!item_getItemStackLimit) LOG_INFO("item_getItemStackLimit: %p", item_getItemStackLimit);
			}

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			if (!itemStack_class) LOG_INFO("itemStack_class: %p", itemStack_class);
			else if (itemStack_class)
			{
				itemStack_getItem = Java::env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
				if (!itemStack_getItem) LOG_INFO("itemStack_getItem: %p", itemStack_getItem);
				itemStack_getMetadata = Java::env->GetMethodID(itemStack_class, "func_77960_j", "()I");
				if (!itemStack_getMetadata) LOG_INFO("itemStack_getMetadata: %p", itemStack_getMetadata);
				itemStack_getMaxDamage = Java::env->GetMethodID(itemStack_class, "func_77958_k", "()I");
				if (!itemStack_getMaxDamage) LOG_INFO("itemStack_getMaxDamage: %p", itemStack_getMaxDamage);
				itemStack_stackSize = Java::env->GetFieldID(itemStack_class, "field_77994_a", "I");
				if (!itemStack_stackSize) LOG_INFO("itemStack_stackSize: %p", itemStack_stackSize);
			}

			Java::AssignClass("net.minecraft.inventory.IInventory", iInventory_class);
			if (!iInventory_class) LOG_INFO("iInventory_class: %p", iInventory_class);
			else if (iInventory_class)
			{
				iInventory_getSizeInventory = Java::env->GetMethodID(iInventory_class, "func_70302_i_", "()I");
				if (!iInventory_getSizeInventory) LOG_INFO("iInventory_getSizeInventory: %p", iInventory_getSizeInventory);
				iInventory_getStackInSlot = Java::env->GetMethodID(iInventory_class, "func_70301_a", "(I)Lnet/minecraft/item/ItemStack;");
				if (!iInventory_getStackInSlot) LOG_INFO("iInventory_getStackInSlot: %p", iInventory_getStackInSlot);
			}

			Java::AssignClass("net.minecraft.inventory.Container", container_class);
			if (!container_class) LOG_INFO("container_class: %p", container_class);
			else if (container_class)
			{
				container_windowId_name = "field_75152_c";
			}

			Java::AssignClass("net.minecraft.enchantment.EnchantmentHelper", enchantmentHelper_class);
			if (!enchantmentHelper_class) LOG_INFO("enchantmentHelper_class: %p", enchantmentHelper_class);
			else if (enchantmentHelper_class)
			{
				enchantmentHelper_getEnchantments = Java::env->GetStaticMethodID(enchantmentHelper_class, "func_82781_a", "(Lnet/minecraft/item/ItemStack;)Ljava/util/Map;");
				if (!enchantmentHelper_getEnchantments) LOG_INFO("enchantmentHelper_getEnchantments: %p", enchantmentHelper_getEnchantments);
			}

			Java::AssignClass("net.minecraft.block.Block", block_class);
			if (!block_class) LOG_INFO("block_class: %p", block_class);
			else if (block_class)
			{
				block_getIdFromBlock = Java::env->GetStaticMethodID(block_class, "func_149682_b", "(Lnet/minecraft/block/Block;)I");
				if (!block_getIdFromBlock) LOG_INFO("block_getIdFromBlock: %p", block_getIdFromBlock);
			}

			Java::AssignClass("", iBlockState_class);
			if (!iBlockState_class) LOG_INFO("iBlockState_class: %p", iBlockState_class);
			else if (iBlockState_class)
			{
				iBlockState_getBlock = Java::env->GetMethodID(iBlockState_class, "", "");
				if (!iBlockState_getBlock) LOG_INFO("iBlockState_getBlock: %p", iBlockState_getBlock);
			}

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			if (!axisAlignedBB_class) LOG_INFO("axisAlignedBB_class: %p", axisAlignedBB_class);
			else if (axisAlignedBB_class)
			{
				axisAlignedBB_minX = Java::env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
				if (!axisAlignedBB_minX) LOG_INFO("axisAlignedBB_minX: %p", axisAlignedBB_minX);
				axisAlignedBB_minY = Java::env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
				if (!axisAlignedBB_minY) LOG_INFO("axisAlignedBB_minY: %p", axisAlignedBB_minY);
				axisAlignedBB_minZ = Java::env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
				if (!axisAlignedBB_minZ) LOG_INFO("axisAlignedBB_minZ: %p", axisAlignedBB_minZ);
				axisAlignedBB_maxX = Java::env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
				if (!axisAlignedBB_maxX) LOG_INFO("axisAlignedBB_maxX: %p", axisAlignedBB_maxX);
				axisAlignedBB_maxY = Java::env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
				if (!axisAlignedBB_maxY) LOG_INFO("axisAlignedBB_maxY: %p", axisAlignedBB_maxY);
				axisAlignedBB_maxZ = Java::env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
				if (!axisAlignedBB_maxZ) LOG_INFO("axisAlignedBB_maxZ: %p", axisAlignedBB_maxZ);
			}

			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			if (!timer_class) LOG_INFO("timer_class: %p", timer_class);
			else if (timer_class)
			{
				timer_renderPartialTicks = Java::env->GetFieldID(timer_class, "field_74281_c", "F");
				if (!timer_renderPartialTicks) LOG_INFO("timer_renderPartialTicks: %p", timer_renderPartialTicks);
			}

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			if (!movingObjectPosition_class) LOG_INFO("movingObjectPosition_class: %p", movingObjectPosition_class);
			else if (movingObjectPosition_class)
			{
				movingObjectPosition_hitVec = Java::env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/Vec3;");
				if (!movingObjectPosition_hitVec) LOG_INFO("movingObjectPosition_hitVec: %p", movingObjectPosition_hitVec);
				movingObjectPosition_entityHit = Java::env->GetFieldID(movingObjectPosition_class, "field_72308_g", "Lnet/minecraft/entity/Entity;");
				if (!movingObjectPosition_entityHit) LOG_INFO("movingObjectPosition_entityHit: %p", movingObjectPosition_entityHit);
				movingObjectPosition_typeOfHit = Java::env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_typeOfHit) LOG_INFO("movingObjectPosition_typeOfHit: %p", movingObjectPosition_typeOfHit);
				movingObjectPosition_BLOCK = Java::env->GetStaticFieldID(movingObjectPosition_class, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				if (!movingObjectPosition_BLOCK) LOG_INFO("movingObjectPosition_BLOCK: %p", movingObjectPosition_BLOCK);
			}

			Java::AssignClass("", blockPos_class);
			if (!blockPos_class) LOG_INFO("blockPos_class: %p", blockPos_class);
			else if (blockPos_class)
			{
				blockPos_constructorDouble = Java::env->GetMethodID(blockPos_class, "", "");
				if (!blockPos_constructorDouble) LOG_INFO("blockPos_constructorDouble: %p", blockPos_constructorDouble);
				blockPos_constructorInt = Java::env->GetMethodID(blockPos_class, "", "");
				if (!blockPos_constructorInt) LOG_INFO("blockPos_constructorInt: %p", blockPos_constructorInt);
			}

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			if (!vec3_class) LOG_INFO("vec3_class: %p", vec3_class);
			else if (vec3_class)
			{
				vec3_xCoord = Java::env->GetFieldID(vec3_class, "field_72450_a", "D");
				if (!vec3_xCoord) LOG_INFO("vec3_xCoord: %p", vec3_xCoord);
				vec3_yCoord = Java::env->GetFieldID(vec3_class, "field_72448_b", "D");
				if (!vec3_yCoord) LOG_INFO("vec3_yCoord: %p", vec3_yCoord);
				vec3_zCoord = Java::env->GetFieldID(vec3_class, "field_72449_c", "D");
				if (!vec3_zCoord) LOG_INFO("vec3_zCoord: %p", vec3_zCoord);
			}

			Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", netHandlerPlayClient_class);
			if (!netHandlerPlayClient_class) LOG_INFO("netHandlerPlayClient_class: %p", netHandlerPlayClient_class);
			else if (netHandlerPlayClient_class)
			{
				netHandlerPlayClient_getPlayerInfo = Java::env->GetMethodID(netHandlerPlayClient_class, "", "");
				if (!netHandlerPlayClient_getPlayerInfo) LOG_INFO("netHandlerPlayClient_getPlayerInfo: %p", netHandlerPlayClient_getPlayerInfo);
				netHandlerPlayClient_playerInfoList = Java::env->GetFieldID(netHandlerPlayClient_class, "field_147303_b", "Ljava/util/List;");
				if (!netHandlerPlayClient_playerInfoList) LOG_INFO("netHandlerPlayClient_playerInfoList: %p", netHandlerPlayClient_playerInfoList);
			}

			Java::AssignClass("", networkPlayerInfo_class);
			if (!networkPlayerInfo_class) LOG_INFO("networkPlayerInfo_class: %p", networkPlayerInfo_class);
			else if (networkPlayerInfo_class)
			{
				networkPlayerInfo_getResponseTime = Java::env->GetMethodID(networkPlayerInfo_class, "", "");
				if (!networkPlayerInfo_getResponseTime) LOG_INFO("networkPlayerInfo_getResponseTime: %p", networkPlayerInfo_getResponseTime);
			}

			Java::AssignClass("net.minecraft.client.gui.GuiPlayerInfo", guiPlayerInfo_class);
			if (!guiPlayerInfo_class) LOG_INFO("guiPlayerInfo_class: %p", guiPlayerInfo_class);
			else if (guiPlayerInfo_class)
			{
				guiPlayerInfo_responseTime = Java::env->GetFieldID(guiPlayerInfo_class, "field_78829_b", "I");
				if (!guiPlayerInfo_responseTime) LOG_INFO("guiPlayerInfo_responseTime: %p", guiPlayerInfo_responseTime);
				guiPlayerInfo_name = Java::env->GetFieldID(guiPlayerInfo_class, "field_78831_a", "Ljava/lang/String;");
				if (!guiPlayerInfo_name) LOG_INFO("guiPlayerInfo_name: %p", guiPlayerInfo_name);
			}

			inventory_class_name = "net.minecraft.client.gui.inventory.GuiInventory";
			chest_gui_class_name = "net.minecraft.client.gui.inventory.GuiChest";
			vec3_class_name = "net.minecraft.util.Vec3";
		}

		initialized = true;
	}

	static void DeleteRefs()
	{
		Java::env->DeleteLocalRef(minecraft_class);
		Java::env->DeleteLocalRef(clientBrandRetriever_class);
		Java::env->DeleteLocalRef(worldClient_class);
		Java::env->DeleteLocalRef(playerControllerMP_class);
		Java::env->DeleteLocalRef(activeRenderInfo_class);
		Java::env->DeleteLocalRef(renderManager_class);
		Java::env->DeleteLocalRef(gameSettings_class);
		Java::env->DeleteLocalRef(entityPlayerSP_class);
		Java::env->DeleteLocalRef(guiContainer_class);
		Java::env->DeleteLocalRef(guiChest_class);
		Java::env->DeleteLocalRef(entity_class);
		Java::env->DeleteLocalRef(entityLivingBase_class);
		Java::env->DeleteLocalRef(entityPlayerMP_class);
		Java::env->DeleteLocalRef(entityPlayer_class);
		Java::env->DeleteLocalRef(inventoryPlayer_class);
		Java::env->DeleteLocalRef(world_class);
		Java::env->DeleteLocalRef(item_class);
		Java::env->DeleteLocalRef(itemStack_class);
		Java::env->DeleteLocalRef(iInventory_class);
		Java::env->DeleteLocalRef(container_class);
		Java::env->DeleteLocalRef(enchantmentHelper_class);
		Java::env->DeleteLocalRef(block_class);
		Java::env->DeleteLocalRef(iBlockState_class);
		Java::env->DeleteLocalRef(axisAlignedBB_class);
		Java::env->DeleteLocalRef(timer_class);
		Java::env->DeleteLocalRef(movingObjectPosition_class);
		Java::env->DeleteLocalRef(blockPos_class);
		Java::env->DeleteLocalRef(vec3_class);
		Java::env->DeleteLocalRef(netHandlerPlayClient_class);
		Java::env->DeleteLocalRef(networkPlayerInfo_class);
		Java::env->DeleteLocalRef(guiPlayerInfo_class);
	}

	static jfieldID GetMovingBlockPositionBLOCK(jclass movingObjectType)
	{
		if (Java::version == MinecraftVersion::UNKNOWN) { return nullptr; }

		if (Java::version == MinecraftVersion::LUNAR_1_8_9)
		{
			return Java::env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		}
		else if (Java::version == MinecraftVersion::LUNAR_1_7_10)
		{
			return Java::env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		}
		else if (Java::version == MinecraftVersion::VANILLA_1_8_9)
		{
			return Java::env->GetStaticFieldID(movingObjectType, "b", "Lauh$a;");
		}
		else if (Java::version == MinecraftVersion::VANILLA_1_7_10)
		{
			return Java::env->GetStaticFieldID(movingObjectType, "b", "Lazv;");
		}
		else if (Java::version == MinecraftVersion::FORGE_1_8_9)
		{
			return Java::env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		}
		else if (Java::version == MinecraftVersion::FORGE_1_7_10)
		{
			return Java::env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		}

		return nullptr;
	}
};