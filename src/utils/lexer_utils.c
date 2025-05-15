#include "../../include/minishell.h"

// Faire avancer le lexer
void	advance(t_lexer *lexer)
{
	if (lexer->pos < lexer->length)
	{
		lexer->pos++;
		lexer->current = lexer->input[lexer->pos];
	}
}

// Pour verifier le caractere suivant du lexer
char	peek(t_lexer *lexer)
{
	if (lexer->pos + 1 < lexer->length)
		return (lexer->input[lexer->pos + 1]);
	return ('\0');
}

// Saute les espaces
void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->pos < lexer->length && (lexer->current == ' '
			|| lexer->current == '\t'))
	{
		lexer->pos++;
		lexer->current = lexer->input[lexer->pos];
	}
}

// Creation du token pour les types OPERATOR
t_token	*create_operator_token(t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	token->word = NULL;
	//token->value = value;
	return (token);
}

// Creation du token pour les types WORD
t_token	*create_word_token(t_token_type type, t_word *word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	token->word = word;
	//token->value = word->value;
	return (token);
}

//Permet de faire avancer le lexer de la taille de loperateur
void	extract_operator_value(t_lexer *lexer)
{
	t_token_type	type;
	char			*value;

	type = get_operator_type(lexer);
	if (!type)
		return ;
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIRECT_APPEND)
		value = malloc(sizeof(char) * 3);
	else
		value = malloc(sizeof(char) * 2);
	if (!value)
		return ;
	value[0] = lexer->current;
	advance(lexer);
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIRECT_APPEND)
	{
		value[1] = lexer->current;
		advance(lexer);
		value[2] = '\0';
	}
	else
		value[1] = '\0';
	free(value);
}
