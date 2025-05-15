#include "../../include/minishell.h"

//ajoute les redirections en addback
int	assign_redirections(t_token **token, t_command **command)
{
	t_redirection	*redir_tail;
	int				er_code;

	er_code = 0;
	if (is_operator(*token) == 1)
	{
		if (!(*command)->redirections)
		{
			er_code = get_redirections(&(*token), &(*command)->redirections);
			if (er_code != ER_OK || !(*command)->redirections)
				return (ER_MALLOC);
			return (0);
		}
		redir_tail = lstlast_redir((*command)->redirections);
		er_code = get_redirections(&(*token), &redir_tail->next);
		if (er_code != ER_OK || !(redir_tail->next))
			return (ER_MALLOC);
	}
	return (0);
}

//check le type de redirection et lui associe le bon fichier
int	get_redirections(t_token **token, t_redirection **redir)
{
	t_redirection	*temp_redir;
	int				er_code;

	er_code = 0;
	temp_redir = malloc(sizeof(t_redirection));
	*redir = temp_redir;
	if (!temp_redir)
		return (ER_MALLOC);
	temp_redir->next = NULL;
	temp_redir->file = NULL;
	if ((*token)->type == TOKEN_REDIRECT_OUT)
		temp_redir->type = REDIR_OUTPUT;
	if ((*token)->type == TOKEN_REDIRECT_IN)
		temp_redir->type = REDIR_INPUT;
	if ((*token)->type == TOKEN_REDIRECT_APPEND)
		temp_redir->type = REDIR_APPEND;
	if ((*token)->type == TOKEN_HEREDOC)
		temp_redir->type = REDIR_HEREDOC;
	er_code = get_redir_file((*token)->next, &temp_redir);
	if (er_code != ER_OK)
		return (ER_MALLOC);
	(*token) = (*token)->next;
	(*token) = (*token)->next;
	return (ER_OK);
}

// recupere le fichier de redirection
int	get_redir_file(t_token *token, t_redirection **redir)
{
	char	*tmp;

	if (!token->word)
		return (0);
	tmp = ft_strdup(token->word->value);
	if (!tmp)
		return (ER_MALLOC);
	if (!token->word->next)
	{
		(*redir)->file = ft_strdup(tmp);
		free(tmp);
		if (!(*redir)->file)
			return (ER_MALLOC);
	}
	join_redir_words(token->word, &(*redir), tmp);
	return (ER_OK);
}

//joint les mots du fichier de redirection
int	join_redir_words(t_word *word, t_redirection **redir, char *tmp)
{
	char	*tmp2;
	t_word	*head;

	head = word;
	while (word->next)
	{
		tmp2 = ft_strdup(word->next->value);
		if (!tmp2)
		{
			free(tmp);
			return (ER_MALLOC);
		}
		(*redir)->file = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		if (!(*redir)->file)
			return (ER_MALLOC);
		word = word->next;
		tmp = (*redir)->file;
	}
	word = head;
	return (ER_OK);
}

//retourne le dernier noeud de la liste de redirections
t_redirection	*lstlast_redir(t_redirection *lst)
{
	t_redirection	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
