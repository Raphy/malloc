/*
** my_malloc.h for malloc in /home/bade/Dev/tek2/Unix/malloc
**
** Made by Barthelemy Delemotte
** Login   <bade@epitech.net>
**
** Started on Thu Feb  6 12:02:21 2014 Barthelemy Delemotte
** Last update Thu Feb  6 12:02:27 2014 Barthelemy Delemotte
*/

#ifndef		MY_MALLOC_H_
# define	MY_MALLOC_H_

# include	<sys/types.h>

/*
** Pointer type
*/
typedef char	*t_ptr;

/*
** CONSTANTS SIZE
*/

/*
** Word and double word size
*/
# define	WORD_SIZE	(sizeof(size_t))
# define	DWORD_SIZE	(2 * WORD_SIZE)

/*
** Size of header plus footer of a block
*/
# define	EXTRA_SIZE	(DWORD_SIZE)

/*
** Minimal memory size increment (and the initial heap size)
*/
# define	CHUNK_SIZE	(4096)

/*
** FOR AN EASIEST BRAIN FUCKING ...
*/

/*
** Word manips
*/
# define	PACK(size, a)	((size) | (a))
# define	GET(ptr)	(*((size_t*)(ptr)))
# define	SET(ptr, value)	(*((size_t*)(ptr)) = (value))

/*
** Block manips
*/

/*
** Get the block size (a multiple of WORD_SIZE)
*/
# define	GET_SIZE(ptr)	(GET(ptr) & ~0x7)

/*
** 1 if the block is allocated, 0 otherwise
*/
# define	IS_ALLOC(ptr)	(GET(ptr) & 0x1)

/*
** Get extras datas, next or prev block
*/
# define	GET_HEAD(b)	((b) - WORD_SIZE)
# define	GET_B_SIZE(b)	(GET_SIZE(GET_HEAD((b))))
# define	GET_FOOT(b)	((b) + GET_B_SIZE(b) - DWORD_SIZE)
# define	GET_NEXT(b)	((b) + GET_B_SIZE(b))
# define	GET_PREV(b)	((b) - GET_SIZE((GET_HEAD((b)) - WORD_SIZE)))
# define	IS_B_ALLOC(b)	(IS_ALLOC(GET_HEAD((b))))

/*
** Internal symbols
*/
extern t_ptr	heap_root;

t_ptr		heap_merge(t_ptr block);
t_ptr		heap_extend(size_t words_nbr);
int		heap_init(void);
t_ptr		heap_search(size_t size);
void		heap_reserve(t_ptr block, size_t size);

/*
** Public symbols
*/
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		*calloc(size_t nmemb, size_t size);
void		free(void *ptr);
void		show_alloc_mem(void);
void		dump_mem(void);

#endif /* MY_MALLOC_H_ */
