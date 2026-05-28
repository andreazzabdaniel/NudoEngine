#include "ndpch.h"
#include <Nudo.h>

class SandBox : public Nudo::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};


Nudo::Application* Nudo::CreateApplication()
{
	return new SandBox();
}