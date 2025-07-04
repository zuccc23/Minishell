/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:39:04 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:39:05 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_token		t_token;
typedef struct s_data		t_data;

// init parser

int		init_parser(t_data *shell);
int		is_minishell(t_data shell);
int		is_same_word(char *str1, char *str2);
void	print_symbol(void);

//check parsing errors

int		parse_tokens(t_token *token);

//parser utils

int		check_single_operator(t_token *token);
int		check_content_before_pipe(t_token *token);
int		check_content_after_operator(t_token *token);
int		check_content_after_pipe(t_token *token);
void	print_token_value(t_word *word, t_token *token);

#endif