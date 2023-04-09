void	set_flag(int *ptr, int index)
{
	*ptr |= 1 << index;
}

void	reset_flag(int *ptr, int index)
{
	*ptr = ~(1 << index);
}

int	has_flag(int flags, int index)
{
	return ((flags >> index) & 1);
}

int	add_flag(int flags, int index)
{
	return (flags | (1 << index));
}

int	remove_flag(int flags, int index)
{
	return (flags & ~(1 << index));
}
