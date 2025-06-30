/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:37:23 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:37:24 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//variable globale pour recupérer le signal
volatile sig_atomic_t	g_signal;

//gere SIGINT en mode interactif
void	handle_sigint(int sig)
{
	g_signal = sig;
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//gere SIGINT en mode exec
void	exec_handle_sigint(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigquit(int sig)
{
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
}
