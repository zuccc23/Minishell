#include "../../include/minishell.h"

static char	*extract_word(t_lexer *lexer)
{
	char	*word;
	int		start;
	int		len;
	char	quote;

	if (!lexer || lexer->pos >= lexer->length)
		return (NULL);
	start = lexer->pos;
	len = 0;
	quote = 0;
	while (lexer->pos < lexer->length)
	{
		if (!quote && (lexer->current == ' ' || is_delimiter_start(lexer->current)))
			break;
		if (is_quote(lexer->current))
		{
			if (quote == 0)
				quote = lexer->current;
			else if (quote == lexer->current)
				quote = 0;
		}
		len++;
		advance(lexer);
	}
	word = malloc (sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &lexer->input[start], len + 1);
	word[len] = '\0';
	return (word);
}

t_token *tokenize(char *input)
{
	t_lexer *lexer;
	t_token *head;
	t_token *new_token;
	char *processed_input;

	head = NULL;
	processed_input = preprocess_input(input);
	if (!processed_input)
		return (NULL);
	lexer = init_lexer(processed_input);
	if (!lexer)
	{
		free(processed_input);
		return (NULL);
	}
	while (lexer->pos < lexer->length)
	{
		skip_whitespace(lexer);
		if (lexer->pos >= lexer->length)
			break;
		// Verifier si on est sur un delimiteur
		if (is_delimiter_start(lexer->current))
		{
			t_token_type type = get_operator_type(lexer);
			char *value = extract_operator_value(lexer);
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
