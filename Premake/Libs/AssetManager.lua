libs              = libs              or {}
libs.AssetManager = libs.AssetManager or {
	name     = "",
	location = ""
}

local AssetManager = libs.AssetManager

function AssetManager:setup()
	self.name     = common:projectName()
	self.location = common:projectLocation()

	kind("StaticLib")
	common:outDirs(true)

	includedirs({ self.location .. "/Inc/" })

	files({
		self.location .. "/Inc/**",
		self.location .. "/Src/**"
	})
	removefiles({ "*.DS_Store" })
end

function AssetManager:setupDep()
	links({ self.name })
	externalincludedirs({ self.location .. "/Inc/" })
end