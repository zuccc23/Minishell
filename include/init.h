/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:49 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:38:50 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_data		t_data;

//init

int		init_shell(t_data *shell, char **envp);
int		init_vars(t_data *shell);

//inside loop

void	minishell_loop(t_data *shell);
int		read_input(t_data *shell);
void	token_part(t_data *shell);
void	check_for_exit(t_data *shell);

#endif
