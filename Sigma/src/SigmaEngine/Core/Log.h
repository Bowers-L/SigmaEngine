#pragma once

#include <memory>

#include "Core.h"
#include <spdlog/spdlog.h>

#define SG_CORE_TRACE(...) ::SigmaEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SG_CORE_INFO(...) ::SigmaEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SG_CORE_WARN(...) ::SigmaEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SG_CORE_ERROR(...) ::SigmaEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SG_CORE_FATAL(...) ::Sigma::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define SG_TRACE(...) ::SigmaEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SG_INFO(...) ::SigmaEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define SG_WARN(...) ::SigmaEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SG_ERROR(...) ::SigmaEngine::Log::GetClientLogger()->error(__VA_ARGS__)
//#define SIGMA_FATAL(...) ::Sigma::Log::GetClientLogger()->fatal(__VA_ARGS__)

#ifdef SG_ENABLE_ASSERTS

#define SG_ASSERT(x, ...) {\
	if (!(x)) {\
		SG_ERROR("Assertion Failed: {0}", __VA_ARGS__);\
		__debugbreak();\
	}\
}

#define SG_CORE_ASSERT(x, ...) {\
	if (!(x)) {\
		SG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);\
		__debugbreak();\
	}\
}

#else

#define SG_ASSERT(x, ...)
#define SG_CORE_ASSERT(x, ...)

#endif

namespace SigmaEngine {
	class SIGMA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr < spdlog::logger> s_ClientLogger;
	};
}


