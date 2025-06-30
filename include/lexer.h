/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:53 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:38:54 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// Garder un etat courant pendant qu'on scanne l'input
typedef struct s_lexer
{
	char	*input;
	int		pos;
	int		length;
	char	current;
}	t_lexer;

typedef struct s_quote_state
{
	char	current_quote;
}	t_quote_state;

t_lexer	*init_lexer(char *input);

// UTILS

void	advance(t_lexer *lexer);
char	peek(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);

#endif
