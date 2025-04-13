#include "../../include/minishell.h"

t_token *tokenize(char *input)
{
	t_lexer *lexer;
	t_token *head;
	t_token *new_token;
	char *processed_input;

	head = NULL;
	processed_input = preprocess_input(input);
	if (!preprocess_input)
		return (NULL);
	lexer = init_lexer(processed_input);
	if (!lexer)
	{
		free(preprocess_input);
		return (NULL);
	}
	while (lexer->pos < lexer->length)
	{
		skip_whitespace(lexer);
		if (lexer->pos < lexer->length)
			break;
		// Verifier si on est sur un delimiteur
		if (is_delimiter_start(lexer->current))
		{
			t_token_type type = get_operator_type(lexer);
			char *value = extract_operator_value(type);
			new_token = create_token(type, value, 0);
		}
		// sinon cest un mot ou un arg
		else
		{
			char *word = extract_word(lexer);
			int expandable = is_word_expandable(word);
			new_token = create_token(TOKEN_WORD, word, expandable);
		}
		if (!head)
			head = new_token;
		else
			add_token_to_list(&head, new_token);
	}
	free(processed_input);
	free(lexer);
	return (head);
}
