#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Engine {

	class Logger
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetSystemLogger();
		static std::shared_ptr<spdlog::logger>& GetAppLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_SystemLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}