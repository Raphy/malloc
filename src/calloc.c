/*
** calloc.c for malloc in /home/delemo_b/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <delemo_b@epitech.net>
**
** Started on Thu Feb  6 12:02:53 2014 Barthelemy Delemotte
** Last update Sun Feb  9 20:25:39 2014 Barthelemy Delemotte
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
