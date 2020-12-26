#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Breakout {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#define LOG_TRACE(...)	Breakout::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	Breakout::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	Breakout::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	Breakout::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)	Breakout::Log::GetLogger()->critical(__VA_ARGS__)