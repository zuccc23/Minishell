#include "../../include/minishell.h"

static char	*extract_word_with_quotes(t_lexer *lexer)
{
	char	*word;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	word = malloc (sizeof(char) * extract_word_length(lexer) + 1);
	if (!word)
		return (NULL);
	while (lexer->pos < lexer->length)
	{
		c = (lexer->input[lexer->pos + i]);
		
	}
	return (word);
}

t_token *tokenize(char *input)
{
	t_lexer *lexer;
	t_token *head;
	t_token *new_token;
	char 	*processed_input;

	lexer = init_lexer(input);
	if (!lexer)
		return (NULL);
	processed_input = preprocess_input(input);
	if (!processed_input)
		return (NULL);

	// "ls -la" | wc -l >> outfile "'"$USER"'"
	printf("\nPrepro : %s\n", processed_input);
	//head = NULL;
	char *value = extract_word_with_quotes(lexer);
	// while (lexer->pos < lexer->length)
	// {
	// 	skip_whitespace(lexer);
	// 	if (is_delimiter_start(lexer->current))
	// 	{
	// 		t_token_type type = get_operator_type(lexer);
	// 		char *value = extract_operator_value(lexer);
	// 		new_token = create_token(type, value, 0);
	// 	}
	// 	else
	// 	{
	// 		char *value = extract_word_with_quotes(lexer);
	// 	}
	// 	add_token_to_list(head, new_token);
	// 	advance(lexer);
	// }
	return (head);
}
