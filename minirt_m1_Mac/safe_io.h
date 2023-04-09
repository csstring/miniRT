#ifndef SAFE_IO_H
# define SAFE_IO_H

# include <stdlib.h>
# include <unistd.h>

int		read_safe(int fd, void *buf, size_t len);
void	write_safe(int fd, const void *buf, size_t len);

void	putstr_safe(const char *str);
void	putnbr_safe(int n);
void	puterr_safe(const char *str);

#endif
