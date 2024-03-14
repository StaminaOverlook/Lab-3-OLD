#include "Camera.h"
#include "PlanetsGame.h"

void Camera::Initialize() {
	inputDevice = game->GetInputDevice();
}

void Camera::Move(Camera_Movement direction, float velocity)
{
    switch (direction)
    {
    case Camera_Movement::FORWARD:
        Position += Front * velocity;
        break;
    case Camera_Movement::BACKWARD:
        Position -= Front * velocity;
        break;
    case Camera_Movement::LEFT:
        Position -= Right * velocity;
        break;
    case Camera_Movement::RIGHT:
        Position += Right * velocity;
        break;
    case Camera_Movement::UP:
        Position += Up * velocity;
        break;
    case Camera_Movement::DOWN:
        Position -= Up * velocity;
        break;
    default:
        break;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::Update() {
    if (game->GetInputDevice()->IsKeyDown(Keys::W)) {
        std::cout << "Moving FORWARD!" << std::endl;
        Move(Camera_Movement::FORWARD, velocity);
    }

    if (game->GetInputDevice()->IsKeyDown(Keys::S)) {
        std::cout << "Moving BACKWARD!" << std::endl;
        Move(Camera_Movement::BACKWARD, velocity);
    }

    if (game->GetInputDevice()->IsKeyDown(Keys::D)) {
        std::cout << "Moving RIGHT!" << std::endl;
        Move(Camera_Movement::RIGHT, velocity);
    }

    if (game->GetInputDevice()->IsKeyDown(Keys::A)) {
        std::cout << "Moving LEFT!" << std::endl;
        Move(Camera_Movement::LEFT, velocity);
    }
    updateCameraVectors();
}