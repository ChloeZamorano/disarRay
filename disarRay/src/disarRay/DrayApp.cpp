#include "DrayApp.h"

namespace Dray
{
	DrayApp::DrayApp()
	{

	}

	DrayApp::~DrayApp()
	{

	}

	const char* coomer[] =
	{
		"Hello, Gordon!",
		"I've been outside Black Mesa, Dr. Freeman. There's nothing there. But YOU. I know there's a world in your dreams. AND I NEED TO GO THERE!!!",
		"Gordon? If you woke up one day, and realized everything around you was a lie...was FAKE...What would you do?",
		"Look Gordon! Ropes! We can use these to help with large pits!",
		"HELP ME GORDON!",
		"Gordon...Every time you go to sleep I can feel my body TORN apart...ATOM by ATOM...It's agonizing Gordon...I've SEEN outside Black Mesa, Gordon...There's NOTHING...But I know YOU. There's a world outside here, Gordon. AND I NEED YOU TO TAKE ME THERE..."
	};

	void DrayApp::Run()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 5);

		while (true)
		{
			printf(coomer[distr(gen)]);
		}
	}
}
