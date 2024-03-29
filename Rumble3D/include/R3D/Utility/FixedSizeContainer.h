#pragma once
#include "R3D/Common/Common.h"

#include <vector>

namespace r3
{
	/**
	 * \brief Template class for a container, which can be resized, with
	 * random access (dependent on Container_Type) and can be filled
	 * similar to a stack. Its size in memory will stay the same at all 
	 * times. Elements can not be erased from it.
	 * \tparam Element_Type Type of the elements, saved in this container.
	 * \tparam Container_Type Container type used for storing elements. Needs
	 * to have a "void resize(unsigned)" function and must be able to store
	 * elements of type Element_Type
	 */
	template<class Element_Type, class Container_Type = std::vector<Element_Type>>
	class R3D_EXPORT FixedSizeContainer // todo: define iterator
	{
	public:
		/**
		 * \brief FixedSizeContainer constructor
		 */
		explicit FixedSizeContainer(size_t size = 0);
		~FixedSizeContainer() = default;

		/**
		 * \brief Initialize the container size. This will reset the
		 * container.
		 * \param size The new size of the container.
		 */
		void init(size_t size);

		/**
		 * \brief Reset the number of used entries.
		 */
		void reset();

		/**
		 * \brief Check if no entries are in use.
		 * \return True if no entries are in use, false otherwise.
		 */
		bool isEmpty() const;
		/**
		 * \brief Check if the maximal number of usable entries has been
		 * reached.
		 * \return True if the container is full, false otherwise.
		 */
		bool isFull() const;

		/**
		 * \brief Get the number of elements, which can still fit in the
		 * container
		 * \return The count of free entries.
		 */
        size_t getEntriesLeft() const;
		/**
		 * \brief Get the number of elements, which are already stored in
		 * the container.
		 * \return The number of used entries.
		 */
        size_t getEntriesUsed() const;
		/**
		 * \brief Get the maximal number of elements, which can fit in
		 * this container.
		 * \return The maximal number of elements.
		 */
        size_t getSize() const;

		/** \brief Get the last element. */
		Element_Type* back();
	
		/** \brief Get the first element. */
		Element_Type* front();

		/**
		 * \brief Get the next available element. This automatically use
		 * the entry.
		 * \return A free element if there are free entries left, nullptr
		 * otherwise.
		 */
		Element_Type* getAvailableEntry();
		/**
		 * \brief Get the internal container.
		 * \return All data. Only the first m_entriesUsed entries are valid!
		 */
		Container_Type& getData();
		/**
		* \brief Get the internal container.
		* \return All data. Only the first m_entriesUsed entries are valid!
		*/
		const Container_Type& getData() const;

	private:
        size_t m_size{};
        size_t m_entriesUsed{};

		Container_Type m_data;
	};
}

#include "R3D/Utility/FixedSizeContainer.inl"