#pragma once
#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <conio.h>

#include "../SDK/libmem++/libmem.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"

MODULEENTRY32 GetModule(DWORD procId, const wchar_t* str);

//IMGUI
struct {
    ImFont* msyhbd = nullptr;
} fonts;

#endif