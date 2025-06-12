#include "../../include/minishell.h"

//checks if 'value' in empty, hasnt reached '$' or if it has '?'
// or checks if it has any weird characters, which it will skip
// ex: $*abc' = 'abc'
char	*check_value(size_t *j, char *value, int *i)
{
	char	*str;

	if (value[(*i)] == '\0' || value[(*i)] != '$')
		*j = 1;
	if (value[(*i)] != '\0' && value[(*i) + 1] == '\0')
	{
		*j = 1;
		(*i)++;
	}
	if (value[(*i)] != '\0' && check_char_v(value[(*i) + 1]) == 1)
	{
		*j = 1;
		(*i) += 2;
	}
	if (value[(*i)] != '\0' && value[(*i) + 1] != '\0' \
&& value[(*i) + 1] == '?')
	{
		str = return_q_mark(&(*j), &(*i));
		return (str);
	}
	return (NULL);
}

// return a string with "$?" in it
char	*return_q_mark(size_t *j, int *i)
{
	char	*str;

	*j = 1;
	(*i) += 2;
	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = '?';
	str[1] = '\0';
	return (str);
}

//returns 0 if its a correct char, 0 if not
int	check_char_v(char c)
{
	if (ft_isalnum(c) == 0 && (c != '_' && c != '?'))
		return (1);
	return (0);
}

//when the expand is '$?', returns a string with the exit code in it
char	*question_mark(char *varname, int ex_code)
{
	char	*str;

	str = ft_itoa(ex_code);
	free(varname);
	if (!str)
		return (NULL);
	return (str);
}
