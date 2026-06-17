#include "ndpch.h"
#include <Nudo.h>

class ExampleLayer : public Nudo::Layer
{
public:
	ExampleLayer()
		: Layer("Exemplo") { }

	void OnUpdate() override
	{
	}

	void OnEvent(Nudo::Event& e) override
	{
		ND_TRACE("LayerEvent: {0}", e);
	}
};


class SandBox : public Nudo::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};


Nudo::Application* Nudo::CreateApplication()
{
	return new SandBox();
}