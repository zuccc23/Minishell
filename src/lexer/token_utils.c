#include "../../include/minishell.h"

t_token_type	get_operator_type(t_lexer *lexer)
{
	if (lexer->current == '|')
		return (TOKEN_PIPE);
	else if (lexer->current == '>' && peek(lexer) != '>')
		return (TOKEN_REDIRECT_OUT);
	else if (lexer->current == '>' && peek(lexer) == '>')
		return (TOKEN_REDIRECT_APPEND);
	else if (lexer->current == '<' && peek(lexer) != '<')
		return (TOKEN_REDIRECT_IN);
	else if (lexer->current == '<' && peek(lexer) == '<')
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

int	is_word_expandable(char *str)
{
}
