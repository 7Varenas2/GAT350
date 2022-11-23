#pragma once
#include "Framework/Component.h"
#include "Renderer/Program.h"

namespace neu
{
	class Program;
	class LightComponent : public Component
	{
	public:

		enum Type
		{
			Point,
			Directional,
			Spot
		};

		CLASS_DECLARATION(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		// Takes in shader program and the index of light in the shader light array
		void SetProgram(std::shared_ptr<Program> program, int index);

	public:
		glm::vec3 color{ 0 };
		Type type = Type::Point;
		float cutoff = 45.0f;
		float exponent = 50.0f;

	};
}