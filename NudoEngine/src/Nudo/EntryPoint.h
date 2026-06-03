#pragma once


extern Nudo::Application* Nudo::CreateApplication();

int main()
{
	Nudo::Log::Init();
	ND_CORE_INFO("Initialize Nudo engine!!");

	auto app = Nudo::CreateApplication();
	app->Run();
	delete app;
}