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
int	expand_vars(t_token **token, char **envp)
{
	t_token	*head;

	head = *token;
	while (*token)
	{
		if ((*token)->type == TOKEN_HEREDOC)
			*token = (*token)->next->next;
		if (is_word(*token) == 1)
		{
			replace_expands(&(*token)->word, envp);
			//secure
		}
		if (*token)
			*token = (*token)->next;
	}
	*token = head;
	return (ER_OK);
}

//remplace les expands de toute la liste chainee
int	replace_expands(t_word **word, char **envp)
{
	t_word	*head;

	head = (*word);
	while ((*word))
	{
		if ((*word)->expandable == 1)
		{
			replace_value(&(*word)->value, envp);
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
char	*get_expand(char *varname, char **envp)
{
	char	*expand;

	if (!varname)
		return (NULL);
	expand = NULL;
	expand = ft_getenv(varname, envp);
	free(varname);
	if (!expand)
		return (NULL);
	return (expand);
}

// recupere les morceaux de la chaine qui ne sont pas expandables
char	*get_leftover(char **value, int *i)
{
	char	*leftover;
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

//change l'ancienne value en son expand
int	replace_value(char **value, char **envp)
{
	int	i;
	char	*leftover;
	char	*varname;
	char	*expand;
	char	*res;

	i = 0;
	res = NULL;
	while ((*value)[i])
	{
		leftover = get_leftover(&(*value), &i);
		varname = get_var_name(&(*value), &i);
		expand = get_expand(varname, envp);
		if (res && leftover)
			res = join_expand(res, leftover);
		if (!res && leftover)
			res = dup_value(leftover);
		if (res && expand)
			res = join_expand(res, expand);
		if (!res && expand)
			res = dup_value(expand);
	}
	free(*value);
	*value = res;
	return (ER_OK);
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

//efface les noeuds avec des valeurs vides
void	delete_empty_values(t_word **word)
{
	t_word	*head;
	t_word	*body;
	t_word	*tmp;

	head = NULL;
	while (*word && !(*word)->value)
	{
		tmp = (*word);
		(*word) = (*word)->next;
		free(tmp);
	}
	if (*word && (*word)->value)
	{
		head = *word;
		body = head;
		while (body->next)
		{
			if (!body->next->value)
				del_node(&(*word));
			body = body->next;
		}
	}
	*word = head;
}

//efface un seul noeud
void	del_node(t_word **word)
{
	t_word	*tmp;

	tmp = (*word)->next;
	(*word)->next = (*word)->next->next;
	free(tmp);
}
