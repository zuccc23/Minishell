#include "../../include/minishell.h"

static char	*extract_word_with_quotes(t_lexer *lexer)
{
	char	*word;
	int		i;
	int		len;
	char	c;

	i = 0;
	len = extract_word_length(lexer);
	word = malloc (sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	while (lexer->pos < lexer->length && i < len)
	{
		c = (lexer->input[lexer->pos]);
		word[i] = c;
		advance(lexer);
		i++;
	}
	word[i] = '\0';
	return (word);
}

// static char	*extract_clean_with_quotes(char *input, int *expandable)
// {

// }

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
	head = NULL;
	char *value = extract_word_with_quotes(lexer);
	get_cleaned_word_length(value);
	// while (lexer->pos < lexer->length)
	// {
	// 	skip_whitespace(lexer);
	// 	if (is_delimiter_start(lexer->current))
	// 	{
	// 		t_token_type type = get_operator_type(lexer);
	// 		char *value = extract_operator_value(lexer);
	// 		new_token = create_token(type, value, 0);
	// 		printf("\n%s\n", new_token->value);
	// 	}
	// 	else
	// 	{
	//		char *value = extract_word_with_quotes(lexer);
	// 		int expandable = 0;
	// 		char *cleaned = extract_clean_with_quotes(value, &expandable)
	// 		printf("%s\n", value);
	// 		printf("oui\n");
	// 	}
	// 	add_token_to_list(&head, new_token);
	// }
	return (head);
}
