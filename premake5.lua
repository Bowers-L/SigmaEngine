workspace "Sigma"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sigma"
	location "Sigma"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/glm-master",
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
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

	filter "configurations:Release"
		defines "SIGMA_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "SIGMA_DIST"
		symbols "On"

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

	filter "configurations:Release"
		defines "SIGMA_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "SIGMA_DIST"
		symbols "On"