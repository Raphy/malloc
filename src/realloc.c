/*
** realloc.c for malloc in /home/bade/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <bade@epitech.net>
**
** Started on Thu Feb  6 12:06:58 2014 Barthelemy Delemotte
** Last update Thu Feb  6 12:07:37 2014 Barthelemy Delemotte
*/

#include	<string.h>
#include	<assert.h>
#include	"my_malloc.h"

/*
** Realloc by merging the next if it isn't reserved.
** Return 0 if the realloc has been done, -1 otherwise
*/
static int	realloc_by_merge(t_ptr block, size_t size)
{
  size_t	total_size;
  size_t	real_size;

  if (size <= DWORD_SIZE)
    real_size = size + EXTRA_SIZE;
  else
    {
      real_size = ((size + EXTRA_SIZE + DWORD_SIZE - 1)
		   / DWORD_SIZE) * DWORD_SIZE;
    }
  total_size = GET_B_SIZE(block) + GET_B_SIZE(GET_NEXT(block));
  if (IS_B_ALLOC(GET_NEXT(block)) || total_size < real_size)
    return (-1);
  SET(GET_HEAD(block), PACK(total_size, 0));
  SET(GET_FOOT(block), PACK(total_size, 0));
  heap_reserve(block, real_size);
  return (0);
}

/*
** Realloc ...
*/
void		*realloc(void *ptr, size_t size)
{
  t_ptr		block;
  t_ptr		new_block;

  if (ptr == NULL)
    return (malloc(size));
  else if (!size)
    {
      free(ptr);
      return NULL;
    }
  block = (t_ptr)ptr;
  assert(IS_B_ALLOC(block));
  if (GET_B_SIZE(block) - EXTRA_SIZE >= size)
    return ptr;
  if (realloc_by_merge(ptr, size) == 0)
    return ptr;
  if ((new_block = malloc(size)) == NULL)
    return NULL;
  memcpy(new_block, block, GET_B_SIZE(block) - EXTRA_SIZE);
  free(block);
  return new_block;
}
