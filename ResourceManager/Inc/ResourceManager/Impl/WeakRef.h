#pragma once

#include "ResourceManager/ResourcePool.h"
#include "ResourceManager/WeakRef.h"

namespace ResourceManager
{
	template <class T, class IndexType>
	WeakRef<T, IndexType>::WeakRef(ResourcePool* pool, IndexT index)
	    : m_Pool(pool), m_Index(index)
	{
		if (m_Pool)
			m_Pool->incWRef(m_Index);
	}

	template <class T, class IndexType>
	WeakRef<T, IndexType>::~WeakRef()
	{
		if (m_Pool)
			m_Pool->decWRef(m_Index);
	}

	template <class T, class IndexType>
	WeakRef<T, IndexType>::Ref WeakRef<T, IndexType>::promote() const
	{
		return valid() ? Ref { m_Pool, m_Index } : Ref { nullptr, IndexT { 0 } };
	}

	template <class T, class IndexType>
	bool WeakRef<T, IndexType>::valid() const
	{
		return m_Pool->valid(m_Index);
	}
} // namespace ResourceManager