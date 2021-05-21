#pragma once

#include "drpch.h"

#include "DrayIntern.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Dray
{
	class DRAY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> engineLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

#define DRAY_ENGINE_TRACE(x, ...)	Dray::Log::GetEngineLogger()->trace		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_ENGINE_INFO(x, ...)	Dray::Log::GetEngineLogger()->info		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_ENGINE_WARN(x, ...)	Dray::Log::GetEngineLogger()->warn		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_ENGINE_ERROR(x, ...)	Dray::Log::GetEngineLogger()->error		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_ENGINE_FATAL(x, ...)	Dray::Log::GetEngineLogger()->critical	((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
																					
#define DRAY_TRACE(x, ...)			Dray::Log::GetClientLogger()->trace		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_INFO(x, ...)			Dray::Log::GetClientLogger()->info		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_WARN(x, ...)			Dray::Log::GetClientLogger()->warn		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_ERROR(x, ...)			Dray::Log::GetClientLogger()->error		((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)
#define DRAY_FATAL(x, ...)			Dray::Log::GetClientLogger()->critical	((str8)"<{0}, {1}> " + (str8)x, __FILENAME__, __LINE__, __VA_ARGS__)

#ifndef DRAY_BUILD
	#define DRAY_ENGINE_TRACE(...)
	#define DRAY_ENGINE_INFO(...)
	#define DRAY_ENGINE_WARN(...)
	#define DRAY_ENGINE_ERROR(...)
	#define DRAY_ENGINE_FATAL(...)
#endif
