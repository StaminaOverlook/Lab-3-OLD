#pragma once

#include "../GameComponent.h"
#include <vector>
#include "../InputDevice.h"

using namespace DirectX;
using namespace SimpleMath;

enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;

class Camera : public GameComponent {
private: 
    InputDevice* inputDevice;
public:
    Vector3 Position;
    Vector3 Front;
    Vector3 Up;
    Vector3 Right;
    Vector3 WorldUp;

    float Yaw;
    float Pitch;

    float MouseSensitivity;
    float Zoom;

    float velocity = 0.1f;

    float FOV = 90;
    float aspect = 16 / 9;
    float viewHeight = 1600 * aspect;
    float viewWidth = 900 * aspect;
    float nearZ = 1;
    float farZ = 100;

    bool perspective = 1;

    
    Camera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(Vector3(0.0f, 0.0f, -1.0f)), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Vector3(0.0f, 0.0f, -1.0f)), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = Vector3(posX, posY, posZ);
        WorldUp = Vector3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Matrix GetViewMatrix()
    {
        return XMMatrixLookAtRH(Position, Position + Front, Up);
    }
    
    Matrix GetProjectionMatrix() {
        if (perspective)
            return XMMatrixPerspectiveFovRH(FOV, aspect, nearZ, farZ);
        else
            return XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);
    }

    /*Matrix GetOrthogonalProjection() {

    }
    Matrix GetPerspectiveProjection() {
        double D2R = XM_PI / 180.0;
        double yScale = 1.0 / tan(D2R * FOV / 2);
        double xScale = yScale / aspect;
        double nearmfar = near - far;
        Matrix m = {
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, (far + near) / nearmfar, -1,
            0, 0, 2 * far * near / nearmfar, 0
        };
        return m;
    }*/

    // возвращает случайное значение
    /*float Random2D(glm::vec2 st)
    {
        return glm::fract(glm::sin(glm::dot(st, glm::vec2(12.9898f, 78.233f))) * 43758.5453123f);
    }*/

    // интерполированный шум
    /*float InterpolatedNoise(int ind, float x, float y) {
        float integer_X = floor(x);
        float fractional_X = glm::fract(x);
        float integer_Y = floor(y);
        float fractional_Y = glm::fract(y);
        glm::vec2 randomInput = glm::vec2(integer_X, integer_Y);
        float a = Random2D(randomInput);
        float b = Random2D(randomInput + glm::vec2(1.0, 0.0));
        float c = Random2D(randomInput + glm::vec2(0.0, 1.0));
        float d = Random2D(randomInput + glm::vec2(1.0, 1.0));

        glm::vec2 w = glm::vec2(fractional_X, fractional_Y);
        w = w * w * w * (10.0f + w * (-15.0f + 6.0f * w));

        float k0 = a,
            k1 = b - a,
            k2 = c - a,
            k3 = d - c - b + a;

        return k0 + k1 * w.x + k2 * w.y + k3 * w.x * w.y;
    }*/

    /*float perlin(glm::vec2 st, int octaves, float freq, float gDispFactor) {
        glm::mat2 m;
        m[0][0] = 0.8;
        m[0][1] = -0.6;
        m[1][0] = 0.6;
        m[1][1] = 0.8;

        float persistence = 0.5;
        float total = 0.0,
            frequency = 0.005 * freq,
            amplitude = gDispFactor;
        for (int i = 0; i < octaves; ++i) {
            frequency *= 2.0;
            amplitude *= persistence;

            glm::vec2 v = frequency * st;

            total += InterpolatedNoise(0, v.x, v.y) * amplitude;
        }
        return total * total * total;
    }*/

    void Initialize() override;

    void Move(Camera_Movement direction, float velocity);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void ProcessMouseScroll(float yoffset);

    void Update();

private:

    void updateCameraVectors() {

        Vector3 front;
        front.x = cos(XMConvertToRadians(Yaw)) * cos(XMConvertToRadians(Pitch));
        front.y = sin(XMConvertToRadians(Pitch));
        front.z = sin(XMConvertToRadians(Yaw)) * cos(XMConvertToRadians(Pitch));

        Front = XMVector3Normalize(front);
        Right = XMVector3Normalize(XMVector3Cross(Front, WorldUp));
        Up = XMVector3Normalize(XMVector3Cross(Right, Front));
    }
};

