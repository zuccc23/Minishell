#include "../../include/minishell.h"

//imprime la valeur entiere du token (localisee dans t_word)
void	print_token_value(t_word *word, t_token *token)
{
	t_word	*head;

	head = word;
	ft_printf("`");
	while (word)
	{
		ft_printf("%s", word->value);
		word = word->next;
	}
	if (token->type == TOKEN_REDIRECT_IN)
		ft_printf("<");
	if (token->type == TOKEN_REDIRECT_OUT)
		ft_printf(">");
	if (token->type == TOKEN_HEREDOC)
		ft_printf("<<");
	if (token->type == TOKEN_REDIRECT_APPEND)
		ft_printf(">>");
	ft_printf("'\n");
	word = head;
}
