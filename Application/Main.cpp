#include "Engine.h"
#include <iostream>

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

	// Load scene
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/test.scn");


	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;
		
		neu::g_renderer.BeginFrame();
		
		auto actor = scene->GetActorFromName("Banana");
		if (actor)
		{
			actor->m_transform.rotation.y += 30.0f * neu::g_time.deltaTime;
		}

		auto material = neu::g_resources.Get<neu::Material>("Materials/multi.mtrl");
		if (material)
		{
			//material->uv_offset.x += neu::g_time.deltaTime;
		}

		// Move camera around
		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin (y) wave
			//actor->m_transform.position.y = std::sin(neu::g_time.time);
		}

		scene->Update();
		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;

}

