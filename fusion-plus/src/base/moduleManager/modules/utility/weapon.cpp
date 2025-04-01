#include "weapon.h"
#include <imgui/imgui.h>
#include <menu/menu.h>

void Weapon::RenderMenu()
{
	Menu::Checkbox("Swords", &settings::Weapon_Sword);
	Menu::Checkbox("Axes", &settings::Weapon_Axe);
	Menu::Checkbox("Sticks", &settings::Weapon_Stick);
	Menu::Checkbox("Fists", &settings::Weapon_Fist);
}
