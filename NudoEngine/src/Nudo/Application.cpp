#include "ndpch.h"
#include "Application.h"

namespace Nudo
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 750);
		ND_CORE_INFO(e);

		while (true)
		{

		}
	}
}