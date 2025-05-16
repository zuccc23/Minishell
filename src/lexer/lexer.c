#include "../../include/minishell.h"

// Initialise les valeurs du lexer
t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = (input);
	lexer->pos = 0;
	lexer->length = ft_strlen(input);
	lexer->current = input[0];
	return (lexer);
}
