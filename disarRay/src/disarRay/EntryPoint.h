#pragma once

#ifdef DRAY_PLAT_WIN
	extern Dray::DrayApp* Dray::MakeDrayApp();

	int main(int argc, char** argv)
	{
		auto app = Dray::MakeDrayApp();
		app->Run();
		delete app;
	}
#endif
