#pragma once

namespace Array
{ 
	template <typename T>
	class ENGINE_API DynamicArray
	{
		/* Constructor */
	public:
		DynamicArray() noexcept;
		~DynamicArray() noexcept;

		/* Public methods */
	public:
		void Push(T value) noexcept;
		void Pop() noexcept;
		void Remove(T value) noexcept;
		void RemoveLast(T value) noexcept;
		void RemoveAt(unsigned int index) noexcept;
		void Insert(T value, unsigned int index) noexcept;

		/* Private methods */
	private:
		void IncreaseCap() noexcept;
		void MoveArray(unsigned int index) noexcept;

	private:
		T* m_Data;
		unsigned int m_Capacity;
		unsigned int m_Size;

		/* Getters and Setters */
	public:
		T Get(unsigned int index) const noexcept;
		T GetFirst() const noexcept;
		T GetLast() const noexcept;
		void Set(T value, unsigned int index) noexcept;

		unsigned int Length() const noexcept { return m_Size + 1; }
	};
}
