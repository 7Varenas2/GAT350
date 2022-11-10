#include "LightComponent.h"
#include "Engine.h"

namespace neu
{
	void LightComponent::Update()
	{
		// transform the light position by the view, puts light in model view space
		glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner->m_transform.position, 1);

		// Transform forward returns a vector pointing in the forward direction of the light
		glm::vec3 direction = m_owner->m_transform.getForward();

		// get all programs in the resource system
		auto programs = g_resources.Get<Program>();
		// set programs light properties
		for (auto& program : programs)
		{
			program->Use();
			program->SetUniform("light.type", (int)type);
			program->SetUniform("light.ambient", glm::vec3{ 0.2f });
			program->SetUniform("light.color", color);
			program->SetUniform("light.position", position);
			// Set uniforms for the light
			program->SetUniform("light.direction", direction); // not updating
			program->SetUniform("light.cutoff", glm::radians(cutoff));
			program->SetUniform("light.exponent", exponent);

		}
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		// Read cutoff and exponent data
		// Read in a string for the type name and set the enum based on the string, if not defined it will default to a point
		std::string type_name;
		READ_DATA(value, type_name);
		if (CompareIgnoreCase(type_name, "directional"))
		{
			type = Type::Directional;
		}
		else if (CompareIgnoreCase(type_name, "spot"))
		{
			type = Type::Spot;
		}
		else
		{
			type = Type::Point;
		}
		
		READ_DATA(value, color);

		return true;
	}

}