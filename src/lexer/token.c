#include "../../include/minishell.h"

t_token	*tokenize(char *input)
{
	t_lexer	*lexer;
	t_token	*head;

	lexer = init_lexer(input);
	if (!lexer)
		return (NULL);

	return (head);
}
