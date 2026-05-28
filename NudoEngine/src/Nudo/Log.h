#pragma once

#include "spdlog/spdlog.h"


namespace Nudo
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// Core Log Messages
#define ND_CORE_TRACE(...)	::Nudo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ND_CORE_INFO(...)	::Nudo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ND_CORE_WARN(...)	::Nudo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ND_CORE_ERROR(...)	::Nudo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ND_CORE_FATAL(...)	::Nudo::Log::GetCoreLogger()->fatal(__VA_ARGS__)



// Client Log Messages
#define ND_TRACE(...)	::Nudo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ND_INFO(...)	::Nudo::Log::GetClientLogger()->info(__VA_ARGS__)
#define ND_WARN(...)	::Nudo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ND_ERROR(...)	::Nudo::Log::GetClientLogger()->error(__VA_ARGS__)
#define ND_FATAL(...)	::Nudo::Log::GetClientLogger()->fatal(__VA_ARGS__)
