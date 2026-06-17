#pragma once

#include "Nudo/Core.h"

#include "Window.h"
#include "Nudo/Renderer/GraphicsContext.h"
#include "Nudo/LayerStack.h"
#include "Nudo/Events/Event.h"
#include "Nudo/Events/ApplicationEvent.h"


namespace Nudo
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);	

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool m_IsRuning = true;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<GraphicsContext> m_GraphicContext;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}
