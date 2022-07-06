#pragma once

#include <cstdint>

namespace ResourceManager
{
	template <class T, class IndexType>
	struct ResourcePool;

	template <class T, class IndexType>
	struct Ref;

	template <class T, class IndexType = std::uint32_t>
	struct WeakRef
	{
	public:
		using Ref          = Ref<T, IndexType>;
		using ResourcePool = ResourcePool<T, IndexType>;
		using IndexT       = IndexType;

	public:
		WeakRef(ResourcePool* pool, IndexT index);
		~WeakRef();

		inline bool valid() const;
		inline Ref  promote() const;

		ResourcePool*       pool() { return m_Pool; }
		const ResourcePool* pool() const { return m_Pool; }
		IndexT              index() const { return m_Index; }

		operator bool() const { return valid(); }

	private:
		ResourcePool* m_Pool;
		IndexT        m_Index;
	};
} // namespace ResourceManager