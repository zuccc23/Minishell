/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:35:52 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:35:53 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Extrait un mot du lexer, garde les quotes retourne une chaîne
static char	*extract_word_with_quotes(t_lexer *lexer)
{
	char	*word;
	int		i;
	int		len;
	char	c;

	i = 0;
	len = extract_word_length(lexer);
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	while (lexer->pos < lexer->length && i < len)
	{
		c = (lexer->input[lexer->pos]);
		word[i] = c;
		advance(lexer);
		i++;
	}
	word[i] = '\0';
	return (word);
}

// Initialise le lexer et traite une premiere fois la chaine
int	init_lexer_preprocess(t_lexer **lexer, char **p_input, char *input)
{
	*p_input = NULL;
	*lexer = init_lexer(input);
	if (!*lexer)
		return (0);
	*p_input = preprocess_input(input);
	if (!*p_input)
		return (0);
	return (1);
}

static t_token	*operator_step(t_lexer *lexer, t_token *head, char *p_input)
{
	t_token_type	type;
	t_token			*new_token;

	type = get_operator_type(lexer);
	if (!extract_operator_value(lexer))
	{
		free_tok_error(&lexer, &head, NULL, &p_input);
		return (NULL);
	}
	new_token = create_operator_token(type);
	if (!new_token)
	{
		free_tok_error(&lexer, &head, NULL, &p_input);
		return (NULL);
	}
	return (new_token);
}

static t_token	*word_step(t_lexer *lexer, t_token *head, char *p_input)
{
	char	*value;
	t_word	*word;
	t_token	*new_token;
	int		er_code;

	er_code = 0;
	value = extract_word_with_quotes(lexer);
	if (!value)
		return (free_tok_error(&lexer, &head, NULL, &p_input));
	word = NULL;
	er_code = clean_words(value, &word);
	if (er_code != 0)
	{
		free_word_list(word);
		free_tok_error(&lexer, &head, &value, &p_input);
		return (NULL);
	}
	new_token = create_word_token(TOKEN_WORD, word);
	if (!new_token)
	{
		free_word_list(word);
		free_tok_error(&lexer, &head, &value, &p_input);
	}
	return (new_token);
}

// Transforme l’entrée en tokens
t_token	*tokenize(char *input)
{
	t_lexer	*lexer;
	t_token	*head;
	t_token	*new_token;
	char	*processed_input;

	head = NULL;
	if (!init_lexer_preprocess(&lexer, &processed_input, input))
		return (free_tok_error(&lexer, &head, NULL, &processed_input), NULL);
	while (lexer->pos < lexer->length)
	{
		skip_whitespace(lexer);
		if (lexer->pos >= lexer->length)
			break ;
		if (is_delimiter_start(lexer->current))
			new_token = operator_step(lexer, head, processed_input);
		else
			new_token = word_step(lexer, head, processed_input);
		if (!new_token)
			return (NULL);
		add_token_to_list(&head, new_token);
	}
	free(lexer);
	free(processed_input);
	return (head);
}
