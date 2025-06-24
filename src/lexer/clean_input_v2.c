#include "../../include/minishell.h"

//Fonction pour nettoyer, recuperer l'input dans liste chainee
int	clean_words(char *input, t_word **word)
{
	int		i;
	t_word	*head;

	i = 0;
	if (get_partial_value(input, &(*word), &i) == -1)
		return (-1);
	head = (*word);
	while (input[i])
	{
		if (get_partial_value(input, &(*word)->next, &i) == -1)
			return (-1);
		(*word) = (*word)->next;
	}
	*word = head;
	free(input);
	return (0);
}

//Creer un nouveau noeud pour t_word list
t_word	*new_word(int size)
{
	t_word	*new;

	new = NULL;
	new = malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->value = malloc(sizeof(char) * (size + 1));
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

//rend une liste chainee pour un token_word
int	get_partial_value(char *input, t_word **word, int *i)
{
	int	er_code;

	er_code = 0;
	while (check_empty_quotes(input[*i], input[(*i) + 1]) == 1)
		(*i) += 2;
	if (is_double_quotes(input[*i]) == 1)
		er_code = get_word_dq(&(*word), input, &(*i));
	else if (is_single_quotes(input[*i]) == 1)
		er_code = get_word_sq(&(*word), input, &(*i));
	else if (is_ok_word(input[*i]) == 1)
		er_code = get_word_nq(&(*word), input, &(*i));
	return (er_code);
}
