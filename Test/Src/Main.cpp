#include "Utils/Core.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

#include <ResourceManager/ResourceManager.h>

template <class T>
void printRegions(const ResourceManager::ResourcePool<T>& resources, std::uint32_t i)
{
	std::ostringstream str;
	str << i << ' ';
	if (resources.regions().size() > 1)
	{
		str << "Regions:\n";
		for (auto& region : resources.regions())
			str << '\t' << region.m_Start << " -> " << region.m_End << ": " << region.m_Offset << '\n';
	}
	else if (!resources.regions().empty())
	{
		auto& region = resources.regions()[0];
		str << "Regions: " << region.m_Start << " -> " << region.m_End << ": " << region.m_Offset << '\n';
	}
	std::cout << str.str();
}

int main(int argc, char** argv)
{
	ResourceManager::ResourcePool<std::uint32_t> resources;

	for (std::uint32_t i = 0; i < 32; ++i)
	{
		resources.emplaceBackPersistent(i);
		printRegions(resources, i);
	}

	std::vector<decltype(resources)::IndexT> indices;
	indices.reserve(16);
	std::mt19937 gen { std::random_device {}() };
	for (std::uint32_t i = 0; i < 16; ++i)
	{
		using IndexT = decltype(resources)::IndexT;
		IndexT index = gen() & 31;
		if (std::find(indices.begin(), indices.end(), index) != indices.end())
			index = gen() & 31;
		indices.emplace_back(index);
	}

	std::cout << "Erasing:\n";

	for (auto i : indices)
	{
		resources.erase(i);
		printRegions(resources, i);
	}

	std::cout << "Adding:\n";

	for (auto i : indices)
	{
		resources.emplaceBackPersistent(i);
		printRegions(resources, i);
	}
}