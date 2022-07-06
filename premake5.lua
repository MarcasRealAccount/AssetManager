require("Premake/Common")

require("Premake/Libs/AssetManager")
require("Premake/Libs/ResourceManager")

workspace("AssetManager")
	common:setConfigsAndPlatforms()
	common:addCoreDefines()

	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("Off")
	flags("MultiProcessorCompile")

	startproject("Test")

	group("Dependencies")
	group("Libs")
	project("AssetManager")
		location("AssetManager/")
		warnings("Extra")
		libs.AssetManager:setup()
		
		common:addActions()

	project("ResourceManager")
		location("ResourceManager/")
		warnings("Extra")
		libs.ResourceManager:setup()
		
		common:addActions()

	group("Apps")
	project("Test")
		location("Test/")
		warnings("Extra")

		common:outDirs()
		common:debugDir()

		kind("ConsoleApp")

		includedirs({ "%{prj.location}/Src/" })
		files({ "%{prj.location}/Src/**" })
		removefiles({ "*.DS_Store" })

		libs.AssetManager:setupDep()
		libs.ResourceManager:setupDep()

		common:addActions()
