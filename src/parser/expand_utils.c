#include "../../include/minishell.h"

// recupere le nom de la variable a expand (=$USER)
char	*get_var_name(char **value, int *i)
{
	char		*varname;
	size_t		j;

	if ((*value)[(*i)] != '$')
		return (NULL);
	j = 0;
	varname = malloc(sizeof(char) * ft_strlen(&(*value)[*i]));
	if (!varname)
		return (NULL);
	(*i)++;
	if ((*value)[(*i)] == '\0')
		return (NULL);
	while (ft_isalnum((*value)[(*i)]) == 1 || (*value)[(*i)] == '_')
	{
		varname[j] = (*value)[(*i)];
		(*i)++;
		j++;
	}
	varname[j] = '\0';
	while (j < ft_strlen(&(*value)[*i]))
	{
		varname[j] = '\0';
		j++;
	}
	return (varname);
}

// recupere le resultat de l'expansion
char	*get_expand(char *varname, t_env *env)
{
	char	*expand;

	if (!varname)
		return (NULL);
	expand = NULL;
	expand = ft_getenv(varname, env);
	free(varname);
	if (!expand)
		return (NULL);
	return (expand);
}

// recupere les morceaux de la chaine qui ne sont pas expandables
char	*get_leftover(char **value, int *i)
{
	char		*leftover;
	size_t		j;

	if ((*value)[(*i)] == '$')
		return (NULL);
	j = 0;
	leftover = NULL;
	leftover = malloc(sizeof(char) * ft_strlen(&(*value)[*i]));
	if (!leftover)
		return (NULL);
	while ((*value)[(*i)] != '$')
	{
		leftover[j] = (*value)[(*i)];
		(*i)++;
		j++;
	}
	while (j < ft_strlen(&(*value)[*i]))
	{
		leftover[j] = '\0';
		j++;
	}
	return (leftover);
}

// strjoin en gros
char	*join_expand(char *s1, char *s2)
{
	char	*res;

	res = NULL;
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!res)
		return (NULL);
	return (res);
}

// strdup en gros
char	*dup_value(char *s1)
{
	size_t	i;
	size_t	size;
	char	*dest;

	if (!s1)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	free(s1);
	return (dest);
}
