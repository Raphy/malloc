/*
** calloc.c for malloc in /home/bade/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <bade@epitech.net>
**
** Started on Thu Feb  6 12:02:53 2014 Barthelemy Delemotte
** Last update Thu Feb  6 12:02:54 2014 Barthelemy Delemotte
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
