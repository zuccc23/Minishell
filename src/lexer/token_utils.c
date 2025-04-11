#include "../../include/minishell.h"

int	skip_whitespace(char *str, int i)
{
	while (str[i] && (str[i] == 32 || str[i] == '\t'))
		i++;
	return (i);
}
