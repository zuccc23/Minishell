#include "../include/minishell.h"


t_token	*new_token(char *value, t_token_type type, int expandable) // fonction temporaire 
{
	t_token *new = NULL;

	//creating a node with proper values
	new = malloc(sizeof(t_token));
	new->value = malloc(sizeof(char) * 100);
	new->value = value;
	new->type = type;
	new->expandable = expandable;
	new->next = NULL;

	return (new);
}

t_token	*temp_tokens(void) // fonction temporaire 
{
	//creating a temporary linked list of tokens
	t_token *head = NULL;
	t_token *token = NULL;

	token = new_token("ls", TOKEN_WORD, 0);
	head = token;

	token->next = new_token("|", TOKEN_PIPE, 0);
	token = token->next;

	token->next = new_token("|", TOKEN_PIPE, 0);
	token = token->next;

	// token->next = new_token("|", TOKEN_PIPE, 0);
	// token = token->next;

	// token->next = new_token("wc", TOKEN_WORD, 0);
	// token = token->next;

	// token->next = new_token("-w", TOKEN_WORD, 0);
	// token = token->next;

	// token->next = new_token(">", TOKEN_REDIRECT_OUT, 0);
	// token = token->next;

	// token->next = new_token("outfile", TOKEN_WORD, 0);
	// token = token->next;

	token = head;
	return (token);
}

void	print_line_tokens(t_token *token) // fonction temporaire 
{
	//print the token list in a single line
	ft_printf("----------------------------\n");
	while (token)
	{
		ft_printf("%s ", token->value);
		token = token->next;
	}
	ft_printf("\n");
}

void	print_tokens(t_token *token) // fonction temporaire 
{
	//print the token list
	while (token)
	{
		ft_printf("%s ", token->value);
		if (token->type == 0)
			ft_printf("--type: word ");
		else 
			ft_printf("--type: operator ");
		ft_printf("--expandable: %d\n", token->expandable);
		token = token->next;
	}
}

// void	print_error(int er_code)
// {
// 	if (er_code == ER_PIPE_SYNTAX)
// 		ft_printf("idk");
	
// }

// void	return_error(t_token *token, int er_code)
// {
// 	//print errors
// 	//free tokens
// }

int	main(int ac, char **av, char **envp)
{
	// char	*input;
	(void)ac;
	(void)av;
	(void)envp;
	
	// Signaux 
	// handle_signal();

	// Initialisation du shell

	// while (1)
	// {
	// 	// Affichage du prompt et recuperation de l'input
	// 	input = readline("minishell> ");
	// 	if (!input) // ctrl + D ou EOF
	// 	{
	// 		write (1, "exit\n", 5);
	// 		break;
	// 	}
	// 	// si l'input n'est pas vide on le traite
	// 	if (*input)
	// 	{
	// 		add_history(input);
	// 	}
	// }

	//cree des tokens temporaires pr les tests
	t_token	*token = NULL;
	int		er_code = 0;

	token = temp_tokens();
	print_tokens(token);
	print_line_tokens(token);

	//parse les erreurs de syntaxe
	er_code = check_single_operator(token);
	// ft_printf("%d\n", er_code);

	er_code = check_content_before_pipe(token);
	// ft_printf("%d\n", er_code);

	er_code = check_content_after_operator(token);
	// ft_printf("%d\n", er_code);
	return (0);
}
