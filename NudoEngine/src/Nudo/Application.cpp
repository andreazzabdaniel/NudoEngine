#include "ndpch.h"
#include "Application.h"

namespace Nudo
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 750);
		ND_CORE_INFO(e);

		while (m_IsRuning)
		{
			m_Window->OnUpdate();
		}
	}
}