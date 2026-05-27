#pragma once

#include <sstream>

#include "Event.h"

namespace Nudo
{
	class WindowsResizeEvent : public Event
	{
	public:
		WindowsResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) { }

		inline unsigned int GetWidth() { return m_Width; }
		inline unsigned int GetHeight() { return m_Height; }

		std::string ToString()
		{
			std::stringstream ss;
			ss << "WindowResizeEvent" << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};
}