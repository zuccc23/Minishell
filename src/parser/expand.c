#include "../../include/minishell.h"

//expand les variables expandables
int	expand_vars(t_token **token, char **env, int ex_code)
{
	t_token	*head;

	head = *token;
	while (*token)
	{
		if ((*token)->type == TOKEN_HEREDOC)
			*token = (*token)->next->next;
		if (is_word(*token) == 1)
		{
			if (replace_expands(&(*token)->word, env, ex_code) != ER_OK)
				return (ER_MALLOC);
			delete_empty_values(&(*token)->word);
		}
		if (*token)
			*token = (*token)->next;
	}
	*token = head;
	return (ER_OK);
}

//remplace les expands de toute la liste chainee
int	replace_expands(t_word **word, char **env, int ex_code)
{
	t_word	*head;

	head = (*word);
	while ((*word))
	{
		if ((*word)->expandable == 1)
		{
			if (replace_value(&(*word)->value, env, ex_code) != ER_OK)
				return (ER_MALLOC);
		}
		(*word) = (*word)->next;
	}
	(*word) = head;
	return (ER_OK);
}

//change l'ancienne value en son expand
int	replace_value(char **value, char **env, int ex_code)
{
	int		i;
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
		expand = get_expand(varname, env, ex_code);
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
		while (body && body->next)
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
