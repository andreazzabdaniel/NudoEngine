#pragma once


extern Nudo::Application* Nudo::CreateApplication();

int main()
{
	Nudo::Log::Init();
	ND_CORE_ERROR("Initialize Nudo engine!!");
	ND_INFO("Teste info app side");

	auto app = Nudo::CreateApplication();
	app->Run();
	delete app;
}