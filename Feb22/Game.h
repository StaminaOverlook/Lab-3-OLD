#pragma once

#include <windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <iostream>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include "DisplayWin32.h"
#include "TriangleComponent.h"
#include "GameComponent.h"

class Game
{
protected:
	//	int backBuffer;
	ID3D11DeviceContext* Context;
	//	int DebugAnnotation;
	Microsoft::WRL::ComPtr<ID3D11Device> Device;
	InputDevice* inputDevice;
	HINSTANCE Instance;
	std::chrono::time_point<std::chrono::steady_clock> PrevTime;
	//	int RenderSRV;
	//	int RenderView;
	//	int ScreenResized;
	//	int StartTime;
	IDXGISwapChain* SwapChain;
	float totalTime = 0;
	DXGI_SWAP_CHAIN_DESC SwapDesc;
	DisplayWin32 display;
	bool isExitRequested;
	MSG msg;

	ID3D11Texture2D* backTex;
	ID3D11RenderTargetView* rtv;

	unsigned int frameCount = 0;

	std::vector <GameComponent*> Components;

	float deltaTime = 0;

public:
	static Game* gameInstance;

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() {
		return Device;
	}
	InputDevice* GetInputDevice() {
		return inputDevice;
	}
	ID3D11DeviceContext* GetContext() {
		return Context;
	}
	DisplayWin32 GetDisplay() {
		return display;
	}
	float GetDeltaTime() {
		return deltaTime;
	}

	Game();

	void AddComponent(GameComponent* comp)
	{
		Components.push_back(comp);
	}

	void CreateBackBuffer();

	void DestroyResources();

	void Draw();

	void EndFrame();

	void Exit();

	void Initialize();

	void MessageHandler();

	void PrepareFrame();

	void PrepareResources();

	void RestoreTargets();

	void Run();

	void Update();

	void UpdateInternal();
};