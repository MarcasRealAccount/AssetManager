libs                 = libs                 or {}
libs.ResourceManager = libs.ResourceManager or {
	name     = "",
	location = ""
}

local ResourceManager = libs.ResourceManager

function ResourceManager:setup()
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

function ResourceManager:setupDep()
	links({ self.name })
	externalincludedirs({ self.location .. "/Inc/" })
end