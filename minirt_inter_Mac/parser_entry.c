#include "parser.h"
#include "safe_mem.h"
#include "libft.h"

t_entry	*make_entry(void)
{
	return (calloc_safe(1, sizeof(t_entry)));
}

void	dispose_entry(t_entry *item)
{
	if (item)
	{
		free(item->value);
		dispose_entry(item->child);
		dispose_entry(item->next);
	}
	free(item);
}
