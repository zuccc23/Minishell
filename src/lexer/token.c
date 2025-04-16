#include "../../include/minishell.h"

static char	*extract_word_with_quotes(t_lexer *lexer)
{
}

t_token *tokenize(char *input)
{
	t_lexer *lexer;
	t_token *head;
	t_token *new_token;
	char *processed_input;

	lexer = init_lexer(input);
	if (!lexer)
		return (NULL);
	processed_input = preprocess_input(input);
	if (!processed_input)
		return (NULL);
	printf("\nPrepro : %s\n", processed_input);
	head = NULL;
	return (head);
}
