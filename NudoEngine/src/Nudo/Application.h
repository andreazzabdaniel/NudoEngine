#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Nudo/Log.h"

namespace Nudo
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
