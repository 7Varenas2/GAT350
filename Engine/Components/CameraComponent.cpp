#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace neu
{

    void CameraComponent::Update()
    {
        // Calculates the view matrix using the glm::LookAt(). 
        // The actor transfor posiiton is used for the eye and the position plus the transform
        // forward the target position.
        m_view = glm::lookAt(m_owner->m_transform.position, m_owner->m_transform.position + m_owner->m_transform.getForward(), glm::vec3{ 0, 1, 0 });

    }

    void CameraComponent::SetPerspective(float fov, float aspectRatio, float near, float far)
    {
        m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);

    }



    bool CameraComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CameraComponent::Read(const rapidjson::Value& value)
    {
         // Will read in th eprojection parameters fov (field of view), aspect ratio
        // (screen width / screen height), near clip distance, far clip distance
        // If aspect ration is not provided in the JSON file, it will be calculated using the renderer window width and height

        float fov;
        READ_DATA(value, fov);
        float aspect_ratio;
        if (!READ_DATA(value, aspect_ratio))
        {
            aspect_ratio = g_renderer.GetWidth() / (float(g_renderer.GetHeight()));
        }

        float near;
        READ_DATA(value, near);
        float far;
        READ_DATA(value, far);

        SetPerspective(fov, aspect_ratio, near, far);
        return true;

    }

    void CameraComponent::SetProgram(std::shared_ptr<Program> program)
    {
        program->Use();
        program->SetUniform("view", m_view);
        program->SetUniform("projection", m_projection);

    }

}
