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
IncludeDir["imgui"] = "disarRay/deps/imgui"
IncludeDir["glm"] = "disarRay/deps/glm"
IncludeDir["spdlog"] = "disarRay/deps/spdlog/include"


group "Dependencies"
	include "disarRay/deps/GLFW"
	include "disarRay/deps/Glad"
	include "disarRay/deps/imgui"
group ""


project "disarRay"
	location "disarRay"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/disarRay")
	objdir ("bin-int/" .. outputdir .. "/disarRay")

	pchheader "drpch.h"
	pchsource "disarRay/src/drpch.cpp"

	files
	{
		"disarRay/src/**.h",
		"disarRay/src/**.cpp",
		"disarRay/deps/glm/glm/**.hpp",
		"disarRay/deps/glm/glm/**.inl"
	}

	includedirs
	{
		"disarRay/src/disarRay",
		"disarRay/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"DRAY_PLAT_WIN",
			"DRAY_BUILD",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "DRAY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DRAY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Deploy"
		defines "DRAY_DEPLOY"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/Sandbox")
	objdir ("bin-int/" .. outputdir .. "/Sandbox")

	files
	{
		"Sandbox/src/**.h",
		"Sandbox/src/**.cpp"
	}

	includedirs
	{
		"disarRay/src/disarRay",
		"disarRay/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"disarRay",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"DRAY_PLAT_WIN"
		}

	filter "configurations:Debug"
		defines "DRAY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DRAY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Deploy"
		defines "DRAY_DEPLOY"
		runtime "Release"
		optimize "On"
