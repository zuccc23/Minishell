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

const char	*token_type_to_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == TOKEN_REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	ft_print_list(t_token *token)
{
	while (token)
	{
		printf("value: %-15s | type: %-15s | expandable: %d\n",
			token->value,
			token_type_to_str(token->type),
			token->expandable);
		token = token->next;
	}
}
