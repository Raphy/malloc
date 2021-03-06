/*
** free.c for malloc in /home/delemo_b/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb  6 12:06:28 2014 Barthelemy Delemotte
** Last update Fri Feb 14 02:17:50 2014 raphael defreitas
*/

#include	<assert.h>
#include	"my_malloc.h"

/*
** Free ...
**	- set the "reserved" boolean at 0
**	- defrag from the current block
*/
void		free(void *ptr)
{
  t_ptr		block;
  size_t	size;

  if (ptr)
    {
      block = (t_ptr)ptr;
      assert(IS_B_ALLOC(block));
      size = GET_B_SIZE(block);
      SET(GET_HEAD(block), PACK(size, 0));
      SET(GET_FOOT(block), PACK(size, 0));
      heap_merge(block);
    }
}
