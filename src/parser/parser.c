/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:37:05 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:37:06 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//fonction qui parse les erreurs de syntaxe ds les tokens
int	parse_tokens(t_token *token)
{
	int	er_code;

	er_code = 0;
	er_code = check_single_operator(token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = check_content_before_pipe(token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = check_content_after_operator(token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = check_content_after_pipe(token);
	if (er_code != ER_OK)
		return (er_code);
	return (ER_OK);
}
