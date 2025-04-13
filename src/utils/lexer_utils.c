#include "../../include/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_delimiter_start(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	has_valid_quote(char *input)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (current_quote == 0)
				current_quote = input[i];
			else if (input[i] == current_quote)
				current_quote = 0;
		}
		i++;
	}
	if (current_quote == 0)
		return (0);
	return (1);
}
