#pragma once

#include "Nudo/Core.h"
#include "Nudo/Events/Event.h"

namespace Nudo
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }

		inline const std::string& GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
} 