#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging - the logging system im using -PC
// This example was Constructed from SpdLog, examples and Yan Chernikov tutorials


namespace Engine {
	
	std::shared_ptr<spdlog::logger> Logger::s_SystemLogger;
	std::shared_ptr<spdlog::logger> Logger::s_AppLogger;

	void Logger::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$"); // this sets the pattern of the logger 
	// in the above brackets it states in the following order - PC
	//  color, name of logger, timestamp, message -PC

		s_SystemLogger = spdlog::stdout_color_mt("ENGINE");
		s_SystemLogger->set_level(spdlog::level::trace);
		s_AppLogger = spdlog::stdout_color_mt("APP");
		s_AppLogger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Logger::GetAppLogger() { return s_AppLogger; }
	std::shared_ptr<spdlog::logger>& Logger::GetSystemLogger() { return s_SystemLogger; }
}