#pragma once

#ifdef SIGMA_PLATFORM_WINDOWS
	#ifdef SIGMA_BUILD_DLL
		#define SIGMA_API __declspec(dllexport)
	#else
		#define SIGMA_API __declspec(dllimport)
	#endif
#else
	#error Sigma only supports Windows.
#endif