#include "../../include/minishell.h"

void	add_token_to_list(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = *token;
	tmp = ft_token_last(*token);
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

void	ft_print_list(t_token *token)
{
	while (token)
	{
		printf("\n------\n");
		printf("value      : %s\n", token->value);
		printf("type       : %d\n", token->type);
		printf("expandable : %d\n", token->expandable);
		token = token->next;
	}
}
