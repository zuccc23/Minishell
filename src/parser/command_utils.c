#include "../../include/minishell.h"

//assemble chaque arg individuel a partir de la liste t_word
int	get_words(t_token *token, t_command **new_command, int *i)
{
	char	*tmp;
	int		er_code;

	er_code = 0;
	if (!token->word)
	{
		(*i)--;
		return (0);
	}
	tmp = ft_strdup(token->word->value);
	if (!tmp)
		return (ER_MALLOC);
	if (!token->word->next && token->word->value)
	{
		(*new_command)->args[(*i)] = ft_strdup(tmp);
		free(tmp);
		if (!(*new_command)->args[(*i)])
			return (ER_MALLOC);
	}
	er_code = join_words(token->word, &(*new_command), tmp, &(*i));
	if (er_code != ER_OK)
		return (ER_MALLOC);
	return (ER_OK);
}

// joint les mots ensemble
int	join_words(t_word *word, t_command **new_command, char *tmp, int *i)
{
	char	*tmp2;
	t_word	*head;

	head = word;
	while (word && word->next)
	{
		tmp2 = ft_strdup(word->next->value);
		if (!tmp2)
		{
			free(tmp);
			return (ER_MALLOC);
		}
		(*new_command)->args[(*i)] = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		if (!(*new_command)->args[(*i)])
			return (ER_MALLOC);
		word = word->next;
		tmp = (*new_command)->args[(*i)];
	}
	word = head;
	return (ER_OK);
}

// compte le nombre d'arguments par commande pour malloc la commande
int	count_args(t_token *token)
{
	int	count;

	if (!token)
		return (0);
	count = 0;
	while (is_pipe(token) == 0)
	{
		while (is_word(token) == 1)
		{
			count++;
			token = token->next; 
		}
		if (is_operator(token) == 1)
		{
			token = token->next;
			token = token->next;
		}
	}
	return (count);
}
