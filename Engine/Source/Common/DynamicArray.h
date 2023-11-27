#pragma once

namespace Array
{ 
	template <typename T>
	class ENGINE_API DynamicArray
	{
		/* Constructor */
	public:
		DynamicArray()
			: m_Data(new T[1])
			, m_Capacity(1)
			, m_Size(0)
		{}

		/* Public methods */
	public:
		void Push(T value) noexcept
		{
			IncreaseCap();

			m_Data[m_Size] = value;
			m_Size += 1;
		}
		void Pop() noexcept
		{
			if (m_Size > 0)
			{
				m_Size--;
			}
			else
			{

			}
		}

		void Remove(T value) noexcept
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
		void RemoveLast(T value) noexcept
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
		void RemoveAt(unsigned int index) noexcept
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

			}
		}

		// TODO: Fix this method if for loop is working not properly
		void Insert(T value, unsigned int index) noexcept
		{
			if (index > m_Size)
			{
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

		void Clear() noexcept { delete[] m_Data; }

		/* Private methods */
	private:
		void IncreaseCap() noexcept
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
			}
		}
		void MoveArray(unsigned int index) noexcept
		{
			for (unsigned int i = index; i < m_Size; i++)
			{
				m_Data[i] = m_Data[i + 1];
			}
		}

	private:
		T* m_Data;
		unsigned int m_Capacity;
		int m_Size;

		/* Getters and Setters */
	public:
		T Get(unsigned int index) const noexcept
		{
			if (index <= m_Size)
			{
				return m_Data[index];
			}
			else
			{
				return T();
			}
		}
		T GetFirst() const noexcept
		{
			return m_Data[0];
		}
		T GetLast() const noexcept
		{
			return m_Data[m_Size];
		}
		void Set(T value, unsigned int index) noexcept
		{
			if (index <= m_Size)
			{
				m_Data[index] = value;
			}
			else
			{

			}
		}
		int Length() const noexcept { return m_Size + 1; }

		/* Operators */
	public:
		T operator[](unsigned int index) const noexcept
		{
			if (index <= m_Size)
			{
				return m_Data[index];
			}
			else
			{
				return T();
			}
		}
		//void operator=(DynamicArray<T> array) noexcept { this = array; }
	};
}
