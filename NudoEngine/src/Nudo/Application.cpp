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
		while (m_IsRuning)
		{
			m_Window->OnUpdate();
		}
	}
}