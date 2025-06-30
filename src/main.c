/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:30:14 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:30:16 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	minishell_loop(&shell);
	rl_clear_history();
	if (shell.exec)
		free_exec(shell.exec);
	return (0);
}
