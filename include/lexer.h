#ifndef LEXER_H
# define LEXER_H

typedef struct	s_lexer
{
	char	*input; // input complet
	int		pos;    // Position actuelle dans la chaine
	int		length; // Longueur totale de l'input
	char	current;// Caractere courant 
}	t_lexer;

t_lexer	*init_lexer(char *input);

#endif