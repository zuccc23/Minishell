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
