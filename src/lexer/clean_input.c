#include "../../include/minishell.h"

void	check_double_quotes(char *str, int *i, int *count)
{
	if (is_double_quotes(str[*i]) == 1)
	{
		(*i)++;
		while (is_double_quotes(str[*i]) == 0)
		{
			(*count)++;
			(*i)++;
		}
		(*i)++;
	}
}

void	check_single_quotes(char *str, int *i, int *count)
{
	if (is_single_quotes(str[*i]) == 1)
	{
		(*i)++;
		while (is_single_quotes(str[*i]) == 0)
		{
			(*count)++;
			(*i)++;
		}
		(*i)++;
	}
}

int	get_cleaned_word_length(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		check_double_quotes(input, &i, &count);
		check_single_quotes(input, &i, &count);
		while (is_ok_word(input[i]) == 1)
		{
			count++;
			i++;
		}
	}
	return (count);
}
