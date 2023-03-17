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
IncludeDir["ImGui"] = "Sigma/vendor/imgui_L"
IncludeDir["SpdLog"] = "Sigma/vendor/spdlog/include"
IncludeDir["STBI"] = "Sigma/vendor/stb"

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
		"%{prj.name}/vendor/glad/**.c",
		"%{IncludeDir.ImGui}/*.cpp",
		"%{IncludeDir.STBI}/*.cpp",

		--ImGui Backends
		"%{IncludeDir.ImGui}/backends/imgui_impl_opengl3.h",
		"%{IncludeDir.ImGui}/backends/imgui_impl_opengl3.cpp",
		"%{IncludeDir.ImGui}/backends/imgui_impl_glfw.h",
		"%{IncludeDir.ImGui}/backends/imgui_impl_glfw.cpp",

		"%{prj.name}/vendor/**.lib",
		--"%{prj.name}/vendor/**.h",
		--"%{prj.name}/vendor/**.hpp"
	}

	includedirs {
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.SpdLog}",
		"%{IncludeDir.STBI}",
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
			--We're using a static library for the engine now, so don't need this anymore.
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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.SpdLog}",
		"%{IncludeDir.STBI}",
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