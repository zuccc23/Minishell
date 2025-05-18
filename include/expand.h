#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_token	t_token;
typedef struct s_word	t_word;

//expand les variables

int		expand_vars(t_token **token, t_env *env);
int		replace_value(char **value, t_env *env);
int		replace_expands(t_word **word, t_env *env);

// expand utils

char	*get_var_name(char **value, int *i);
char	*get_expand(char *varname, t_env *env);
char	*get_leftover(char **value, int *i);
char	*join_expand(char *s1, char *s2);
char	*dup_value(char *s1);

// supprime les noeuds avec des valeurs vides

void	delete_empty_values(t_word **word);
void	del_node(t_word **word);

#endif