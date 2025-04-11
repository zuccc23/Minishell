#ifndef PREPROCESS_H
# define PREPROCESS_H

typedef struct s_process
{
	char	*input;
	char	*result;
	int		i;
	int		j;
	char	quote;
}			t_process;

typedef struct s_spacer
{
	char	*str;
	int		i;
	int		j;
	char	quote;
	int		space_found;
}			t_spacer;

char	*preprocess_input(char *input);
char	*remove_extra_spaces(char *str);

// UTILS

void	process_quote(t_process *p);
void	add_space_before(t_process *p);
void	update_quote(char c, char *quote);
void	handle_quote_in_remove(t_spacer *s);
void	handle_space(t_spacer *s);
int		is_quote(char c);
int		is_delimiter_start(char c);
int		has_valid_quote(char *input);

#endif
