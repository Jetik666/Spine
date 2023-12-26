#include "Engine.h"
#include "GraphicalInput.h"

void* GraphicalInput::operator new(std::size_t size)
{
	void* ptr = ::operator new(size);
	return ptr;
}

void GraphicalInput::operator delete(void* ptr)
{
	::operator delete(ptr);
}
