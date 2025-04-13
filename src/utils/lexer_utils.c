#include "../../include/minishell.h"

void	advance(t_lexer *lexer)
{
	if (lexer->pos < lexer->length)
	{
		lexer->pos++;
		lexer->current = lexer->input[lexer->pos];
	}
}

char	peek(t_lexer *lexer)
{
	if (lexer->pos + 1 < lexer->length)
		return (lexer->input[lexer->pos + 1]);
	return ('\0');
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->pos < lexer->length && (lexer->current == ' '
			|| lexer->current == '\t'))
	{
		lexer->pos++;
		lexer->current = lexer->input[lexer->pos];
	}
}

t_token	*create_token(t_token_type type, char *value, int expandable)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->expandable = expandable;
	token->type = type;
	token->next = NULL;
	token->value = value;
	return (token);
}

char	*extract_operator_value(t_lexer *lexer)
{
	t_token_type	type;
	char			*value;

	type = get_operator_type(lexer);
	if (!type)
		return (NULL);
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIRECT_APPEND)
		value = malloc(sizeof(char) * 3);
	else
		value = malloc(sizeof(char) * 2);
	if (!value)
		return (NULL);
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
	return (value);
}
