#ifndef SAFE_MEM_H
# define SAFE_MEM_H

# include <stdlib.h>

void	*malloc_safe(size_t size);
void	*calloc_safe(size_t count, size_t size);
int		free_safe(void *ptr);

#endif
