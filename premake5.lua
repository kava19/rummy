
workspace "Rummy_workspace"
   configurations { "Default" }

project "Rummy"
    kind "ConsoleApp"
    language "C++"
	links { "pthread", "X11" }
	buildoptions { "-std=c++17" }
    files{
        "src/client/*.cpp"

    }
	filter "configurations:Default"
		defines { "DEBUG" }
		flags { "Symbols" }
		links {"SCL", "raylib"}

project "test_server"
    kind "ConsoleApp"
    language "C++"
	links { "pthread", "X11" }
	buildoptions { "-std=c++17" }
    files{
        "src/scl/test_server.cpp"

    }
	filter "configurations:Default"
		defines { "DEBUG" }
		flags { "Symbols" }
		links {"SCL"}

project "SCL"
    kind "StaticLib"
    language "C++"
	links { "pthread", "X11" }
	buildoptions { "-std=c++17" }
    files{
        "src/scl/scl.h",
        "src/scl/scl_server.cpp"

    }
