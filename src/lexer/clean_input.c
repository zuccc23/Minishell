#include "../../include/minishell.h"

//fonction pour nettoyer et recuperer l'input
char	*extract_clean_with_quotes(char *input, int *expandable)
{
	int	i = 0;
	char	*word;

	int len = get_cleaned_word_length(input);
	word = malloc(sizeof(char) * (len + 1));
	while (input[i])
	{
		if (is_double_quotes(input[i]) == 1)
		{
			i++;
			while (is_double_quotes(input[i]) == 0)
			{
				if (is_expandable(input[i], input[i+1]) == 1)
					*expandable = 1;
				str[a][j] = input[i];
				i++;
			}
			i++;
		}
		if (is_single_quotes(input[i]) == 1)
		{
			i++;
			while (is_single_quotes(input[i]) == 0)
			{
				str[a][j] = input[i];
				i++;
			}
			i++;
		}
		while (is_ok_word(input[i]) == 1)
		{
			if (is_expandable(input[i], input[i+1]) == 1)
				expand = 1;
			str[a][j] = input[i];
				i++;
		}
	}
	printf("%s\n", word);
	return (word);
}

static void	check_double_quotes(char *str, int *i, int *count)
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

static void	check_single_quotes(char *str, int *i, int *count)
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
