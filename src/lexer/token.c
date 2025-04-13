#include "../../include/minishell.h"

t_token	*tokenize(char *input)
{
	int		i;
	t_lexer	*lexer;
	t_token	*head;
	char	*processed_input;

	i = 0;
	processed_input = preprocess_input(input);
	lexer = init_lexer(processed_input);
	if (!lexer)
		return (NULL);

	return (head);
}
