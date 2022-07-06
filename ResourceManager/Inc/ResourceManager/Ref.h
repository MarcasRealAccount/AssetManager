#pragma once

#include <cstdint>

namespace ResourceManager
{
	template <class T, class IndexType>
	struct ResourcePool;

	template <class T, class IndexType>
	struct WeakRef;

	template <class T, class IndexType = std::uint32_t>
	struct Ref
	{
	public:
		using WeakRef      = WeakRef<T, IndexType>;
		using ResourcePool = ResourcePool<T, IndexType>;
		using IndexT       = IndexType;

	public:
		Ref(ResourcePool* pool, IndexT index);
		~Ref();

		inline bool    valid() const;
		inline WeakRef getWeak() const;

		inline T*       get();
		inline const T* get() const;

		ResourcePool*       pool() { return m_Pool; }
		const ResourcePool* pool() const { return m_Pool; }
		IndexT              index() const { return m_Index; }

		         operator T&() { return *get(); }
		         operator const T&() const { return *get(); }
		T*       operator->() { return get(); }
		const T* operator->() const { return get(); }
		T&       operator*() { return *get(); }
		const T& operator*() const { return *get(); }

	private:
		ResourcePool* m_Pool;
		IndexT        m_Index;
	};
} // namespace ResourceManager