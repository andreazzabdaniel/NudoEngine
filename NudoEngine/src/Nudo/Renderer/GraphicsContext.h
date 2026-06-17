#pragma once

namespace Nudo
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;


		static GraphicsContext* Create(void* nativeWindow);
	};
}