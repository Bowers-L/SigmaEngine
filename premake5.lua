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
IncludeDir["Glad"] = "Sigma/vendor/glad/include"
IncludeDir["Glm"] = "Sigma/vendor/glm-master"
IncludeDir["SpdLog"] = "Sigma/vendor/spdlog/include"

include "Sigma/vendor/GLFW_L"

project "Sigma"
	location "Sigma"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Assets/**.shader",
		"%{prj.name}/vendor/glad/src/glad.c",
		"%{prj.name}/vendor/**.lib",
		"%{prj.name}/vendor/**.h",
	}

	includedirs {
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Glm}",
		"%{IncludeDir.SpdLog}",
		"%{prj.name}/src",
	}

	links {
		"GLFW",
		"opengl32",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"SIGMA_PLATFORM_WINDOWS",
			"SIGMA_BUILD_DLL",
		}

		postbuildcommands {
			--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines {
			"SIGMA_DEBUG",
			"SG_ENABLE_ASSERTS"
		}
		symbols "Off"
		runtime "Debug"

	filter "configurations:Release"
		defines "SIGMA_RELEASE"
		symbols "Off"
		runtime "Release"

	filter "configurations:Dist"
		defines "SIGMA_DIST"
		symbols "Off"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Sigma/Assets/**.shader",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Assets/**.shader"
	}

	includedirs {
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Glm}",
		"%{IncludeDir.SpdLog}",
		"Sigma/src"
	}

	links {
		"Sigma"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"SIGMA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SIGMA_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "SIGMA_RELEASE"
		symbols "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "SIGMA_DIST"
		symbols "On"
		runtime "Release"