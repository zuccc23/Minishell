#include "../../include/minishell.h"

static char	*add_spaces_around_delimiters(char *input)
{
	int		i;
	int		j;
	char	*result;
	char	quote;

	result = malloc(sizeof(char) * (ft_strlen(input) * 3 + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (quote  == 0)
				quote = result[i];
			else if (quote == result[i])
				quote = 0;
			result[j++] = input[i++];
			continue;
		}
		if (!quote && is_delimiter_start(input[i]) == 1)
		{
			if (j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
			result[j++] = input[i++];
			if (input [i] && ((input[i] == '>' && input[i - 1] == '>')
				|| (input[i] == '<' && input[i - 1] == '<')))
				result[j++] = input[i++];
			if (input[i] && input[i] != ' ')
				result[j++] = ' ';
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*remove_extra_spaces(char *str)
{
	int		i;
	int		j;
	int		space_found;
	char	quote;

	j = 0;
	i = 0;
	space_found = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			str[j++] = str[i++];
			continue;
		}
		if (quote)
		{
			str[j++] = str[i++];
			continue;
		}
		if (str[i] == ' ')
		{
			if (!space_found)
			{
				str[j++] = str[i++];
				space_found = 1;
			}
			else
				i++;
		}
		else
		{
			space_found = 0;
			str[j++] = str[i++];
		}
	}
	str[j] = '\0';
	return (str);
}

char	*preprocess_input(char *input)
{
	char	*step1;
	char	*step2;

	if (!input)
		return (NULL);
	step1 = add_spaces_around_delimiters(input);
	printf("step 1 : %s\n", step1);
	if (!step1)
		return (NULL);
	step2 = remove_extra_spaces(step1);
	if (!step2)
		return (NULL);
	return (step2);
}
