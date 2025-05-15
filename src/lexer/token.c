#include "../../include/minishell.h"

// Extrait un mot du lexer, en gardant les quotes, et retourne une chaîne allouée.
static char *extract_word_with_quotes(t_lexer *lexer)
{
	char *word;
	int i;
	int len;
	char c;

	i = 0;
	len = extract_word_length(lexer);
	word = malloc(sizeof(char) * len + 1);
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

// Initialise le lexer et traite une premiere fois la chaine
int init_lexer_preprocess(t_lexer **lexer, char **p_input, char *input)
{
	*lexer = init_lexer(input);
	if (!*lexer)
		return (0);
	*p_input = preprocess_input(input);
	if (!*p_input)
		return (0);
	return (1);
}
// Transforme l’entrée utilisateur en tokens distincts en traitant opérateurs, mots, espaces et quotes
t_token *tokenize(char *input)
{
	t_lexer *lexer;
	t_token *head;
	t_token *new_token;
	char *processed_input;

	if (!init_lexer_preprocess(&lexer, &processed_input, input))
	{
		if (lexer)
			free(lexer);
		return (NULL);
	}
	// printf("\nPrepro : %s\n", processed_input);
	head = NULL;
	while (lexer->pos < lexer->length)
	{
		skip_whitespace(lexer);
		if (is_delimiter_start(lexer->current))
		{
			t_token_type type = get_operator_type(lexer);
			if (!extract_operator_value(lexer))
			{
				free_tok_error(lexer, head, NULL, processed_input);
				return (NULL);
			}
			new_token = create_operator_token(type);
			if (!new_token)
			{
				free_tok_error(lexer, head, NULL, processed_input);
				return (NULL);
			}
		}
		else
		{
			char *value = extract_word_with_quotes(lexer);
			if (!value)
			{
				free_tok_error(lexer, head, NULL, processed_input);
				return (NULL);
			}
			t_word *word = NULL;
			clean_words(value, &word); // proteger en cas dechec
			if (!word)
			{
				free_tok_error(lexer, head, value, processed_input);
				return (NULL);
			}
			free(value);
			new_token = create_word_token(TOKEN_WORD, word); // proteger en cas dechec
			{
				free_tok_error(lexer, head, value, processed_input);
				return (NULL);
			}
		}
		// new_token->next = NULL;
		add_token_to_list(&head, new_token);
	}
	free(lexer);
	free(processed_input);
	return (head);
}
