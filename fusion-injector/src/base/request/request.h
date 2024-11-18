#pragma once

#include <windows.h>
#include <winhttp.h>
#include <string>
#include <fstream>
#include <iostream>

#pragma comment(lib, "winhttp.lib")

namespace Request {

    // Function to perform a simple GET request and return the response as a string
    std::string Get(const std::wstring& url);

    // Function to download a file from a given URL to the specified file path
    bool DownloadToFile(const std::wstring& url, const std::wstring& filePath);

} // namespace Request
