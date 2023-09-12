#include "main.h"

/**
 * copyData - Copies information from one pointer to another.
 * @newptr: Destination pointer.
 * @ptr: Source pointer.
 * @size: Size of the destination.
 * Return: None.
 */
void copyData(void *newptr, const void *ptr, unsigned int size)
{
	char *_ptr = (char *)ptr;
	char *_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
	{
		_newptr[i] = _ptr[i];
	}
}

/**
 * resizeMemory - Reallocates memory to a new size.
 * @ptr: Initial memory to be reallocated.
 * @oldSize: Old size of the memory.
 * @newSize: New size of the memory.
 * Return: Pointer to the reallocated memory.
 */
void *resizeMemory(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(newSize));
	if (newSize == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (newSize == oldSize)
		return (ptr);
	new_ptr = malloc(newSize);
	if (new_ptr == NULL)
		return (NULL);
	if (newSize < oldSize)
		copyData(new_ptr, ptr, newSize);
	else
		copyData(new_ptr, ptr, oldSize);

	free(ptr);
	return (new_ptr);
}

/**
 * resizeDblePtrMem - Reallocates memory for an array of pointers.
 * @ptr: Initial memory to be reallocated.
 * @oldSize: Old size of the memory.
 * @newSize: New size of the memory.
 * Return: Pointer to the reallocated memory.
 */
char **resizeDblePtrMem(char **ptr, unsigned int oldSize, unsigned int newSize)
{
	char **new_ptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * newSize));
	if (newSize == oldSize)
		return (ptr);
	new_ptr = malloc(sizeof(char *) * newSize);
	if (new_ptr == NULL)
		return (NULL);
	for (i = 0; i < oldSize; i++)
	{
		new_ptr[i] = ptr[i];
	}
	free(ptr);
	return (new_ptr);
}
