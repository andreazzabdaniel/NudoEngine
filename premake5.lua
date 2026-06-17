workspace "NudoEngine"
	architecture "x64"
	systemversion "latest"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"]   = "vendor/GLFW/include"
IncludeDir["Vulkan"] = "%{os.getenv('VULKAN_SDK')}/Include"
IncludeDir["VMA"]    = "vendor/VMA/include"
IncludeDir["GLM"]    = "vendor/glm-1.0.3"

LibDir = {}
LibDir["Vulkan"] = "%{os.getenv('VULKAN_SDK')}/Lib"

include "vendor/GLFW"

project "NudoEngine"
	location "NudoEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.VMA}",
		"%{IncludeDir.GLM}"
	}

	libdirs
	{
		"%{LibDir.Vulkan}"
	}

	links
	{
		"GLFW",
		"vulkan-1"
	}

	pchheader "ndpch.h"
	pchsource "NudoEngine/src/ndpch.cpp"

	buildoptions { "/utf-8" }

	filter "configurations:Debug"
		defines "NUDO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NUDO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NUDO_DIST"
		runtime "Release"
		optimize "on"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NudoEngine/src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.GLM}"
	}

	links
	{
		"NudoEngine"
	}

	buildoptions { "/utf-8" }

	filter "configurations:Debug"
		defines "NUDO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NUDO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NUDO_DIST"
		runtime "Release"
		optimize "on"
