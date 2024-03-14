#include "PlanetsGame.h"

PlanetsGame::PlanetsGame() {
	inputDevice = new InputDevice(this);
	gameInstance = this;
}

void PlanetsGame::Update() {
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
