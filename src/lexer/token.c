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

int	init_lexer_preprocess(t_lexer **lexer, char **processed_input ,char *input)
{
	*lexer = init_lexer(input);
	if (!*lexer)
		return (0);
	*processed_input = preprocess_input(input);
	if (!*processed_input)
		return (0);
	return (1);
}

t_token *tokenize(char *input)
{
	t_lexer *lexer;
	t_token *head;
	t_token *new_token;
	char 	*processed_input;

	if (!init_lexer_preprocess(&lexer, &processed_input, input))
		return (NULL);
	printf("\nPrepro : %s\n", processed_input);
	head = NULL;
	while (lexer->pos < lexer->length)
	{
		skip_whitespace(lexer);
		if (is_delimiter_start(lexer->current))
		{
			t_token_type type = get_operator_type(lexer);
			char *value = extract_operator_value(lexer);
			new_token = create_token(type, value, 0);
		}
		else
		{
			char *value = extract_word_with_quotes(lexer);
			int expandable = 0;
			char *cleaned = extract_clean_with_quotes(value, &expandable);
			new_token = create_token(TOKEN_WORD, cleaned, expandable);

			printf("\n-----------TEST------------\n");
			t_word	*word = NULL;
			clean_words(value, &word);
			printf("---------FIN TEST---------\n");
		}
		add_token_to_list(&head, new_token);
	}
	return (head);
}
