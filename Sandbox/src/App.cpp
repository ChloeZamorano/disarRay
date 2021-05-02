#include <Dray.h>

class Sandbox : public Dray::DrayApp
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Dray::DrayApp* Dray::MakeDrayApp()
{
	return new Sandbox();
}
