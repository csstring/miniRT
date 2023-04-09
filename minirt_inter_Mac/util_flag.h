#ifndef UTIL_FLAG_H
# define UTIL_FLAG_H

void	set_flag(int *ptr, int index);
void	reset_flag(int *ptr, int index);
int		has_flag(int flags, int index);
int		add_flag(int flags, int index);
int		remove_flag(int flags, int index);

#endif
