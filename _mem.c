#include "main.h"

/**
 * _memcpy - operation consist on copies infos between void pointers.
 * @newptr: the destination of a pointer.
 * @ptr: the source of a pointer.
 * @size: the size of the new pointer.
 * Return: no return printed.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int n;

	for (n = 0; n < size; n++)
		char_newptr[n] = char_ptr[n];
}

/**
 * _realloc - reallocates memory to the block.
 * @ptr: the pointer to memory previously allocated.
 * @old_size: the size, in bytes, of the allocated space of ptr.
 * @new_size: the new size, in bytes, of new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: the double pointer to the memory previously allocated.
 * @old_size: the size, in bytes, of the allocated space of ptr.
 * @new_size: the new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without any changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int n;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (n = 0; n < old_size; n++)
		newptr[n] = ptr[n];

	free(ptr);

	return (newptr);
}
