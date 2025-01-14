#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <windows.h>
#include <shlobj.h>

#include "nlohmann/json.hpp"
#include "settings.h"

using json = nlohmann::json;

namespace ConfigManager
{
	const std::string FILE_SUFFIX = ".fusion";

	bool LoadConfig(const char* name);
	bool SaveConfig(const char* name);

	std::vector<std::string> GetConfigList();

    // SFINAE check to ensure that T is a type that can be deserialized from json // S.O ChatGPT
    template<typename T, typename = void>
    struct is_json_deserializable : std::false_type {};

    template<typename T>
    struct is_json_deserializable<T, std::void_t<decltype(std::declval<json>().get<T>())>> : std::true_type {};

    template<typename T>
    bool GetJsonValue(const json& j, T& value, const std::string& key)
    {
        if constexpr (is_json_deserializable<T>::value) {  // Check if T is deserializable from json
            if (j.contains(key) && !j.at(key).is_null()) {
                value = j.at(key).get<T>();
                return true;
            }
        }
		else if (std::is_same<T, float[4]>::value) {
			if (j.contains(key) && j.at(key).is_array() && j.at(key).size() == 4) {
				for (size_t i = 0; i < 4; ++i) {
					if (!j.at(key)[i].is_number()) {
						return false;
					}
					value[i] = j.at(key)[i].get<float>();
				}
				return true;
			}
		}
		else if (std::is_same<T, float[3]>::value)
		{
			if (j.contains(key) && j.at(key).is_array() && j.at(key).size() == 3) {
				for (size_t i = 0; i < 3; ++i) {
					if (!j.at(key)[i].is_number()) {
						return false;
					}
					value[i] = j.at(key)[i].get<float>();
				}
				return true;
			}
		}
		else if (std::is_same<T, float[2]>::value)
		{
			if (j.contains(key) && j.at(key).is_array() && j.at(key).size() == 2) {
				for (size_t i = 0; i < 2; ++i) {
					if (!j.at(key)[i].is_number()) {
						return false;
					}
					value[i] = j.at(key)[i].get<float>();
				}
				return true;
			}
		}
		return false;
    }

	bool SettingsToJson(json& j);
	bool JsonToSettings(const json& j);

    std::string GetDocumentsPath();

	std::string GetConfigPath();
	std::string GetFusionPath();

	// Friends
	bool LoadFriends();
	bool SaveFriends();
	bool AddFriend(const std::string& name);
	bool RemoveFriend(const std::string& name);
	bool IsFriend(const std::string& name);
};