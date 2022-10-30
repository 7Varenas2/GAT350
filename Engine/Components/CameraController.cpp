#include "CameraController.h"
#include "Engine.h"

void neu::CameraController::Update()
{
    if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
        m_owner->m_transform.position.x -= speed * g_time.deltaTime;

    if (g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
        m_owner->m_transform.position.x += speed * g_time.deltaTime;

    if (g_inputSystem.GetKeyState(key_up) == InputSystem::KeyState::Held)
        m_owner->m_transform.position.y += speed * g_time.deltaTime;

    if (g_inputSystem.GetKeyState(key_down) == InputSystem::KeyState::Held)
        m_owner->m_transform.position.y -= speed * g_time.deltaTime;

    if (g_inputSystem.GetButtonState(button_left) == InputSystem::KeyState::Held)
        m_owner->m_transform.position.z += speed * g_time.deltaTime;
    if (g_inputSystem.GetButtonState(button_right) == InputSystem::KeyState::Held)
        m_owner->m_transform.position.z -= speed * g_time.deltaTime;
}



bool neu::CameraController::Write(const rapidjson::Value& value) const
{
    return true;
}

bool neu::CameraController::Read(const rapidjson::Value& value)
{
    READ_DATA(value, speed);
    return true;
}



