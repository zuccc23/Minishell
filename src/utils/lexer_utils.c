#include "../../include/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_delimiter_start(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

