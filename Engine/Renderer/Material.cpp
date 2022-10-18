#include "Material.h"
#include "Engine.h"

namespace neu
{
	bool Material::Create(std::string filename, ...)
	{
		// Load program json document
		rapidjson::Document document;
		bool success = neu::json::Load(filename, document);
		if (!success)
		{
			LOG("Could not load program file (%s).", filename.c_str());
			return false;
		}

		// Read the program name
		std::string program;
		READ_DATA(document, program);
		m_program = neu::g_resources.Get<neu::Program>(program);

		// Get program resource
		std::string texture;
		READ_DATA(document, texture);
		if (!texture.empty())
		{
			// Get texture resource
			m_textures.push_back(neu::g_resources.Get<neu::Texture>(texture));
		}

		// Read colors 
		
		READ_DATA(document, ambient);
		READ_DATA(document, diffuse);
		READ_DATA(document, specular);
		READ_DATA(document, shininess);

		return true;
	}

	void Material::Bind()
	{
		m_program->Use();
		for (auto& texture : m_textures)
		{
			texture->Bind();
		}
	}
}
