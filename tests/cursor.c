
// static void	update_quote(char c, char *quote)
// {
// 	if (*quote == 0)
// 		*quote = c;
// 	else if (*quote == c)
// 		*quote = 0;
// }

// static void	process_quote(t_process *p)
// {
// 	update_quote(p->input[p->i], &p->quote);
// 	p->result[p->j++] = p->input[p->i++];
// }

// static void	add_space_before(t_process *p)
// {
// 	if (p->j > 0 && p->result[p->j - 1] != ' ')
// 		p->result[p->j++] = ' ';
// }

// static void	handle_double_delimiter(t_process *p)
// {
// 	p->result[p->j++] = p->input[p->i++];
// 	if (p->input[p->i] && ((p->input[p->i] == '>' && p->input[p->i - 1] == '>')
// 		|| (p->input[p->i] == '<' && p->input[p->i - 1] == '<')))
// 		p->result[p->j++] = p->input[p->i++];
// 	if (p->input[p->i] && p->input[p->i] != ' ')
// 		p->result[p->j++] = ' ';
// }

// static void	process_delimiter(t_process *p)
// {
// 	add_space_before(p);
// 	handle_double_delimiter(p);
// }

// static char	*add_spaces_around_delimiters(char *input)
// {
// 	t_process	p;

// 	p.result = malloc(sizeof(char) * (ft_strlen(input) * 3 + 1));
// 	if (!p.result)
// 		return (NULL);
// 	p.input = input;
// 	p.i = 0;
// 	p.j = 0;
// 	p.quote = 0;
// 	while (input[p.i])
// 	{
// 		if (is_quote(input[p.i]))
// 			process_quote(&p);
// 		else if (!p.quote && is_delimiter_start(input[p.i]))
// 			process_delimiter(&p);
// 		else
// 			p.result[p.j++] = input[p.i++];
// 	}
// 	p.result[p.j] = '\0';
// 	return (p.result);
// }

// static void	handle_quote_in_remove(t_spacer *s)
// {
// 	update_quote(s->str[s->i], &s->quote);
// 	s->str[s->j++] = s->str[s->i++];
// }

// static void	handle_space(t_spacer *s)
// {
// 	if (!s->space_found)
// 	{
// 		s->str[s->j++] = s->str[s->i++];
// 		s->space_found = 1;
// 	}
// 	else
// 		s->i++;
// }

// char	*remove_extra_spaces(char *str)
// {
// 	t_spacer	s;

// 	s.str = str;
// 	s.i = 0;
// 	s.j = 0;
// 	s.quote = 0;
// 	s.space_found = 0;
// 	while (str[s.i])
// 	{
// 		if (is_quote(str[s.i]))
// 			handle_quote_in_remove(&s);
// 		else if (s.quote)
// 			s.str[s.j++] = s.str[s.i++];
// 		else if (str[s.i] == ' ')
// 			handle_space(&s);
// 		else
// 		{
// 			s.space_found = 0;
// 			s.str[s.j++] = s.str[s.i++];
// 		}
// 	}
// 	s.str[s.j] = '\0';
// 	return (s.str);
// }

// char	*preprocess_input(char *input)
// {
// 	char	*step1;
// 	char	*step2;

// 	if (!input)
// 		return (NULL);
// 	step1 = add_spaces_around_delimiters(input);
// 	if (!step1)
// 		return (NULL);
// 	step2 = remove_extra_spaces(step1);
// 	free(step1);
// 	if (!step2)
// 		return (NULL);
// 	return (step2);
// }
