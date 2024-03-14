#include "Game.h"

Game* Game::gameInstance = nullptr;

Game::Game() {
	inputDevice = new InputDevice(this);
	gameInstance = this;
}

void Game::CreateBackBuffer() {

}

void Game::DestroyResources() {

}

void Game::Draw() {
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(display.GetClientWidth());
	viewport.Height = static_cast<float>(display.GetClientHeight());
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	Context->RSSetViewports(1, &viewport);

	for (auto& component : Components)
	{
		component->Draw();
	}

	Context->OMSetRenderTargets(0, nullptr, nullptr);
	SwapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}

void Game::EndFrame() {

}

void Game::Exit() {

}

void Game::Initialize() {
	SwapDesc.BufferCount = 2;
	SwapDesc.BufferDesc.Width = display.GetClientWidth();
	SwapDesc.BufferDesc.Height = display.GetClientWidth();
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDesc.OutputWindow = display.GethWnd();
	SwapDesc.Windowed = true;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	SwapDesc.SampleDesc.Count = 1;
	SwapDesc.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	bool isExitRequested = false;

	auto res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&SwapDesc,
		&SwapChain,
		&Device,
		nullptr,
		&Context);

	if (FAILED(res))
	{
		std::cout << "Well , unexpected shit happens\n";
		// Well, that was unexpected
	}

	res = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)
	res = Device->CreateRenderTargetView(backTex, nullptr, &rtv);

	for (auto& component : Components)
	{
		component->game = gameInstance;
		component->Initialize();
	}

	PrevTime = std::chrono::steady_clock::now();
}

void Game::MessageHandler() {

}

void Game::PrepareFrame() {
	Context->OMSetRenderTargets(1, &rtv, nullptr);

	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Context->ClearRenderTargetView(rtv, color);
}

void Game::PrepareResources() {

}

void Game::RestoreTargets() {

}

void Game::Run() {
	display.Initialize();
	Initialize();
	isExitRequested = false;
	while (!isExitRequested) {
		UpdateInternal();

		Update();
		PrepareFrame();
		Draw();
		EndFrame();
	}
	DestroyResources();
}

void Game::Update() {
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT) {
		isExitRequested = true;
	}

	for (int i = 0; i < Components.size(); i++) {
		Components[i]->Update();
	}
	Context->ClearState();
}

void Game::UpdateInternal() {
	auto	curTime = std::chrono::steady_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - PrevTime).count() / 1000000.0f;
	PrevTime = curTime;

	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f) {
		float fps = frameCount / totalTime;

		totalTime -= 1.0f;

		WCHAR text[256];
		swprintf_s(text, TEXT("FPS: %f"), fps);
		SetWindowText(display.GethWnd(), text);

		frameCount = 0;
	}
}
