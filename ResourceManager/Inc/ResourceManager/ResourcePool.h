#pragma once

#include "Ref.h"
#include "Resource.h"
#include "Utils/Region.h"
#include "WeakRef.h"

#include <cstdint>

#include <type_traits>
#include <vector>

namespace ResourceManager
{
	template <class T, class IndexType = std::uint32_t>
	struct ResourcePool
	{
	public:
		using Ref          = Ref<T, IndexType>;
		using WeakRef      = WeakRef<T, IndexType>;
		using Region       = Utils::Region<IndexType>;
		using Resource     = Resource<T>;
		using RegionList   = std::vector<Region>;
		using ResourceList = std::vector<Resource>;
		using IndexT       = IndexType;

	public:
		ResourcePool() : m_CurrentIndex(0U) {}

		void incRef(IndexT index);
		void decRef(IndexT index);
		void incWRef(IndexT index);
		void decWRef(IndexT index);

		bool valid(IndexT index) const;

		template <class... Args>
		Ref emplaceBack(Args&&... args) requires std::is_constructible_v<T, Args...>;
		template <class... Args>
		Ref  emplaceBackPersistent(Args&&... args) requires std::is_constructible_v<T, Args...>;
		void erase(IndexT index);

		T*       getResource(IndexT index);
		const T* getResource(IndexT index) const;

		auto& regions() const { return m_Regions; }
		auto& resources() const { return m_Resources; }
		auto  currentIndex() const { return m_CurrentIndex; }

	protected:
		void nextOptimalIndex();

		Resource*       getResourcePtr(IndexT index);
		const Resource* getResourcePtr(IndexT index) const;

		RegionList::iterator       getLowerRegion(IndexT index);
		RegionList::const_iterator getLowerRegion(IndexT index) const;
		RegionList::iterator       getRegion(IndexT index);
		RegionList::const_iterator getRegion(IndexT index) const;

	private:
		RegionList   m_Regions;
		ResourceList m_Resources;

		IndexT m_CurrentIndex;
	};
} // namespace ResourceManager