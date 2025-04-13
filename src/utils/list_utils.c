#include "../../include/minishell.h"

void	add_token_to_list(t_token **token, t_list *new)
{
	t_token	*tmp;

	tmp = *token;
	tmp = ft_token_last(*lst);
	if (!tmp)
		*token = new;
	else
		tmp->next = new;
}

t_token	*ft_token_last(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
