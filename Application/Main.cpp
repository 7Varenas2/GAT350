#include "Engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	// DO NOT REMOVE
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");
	 
	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initialized...");

	// Load scene
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/basic_lit.scn");


	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;
		
		neu::g_renderer.BeginFrame();
		
		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation.y += 90.0f * neu::g_time.deltaTime;
		}
		scene->Update();
		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;

}

