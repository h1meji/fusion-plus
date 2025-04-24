#pragma once

#include <iomanip>
#include <sstream>
#include <string>

#include "util/math/math.h"

struct StringUtils
{
    static std::string FloatToString(float value, int precision)
    {
        if (value == NAN || value == INFINITY || value == -INFINITY) return "0";

        std::ostringstream out;
        out << std::fixed << std::setprecision(precision) << value;
        return out.str();
    }

    static std::string YawToDirection(float yaw)
    {
        float warpedYaw = Math::WrapAngleTo180(yaw);

        // 0 = South, 45 = South-West, 90 = West, 135 = North-West, -180 = North, -135 = North-East, -90 = East, -45 = South-East
        if (warpedYaw >= -22.5 && warpedYaw < 22.5) return "S";
        if (warpedYaw >= 22.5 && warpedYaw < 67.5) return "SW";
        if (warpedYaw >= 67.5 && warpedYaw < 112.5) return "W";
        if (warpedYaw >= 112.5 && warpedYaw < 157.5) return "NW";
        if (warpedYaw >= 157.5 || warpedYaw < -157.5) return "N";
        if (warpedYaw >= -157.5 && warpedYaw < -112.5) return "NE";
        if (warpedYaw >= -112.5 && warpedYaw < -67.5) return "E";
        if (warpedYaw >= -67.5 && warpedYaw < -22.5) return "SE";

        return "N/A";
    }

    static const char* ExtractBeforeDoubleHash(const char* label)
    {
        const char* pos = strstr(label, "##"); // Find occurrence of ##
        if (pos) {
            size_t len = pos - label; // Length before ##
            char* newLabel = new char[len + 1]; // Allocate new string
            strncpy_s(newLabel, len + 1, label, len); // Copy up to ##
            newLabel[len] = '\0'; // Null-terminate
            return newLabel; // Return new string
        }
        return label; // No ## found, return original
    }

    static std::string ToLower(const std::string& str)
    {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
};