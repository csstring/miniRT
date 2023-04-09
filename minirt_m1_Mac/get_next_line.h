#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef BUCKET_SIZE
#  define BUCKET_SIZE 5
# endif

typedef struct s_pair	t_pair;

typedef struct s_chain	t_chain;

struct s_pair
{
	int		fd;
	t_chain	*head;
	t_pair	*next;
};

struct s_chain
{
	char	buf[BUFFER_SIZE];
	ssize_t	size;
	ssize_t	offset;
	t_chain	*next;
};

char	*get_next_line(int fd);

#endif
