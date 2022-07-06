#pragma once

#include "ResourceManager/Ref.h"
#include "ResourceManager/ResourcePool.h"

namespace ResourceManager
{
	template <class T, class IndexType>
	Ref<T, IndexType>::Ref(ResourcePool* pool, IndexT index)
	    : m_Pool(pool), m_Index(index)
	{
		if (m_Pool)
			m_Pool->incRef(m_Index);
	}

	template <class T, class IndexType>
	Ref<T, IndexType>::~Ref()
	{
		if (m_Pool)
			m_Pool->decRef(m_Index);
	}

	template <class T, class IndexType>
	bool Ref<T, IndexType>::valid() const
	{
		return m_Pool;
	}

	template <class T, class IndexType>
	Ref<T, IndexType>::WeakRef Ref<T, IndexType>::getWeak() const
	{
		return WeakRef { m_Pool, m_Index };
	}

	template <class T, class IndexType>
	T* Ref<T, IndexType>::get()
	{
		return m_Pool->getResource(m_Index);
	}

	template <class T, class IndexType>
	const T* Ref<T, IndexType>::get() const
	{
		return m_Pool->getResource(m_Index);
	}
} // namespace ResourceManager