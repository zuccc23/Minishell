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
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == 0)
				quote = str[i];
			else if (str[i] == quote)
				quote = 0;
		}
		if (str[i] == '$' && quote == '\'')
			return (1);
		i++;
	}
	return (0);
}
