/*
** heap.c for malloc in /home/delemo_b/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb  6 12:06:35 2014 Barthelemy Delemotte
** Last update Fri Feb 14 02:17:42 2014 raphael defreitas
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<assert.h>
#include	<stdio.h>
#include	"my_malloc.h"

/*
** Pointer to the first block
*/
t_ptr		heap_root = NULL;

/*
** Merge as possible the next block or/and
** the previous block with the current parameter.
** Return the new address of the current block.
*/
t_ptr		heap_merge(t_ptr block)
{
  size_t	size;
  size_t	prev_state;
  size_t	next_state;

  assert(!IS_B_ALLOC(block));
  size = GET_B_SIZE(block);
  prev_state = IS_B_ALLOC(GET_PREV(block));
  next_state = IS_B_ALLOC(GET_NEXT(block));
  if (!prev_state)
    {
      size += GET_B_SIZE(GET_PREV(block));
      if (!next_state)
	size += GET_B_SIZE(GET_NEXT(block));
      SET(GET_HEAD(GET_PREV(block)), PACK(size, 0));
      SET(GET_FOOT(GET_PREV(block)), PACK(size, 0));
      block = GET_PREV(block);
    }
  else if (!next_state)
    {
      size += GET_B_SIZE(GET_NEXT(block));
      SET(GET_HEAD(block), PACK(size, 0));
      SET(GET_FOOT(block), PACK(size, 0));
    }
  return (block);
}

/*
** Extend the heap by words_nbr * WORD_SIZE bytes.
** If words_nbr is not a multiple of 2, one word is added.
*/
t_ptr		heap_extend(size_t words_nbr)
{
  size_t	size;
  t_ptr		new_block;

  size = (words_nbr % 2 ? words_nbr + 1: words_nbr) * WORD_SIZE;
  if ((new_block = sbrk(size)) == NULL)
    return (NULL);
  SET(GET_HEAD(new_block), PACK(size, 0));
  SET(GET_FOOT(new_block), PACK(size, 0));
  SET(GET_HEAD(GET_NEXT(new_block)), PACK(0, 1));
  return (heap_merge(new_block));
}

/*
** Init the heap :
**	- move the program break
**	- init the heap root
**	- write the pad and prologue (4 WORDS)
**	- extend the heap, create the first block
** Return 0 on success, -1 if an error occured
*/
int		heap_init(void)
{
  if ((heap_root = sbrk(4 * WORD_SIZE)) == NULL)
    return (-1);
  SET(heap_root, 0);
  SET(heap_root + WORD_SIZE, PACK(EXTRA_SIZE, 1));
  SET(heap_root + DWORD_SIZE, PACK(EXTRA_SIZE, 1));
  SET(heap_root + DWORD_SIZE + WORD_SIZE, PACK(0, 1));
  heap_root += 4 * WORD_SIZE;
  if (heap_extend(CHUNK_SIZE / WORD_SIZE) == NULL)
    return (-1);
  return (0);
}

/*
** First-fit search.
** Serch and return the first free block which can greet this size.
** Returns NULL if there it can't find a block
*/
t_ptr		heap_search(size_t size)
{
  t_ptr		block;

  block = heap_root;
  while (GET_B_SIZE(block) > 0)
    {
      if (!IS_B_ALLOC(block) && size <= GET_B_SIZE(block))
	return (block);
      block = GET_NEXT(block);
    }
  return (NULL);
}

/*
** Reserve size bytes in the current block.
** Split the current block if it is possible.
*/
void		heap_reserve(t_ptr block, size_t size)
{
  size_t	block_size;

  assert(!IS_B_ALLOC(block));
  block_size = GET_B_SIZE(block);
  assert(block_size >= size);
  if (block_size - size >= DWORD_SIZE + EXTRA_SIZE)
    {
      SET(GET_HEAD(block), PACK(size, 1));
      SET(GET_FOOT(block), PACK(size, 1));
      SET(GET_HEAD(GET_NEXT(block)), PACK(block_size - size, 0));
      SET(GET_FOOT(GET_NEXT(block)), PACK(block_size - size, 0));
    }
  else
    {
      SET(GET_HEAD(block), PACK(block_size, 1));
      SET(GET_FOOT(block), PACK(block_size, 1));
    }
}
