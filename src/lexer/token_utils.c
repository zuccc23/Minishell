#include "../../include/minishell.h"

t_token_type get_operator_type(t_lexer *lexer)
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

int extract_word_length(t_lexer *lexer)
{
	int i;
	char quote;
	char c;

	i = 0;
	quote = 0;
	while (lexer->pos + i < lexer->length)
	{
		c = lexer->input[lexer->pos + i];
		printf("%c | %c\n",c, lexer->input[lexer->pos + 1 + i]);
		if (is_quote(c))
		{
			if (quote == 0)
				quote = c;
			else if (quote != 0)
				quote = 0;
			i++;
			continue;
		}
		if (quote == 0 && (c == ' ' || c == '\t' || is_delimiter_start(c)))
			break;
		i++;
	}
	printf("%d\n", i);
	return (i);
}

// int	is_word_expandable(char *str)
// {
// }
