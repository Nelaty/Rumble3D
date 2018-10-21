#include <cassert>

namespace r3
{
	template <class Element_Type, class Container_Type>
	FixedSizeContainer<Element_Type, Container_Type>::FixedSizeContainer(const int size)
	{
		init(size);
	}

	template <class Element_Type, class Container_Type>
	FixedSizeContainer<Element_Type, Container_Type>::~FixedSizeContainer()
		= default;

	template <class Element_Type, class Container_Type>
	void FixedSizeContainer<Element_Type, Container_Type>::init(const int size)
	{
		assert(size > 0);

		m_data.resize(size);
		m_size = size;

		reset();
	}

	template <class Element_Type, class Container_Type>
	void FixedSizeContainer<Element_Type, Container_Type>::reset()
	{
		m_entriesUsed = 0;
	}

	template <class Element_Type, class Container_Type>
	bool FixedSizeContainer<Element_Type, Container_Type>::isFull() const
	{
		return m_size == m_entriesUsed;
	}

	template <class Element_Type, class Container_Type>
	int FixedSizeContainer<Element_Type, Container_Type>::getEntriesLeft() const
	{
		return m_size - m_entriesUsed;
	}

	template <class Element_Type, class Container_Type>
	int FixedSizeContainer<Element_Type, Container_Type>::getEntriesUsed() const
	{
		return m_entriesUsed;
	}

	template <class Element_Type, class Container_Type>
	int FixedSizeContainer<Element_Type, Container_Type>::getSize() const
	{
		return m_size;
	}

	template <class Element_Type, class Container_Type>
	Element_Type* FixedSizeContainer<Element_Type, Container_Type>::getAvailableEntry()
	{
		if (isFull()) return nullptr;

		const auto result = &m_data[m_entriesUsed];
		++m_entriesUsed;
		return result;
	}

	template <class Element_Type, class Container_Type>
	Container_Type& FixedSizeContainer<Element_Type, Container_Type>::getData()
	{
		return m_data;
	}

	template <class Element_Type, class Container_Type>
	const Container_Type& FixedSizeContainer<Element_Type, Container_Type>::getData() const
	{
		return m_data;
	}
}