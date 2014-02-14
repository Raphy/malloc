/*
** calloc.c for malloc in /home/delemo_b/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb  6 12:02:53 2014 Barthelemy Delemotte
** Last update Fri Feb 14 02:17:55 2014 raphael defreitas
*/

#include	<string.h>
#include	"my_malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  ptr = malloc(nmemb * size);
  if (ptr)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}
