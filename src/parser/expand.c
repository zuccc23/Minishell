#include "../../include/minishell.h"

//g refait la fonction getenv pour recupere le bon environnement
char	*ft_getenv(char *str, char **envp)
{
	int		i;
	char	*expand;

	i = 0;
	expand = NULL;
	while (envp[i])
	{
		if (ft_strncmp(str, envp[i], ft_strlen(str)) == 0)
		{
			expand = copy_path(envp[i], ft_strlen(str) + 1);
			if (!expand)
				return (NULL);
		}
		i++;
	}
	return (expand);
}

//strdup du bon chemin pour la var d'env
char	*copy_path(const char *s1, int start)
{
	int		i;
	int		j;
	int		size;
	char	*dest;

	i = 0;
	j = 0;
	size = ft_strlen(s1 + start);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < start)
		i++;
	while (s1[i])
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

//expand les variables expandables
int	expand_vars(t_token **token)
{
	t_token	*head;

	head = *token;
	while (*token)
	{
		if ((*token)->type == TOKEN_HEREDOC)
			*token = (*token)->next->next;
		if (is_word(*token) == 1)
		{
			//replace and expand
			//secure
		}
		if (*token)
			*token = (*token)->next;
	}
	*token = head;
	return (ER_OK);
}

//echange la variable avec l'expand qui correspond
int	replace_expands(t_word **word)
{
	t_word	*head;

	head = (*word);
	while ((*word))
	{
		if ((*word)->expandable == 1)
		{

		}
		(*word) = (*word)->next;
	}
	(*word) = head;
	return (ER_OK);
}

// recupere le nom de la variable a expand (=$USER)
char	*get_var_name(char **value, int *i)
{
	char	*varname;
	size_t		j;

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
	while (j < ft_strlen(&(*value)[*i]))
	{
		varname[j] = '\0';
		j++;
	}
	return (varname);
}

char	*get_expand(char *varname, char **envp)
{
	char	*expand;

	expand = NULL;
	expand = ft_getenv(varname, envp);
	free(varname);
	if (!expand)
		return (NULL);
	return (expand);
}

char	*get_leftover(char **value, int *i)
{
	char	*leftover;
	size_t		j;

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