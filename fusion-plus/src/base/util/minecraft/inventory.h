#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

/*
For Armor:
- Calculate "Percent damage reduction" for each armor piece in the inventory (include armor enchantments) choose the best armor piece to wear

For Weapons:
- Calculate "Damage" for each weapon in the inventory (include weapon enchantments) choose the best weapon to use

Item Categories:
- Armor (Damage reduction priority)
- Weapons (Damage priority, excluding Bow)
- Tools (Custom priority)
- Food (Custom priority)
- Blocks (Custom priority)
- (Enchanted) Golden Apples (Enchanted Golden Apple, Golden Apple)
- Projectiles (Snowballs, Eggs, Finish Rods, etc)
- Potions (each effect has a different priority depending on the slot)

User can make custom categories and set the priority of each item in the category
*/

struct InventorySystem {
    enum Material
    {
        MATERIAL_UNKNOWN,
        WOOD,
        LEATHER,
        CHAINMAIL,
        IRON,
        DIAMOND,
        GOLD,
        STONE,
    };

    enum ArmorType
    {
        ARMOR_UNKNOWN,
        HELMET,
        CHESTPLATE,
        LEGGINGS,
        BOOTS,
    };

    enum class ItemCategory
    {
        None,
        Armor,
        Sword,
        Tool,
        Food,
        Block,
        GoldenApple,
        Projectile,
        Potion,
        Custom
    };

    struct Item {
        int id;
        int metadata;
        int priority;

        Item(int itemId, int meta, int prio)
            : id(itemId), metadata(meta), priority(prio) {}
    };

    struct Category
    {
        int id;

        std::string name; // Use std::string for safe string management
        ItemCategory category;
        std::vector<Item> items;

        Category(const char* catName, ItemCategory cat, std::vector<Item> item)
            : name(catName), category(cat), items(item)
        {
			std::string idString = name;
            for (Item item : items)
            {
                idString += std::to_string(item.id);
                idString += std::to_string(item.metadata);
            }

            id = static_cast<int>(std::hash<std::string>{}(idString));
        }
    };


    struct Slot
    {
        Category category;
		Item item;
        int slotIndex;

		Slot(Category cat, int index)
			: category(cat), slotIndex(index), item(-1, -1, -1) {}

		Slot(Item item, int index)
            : item(item), slotIndex(index), category("", ItemCategory::None, {}) {}
    };

    static inline std::vector<Slot> inventorySlots = std::vector<Slot>{};
    static inline std::vector<Slot> armorSlots = std::vector<Slot>{};

	static inline int defaultCategories = 0;
	static inline std::vector<Category> categoryList = std::vector<Category>{};

    static inline void AddCategoryToSlot(int slotIndex, int categoryIndex)
    {
		if (!IsInitialized) Init();

		if (categoryIndex >= categoryList.size())
			return;

		inventorySlots[slotIndex].category = categoryList[categoryIndex];
		inventorySlots[slotIndex].item = Item(-1, -1, -1);
    }

    static inline void AddItemToSlot(int slotIndex, int id, int meta)
    {
        if (!IsInitialized) Init();

		inventorySlots[slotIndex].item = Item(id, meta, 0);
		inventorySlots[slotIndex].category = categoryList[0];
    }

    static inline void AddItemToCategory(int categoryIndex, const Item& item)
    {
        if (!IsInitialized) Init();
        categoryIndex += defaultCategories;

		if (categoryIndex >= categoryList.size())
			return;

		categoryList[categoryIndex].items.push_back(item);
    }

    static inline void RemoveItemFromCategory(int categoryIndex, int itemIndex)
    {
        if (!IsInitialized) Init();

		if (categoryIndex >= categoryList.size() || itemIndex >= categoryList[categoryIndex].items.size())
			return;

		categoryList[categoryIndex].items.erase(categoryList[categoryIndex].items.begin() + itemIndex);
    }

    static inline void EditItemInCategory(int categoryIndex, int itemIndex, const Item& item)
    {
        if (!IsInitialized) Init();

        if (categoryIndex >= categoryList.size() || itemIndex >= categoryList[categoryIndex].items.size())
            return;

        categoryList[categoryIndex].items[itemIndex] = item;
    }

    static inline void CreateCustomCategory(std::vector<Item> items, const char* name)
    {
        if (!IsInitialized) Init();

        std::string categoryNameCopy(name);

        categoryList.push_back(Category(categoryNameCopy.c_str(), ItemCategory::Custom, items));
    }

	static inline void EditCustomCategory(int categoryIndex, std::vector<Item> items, const char* name)
	{
		if (!IsInitialized) Init();

		if (categoryIndex >= categoryList.size())
			return;

		std::string categoryNameCopy(name);

		categoryList[categoryIndex] = Category(categoryNameCopy.c_str(), ItemCategory::Custom, items);
	}

    static inline void RemoveCategory(int categoryIndex)
    {
        if (!IsInitialized) Init();

        if (categoryIndex >= categoryList.size())
            return;

        categoryList.erase(categoryList.begin() + categoryIndex);
    }

    static inline float CalculateDamageReduction(Material material, ArmorType armorType, int protectionLevel) {
		if (material == Material::WOOD || material == Material::STONE || material == Material::MATERIAL_UNKNOWN || armorType == ArmorType::ARMOR_UNKNOWN)
			return -1.0f;
        
        float baseReduction = armorMaterialBaseReduction[material][armorType];
		std::cout << "Base Reduction: " << baseReduction << std::endl;
        float protectionReduction = protectionLevel * 0.04f;
		std::cout << "Protection Reduction: " << protectionReduction << std::endl;
        float totalReduction = baseReduction + protectionReduction;
		std::cout << "Total Reduction: " << totalReduction << std::endl;

        return totalReduction;
    }

    static inline float CalculateDamage(Material material, int shaprnessLevel) {
        if (material == Material::CHAINMAIL || material == Material::LEATHER)
            return -1.0f;

		float baseDamage = weaponMaterialBaseDamage[material];
        baseDamage += (float)shaprnessLevel * 1.25f;

        return baseDamage;
    }

	static inline std::vector<Category> GetCategories()
    {
		return categoryList;
	}

    static inline std::vector<Category> GetCustomCategories()
    {
        std::vector<Category> customCategories;
        for (Category cat : categoryList)
        {
            if (cat.category == ItemCategory::Custom)
                customCategories.push_back(cat);
        }

        return customCategories;
    }

	static inline std::vector<Item> GetItemsInCategory(int categoryIndex)
	{
		if (categoryIndex >= categoryList.size())
			return {};

		return categoryList[categoryIndex].items;
	}

	static inline std::vector<Slot> GetInventorySlots()
	{
		return inventorySlots;
	}

	static inline std::vector<Slot> GetArmorSlots()
	{
		return armorSlots;
	}

// === Helpers === //
    static inline Material GetMaterialFromName(const std::string& unlocalizedName) {
        if (unlocalizedName.find("Cloth") != std::string::npos)
            return Material::LEATHER;
        else if (unlocalizedName.find("Chain") != std::string::npos)
            return Material::CHAINMAIL;
        else if (unlocalizedName.find("Iron") != std::string::npos)
            return Material::IRON;
        else if (unlocalizedName.find("Gold") != std::string::npos)
            return Material::GOLD;
        else if (unlocalizedName.find("Diamond") != std::string::npos)
            return Material::DIAMOND;
        else if (unlocalizedName.find("Wood") != std::string::npos)
			return Material::WOOD;
        else if (unlocalizedName.find("Stone") != std::string::npos)
			return Material::STONE;

        return Material::MATERIAL_UNKNOWN;
    }

	static inline std::string ArmorTypeToString(ArmorType type) {
		switch (type)
		{
		case HELMET:
			return "helmet";
		case CHESTPLATE:
			return "chestplate";
		case LEGGINGS:
			return "leggings";
		case BOOTS:
			return "boots";
		default:
			return "unknown";
		}
	}

// === Private === //
    static inline std::map<Material, std::map<ArmorType, float>> armorMaterialBaseReduction = {
        {},
        {},
        {LEATHER, {{HELMET, 1.f}, {CHESTPLATE, 3.f}, {LEGGINGS, 2.f}, {BOOTS, 1.f}}},
        {CHAINMAIL, {{HELMET, 2.f}, {CHESTPLATE, 5.f}, {LEGGINGS, 3.f}, {BOOTS, 1.f}}},
        {IRON, {{HELMET, 2.f}, {CHESTPLATE, 6.f}, {LEGGINGS, 5.f}, {BOOTS, 2.f}}},
        {DIAMOND, {{HELMET, 3.f}, {CHESTPLATE, 8.f}, {LEGGINGS, 6.f}, {BOOTS, 3.f}}},
        {GOLD, {{HELMET, 2.f}, {CHESTPLATE, 5.f}, {LEGGINGS, 3.f}, {BOOTS, 2.f}}},
        {},
    };

	static inline std::map<Material, float> weaponMaterialBaseDamage = {
        {},
		{WOOD, 4.0f},
        {},
        {},
		{IRON, 6.0f},
		{DIAMOND, 7.0f},
		{GOLD, 4.0f},
		{STONE, 5.0f},
	};

// === INIT === //
	static inline bool IsInitialized = false;
    static inline void Init()
    {
        categoryList.push_back(Category("None", ItemCategory::None, {})); defaultCategories++;
		categoryList.push_back(Category( "Food", ItemCategory::Food, {
			Item(320, 0, 0), // Cooked Porkchop
			Item(364, 0, 1), // Cooked Beef
			Item(366, 0, 2), // Cooked Chicken
			Item(423, 0, 3), // Cooked Mutton
			Item(412, 0, 4), // Cooked Rabbit
			Item(297, 0, 4), // Bread
			Item(393, 0, 4), // Bake Potato
			Item(400, 0, 5), // Pumpkin Pie
			Item(260, 0, 6), // Apple
			Item(391, 0, 6), // Carrot
			Item(393, 0, 7), // Potato
        } )); defaultCategories++;
        categoryList.push_back(Category("Blocks", ItemCategory::Block, { Item(1, 0, 0), Item(5, 0, 0) })); defaultCategories++;
        categoryList.push_back(Category( "Golden Apple(s)", ItemCategory::GoldenApple, { Item(322, 1, 0), Item(322, 0, 1) })); defaultCategories++;
        categoryList.push_back(Category( "Projectiles", ItemCategory::Projectile, { Item(332, 0, 0), Item(344, 0, 1) })); defaultCategories++;
        
		// UNIQE CATEGORIES
		categoryList.push_back(Category( "Sword", ItemCategory::Sword, {} )); defaultCategories++;

        // ARMOR
		Category armorCategory = Category("Armor", ItemCategory::Armor, {}); defaultCategories++;
		for (int i = 0; i < 4; i++)
		{
			armorSlots.push_back({ armorCategory, i });
		}

        // NORMAL SLOTS
		for (int i = 0; i < 36; i++)
		{
			inventorySlots.push_back({ categoryList[0], i });
		}

		IsInitialized = true;
    }
};
