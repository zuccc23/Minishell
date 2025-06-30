/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:34:48 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:34:49 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//check the redirection files' access rights 
//= (open, read, write, append)
// returns 1 if access error, 0 if no error
int	check_file_access(t_redirection *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
			return (check_input_redir(redir));
		if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			return (check_output_redir(redir));
		redir = redir->next;
	}
	return (ER_OK);
}

//check input redir files (<)
int	check_input_redir(t_redirection *redir)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
		return (1);
	close(redir->fd);
	redir->fd = -1;
	return (0);
}

//check output redir files (>, >>)
int	check_output_redir(t_redirection *redir)
{
	if (redir->type == REDIR_OUTPUT)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC);
	if (redir->type == REDIR_APPEND)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT);
	if (redir->fd == -1)
		return (1);
	close(redir->fd);
	redir->fd = -1;
	return (0);
}
