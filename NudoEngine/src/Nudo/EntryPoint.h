#pragma once

extern Nudo::Application* Nudo::CreateApplication();

int main()
{
	auto app = Nudo::CreateApplication();
	app->Run();
	delete app;
}