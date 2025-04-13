#ifndef LEXER_H
# define LEXER_H

// Garder un etat courant pendant qu'on scanne l'input
typedef struct	s_lexer
{
	char	*input; // input complet
	int		pos;    // Position actuelle dans la chaine
	int		length; // Longueur totale de l'input
	char	current;// Caractere courant
}	t_lexer;

t_lexer	*init_lexer(char *input);

// UTILS

void	advance(t_lexer *lexer);
char	peek(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);

#endif
