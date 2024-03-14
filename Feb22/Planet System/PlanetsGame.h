#pragma once

#include "../Game.h"
#include "Sphere.h"
#include "Camera.h"

class PlanetsGame : public Game
{
private:
	Camera* camera;
	std::vector <Sphere*> spheres;

public:
	void AssignCamera(Camera* _camera) {
		camera = _camera;
	}
	Camera* GetCamera() {
		return camera;
	}
	void AddSphere(Sphere* pl) {
		spheres.push_back(pl);
	}
	std::vector <Sphere*> GetSpheres() {
		return spheres;
	}

	PlanetsGame();

	void Update();
};

