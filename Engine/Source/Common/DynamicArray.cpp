#include "Engine.h"
#include "DynamicArray.h"

namespace Array
{
	template <typename T>
	DynamicArray<T>::DynamicArray()
		: m_Data(new T[1])
		, m_Capacity(1)
		, m_Size(0)
	{ }
	template<typename T>
	DynamicArray<T>::~DynamicArray() noexcept
	{
		delete[] m_Data;
	}

	template<typename T>
	void DynamicArray<T>::Push(T value) noexcept
	{
		IncreaseCap();

		data[m_Size] = value;
		m_Size++;
	}
	template<typename T>
	void DynamicArray<T>::Pop() noexcept
	{
		if (m_Size > 0)
		{
			m_Size--;
		}
		else
		{
			Logger::PrintLog("Dynamic array size is less than 1.\n");
		}
	}

	template<typename T>
	void DynamicArray<T>::Remove(T value) noexcept
	{
		for (unsigned int i = 0; i < Length(); i++)
		{
			if (m_Data[i] != value)
			{
				continue;
			}

			if (i == m_Size)
			{
				m_Size--;
				break;
			}

			MoveArray(i);
			m_Size--;
			break;
		}
	}
	template<typename T>
	void DynamicArray<T>::RemoveLast(T value) noexcept
	{
		unsigned int tempIndex = 0;
		bool exists = false;

		for (unsigned int i = 0; i < Length(); i++)
		{
			if (m_Data[i] != value)
			{
				continue;
			}

			exists = true;
			if (tempIndex < i)
			{
				tempIndex = i;
			}
		}

		if (exists)
		{
			if (tempIndex == m_Size)
			{
				m_Size--;
				return;
			}

			MoveArray(tempIndex);
			m_Size--;
		}
	}
	template<typename T>
	void DynamicArray<T>::RemoveAt(unsigned int index) noexcept
	{
		if (index < m_Size)
		{
			MoveArray(index);
			m_Size--;
		}
		else if (index == m_Size)
		{
			m_Size--;
		}
		else
		{
			Logger::PrintLog("Index is out of range.\n");
		}
	}

	// TODO: Fix this method if for loop is working not properly
	template<typename T>
	void DynamicArray<T>::Insert(T value, unsigned int index) noexcept
	{
		if (index > m_Size)
		{
			Logger::PrintLog("Index is out of range.\n");
			return;
		}

		IncreaseCap();

		if (index == m_Size)
		{
			T* temp = m_Data[index];
			m_Data[index] = value;
			m_Size++;
			m_Data[m_Size] = temp;
		}
		else
		{
			T* temp = m_Data[index];
			m_Data[index] = value;
			m_Size++;

			for (unsigned int i = index + 1; i < m_Size; i++)
			{
				m_Data[i] = temp;
				temp = m_Data[i + 1];
			}
		}
	}

	template<typename T>
	void DynamicArray<T>::IncreaseCap() noexcept
	{
		if (m_Capacity == m_Size)
		{
			T* temp = new T[2 * m_Capacity];
			for (unsigned int i = 0; i < Length(); i++)
			{
				temp[i] = m_Data[i];
			}
			delete[] m_Data;
			m_Capacity *= 2;
			m_Data = temp;
			delete[] temp;
		}
	}
	template<typename T>
	void DynamicArray<T>::MoveArray(unsigned int index) noexcept
	{
		for (unsigned int i = index; i < m_Size; i++)
		{
			m_Data[i] = m_Data[i + 1];
		}
	}

	template<typename T>
	T DynamicArray<T>::Get(unsigned int index) const noexcept
	{
		if (index <= m_Size)
		{
			return m_Data[index];
		}
		else
		{
			Logger::PrintLog("Index is out of range.\n");
			return NULL;
		}
	}
	template<typename T>
	T DynamicArray<T>::GetFirst() const noexcept
	{
		return m_Data[0];
	}
	template<typename T>
	T DynamicArray<T>::GetLast() const noexcept
	{
		return m_Data[m_Size];
	}
	template<typename T>
	void DynamicArray<T>::Set(T value, unsigned int index) noexcept
	{
		if (index <= m_Size)
		{
			m_Data[index] = value;
		}
		else
		{
			Logger::PrintLog("Index is out of range.\n");
		}
	}

	template<typename T>
	T DynamicArray<T>::operator[](unsigned int index) const noexcept
	{
		if (index <= m_Size)
		{
			return m_Data[index];
		}
		else
		{
			Logger::PrintLog("Index is out of range.\n");
			return NULL;
		}
	}
}