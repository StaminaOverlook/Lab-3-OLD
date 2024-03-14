#pragma once

#include <windows.h>
#include <iostream>
#include "InputDevice.h"

static int count_messages = 0;


class DisplayWin32
{
private:
	int ClientHeight = 800;
	int ClientWidth = 800;
	HINSTANCE hInstance;
	LPCWSTR Name = L"MyGame";
	HWND hWnd;
	int Module;
	WNDCLASSEX wc;

public:
	HWND GethWnd() {
		return hWnd;
	}
	int GetClientHeight() {
		return ClientHeight;
	}
	int GetClientWidth() {
		return ClientWidth;
	}

	DisplayWin32();

	void Initialize();
};

