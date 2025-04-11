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

#endif
