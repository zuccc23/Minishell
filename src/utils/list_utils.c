#include "../../include/minishell.h"

void	add_token_to_list(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = *token;
	tmp = ft_token_last(*token);
	if (!tmp)
		*token = new;
	else
		tmp->next = new;
}

t_token	*ft_token_last(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

// Facilite laffichage des types de token
const char	*token_type_to_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == TOKEN_REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	ft_print_list(t_token *token)
{
	int		token_index = 0;
	t_word	*word;

	while (token)
	{
		printf("=== Token #%d ===\n", token_index++);
		printf("Type          : %s\n", token_type_to_str(token->type));
		if (token->type == TOKEN_WORD && token->word)
		{
			printf("Raw value     : %s\n", token->word->value);
			int word_index = 0;
			word = token->word;
			while (word)
			{
				printf("  └─ Word #%d: %s (expandable: ", word_index++, word->value);
				if (word->expandable == 1)
					printf("yes)\n");
				else
					printf("no)\n");
				word = word->next;
			}
		}
		else
		{
			printf("Operator is a %s\n", token_type_to_str(token->type));
		}
		printf("\n\n");
		token = token->next;
	}
}

// Free la liste chainee WORD
void	free_word_list(t_word *word)
{
	t_word	*tmp;

	while (word)
	{
		tmp = word->next;
		if (word->value)
			free(word->value);
		free(word);
		word = tmp;
	}
}

// Free la liste chainee TOKEN
void	ft_free_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->word)
		{
			free_word_list(token->word);
			token->word = NULL;
		}
		free(token);
		token = tmp;
	}
}
