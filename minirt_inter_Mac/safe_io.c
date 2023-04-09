#include "safe_io.h"

int	read_safe(int fd, void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = read(fd, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		if (res == 0)
			return (0);
		off += res;
	}
	return (1);
}

void	write_safe(int fd, const void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = write(fd, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		off += res;
	}
}
