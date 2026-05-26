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
		"vendor/spdlog/include"
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
		"vendor/spdlog/include"
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
