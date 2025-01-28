#pragma once
#include "java/java.h"

#include "util/logger.h"

struct StrayCache {

	inline static bool initialized;

	// MINECRAFT CLASS
	inline static jclass minecraft_class;
	inline static jmethodID minecraft_getMinecraft;
	inline static jfieldID minecraft_thePlayer;
	inline static jfieldID minecraft_playerController;
	inline static jfieldID minecraft_theWorld;
	inline static jfieldID minecraft_renderManager;
	inline static jfieldID minecraft_timer;
	inline static jfieldID minecraft_gameSettings;
	inline static jmethodID minecraft_getRenderViewEntity;
	inline static jfieldID minecraft_currentScreen;
	inline static jfieldID minecraft_objectMouseOver;
	inline static jmethodID minecraft_clickMouse;

	// WORLD CLIENT CLASS
	inline static jclass worldClient_class;
	inline static jfieldID worldClient_entityList;

	// ACTIVE RENDER INFO CLASS
	inline static jclass activeRenderInfo_class;
	inline static jfieldID activeRenderInfo_projection;
	inline static jfieldID activeRenderInfo_modelView;

	// RENDER MANAGER CLASS
	inline static jclass renderManager_class;
	inline static jfieldID renderManager_renderPosX;
	inline static jfieldID renderManager_renderPosY;
	inline static jfieldID renderManager_renderPosZ;
	inline static jfieldID renderManager_viewerPosX;
	inline static jfieldID renderManager_viewerPosY;
	inline static jfieldID renderManager_viewerPosZ;

	// GAME SETTINGS CLASS
	inline static jclass gameSettings_class;
	inline static jfieldID gameSettings_thirdPersonView;
	inline static jfieldID gameSettings_fovSetting;
	inline static jfieldID gameSettings_keyBindFullscreen;
	inline static jmethodID gameSettings_setOptionKeyBinding;

	// TIMER CLASS
	inline static jclass timer_class;
	inline static jfieldID timer_renderPartialTicks;

	// WORLD CLASS
	inline static jclass world_class;
	inline static jfieldID world_playerEntities;
	inline static jmethodID world_rayTraceBlocks;
	inline static jmethodID world_getBlockState;

	// ENTITY CLASS
	inline static jclass entity_class;
	inline static jmethodID entity_getName;
	inline static jmethodID entity_isSneaking;
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

	// ENTITY PLAYER CLASS
	inline static jclass entityPlayer_class;
	inline static jfieldID entityPlayer_inventory;

	// ENTITY PLAYER SP CLASS
	inline static jclass entityPlayerSP_class;

	// ENTITY PLAYER MP CLASS
	inline static jclass playerControllerMP_class;
	inline static jmethodID playerControllerMP_windowClick;

	// AXIS ALIGNED BB CLASS
	inline static jclass axisAlignedBB_class;
	inline static jfieldID axisAlignedBB_minX;
	inline static jfieldID axisAlignedBB_minY;
	inline static jfieldID axisAlignedBB_minZ;
	inline static jfieldID axisAlignedBB_maxX;
	inline static jfieldID axisAlignedBB_maxY;
	inline static jfieldID axisAlignedBB_maxZ;

	// MOVING OBJECT POSITION CLASS
	inline static jclass movingObjectPosition_class;
	inline static jfieldID movingObjectPosition_hitVec;
	inline static jfieldID movingObjectPosition_typeOfHit;
	inline static jfieldID movingObjectPosition_entityHit;

	// VEC3 CLASS
	inline static jclass vec3_class;
	inline static jfieldID vec3_xCoord;
	inline static jfieldID vec3_yCoord;
	inline static jfieldID vec3_zCoord;

	// INVENTORY PLAYER CLASS
	inline static jclass inventoryPlayer_class;
	inline static jmethodID inventoryPlayer_getCurrentItem;
	inline static jfieldID inventoryPlayer_mainInventory;
	inline static jfieldID inventoryPlayer_armorInventory;

	// ITEM STACK CLASS
	inline static jclass itemStack_class;
	inline static jmethodID itemStack_getItem;
	inline static jmethodID itemStack_getMetadata;
	inline static jmethodID itemStack_getMaxDamage;
	inline static jfieldID itemStack_stackSize;

	// ITEM CLASS
	inline static jclass item_class;
	inline static jmethodID item_getUnlocalizedName;
	inline static jmethodID item_getIdFromItem;
	inline static jmethodID item_getItemStackLimit;

	// BLOCK CLASS
	inline static jclass block_class;
	inline static jmethodID block_getIdFromBlock;

	// IBLOCK STATE CLASS
	inline static jclass iBlockState_class;
	inline static jmethodID iBlockState_getBlock;

	// BLOCK POS CLASS
	inline static jclass blockPos_class;
	inline static jmethodID blockPos_constructorInt;
	inline static jmethodID blockPos_constructorDouble;

	// GUI CHEST CLASS
	inline static jclass guiChest_class;
	inline static jfieldID guiChest_upperChestInventory;
	inline static jfieldID guiChest_lowerChestInventory;
	inline static jfieldID guiChest_inventoryRows;

	// GUI CONTAINER CLASS
	inline static jclass guiContainer_class;
	inline static jfieldID guiContainer_inventorySlots;

	// IINVENTORY CLASS
	inline static jclass iInventory_class;
	inline static jmethodID iInventory_getSizeInventory;
	inline static jmethodID iInventory_getStackInSlot;

	// CONTAINER CLASS
	inline static jclass container_class;
	inline static const char* container_windowId_name;

	// ENCHANTMENT HELPER CLASS
	inline static jclass enchantmentHelper_class;
	inline static jmethodID enchantmentHelper_getEnchantments;

	// STRINGS
	inline static const char* inventory_class_name;
	inline static const char* chest_gui_class_name;

	static void Initialize() {
		if (Java::Version == MinecraftVersion::UNKNOWN) { return; }
		if (initialized) { return; }
		
		if (Java::Version == MinecraftVersion::LUNAR_1_8_9)
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
			minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "clickMouse", "()V");

			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");

			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_projection = Java::Env->GetStaticFieldID(activeRenderInfo_class, "PROJECTION", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_modelView = Java::Env->GetStaticFieldID(activeRenderInfo_class, "MODELVIEW", "Ljava/nio/FloatBuffer;");

			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "renderPosX", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "renderPosY", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "renderPosZ", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "viewerPosX", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "viewerPosY", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "viewerPosZ", "D");

			Java::AssignClass("net.minecraft.client.settings.GameSettings", gameSettings_class);
			gameSettings_thirdPersonView = Java::Env->GetFieldID(gameSettings_class, "thirdPersonView", "I");
			gameSettings_fovSetting = Java::Env->GetFieldID(gameSettings_class, "fovSetting", "F");
			gameSettings_keyBindFullscreen = Java::Env->GetFieldID(gameSettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
			gameSettings_setOptionKeyBinding = Java::Env->GetMethodID(gameSettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");

			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_renderPartialTicks = Java::Env->GetFieldID(timer_class, "renderPartialTicks", "F");

			Java::AssignClass("net.minecraft.world.World", world_class);
			world_playerEntities = Java::Env->GetFieldID(world_class, "playerEntities", "Ljava/util/List;");
			world_rayTraceBlocks = Java::Env->GetMethodID(world_class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
			world_getBlockState = Java::Env->GetMethodID(world_class, "getBlockState", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");

			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_getName = Java::Env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "isSneaking", "()Z");
			entity_posX = Java::Env->GetFieldID(entity_class, "posX", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "posY", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "posZ", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "lastTickPosX", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "lastTickPosY", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "lastTickPosZ", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "width", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "height", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "distanceWalkedModified", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "rotationYaw", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "rotationPitch", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "prevRotationYaw", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "prevRotationPitch", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "motionX", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "motionY", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "motionZ", "D");
			entity_hurtResistantTime = Java::Env->GetFieldID(entity_class, "hurtResistantTime", "I");

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_inventory = Java::Env->GetFieldID(entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");

			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);

			Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerMP_class);
			playerControllerMP_windowClick = Java::Env->GetMethodID(playerControllerMP_class, "windowClick", "(IIIILnet/minecraft/entity/player/EntityPlayer;)Lnet/minecraft/item/ItemStack;");

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "minX", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "minY", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "minZ", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "maxX", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "maxY", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "maxZ", "D");

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/Vec3;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			movingObjectPosition_entityHit = Java::Env->GetFieldID(movingObjectPosition_class, "entityHit", "Lnet/minecraft/entity/Entity;");

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "xCoord", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "yCoord", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "zCoord", "D");

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_mainInventory = Java::Env->GetFieldID(inventoryPlayer_class, "mainInventory", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_armorInventory = Java::Env->GetFieldID(inventoryPlayer_class, "armorInventory", "[Lnet/minecraft/item/ItemStack;");

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
			itemStack_getMetadata = Java::Env->GetMethodID(itemStack_class, "getMetadata", "()I");
			itemStack_getMaxDamage = Java::Env->GetMethodID(itemStack_class, "getMaxDamage", "()I");
			itemStack_stackSize = Java::Env->GetFieldID(itemStack_class, "stackSize", "I");

			Java::AssignClass("net.minecraft.item.Item", item_class);
			item_getUnlocalizedName = Java::Env->GetMethodID(item_class, "getUnlocalizedName", "()Ljava/lang/String;");
			item_getIdFromItem = Java::Env->GetStaticMethodID(item_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");
			item_getItemStackLimit = Java::Env->GetMethodID(item_class, "getItemStackLimit", "()I");

			Java::AssignClass("net.minecraft.block.Block", block_class);
			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "getIdFromBlock", "(Lnet/minecraft/block/Block;)I");

			Java::AssignClass("net.minecraft.block.state.IBlockState", iBlockState_class);
			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "getBlock", "()Lnet/minecraft/block/Block;");

			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_constructorInt = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_constructorDouble = Java::Env->GetMethodID(blockPos_class, "<init>", "(DDD)V");

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiChest", guiChest_class);
			guiChest_upperChestInventory = Java::Env->GetFieldID(guiChest_class, "upperChestInventory", "Lnet/minecraft/inventory/IInventory;");
			guiChest_lowerChestInventory = Java::Env->GetFieldID(guiChest_class, "lowerChestInventory", "Lnet/minecraft/inventory/IInventory;");
			guiChest_inventoryRows = Java::Env->GetFieldID(guiChest_class, "inventoryRows", "I");

			Java::AssignClass("net.minecraft.inventory.IInventory", iInventory_class);
			iInventory_getSizeInventory = Java::Env->GetMethodID(iInventory_class, "getSizeInventory", "()I");
			iInventory_getStackInSlot = Java::Env->GetMethodID(iInventory_class, "getStackInSlot", "(I)Lnet/minecraft/item/ItemStack;");

			Java::AssignClass("net.minecraft.client.gui.inventory.GuiContainer", guiContainer_class);
			guiContainer_inventorySlots = Java::Env->GetFieldID(guiContainer_class, "inventorySlots", "Lnet/minecraft/inventory/Container;");

			Java::AssignClass("net.minecraft.inventory.Container", container_class);
			container_windowId_name = "windowId";

			Java::AssignClass("net.minecraft.enchantment.EnchantmentHelper", enchantmentHelper_class);
			enchantmentHelper_getEnchantments = Java::Env->GetStaticMethodID(enchantmentHelper_class, "getEnchantments", "(Lnet/minecraft/item/ItemStack;)Ljava/util/Map;");

			inventory_class_name = "net.minecraft.client.gui.inventory.GuiInventory";
			chest_gui_class_name = "net.minecraft.client.gui.inventory.GuiChest";
		}
		else if (Java::Version == MinecraftVersion::LUNAR_1_7_10)
		{

		}
		else if (Java::Version == MinecraftVersion::VANILLA_1_8_9)
		{
			Java::AssignClass("ave", minecraft_class);
			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "A", "()Lave;");
			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "h", "Lbew;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "f", "Lbdb;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "aa", "Lbiu;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "Y", "Lavl;");
			minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "t", "Lavh;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "ac", "()Lpk;");
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "m", "Laxu;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "s", "Lauh;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "aw", "()V");

			Java::AssignClass("bdb", worldClient_class);
			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "c", "Ljava/util/Set;");

			Java::AssignClass("auz", activeRenderInfo_class);
			activeRenderInfo_projection = Java::Env->GetStaticFieldID(activeRenderInfo_class, "c", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_modelView = Java::Env->GetStaticFieldID(activeRenderInfo_class, "b", "Ljava/nio/FloatBuffer;");

			Java::AssignClass("biu", renderManager_class);
			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "o", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "p", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "q", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "h", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "i", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "j", "D");

			Java::AssignClass("avh", gameSettings_class);
			gameSettings_thirdPersonView = Java::Env->GetFieldID(gameSettings_class, "aB", "I");
			gameSettings_fovSetting = Java::Env->GetFieldID(gameSettings_class, "aI", "F");
			gameSettings_keyBindFullscreen = Java::Env->GetFieldID(gameSettings_class, "aq", "Lavb;");
			gameSettings_setOptionKeyBinding = Java::Env->GetMethodID(gameSettings_class, "a", "(Lavb;I)V");

			Java::AssignClass("avl", timer_class);
			timer_renderPartialTicks = Java::Env->GetFieldID(timer_class, "c", "F");

			Java::AssignClass("adm", world_class);
			world_playerEntities = Java::Env->GetFieldID(world_class, "j", "Ljava/util/List;");
			world_rayTraceBlocks = Java::Env->GetMethodID(world_class, "a", "(Laui;Laui;ZZZ)Lauh;");
			world_getBlockState = Java::Env->GetMethodID(world_class, "p", "(Lcj;)Lalz;");

			Java::AssignClass("pk", entity_class);
			entity_getName = Java::Env->GetMethodID(entity_class, "e_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "av", "()Z");
			entity_posX = Java::Env->GetFieldID(entity_class, "s", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "t", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "u", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "P", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "Q", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "R", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "J", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "K", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "M", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "L", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "y", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "z", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "A", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "B", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "f", "Laug;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "v", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "w", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "x", "D");
			entity_hurtResistantTime = Java::Env->GetFieldID(entity_class, "Z", "I");

			Java::AssignClass("pr", entityLivingBase_class);
			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "bn", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "bu", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "t", "(Lpk;)Z");

			Java::AssignClass("wn", entityPlayer_class);
			entityPlayer_inventory = Java::Env->GetFieldID(entityPlayer_class, "bi", "Lwm;");

			Java::AssignClass("bew", entityPlayerSP_class);

			Java::AssignClass("bda", playerControllerMP_class);
			playerControllerMP_windowClick = Java::Env->GetMethodID(playerControllerMP_class, "a", "(IIIILwn;)Lzx;");

			Java::AssignClass("aug", axisAlignedBB_class);
			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "f", "D");

			Java::AssignClass("auh", movingObjectPosition_class);
			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "c", "Laui;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "a", "Lauh$a;");
			movingObjectPosition_entityHit = Java::Env->GetFieldID(movingObjectPosition_class, "d", "Lpk;");

			Java::AssignClass("aui", vec3_class);
			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "c", "D");

			Java::AssignClass("wm", inventoryPlayer_class);
			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "h", "()Lzx;");
			inventoryPlayer_mainInventory = Java::Env->GetFieldID(inventoryPlayer_class, "a", "[Lzx;");
			inventoryPlayer_armorInventory = Java::Env->GetFieldID(inventoryPlayer_class, "b", "[Lzx;");

			Java::AssignClass("zx", itemStack_class);
			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "b", "()Lzw;");
			itemStack_getMetadata = Java::Env->GetMethodID(itemStack_class, "i", "()I");
			itemStack_getMaxDamage = Java::Env->GetMethodID(itemStack_class, "j", "()I");

			Java::AssignClass("zw", item_class);
			item_getUnlocalizedName = Java::Env->GetMethodID(item_class, "a", "()Ljava/lang/String;");
			item_getIdFromItem = Java::Env->GetStaticMethodID(item_class, "b", "(Lzw;)I");

			Java::AssignClass("afh", block_class);
			block_getIdFromBlock = Java::Env->GetStaticMethodID(block_class, "a", "(Lafh;)I");

			Java::AssignClass("alz", iBlockState_class);
			iBlockState_getBlock = Java::Env->GetMethodID(iBlockState_class, "c", "()Lafh;");

			Java::AssignClass("cj", blockPos_class);
			blockPos_constructorInt = Java::Env->GetMethodID(blockPos_class, "<init>", "(III)V");
			blockPos_constructorDouble = Java::Env->GetMethodID(blockPos_class, "<init>", "(FFF)V");

			Java::AssignClass("ayr", guiChest_class);
			guiChest_upperChestInventory = Java::Env->GetFieldID(guiChest_class, "v", "Log;");
			guiChest_lowerChestInventory = Java::Env->GetFieldID(guiChest_class, "w", "Log;");
			guiChest_inventoryRows = Java::Env->GetFieldID(guiChest_class, "x", "I");

			Java::AssignClass("og", iInventory_class);
			iInventory_getSizeInventory = Java::Env->GetMethodID(iInventory_class, "o_", "()I");
			iInventory_getStackInSlot = Java::Env->GetMethodID(iInventory_class, "a", "(I)Lzx;");

			Java::AssignClass("ayl", guiContainer_class);
			guiContainer_inventorySlots = Java::Env->GetFieldID(guiContainer_class, "h", "Lxi;");

			Java::AssignClass("xi", container_class);
			container_windowId_name = "d";

			inventory_class_name = "azc";
			chest_gui_class_name = "ayr";
		}
		else if (Java::Version == MinecraftVersion::VANILLA_1_7_10)
		{
			
		}

		initialized = true;
	}

	static void DeleteRefs() {
		Java::Env->DeleteLocalRef(entity_class);
		Java::Env->DeleteLocalRef(entityLivingBase_class);
		Java::Env->DeleteLocalRef(axisAlignedBB_class);
		Java::Env->DeleteLocalRef(movingObjectPosition_class);
		Java::Env->DeleteLocalRef(vec3_class);
	}

	static jfieldID GetMovingBlockPositionBLOCK(jclass movingObjectType)
	{
		if (Java::Version == MinecraftVersion::UNKNOWN) { return nullptr; }

		if (Java::Version == MinecraftVersion::LUNAR_1_8_9)
		{
			return Java::Env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		}
		else if (Java::Version == MinecraftVersion::LUNAR_1_7_10)
		{

		}
		else if (Java::Version == MinecraftVersion::VANILLA_1_8_9)
		{
			return Java::Env->GetStaticFieldID(movingObjectType, "b", "Lauh$a;");
		}
		else if (Java::Version == MinecraftVersion::VANILLA_1_7_10)
		{
			return nullptr;
		}

		return nullptr;
	}
};