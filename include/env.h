#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;  // Exemple : "PATH"
	char			*value;// Exemple : "usr/bin:/bin:..."
	struct s_env	*next; // Pointeur vers la prochaine variable
}	t_env;

//recupere l'env
char	*ft_getenv(char *str, char **envp);
char	*copy_path(const char *s1, int start);

//expand les variables
int	expand_vars(t_token **token); //step 1
int	replace_expands(t_word **word); //step 2

char	*get_var_name(char **value, int *i); //step 3
char	*get_expand(char *varname, char **envp);//step 3,5
char	*get_leftover(char **value, int *i);//step 3
char	*join_expand(char *s1, char *s2); //step 4

#endif