#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "configManager/settings.h"
#include "sdk/net/minecraft/item/ItemStack.h"
#include "util/logger.h"

// Structure to hold ID and metadata
struct BlockData
{
    int id;
    int metadata;
};

struct MinecraftItems
{
    // Mapping from name to BlockData
    static inline std::unordered_map<std::string, BlockData> nameToBlock = {
       {"Acacia Door", {430, 0}},
       {"Acacia Fence", {192, 0}},
       {"Acacia Fence Gate", {187, 0}},
       {"Acacia Stairs", {163, 0}},
       {"Activator Rails", {157, 0}},
       {"Air", {0, 0}},
       {"Anvil", {145, 0}},
       {"Slightly Damaged Anvil", {145, 1}},
       {"Very Damaged Anvil", {145, 2}},
       {"Apple", {260, 0}},
       {"Armor Stand", {416, 0}},
       {"Arrow", {262, 0}},
       {"Baked Potato", {393, 0}},
       {"Black Banner", {425, 0}},
       {"Red Banner", {425, 1}},
       {"Green Banner", {425, 2}},
       {"Brown Banner", {425, 3}},
       {"Blue Banner", {425, 4}},
       {"Purple Banner", {425, 5}},
       {"Cyan Banner", {425, 6}},
       {"Light Gray Banner", {425, 7}},
       {"Gray Banner", {425, 8}},
       {"Pink Banner", {425, 9}},
       {"Lime Banner", {425, 10}},
       {"Yellow Banner", {425, 11}},
       {"Light Blue Banner", {425, 12}},
       {"Magenta Banner", {425, 13}},
       {"Orange Banner", {425, 14}},
       {"White Banner", {425, 15}},
       {"Barrier", {166, 0}},
       {"Beacon", {138, 0}},
       {"Red Bed", {355, 0}},
       {"Bedrock", {7, 0}},
       {"Raw Beef", {363, 0}},
       {"Birch Door", {428, 0}},
       {"Birch Fence", {189, 0}},
       {"Birch Fence Gate", {184, 0}},
       {"Birch Stairs", {135, 0}},
       {"Blaze Powder", {377, 0}},
       {"Blaze Rod", {369, 0}},
       {"Oak Boat", {333, 0}},
       {"Bone", {352, 0}},
       {"Book", {340, 0}},
       {"Bookshelf", {47, 0}},
       {"Bow", {261, -1}},
       {"Bowl", {281, 0}},
       {"Bread", {297, 0}},
       {"Brewing Stand", {379, 0}},
       {"Brick", {336, 0}},
       {"Bricks", {45, 0}},
       {"Brick Stairs", {108, 0}},
       {"Brown Mushroom", {39, 0}},
       {"Brown Mushroom Block", {99, 0}},
       {"Bucket", {325, 0}},
       {"Cactus", {81, 0}},
       {"Cake", {354, 0}},
       {"White Carpet", {171, 0}},
       {"Orange Carpet", {171, 1}},
       {"Magenta Carpet", {171, 2}},
       {"Light Blue Carpet", {171, 3}},
       {"Yellow Carpet", {171, 4}},
       {"Lime Carpet", {171, 5}},
       {"Pink Carpet", {171, 6}},
       {"Gray Carpet", {171, 7}},
       {"Light Gray Carpet", {171, 8}},
       {"Cyan Carpet", {171, 9}},
       {"Purple Carpet", {171, 10}},
       {"Blue Carpet", {171, 11}},
       {"Brown Carpet", {171, 12}},
       {"Green Carpet", {171, 13}},
       {"Red Carpet", {171, 14}},
       {"Black Carpet", {171, 15}},
       {"Carrot", {391, 0}},
       {"Carrot on a Stick", {398, 0}},
       {"Cauldron", {380, 0}},
       {"Chain Boots", {305, -1}},
       {"Chain Chestplate", {303, -1}},
       {"Chain Helmet", {302, -1}},
       {"Chain Leggings", {304, -1}},
       {"Chest", {54, 0}},
       {"Minecart with Chest", {342, 0}},
       {"Raw Chicken", {365, 0}},
       {"Clay Block", {82, 0}},
       {"Clay Ball", {337, 0}},
       {"Clock", {347, 0}},
       {"Coal", {263, 0}},
       {"Charcoal", {263, 1}},
       {"Coal Block", {173, 0}},
       {"Coal Ore", {16, 0}},
       {"Cobblestone", {4, 0}},
       {"Cobblestone Wall", {139, 0}},
       {"Mossy Cobblestone Wall", {139, 1}},
       {"Command Block", {137, 0}},
       {"Minecart with Command Block", {422, 0}},
       {"Redstone Comparator", {404, 0}},
       {"Compass", {345, 0}},
       {"Steak", {364, 0}},
       {"Cooked Chicken", {366, 0}},
       {"Cooked Fish", {350, 0}},
       {"Cooked Salmon", {350, 1}},
       {"Cooked Mutton", {424, 0}},
       {"Cooked Porkchop", {320, 0}},
       {"Cooked Rabbit", {412, 0}},
       {"Cookie", {357, 0}},
       {"Crafting Table", {58, 0}},
       {"Dark Oak Door", {431, 0}},
       {"Dark Oak Fence", {191, 0}},
       {"Dark Oak Fence Gate", {186, 0}},
       {"Dark Oak Stairs", {164, 0}},
       {"Daylight Detector", {151, 0}},
       {"Dead Bush", {32, 0}},
       {"Detector Rails", {28, 0}},
       {"Diamond", {264, 0}},
       {"Diamond Axe", {279, -1}},
       {"Block of Diamond", {57, 0}},
       {"Diamond Boots", {313, -1}},
       {"Diamond Chestplate", {311, -1}},
       {"Diamond Helmet", {310, -1}},
       {"Diamond Hoe", {293, -1}},
       {"Diamond Horse Armor", {419, 0}},
       {"Diamond Leggings", {312, -1}},
       {"Diamond Ore", {56, 0}},
       {"Diamond Pickaxe", {278, -1}},
       {"Diamond Shovel", {277, -1}},
       {"Diamond Sword", {276, -1}},
       {"Dirt", {3, 0}},
       {"Coarse Dirt", {3, 1}},
       {"Podzol", {3, 2}},
       {"Dispenser", {23, 0}},
       {"Sunflower", {175, 0}},
       {"Lilac", {175, 1}},
       {"Tall Grass", {175, 2}},
       {"Large Fern", {175, 3}},
       {"Rose Bush", {175, 4}},
       {"Peony", {175, 5}},
       {"Dragon Egg", {122, 0}},
       {"Dropper", {158, 0}},
       {"Ink Sac", {351, 0}},
       {"Red Dye", {351, 1}},
       {"Green Dye", {351, 2}},
       {"Cocoa Beans", {351, 3}},
       {"Lapis Lazuli", {351, 4}},
       {"Purple Dye", {351, 5}},
       {"Cyan Dye", {351, 6}},
       {"Light Gray Dye", {351, 7}},
       {"Gray Dye", {351, 8}},
       {"Pink Dye", {351, 9}},
       {"Lime Dye", {351, 10}},
       {"Yellow Dye", {351, 11}},
       {"Light Blue Dye", {351, 12}},
       {"Magenta Dye", {351, 13}},
       {"Orange Dye", {351, 14}},
       {"Bone Meal", {351, 15}},
       {"Egg", {344, 0}},
       {"Emerald", {388, 0}},
       {"Block of Emerald", {133, 0}},
       {"Emerald Ore", {129, 0}},
       {"Enchanted Book", {403, 0}},
       {"Enchanting Table", {116, 0}},
       {"End Portal Frame", {120, 0}},
       {"End Stone", {121, 0}},
       {"Ender Chest", {130, 0}},
       {"Eye of Ender", {381, 0}},
       {"Ender Pearl", {368, 0}},
       {"Bottle o'Enchanting", {384, 0}},
       {"Farmland", {60, 0}},
       {"Feather", {288, 0}},
       {"Oak Fence", {85, 0}},
       {"Oak Fence Gate", {107, 0}},
       {"Fermented Spider Eye", {376, 0}},
       {"Fire Charge", {385, 0}},
       {"Firework Rocket", {401, 0}},
       {"Raw Fish", {349, 0}},
       {"Raw Salmon", {349, 1}},
       {"Tropical Fish (Clownfish)", {349, 2}},
       {"Pufferfish", {349, 3}},
       {"Fishing Rod", {346, -1}},
       {"Flint", {318, 0}},
       {"Flint and Steel", {259, -1}},
       {"Flower Pot", {390, 0}},
       {"Furnace", {61, 0}},
       {"Minecart with Furnace", {343, 0}},
       {"Ghast Tear", {370, 0}},
       {"Glass", {20, 0}},
       {"Glass Bottle", {374, 0}},
       {"Glass Pane", {102, 0}},
       {"Glowstone", {89, 0}},
       {"Glowstone Dust", {348, 0}},
       {"Block of Gold", {41, 0}},
       {"Gold Ingot", {266, 0}},
       {"Gold Nugget", {371, 0}},
       {"Gold Ore", {14, 0}},
       {"Golden Apple", {322, 0}},
       {"Enchanted Golden Apple", {322, 1}},
       {"Golden Axe", {286, -1}},
       {"Golden Boots", {317, -1}},
       {"Golden Carrot", {396, -1}},
       {"Golden Chestplate", {315, -1}},
       {"Golden Helmet", {314, -1}},
       {"Golden Hoe", {294, -1}},
       {"Gold Horse Armor", {418, 0}},
       {"Golden Leggings", {316, -1}},
       {"Golden Pickaxe", {285, -1}},
       {"Powered Rails", {27, 0}},
       {"Golden Shovel", {284, -1}},
       {"Golden Sword", {283, -1}},
       {"Grass Block", {2, 0}},
       {"Gravel", {13, 0}},
       {"Gunpowder", {289, 0}},
       {"Terracotta", {172, 0}},
       {"Hay Bale", {170, 0}},
       {"Heavy Weighted Pressure Plate", {148, 0}},
       {"Hopper", {154, 0}},
       {"Minecart with Hopper", {408, 0}},
       {"Ice", {79, 0}},
       {"Iron Axe", {258, -1}},
       {"Iron Bars", {101, 0}},
       {"Block of Iron", {42, 0}},
       {"Iron Boots", {309, -1}},
       {"Iron Chestplate", {307, -1}},
       {"Iron Door", {330, 0}},
       {"Iron Helmet", {306, -1}},
       {"Iron Hoe", {292, -1}},
       {"Iron Horse Armor", {417, 0}},
       {"Iron Ingot", {265, 0}},
       {"Iron Leggings", {308, -1}},
       {"Iron Ore", {15, 0}},
       {"Iron Pickaxe", {257, -1}},
       {"Iron Shovel", {256, -1}},
       {"Iron Sword", {267, -1}},
       {"Iron Trapdoor", {167, 0}},
       {"Item Frame", {389, 0}},
       {"Jukebox", {84, 0}},
       {"Jungle Door", {429, 0}},
       {"Jungle Fence", {190, 0}},
       {"Jungle Fence Gate", {185, 0}},
       {"Jungle Stairs", {136, 0}},
       {"Ladder", {65, 0}},
       {"Lapis Lazuli Block", {22, 0}},
       {"Lapis Lazuli Ore", {21, 0}},
       {"Lava Bucket", {327, 0}},
       {"Lead", {420, 0}},
       {"Leather", {334, 0}},
       {"Leather Boots", {301, -1}},
       {"Leather Tunic", {299, -1}},
       {"Leather Cap", {298, -1}},
       {"Leather Pants", {300, -1}},
       {"Oak Leaves", {18, 0}},
       {"Spruce Leaves", {18, 1}},
       {"Birch Leaves", {18, 2}},
       {"Jungle Leaves", {18, 3}},
       {"Acacia Leaves", {161, 0}},
       {"Dark Oak Leaves", {161, 1}},
       {"Lever", {69, 0}},
       {"Light Weighted Pressure Plate", {147, 0}},
       {"Jack o'Lantern", {91, 0}},
       {"Oak Log", {17, 0}},
       {"Spruce Log", {17, 1}},
       {"Birch Log", {17, 2}},
       {"Jungle Log", {17, 3}},
       {"Acacia Log", {162, 0}},
       {"Dark Oak Log", {162, 1}},
       {"Magma Cream", {378, 0}},
       {"Map", {395, 0}},
       {"Melon Slice", {360, 0}},
       {"Block of Melon", {103, 0}},
       {"Melon Seeds", {362, 0}},
       {"Milk Bucket", {335, 0}},
       {"Minecart", {328, 0}},
       {"Monster Spawner", {52, 0}},
       {"Infested Stone", {97, 0}},
       {"Infested Cobblestone", {97, 1}},
       {"Infested Stone Bricks", {97, 2}},
       {"Infested Mossy Stone Bricks", {97, 3}},
       {"Infested Cracked Stone Bricks", {97, 4}},
       {"Infested Chiseled Stone Bricks", {97, 5}},
       {"Mossy Cobblestone", {48, 0}},
       {"Mushroom Stew", {282, 0}},
       {"Raw Mutton", {423, 0}},
       {"Mycelium", {110, 0}},
       {"Name Tag", {421, 0}},
       {"Block of Nether Bricks", {112, 0}},
       {"Nether Brick Fence", {113, 0}},
       {"Nether Brick Stairs", {114, 0}},
       {"Nether Star", {399, 0}},
       {"Nether Wart", {372, 0}},
       {"Nether Brick", {405, 0}},
       {"Netherrack", {87, 0}},
       {"Note Block", {25, 0}},
       {"Oak Stairs", {53, 0}},
       {"Obsidian", {49, 0}},
       {"Packed Ice", {174, 0}},
       {"Painting", {321, 0}},
       {"Paper", {339, 0}},
       {"Piston", {33, 0}},
       {"Oak Planks", {5, 0}},
       {"Spruce Planks", {5, 1}},
       {"Birch Planks", {5, 2}},
       {"Jungle Planks", {5, 3}},
       {"Acacia Planks", {5, 4}},
       {"Dark Oak Planks", {5, 5}},
       {"Poisonous Potato", {394, 0}},
       {"Raw Porkchop", {319, 0}},
       {"Potato", {392, 0}},
       {"Water Bottle", {373, 0}},
       {"Potion of Regeneration (0:45)", {373, 8193}},
       {"Potion of Swiftness (3:00 - Speed)", {373, 8194}},
       {"Potion of Poison (0:45)", {373, 8196}},
       {"Potion of Strength (3:00)", {373, 8201}},
       {"Potion of Leaping (3:00 - Jump Boost)", {373, 8203}},
       {"Potion of Regeneration (0:22 - Regeneration II)", {373, 8225}},
       {"Potion of Swiftness (1:30 - Speed II)", {373, 8226}},
       {"Potion of Fire Resistance (3:00)", {373, 8227}},
       {"Potion of Poison (0:21/0:22 - Poison II)", {373, 8228}},
       {"Potion of Healing (Instant Health II)", {373, 8229}},
       {"Potion of Night Vision (3:00)", {373, 8230}},
       {"Potion of Weakness (1:30)", {373, 8232}},
       {"Potion of Strength (1:30 - Strength II)", {373, 8233}},
       {"Potion of Slowness (1:30)", {373, 8234}},
       {"Potion of Leaping (1:30 - Jump Boost II)", {373, 8235}},
       {"Potion of Harming (Instant Damage II)", {373, 8236}},
       {"Potion of Water Breathing (3:00)", {373, 8237}},
       {"Potion of Invisibility (3:00)", {373, 8238}},
       {"Potion of Regeneration (1:30/2:00)", {373, 8257}},
       {"Potion of Swiftness (8:00 - Speed)", {373, 8258}},
       {"Potion of Fire Resistance (8:00)", {373, 8259}},
       {"Potion of Poison (1:30/2:00)", {373, 8260}},
       {"Potion of Healing (Instant Health)", {373, 8261}},
       {"Potion of Night Vision (8:00)", {373, 8262}},
       {"Potion of Weakness (4:00)", {373, 8264}},
       {"Potion of Strength (8:00)", {373, 8265}},
       {"Potion of Slowness (4:00)", {373, 8266}},
       {"Potion of Leaping (8:00 - Jump Boost)", {373, 8267}},
       {"Potion of Harming (Instant Damage)", {373, 8268}},
       {"Potion of Water Breathing (8:00)", {373, 8269}},
       {"Potion of Invisibility (8:00)", {373, 8270}},
       {"Splash Potion of Regeneration (0:45/0:33)", {373, 16385}},
       {"Splash Potion of Swiftness (3:00/2:15 - Speed)", {373, 16386}},
       {"Splash Potion of Poison (0:45/0:33)", {373, 16388}},
       {"Splash Potion of Strength (3:00/2:15)", {373, 16393}},
       {"Splash Potion of Leaping (3:00/2:15 - Jump Boost)", {373, 16395}},
       {"Splash Potion of Regeneration (0:22/0:16 - Regeneration II)", {373, 16417}},
       {"Splash Potion of Swiftness (1:30/1:07 - Speed II)", {373, 16418}},
       {"Splash Potion of Fire Resistance (3:00/2:15)", {373, 16419}},
       {"Splash Potion of Poison (0:21/0:16 - Poison II)", {373, 16420}},
       {"Splash Potion of Healing (Instant Health II)", {373, 16421}},
       {"Splash Potion of Night Vision (3:00/2:15)", {373, 16422}},
       {"Splash Potion of Weakness (1:30/1:07)", {373, 16424}},
       {"Splash Potion of Strength (1:30/1:07 - Strength II)", {373, 16425}},
       {"Splash Potion of Slowness (1:30/1:07)", {373, 16426}},
       {"Splash Potion of Leaping (1:30/1:07 - Jump Boost II)", {373, 16427}},
       {"Splash Potion of Harming (Instant Damage II)", {373, 16428}},
       {"Splash Potion of Water Breathing (3:00/2:15)", {373, 16429}},
       {"Splash Potion of Invisibility (3:00/2:15)", {373, 16430}},
       {"Splash Potion of Regeneration (1:30)", {373, 16449}},
       {"Splash Potion of Swiftness (8:00/6:00 - Speed)", {373, 16450}},
       {"Splash Potion of Fire Resistance (8:00/6:00)", {373, 16451}},
       {"Splash Potion of Poison (1:30)", {373, 16452}},
       {"Splash Potion of Healing (Instant Health)", {373, 16453}},
       {"Splash Potion of Night Vision (8:00/6:00)", {373, 16454}},
       {"Splash Potion of Weakness (4:00/3:00)", {373, 16456}},
       {"Splash Potion of Strength (8:00/6:00)", {373, 16457}},
       {"Splash Potion of Slowness (4:00/3:00)", {373, 16458}},
       {"Splash Potion of Leaping (8:00/6:00 - Jump Boost)", {373, 16459}},
       {"Splash Potion of Harming (Instant Damage)", {373, 16460}},
       {"Splash Potion of Water Breathing (8:00/6:00)", {373, 16461}},
       {"Splash Potion of Invisibility (8:00/6:00)", {373, 16462}},
       {"Prismarine", {168, 0}},
       {"Prismarine Bricks", {168, 1}},
       {"Dark Prismarine", {168, 2}},
       {"Prismarine Crystals", {410, 0}},
       {"Prismarine Shard", {409, 0}},
       {"Pumpkin", {86, 0}},
       {"Pumpkin Pie", {400, 0}},
       {"Pumpkin Seeds", {361, 0}},
       {"Nether Quartz", {406, 0}},
       {"Block of Quartz", {155, 0}},
       {"Chiseled Quartz Block", {155, 1}},
       {"Quartz Pillar", {155, 2}},
       {"Nether Quartz Ore", {153, 0}},
       {"Quartz Stairs", {156, 0}},
       {"Raw Rabbit", {411, 0}},
       {"Rabbit's Foot", {414, 0}},
       {"Rabbit Hide", {415, 0}},
       {"Rabbit Stew", {413, 0}},
       {"Rails", {66, 0}},
       {"Music Disc (C418 - 11)", {2266, 0}},
       {"Music Disc (C418 - 13)", {2256, 0}},
       {"Music Disc (C418 - blocks)", {2258, 0}},
       {"Music Disc (C418 - cat)", {2257, 0}},
       {"Music Disc (C418 - chirp)", {2259, 0}},
       {"Music Disc (C418 - far)", {2260, 0}},
       {"Music Disc (C418 - mall)", {2261, 0}},
       {"Music Disc (C418 - mellohi)", {2262, 0}},
       {"Music Disc (C418 - stal)", {2263, 0}},
       {"Music Disc (C418 - strad)", {2264, 0}},
       {"Music Disc (C418 - wait)", {2267, 0}},
       {"Music Disc (C418 - ward)", {2265, 0}},
       {"Poppy", {38, 0}},
       {"Blue Orchid", {38, 1}},
       {"Allium", {38, 2}},
       {"Azure Bluet", {38, 3}},
       {"Red Tulip", {38, 4}},
       {"Orange Tulip", {38, 5}},
       {"White Tulip", {38, 6}},
       {"Pink Tulip", {38, 7}},
       {"Oxeye Daisy", {38, 8}},
       {"Red Mushroom", {40, 0}},
       {"Red Mushroom Block", {100, 0}},
       {"Red Sandstone", {179, 0}},
       {"Chiseled Red Sandstone", {179, 1}},
       {"Smooth Red Sandstone", {179, 2}},
       {"Red Sandstone Stairs", {180, 0}},
       {"Redstone Dust", {331, 0}},
       {"Block of Redstone", {152, 0}},
       {"Redstone Lamp", {123, 0}},
       {"Redstone Ore", {73, 0}},
       {"Redstone Torch", {76, 0}},
       {"Sugar Canes", {338, 0}},
       {"Redstone Repeater", {356, 0}},
       {"Rotten Flesh", {367, 0}},
       {"Saddle", {329, 0}},
       {"Sand", {12, 0}},
       {"Red Sand", {12, 1}},
       {"Sandstone", {24, 0}},
       {"Chiseled Sandstone", {24, 1}},
       {"Smooth Sandstone", {24, 2}},
       {"Sandstone Stairs", {128, 0}},
       {"Oak Sapling", {6, 0}},
       {"Spruce Sapling", {6, 1}},
       {"Birch Sapling", {6, 2}},
       {"Jungle Sapling", {6, 3}},
       {"Acacia Sapling", {6, 4}},
       {"Dark Oak Sapling", {6, 5}},
       {"Sea Lantern", {169, 0}},
       {"Shears", {359, -1}},
       {"Oak Sign", {323, 0}},
       {"Skeleton Skull", {397, 0}},
       {"Wither Skeleton Skull", {397, 1}},
       {"Zombie Head", {397, 2}},
       {"Player Head", {397, 3}},
       {"Creeper Head", {397, 4}},
       {"Slime Block", {165, 0}},
       {"Slimeball", {341, 0}},
       {"Snow Block", {80, 0}},
       {"Snow", {78, 0}},
       {"Snowball", {332, 0}},
       {"Soul Sand", {88, 0}},
       {"Creeper Spawn Egg", {383, 50}},
       {"Skeleton Spawn Egg", {383, 51}},
       {"Spider Spawn Egg", {383, 52}},
       {"Zombie Spawn Egg", {383, 54}},
       {"Slime Spawn Egg", {383, 55}},
       {"Ghast Spawn Egg", {383, 56}},
       {"Zombified Piglin Spawn Egg", {383, 57}},
       {"Enderman Spawn Egg", {383, 58}},
       {"Cave Spider Spawn Egg", {383, 59}},
       {"Silverfish Spawn Egg", {383, 60}},
       {"Blaze Spawn Egg", {383, 61}},
       {"Magma Cube Spawn Egg", {383, 62}},
       {"Bat Spawn Egg", {383, 65}},
       {"Witch Spawn Egg", {383, 66}},
       {"Endermite Spawn Egg", {383, 67}},
       {"Guardian Spawn Egg", {383, 68}},
       {"Pig Spawn Egg", {383, 90}},
       {"Sheep Spawn Egg", {383, 91}},
       {"Cow Spawn Egg", {383, 92}},
       {"Chicken Spawn Egg", {383, 93}},
       {"Squid Spawn Egg", {383, 94}},
       {"Wolf Spawn Egg", {383, 95}},
       {"Mooshroom Spawn Egg", {383, 96}},
       {"Ocelot Spawn Egg", {383, 98}},
       {"Horse Spawn Egg", {383, 100}},
       {"Rabbit Spawn Egg", {383, 101}},
       {"Villager Spawn Egg", {383, 120}},
       {"Glistering Melon Slice", {382, 0}},
       {"Spider Eye", {375, 0}},
       {"Sponge", {19, 0}},
       {"Wet Sponge", {19, 1}},
       {"Spruce Door", {427, 0}},
       {"Spruce Fence", {188, 0}},
       {"Spruce Fence Gate", {183, 0}},
       {"Spruce Stairs", {134, 0}},
       {"White Stained Glass", {95, 0}},
       {"Orange Stained Glass", {95, 1}},
       {"Magenta Stained Glass", {95, 2}},
       {"Light Blue Stained Glass", {95, 3}},
       {"Yellow Stained Glass", {95, 4}},
       {"Lime Stained Glass", {95, 5}},
       {"Pink Stained Glass", {95, 6}},
       {"Gray Stained Glass", {95, 7}},
       {"Light Gray Stained Glass", {95, 8}},
       {"Cyan Stained Glass", {95, 9}},
       {"Purple Stained Glass", {95, 10}},
       {"Blue Stained Glass", {95, 11}},
       {"Brown Stained Glass", {95, 12}},
       {"Green Stained Glass", {95, 13}},
       {"Red Stained Glass", {95, 14}},
       {"Black Stained Glass", {95, 15}},
       {"White Stained Glass Pane", {160, 0}},
       {"Orange Stained Glass Pane", {160, 1}},
       {"Magenta Stained Glass Pane", {160, 2}},
       {"Light Blue Stained Glass Pane", {160, 3}},
       {"Yellow Stained Glass Pane", {160, 4}},
       {"Lime Stained Glass Pane", {160, 5}},
       {"Pink Stained Glass Pane", {160, 6}},
       {"Gray Stained Glass Pane", {160, 7}},
       {"Light Gray Stained Glass Pane", {160, 8}},
       {"Cyan Stained Glass Pane", {160, 9}},
       {"Purple Stained Glass Pane", {160, 10}},
       {"Blue Stained Glass Pane", {160, 11}},
       {"Brown Stained Glass Pane", {160, 12}},
       {"Green Stained Glass Pane", {160, 13}},
       {"Red Stained Glass Pane", {160, 14}},
       {"Black Stained Glass Pane", {160, 15}},
       {"White Terracotta", {159, 0}},
       {"Orange Terracotta", {159, 1}},
       {"Magenta Terracotta", {159, 2}},
       {"Light Blue Terracotta", {159, 3}},
       {"Yellow Terracotta", {159, 4}},
       {"Lime Terracotta", {159, 5}},
       {"Pink Terracotta", {159, 6}},
       {"Gray Terracotta", {159, 7}},
       {"Light Gray Terracotta", {159, 8}},
       {"Cyan Terracotta", {159, 9}},
       {"Purple Terracotta", {159, 10}},
       {"Blue Terracotta", {159, 11}},
       {"Brown Terracotta", {159, 12}},
       {"Green Terracotta", {159, 13}},
       {"Red Terracotta", {159, 14}},
       {"Black Terracotta", {159, 15}},
       {"Stick", {280, 0}},
       {"Sticky Piston", {29, 0}},
       {"Stone", {1, 0}},
       {"Granite", {1, 1}},
       {"Polished Granite", {1, 2}},
       {"Diorite", {1, 3}},
       {"Polished Diorite", {1, 4}},
       {"Andesite", {1, 5}},
       {"Polished Andesite", {1, 6}},
       {"Stone Axe", {275, -1}},
       {"Stone Brick Stairs", {109, 0}},
       {"Stone Button", {77, 0}},
       {"Stone Hoe", {291, -1}},
       {"Stone Pickaxe", {274, -1}},
       {"Stone Pressure Plate", {70, 0}},
       {"Stone Shovel", {273, -1}},
       {"Stone Slab", {44, 0}},
       {"Sandstone Slab", {44, 1}},
       {"Cobblestone Slab", {44, 3}},
       {"Brick Slab", {44, 4}},
       {"Stone Brick Slab", {44, 5}},
       {"Nether Brick Slab", {44, 6}},
       {"Quartz Slab", {44, 7}},
       {"Red Sandstone Slab", {182, 0}},
       {"Cobblestone Stairs", {67, 0}},
       {"Stone Sword", {272, -1}},
       {"Stone Bricks", {98, 0}},
       {"Mossy Stone Bricks", {98, 1}},
       {"Cracked Stone Bricks", {98, 2}},
       {"Chiseled Stone Bricks", {98, 3}},
       {"String", {287, 0}},
       {"Sugar", {353, 0}},
       {"Grass", {31, 1}},
       {"Fern", {31, 2}},
       {"TNT", {46, 0}},
       {"Minecart with TNT", {407, 0}},
       {"Torch", {50, 0}},
       {"Oak Trapdoor", {96, 0}},
       {"Trapped Chest", {146, 0}},
       {"Tripwire Hook", {131, 0}},
       {"Vines", {106, 0}},
       {"Water Bucket", {326, 0}},
       {"Lily Pad", {111, 0}},
       {"Cobweb", {30, 0}},
       {"Wheat", {296, 0}},
       {"Seeds", {295, 0}},
       {"Wooden Axe", {271, -1}},
       {"Oak Button", {143, 0}},
       {"Oak Door", {324, 0}},
       {"Wooden Hoe", {290, -1}},
       {"Wooden Pickaxe", {270, -1}},
       {"Oak Pressure Plate", {72, 0}},
       {"Wooden Shovel", {269, -1}},
       {"Oak Slab", {126, 0}},
       {"Spruce Slab", {126, 1}},
       {"Birch Slab", {126, 2}},
       {"Jungle Slab", {126, 3}},
       {"Acacia Slab", {126, 4}},
       {"Dark Oak Slab", {126, 5}},
       {"Wooden Sword", {268, -1}},
       {"White Wool", {35, 0}},
       {"Orange Wool", {35, 1}},
       {"Magenta Wool", {35, 2}},
       {"Light Blue Wool", {35, 3}},
       {"Yellow Wool", {35, 4}},
       {"Lime Wool", {35, 5}},
       {"Pink Wool", {35, 6}},
       {"Gray Wool", {35, 7}},
       {"Light Gray Wool", {35, 8}},
       {"Cyan Wool", {35, 9}},
       {"Purple Wool", {35, 10}},
       {"Blue Wool", {35, 11}},
       {"Brown Wool", {35, 12}},
       {"Green Wool", {35, 13}},
       {"Red Wool", {35, 14}},
       {"Black Wool", {35, 15}},
       {"Book and Quill", {386, 0}},
       {"Written Book", {387, 0}},
       {"Dandelion", {37, 0}},
    };

    // Reverse mapping from BlockData to name (optional, for reverse lookup)
    static inline std::unordered_map<int, std::unordered_map<int, std::string>> blockToName;

    static void Init()
    {
        for (const auto& [name, data] : nameToBlock)
        {
            blockToName[data.id][data.metadata] = name;
        }
        LOG_INFO("Loaded all Minecraft blocks");
    }

    static BlockData GetBlockByName(const std::string& name)
    {
        if (nameToBlock.find(name) != nameToBlock.end())
        {
            return nameToBlock[name];
        }
        else
        {
            return { -1, -1 };
        }
    }

    static std::string GetNameByData(int id, int metadata)
    {
        if (blockToName.find(id) != blockToName.end() && blockToName[id].find(metadata) != blockToName[id].end())
        {
            return blockToName[id][metadata];
        }
        else
        {
			return "Unknown";
        }
    }
};

struct MinecraftUtils
{
    static inline bool IsWeapon(int id)
    {
        bool isSword = (id == 268 || id == 272 || id == 267 || id == 276 || id == 283) && settings::Weapon_Sword;
		bool isAxe = (id == 271 || id == 275 || id == 258 || id == 279 || id == 286) && settings::Weapon_Axe;
		bool isStick = (id == 280) && settings::Weapon_Stick;

		return isSword || isAxe || isStick;
    }

    static inline bool IsWeapon(std::string name)
    {
		return name.find("sword") != std::string::npos;
    }

    static inline bool IsWeapon(CItemStack item)
    {
        if (item.GetInstance() != nullptr)
        {
            return IsWeapon(item.GetItem().GetID());
        }

        return settings::Weapon_Fist || false;
    }

    static inline bool IsEmpty(CItemStack item)
    {
        return item.GetInstance() == nullptr;
    }

    static int MainInventoryToWindowClick(int index)
    {
        if (index < 9) return index + 36;
        return index;
    }
};