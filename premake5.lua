workspace "Sigma"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sigma/vendor/GLFW_L/include"

include "Sigma/vendor/GLFW_L"

project "Sigma"
	location "Sigma"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glad/src/glad.c",
		"%{prj.name}/vendor/**.lib",
		"%{prj.name}/vendor/**.h",
	}

	includedirs {
		"%{IncludeDir.GLFW}",
		"%{prj.name}/vendor/glm-master",
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
	}

	links {
		"GLFW",
		"opengl32",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"SIGMA_PLATFORM_WINDOWS",
			"SIGMA_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SIGMA_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "SIGMA_RELEASE"
		symbols "On"
		rutnime "Release"

	filter "configurations:Dist"
		defines "SIGMA_DIST"
		symbols "On"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Sigma/vendor/spdlog/include",
		"Sigma/src"
	}

	links {
		"Sigma"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"SIGMA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SIGMA_DEBUG"
		symbols "On"
		staticruntime "Debug"

	filter "configurations:Release"
		defines "SIGMA_RELEASE"
		symbols "On"
		staticruntime "Release"

	filter "configurations:Dist"
		defines "SIGMA_DIST"
		symbols "On"
		staticruntime "Release"