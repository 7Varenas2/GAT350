#include "Engine.h"
#include <iostream>

#define POST_PROCESS

int main(int argc, char** argv)
{
	std::cout << neu::ToLower("HeLLo WorLd") << '\n';

	// DO NOT REMOVE
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");
	 
	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 800);
	LOG("Window Initialized...");
	neu::g_gui.Initialize(neu::g_renderer);

	// Create framebuffer texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(64, 64);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);
	
	// Create framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	// Load scene
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/postprocess.scn");

	float x = 0;
	glm::vec3 rot = glm::vec3{ 0,0,0 };
	bool quit = false;

	float refractiveIndex = 1.0;
	float interpolation = 1.0;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;
		
		neu::g_renderer.BeginFrame();

		//auto program = neu::g_resources.Get<neu::Program>("shaders/fx/refraction.prog");
		//if (program)
		//{
		//	program->Use();
		//	program->SetUniform("interp", interpolation);
		//	program->SetUniform("refractiveIndex", refractiveIndex);
		//}
		
		auto actor = scene->GetActorFromName("Skybox");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		// Move camera around
		actor = scene->GetActorFromName("Light");
		actor = scene->GetActorFromName("Light2");
		if (actor)
		{
			// move light using sin (y) wave
			/*actor->m_transform.position = rot;*/
		}


		ImGui::Begin("Hola!");
		//ImGui::Button("Press Me!");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::SliderFloat("Interpolation", &interpolation, 0.01f, 1);
		ImGui::DragFloat("Refraction Index", &refractiveIndex, 0.01f, 1);
		ImGui::End();

		scene->Update();

		{
			auto actor = scene->GetActorFromName("Skybox");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		// Render pass 1 (render to framebuffer)
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();

		{
			auto actor = scene->GetActorFromName("Banana");
			if (actor)
			{
				actor->SetActive(true);
			}
		}

		// Render pass 2 (render to screen)
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();

		//POST PROCESS
#ifdef POST_PROCESS
		// Dont draw post process actor when rendering to the framebuffer
  // don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 
		// Working till Main additions



		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;

}

