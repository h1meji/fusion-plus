#pragma once

#include <windows.h>
#include <winhttp.h>
#include <string>
#include <fstream>

#pragma comment(lib, "winhttp.lib")

namespace Request {

    std::string Get(const std::wstring& url);

    bool DownloadToFile(const std::wstring& url, const std::wstring& filePath);

}
