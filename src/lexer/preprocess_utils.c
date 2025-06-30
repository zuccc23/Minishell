/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:35:30 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:35:31 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_quote(t_process *p)
{
	update_quote(p->input[p->i], &p->quote);
	p->result[p->j++] = p->input[p->i++];
}

void	add_space_before(t_process *p)
{
	if (p->j > 0 && p->result[p->j - 1] != ' ')
		p->result[p->j++] = ' ';
}

void	update_quote(char c, char *quote)
{
	if (*quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

void	handle_quote_in_remove(t_spacer *s)
{
	update_quote(s->str[s->i], &s->quote);
	s->str[s->j++] = s->str[s->i++];
}

void	handle_space(t_spacer *s)
{
	if (!s->space_found)
	{
		s->str[s->j++] = s->str[s->i++];
		s->space_found = 1;
	}
	else
		s->i++;
}
