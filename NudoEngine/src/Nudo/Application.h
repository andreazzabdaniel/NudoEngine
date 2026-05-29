#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Window.h"

#include "Nudo/Log.h"

namespace Nudo
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;

		// Temp
		bool m_IsRuning;
	};

	Application* CreateApplication();
}
