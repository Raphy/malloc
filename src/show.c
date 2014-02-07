
#include	<unistd.h>
#include	<stdio.h>

#include	"my_malloc.h"

/*
** dump the current break and each allocated block
*/
void		show_alloc_mem(void)
{
  t_ptr		block;
  size_t	size;

  printf("break : %p\n", sbrk(0));
  if ((block = heap_root))
    {
      while (GET_B_SIZE(block) > 0)
	{
	  if (IS_B_ALLOC(block))
	    {
	      size = GET_B_SIZE(block) - EXTRA_SIZE;
	      printf("%p - %p : %lu octets\n", block, block + size, size);
	    }
	  block = GET_NEXT(block);
	}
    }
}

/*
** dump the current break and each block
*/
void		dump_mem(void)
{
  t_ptr		block;
  size_t	size;

  printf("break : %p\n", sbrk(0));
  if ((block = heap_root))
    {
      while (GET_B_SIZE(block) > 0)
	{
	  size = GET_B_SIZE(block) - EXTRA_SIZE;
	  printf("%p - %p : %lu octets %s\n", block, block + size, size,
		 IS_B_ALLOC(block) ? "reserved" : "free");
	  block = GET_NEXT(block);
	}
    }
}
