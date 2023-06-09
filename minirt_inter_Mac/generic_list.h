#ifndef GENERIC_LIST_H
# define GENERIC_LIST_H

# include <stddef.h>

typedef struct s_generic_list
{
	struct s_generic_list	*next;
}	t_generic_list;

typedef int	t_gl_func();

int				list_walk(t_generic_list *list, t_gl_func *func);
t_generic_list	*list_reverse(t_generic_list *list);
size_t			list_length(t_generic_list *list);
void			list_append(t_generic_list **head, t_generic_list *elem);
t_generic_list	*list_remove(t_generic_list **list, t_gl_func *cmp, void *arg);

#endif
