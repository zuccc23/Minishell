#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_token	t_token;
typedef struct s_word	t_word;

//expand les variables

int		expand_vars(t_token **token, char **env, int ex_code);
int		replace_value(char **value, char **env, int ex_code);
int		replace_expands(t_word **word, char **env, int ex_code);

// expand utils

char	*get_var_name(char **value, int *i);
char	*get_expand(char *varname, char **env, int ex_code);
char	*get_leftover(char **value, int *i);
char	*join_expand(char *s1, char *s2);
char	*dup_value(char *s1);

//more utils

char	*question_mark(char *varname, int ex_code);
char	*check_value(size_t *j, char *value, int *i);
int		check_char_v(char c);
char	*return_q_mark(size_t *j, int *i);
int		check_single_dollar(char **value, int *i);

// supprime les noeuds avec des valeurs vides

void	delete_empty_values(t_word **word);
void	del_node(t_word **word);

#endif
