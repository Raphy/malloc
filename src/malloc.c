/*
** malloc.c for malloc in /home/delemo_b/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb  6 12:06:43 2014 Barthelemy Delemotte
** Last update Fri Feb 14 02:17:32 2014 raphael defreitas
*/

#include	<stdlib.h>
#include	"my_malloc.h"

/*
** The famous ...
**	- reajust the size (alignment)
**	- search a place
**	- extend the heap if necessary
**	- reserve the block
** Return NULL if size is null or sbrk fails.
*/
void		*malloc(size_t size)
{
  size_t	real_size;
  t_ptr		block;

  if (!size || (!heap_root && heap_init() == -1))
    return (NULL);
  if (size <= DWORD_SIZE)
    real_size = DWORD_SIZE + EXTRA_SIZE;
  else
    {
      real_size = ((size + EXTRA_SIZE + DWORD_SIZE - 1)
		   / DWORD_SIZE) * DWORD_SIZE;
    }
  block = heap_search(real_size);
  if (!block)
    block = heap_extend((real_size > CHUNK_SIZE ?
			 real_size : CHUNK_SIZE) / WORD_SIZE);
  if (block)
    heap_reserve(block, real_size);
  return (block);
}
