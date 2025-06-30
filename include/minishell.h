/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:59 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:39:00 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>

# include "../libft/libft.h"
# include "token.h"
# include "redirection.h"
# include "command.h"
# include "builtins.h"
# include "env.h"
# include "expand.h"
# include "defines.h"
# include "utils.h"
# include "parser.h"
# include "executor.h"
# include "lexer.h"
# include "signals.h"
# include "preprocess.h"
# include "test.h"
# include "path.h"
# include "heredoc.h"
# include "init.h"

typedef struct s_data
{
	char		*input;
	t_command	*command;
	t_exec		*exec;
	t_token		*token;
	int			exit_status;
	int			parser_status;
}	t_data;

#endif
