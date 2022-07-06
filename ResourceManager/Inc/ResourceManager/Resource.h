#pragma once

#include <type_traits>
#include <utility>

namespace ResourceManager
{
	template <class T>
	struct Resource
	{
	public:
		template <class... Args>
		Resource(Args&&... args) requires std::is_constructible_v<T, Args...>;

		inline bool isPersistent() const;
		inline void setPersistent();

		inline void incRef();
		inline bool decRef();
		inline void incWRef();
		inline bool decWRef();
		inline void destroy();

		T*       getValue() { return &m_Value; }
		const T* getValue() const { return &m_Value; }

		auto getRefCount() const { return m_RefCount; }
		auto getWRefCount() const { return m_WRefCount; }

		bool valid() const { return getRefCount() > 0; }

		         operator T&() { return m_Value; }
		         operator T&() const { return m_Value; }
		T*       operator->() { return &m_Value; }
		const T* operator->() const { return &m_Value; }
		T&       operator*() { return m_Value; }
		const T& operator*() const { return m_Value; }

	private:
		T             m_Value;
		std::uint16_t m_RefCount;
		std::uint16_t m_WRefCount;
	};
} // namespace ResourceManager

//----------------
// Implementation
//----------------

namespace ResourceManager
{
	template <class T>
	template <class... Args>
	Resource<T>::Resource(Args&&... args) requires std::is_constructible_v<T, Args...>
	    : m_Value(std::forward<Args>(args)...), m_RefCount(0), m_WRefCount(1)
	{
	}

	template <class T>
	bool Resource<T>::isPersistent() const
	{
		return m_RefCount == static_cast<std::uint16_t>(~0U) && m_WRefCount == static_cast<std::uint16_t>(~0U);
	}

	template <class T>
	void Resource<T>::setPersistent()
	{
		m_RefCount  = ~0U;
		m_WRefCount = ~0U;
	}

	template <class T>
	void Resource<T>::incRef()
	{
		if (!isPersistent())
			++m_RefCount;
	}

	template <class T>
	bool Resource<T>::decRef()
	{
		if (isPersistent())
			return false;

		if (--m_RefCount == 0)
		{
			destroy();
			return decWRef();
		}
		return false;
	}

	template <class T>
	void Resource<T>::incWRef()
	{
		if (!isPersistent())
			++m_WRefCount;
	}

	template <class T>
	bool Resource<T>::decWRef()
	{
		if (!isPersistent())
			return --m_WRefCount == 0;
		return false;
	}

	template <class T>
	void Resource<T>::destroy()
	{
		m_Value.~T();
	}
} // namespace ResourceManager