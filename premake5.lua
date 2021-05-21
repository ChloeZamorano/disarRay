workspace "disarRay"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Deploy"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["GLFW"] = "disarRay/deps/GLFW/include"
IncludeDir["Glad"] = "disarRay/deps/Glad/include"
IncludeDir["ImGui"] = "disarRay/deps/imgui"


group "Dependencies"
	include "disarRay/deps/GLFW"
	include "disarRay/deps/Glad"
	include "disarRay/deps/imgui"
group ""


project "disarRay"
	location "disarRay"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/disarRay")
	objdir ("bin-obj/" .. outputdir .. "/disarRay")

	pchheader "drpch.h"
	pchsource "disarRay/src/drpch.cpp"

	files
	{
		"disarRay/src/**.h",
		"disarRay/src/**.cpp"
	}

	includedirs
	{
		"disarRay/deps/spdlog/include",
		"disarRay/src/disarRay",
		"disarRay/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines "GLFW_INCLUDE_NONE"

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DRAY_PLAT_WIN",
			"DRAY_BUILD"
		}

	filter "configurations:Debug"
		defines "DRAY_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "DRAY_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Deploy"
		defines "DRAY_DEPLOY"
		optimize "On"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/Sandbox")
	objdir ("bin-obj/" .. outputdir .. "/Sandbox")

	files
	{
		"Sandbox/src/**.h",
		"Sandbox/src/**.cpp"
	}

	includedirs
	{
		"disarRay/deps/spdlog/include",
		"disarRay/src/disarRay",
		"disarRay/src"
	}

	links
	{
		"disarRay"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DRAY_PLAT_WIN"
		}

		postbuildcommands
		{
			("copy ..\\bin\\" .. outputdir .. "\\disarRay\\disarRay.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\")
		}

	filter "configurations:Debug"
		defines "DRAY_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "DRAY_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Deploy"
		defines "DRAY_DEPLOY"
		optimize "On"
		runtime "Release"
