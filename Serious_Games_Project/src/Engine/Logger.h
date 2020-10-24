#pragma once

#include <memory>

#include "System.h"
#include "spdlog/spdlog.h"

namespace Engine {

	class ENGINE_API Logger
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