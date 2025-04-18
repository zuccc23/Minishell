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

	token = new_token(">", TOKEN_REDIRECT_OUT, 0);
	head = token;

	// token->next = new_token("-l", TOKEN_WORD, 0);
	// token = token->next;

	// token->next = new_token(">", TOKEN_REDIRECT_OUT, 0);
	// token = token->next;

	token->next = new_token("infile", TOKEN_WORD, 0);
	token = token->next;

	token->next = new_token("|", TOKEN_PIPE, 0);
	token = token->next;

	token->next = new_token("-w", TOKEN_WORD, 0);
	token = token->next;

	// token->next = new_token("-w", TOKEN_WORD, 0);
	// token = token->next;

	token->next = new_token(">", TOKEN_REDIRECT_OUT, 0);
	token = token->next;

	token->next = new_token("outfile", TOKEN_WORD, 0);
	token = token->next;

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
			ft_printf("        =word ");
		else 
			ft_printf("       =operator ");
		ft_printf("=expandable:%d\n", token->expandable);
		token = token->next;
	}
}

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

	//nettoyage input
	// char	input[] = "'\"'$USER'\"'";
	// char	input[] = "''$USER   'l's    ''";
	// char	input[] = "\"'\"$USER\"'\"";
	// char	input[] = "\"'\"'$USER'\"'\"";

	// char	**strs;

	
	// printf("INPUT:\n");
	// printf("%s\n", input);

	// strs = clean(input);

	// printf("\n");
	// printf("CLEAN INPUT:\n");
	// strs_print(strs);
	// exit (0);

	//cree des tokens temporaires pr les tests
	t_token	*token = NULL;
	int		er_code = 0;

	token = temp_tokens();
	print_tokens(token);
	print_line_tokens(token);

	//parse les erreurs de syntaxe ds les tokens
	er_code = parse_tokens(token);
	if (er_code != ER_OK)
		exit(er_code);
	
	// test redirections
	// t_redirection *redir;
	// t_command	*commands;

	// commands = malloc (sizeof(t_command));
	// commands->redirections = get_redirections(&token);
	// ft_printf("%d\n", commands->redirections->type);
	// ft_printf("%s\n", commands->redirections->file);
	// if (token)
	// 	ft_printf("%s\n", token->value);
	// exit(0);

	//commands count
	// int	c_count = count_args(token);
	// ft_printf("%d\n", c_count);
	// exit(0);
	
	//recuperer les commandes et redirections
	t_command	*command;
	
	// ft_printf("command count = %d\n", count_args(token));
	// command = new_command(token, count_args(token));
	command = get_commands(token);
	// ft_printf("%s\n", command->args[0]);
	// ft_printf("%s\n", command->args[1]);
	ft_printf("%d\n", command->redirections->type);
	ft_printf("%s\n", command->redirections->file);
	// ft_printf("%s\n", command->args[2]);
	// ft_printf("%s\n", command->args[3]);

	command = command->next;
	ft_printf("%s\n", command->args[0]);
	ft_printf("%d\n", command->redirections->type);
	ft_printf("%s\n", command->redirections->file);
	// ft_printf("%s\n", command->args[1]);

	return (0);
}

/*THINGS TO FREE
-tokens linked list
-commands linked list
*/