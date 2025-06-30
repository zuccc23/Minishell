/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:18 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:38:19 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "redirection.h"

typedef struct s_token	t_token;

//args = Tableau d'arguments, redirections = liste de redirections
typedef struct s_command
{
	char				**args;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

// get the commands and their redirections

int		get_commands(t_token *token, t_command **commands);
int		new_command(t_token *token, t_command **command, int args_count);
int		alloc_command(t_command **command, int args_count);
int		assign_args(t_token **token, t_command **new_command, int *i);

//commands utils

int		count_args(t_token *token);
int		get_words(t_token *token, t_command **new_command, int *i);
int		join_words(t_word *word, t_command **new_command, char *tmp, int *i);

//check token type

int		is_operator(t_token *token);
int		is_pipe(t_token *token);
int		is_word(t_token *token);

#endif
