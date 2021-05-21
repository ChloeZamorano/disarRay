#pragma once

#ifdef DRAY_PLAT_WIN
	extern Dray::DrayApp* Dray::MakeDrayApp();

	i32 main(i32 argc, str8* argv)
	{
		Dray::Log::Init();
		DRAY_ENGINE_INFO("Engine and client loggers initialized.");

		auto app = Dray::MakeDrayApp();
		app->Run();
		delete app;

		return EXIT_SUCCESS;
	}
#endif
