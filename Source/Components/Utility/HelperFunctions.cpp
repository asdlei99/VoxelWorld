/*================================================================
Filename: HelperFunctions.cpp
Date: 2018.1.13
Created by AirGuanZ
================================================================*/
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <Windows.h>

#include "D3D11Header.h"
#include "HelperFunctions.h"

std::string Helper::ToStr(const std::wstring &wstr)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char *chs = new char[size];
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, chs, size, nullptr, nullptr);
    std::string str(chs);
    delete[] chs;
    return str;
}

std::wstring Helper::ToWStr(const std::string &str)
{
    int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t *wide = new wchar_t[num];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
    std::wstring wstr(wide);
    delete[] wide;
    return wstr;
}
