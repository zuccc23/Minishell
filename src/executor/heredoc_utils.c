/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:34:04 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:34:05 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Gestionnaire SIGINT pour heredocs qui ferme stdin et définit g_signal
void	heredoc_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		close(STDIN_FILENO);
		g_signal = SIGINT;
	}
}

// Ferme tous les file descriptors des heredocs dans toutes les commandes
void	close_all_heredoc_fds(t_command *cmd)
{
	t_redirection	*redir;

	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->fd >= 0)
				safe_close(&redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

// Vérifie si le processus heredoc a été interrompu par SIGINT
int	is_heredoc_interrupted(int status, int fd)
{
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(fd);
		return (1);
	}
	return (0);
}

// Écrit une ligne dans le heredoc avec expansion si disponible
void	write_heredoc_line(int fd, char *line, char *expanded)
{
	if (expanded)
	{
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	else
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

// Traite l'expansion de $?
void	handle_exit_code(const char *line, size_t *i, t_expand_data *data)
{
	(void)line;
	copy_to_result(data, data->exit_str);
	(*i)++;
}
