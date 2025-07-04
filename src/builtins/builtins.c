/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:30:31 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:30:32 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_parent_builtin(const char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strnstr(cmd_name, "cd", 2) != 0 && ft_strlen(cmd_name) == 2)
		return (true);
	else if (ft_strnstr(cmd_name, "exit", 4) != 0 && ft_strlen(cmd_name) == 4)
		return (true);
	else if (ft_strnstr(cmd_name, "export", 6) != 0 && ft_strlen(cmd_name) == 6)
		return (true);
	else if (ft_strnstr(cmd_name, "unset", 5) != 0 && ft_strlen(cmd_name) == 5)
		return (true);
	else
		return (false);
}
