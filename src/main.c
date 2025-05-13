#include "../include/minishell.h"

//creating a node with proper values
t_token	*new_token(char *value1, char *value2, char *operator, t_token_type type, int expandable, int expandable2) // fonction temporaire 
{
	t_token *new = NULL;

	new = malloc(sizeof(t_token));
	new->word = NULL;
	// new->value = NULL;

	if (operator)
		new->value = ft_strdup(operator);
	new->type = type;

	if (value1)
	{
		new->word = malloc(sizeof(t_word));
		new->word->value = ft_strdup(value1);

		new->word->next = malloc(sizeof(t_word));
		// new->word->value = NULL;
		new->word->next->value = ft_strdup(value2);
		new->word->next->next = NULL;

		new->word->expandable = expandable;
		new->word->next->expandable = expandable2;
	}

	new->next = NULL;

	return (new);
}


t_token	*temp_tokens(void) // fonction temporaire 
{
	//creating a temporary linked list of tokens
	t_token *head = NULL;
	t_token *token = NULL;

	token = new_token("l", "s", NULL, TOKEN_WORD, 0, 0);
	head = token;

	token->next = new_token("-", "l", NULL, TOKEN_WORD, 0, 0);
	token = token->next;

	token->next = new_token(NULL, NULL, ">", TOKEN_REDIRECT_OUT, 0, 0);
	token = token->next;

	token->next = new_token("out", "file", NULL, TOKEN_WORD, 0, 0);
	token = token->next;

	token->next = new_token(NULL, NULL, ">>", TOKEN_REDIRECT_APPEND, 0, 0);
	token = token->next;

	token->next = new_token("test", "file", NULL, TOKEN_WORD, 0, 0);
	token = token->next;

	// token->next = new_token("-", "l", TOKEN_WORD, 0, 0);
	// token = token->next;

	token = head;
	return (token);
}

//print the token list in a single line
void	print_line_tokens(t_token *token) // fonction temporaire 
{
	ft_printf("----------------------------\n");
	while (token)
	{
		if (token->word)
		{
			ft_printf("%s", token->word->value);
			ft_printf("%s", token->word->next->value);
			ft_printf(" ");
		}
		if (token->value)
		{
			ft_printf("%s ", token->value);
		}
		token = token->next;
	}
	ft_printf("\n");
	ft_printf("----------------------------\n");
}

//print the token list
void	print_tokens(t_token *token) // fonction temporaire 
{
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

	//NETTOYAGE INPUT
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

	//CREER DES TOKENS TEMPORAIRES POUR LES TESTS
	t_token	*token = NULL;
	int		er_code = 0;

	token = temp_tokens();
	// print_tokens(token);
	// print_line_tokens(token);

	//PARSE LES ERREURS DE SYNTAXE DS LES TOKENS
	er_code = parse_tokens(token);
	if (er_code != ER_OK)
	{
		free_tokens(token);
		exit(er_code);
	}
	
	// TEST REDIRECTIONS
	// t_redirection *redir;
	// t_command	*commands;

	// commands = malloc (sizeof(t_command));
	// commands->redirections = get_redirections(&token);
	// ft_printf("%d\n", commands->redirections->type);
	// ft_printf("%s\n", commands->redirections->file);
	// if (token)
	// 	ft_printf("%s\n", token->value);
	// exit(0);

	//TEST COMMAND COUNT
	// int	c_count = count_args(token);
	// ft_printf("%d\n", c_count);
	// exit(0);

	// ENV & EXPAND
	// expand_vars(&token, envp);
	// printf("%s\n", getenv("PATH"));
	// strs_print(envp);
	// printf("%s\n", ft_getenv("PATH", envp));

	// char *leftover;
	// char *varname;
	// char *expand;
	// char *res;

	// printf("%s\n", token->word->value);
	// replace_expands(&token->word, envp);
	
	// printf("%s\n", token->word->value);
	// printf("%s\n", token->word->next->value);
	// printf("-------\n");
	// printf("%s\n", token->next->word->value);
	// printf("%s\n", token->next->word->next->value);

	// replace_value(&(token->word->value), envp);
	// printf("%s\n", token->word->value);

	// exit(0);

	// leftover = get_leftover(&(token->word->value), &i);
	// printf("%s\n", leftover);
	// varname = get_var_name(&(token->word->value), &i);
	// printf("%s\n", varname);
	// expand = get_expand(varname, envp);
	// printf("%s\n", expand);
	// res = join_expand(leftover, expand);
	// printf("%s\n", res);

	//RECUP LES COMMANDES ET REDIRECTIONS
	t_command	*command;
	// command = malloc (sizeof(t_command));
	// command->args = malloc(sizeof(char *) * (count_args(token) + 1));
	// int i = 0;
	// t_redirection *redir = malloc (sizeof(t_redirection));
	
	get_commands(token, &command);
	printf("%s\n", token->word->value);
	// new_command(token, &command, count_args(token));
	// command = malloc(sizeof(t_command));
	// command->args = malloc(sizeof(char) * 3);
	// assign_args(&token, &command, &i);
	// printf("%s\n", token->word->value);
	// get_redir_file(token, &redir);
	// get_redirections(&token, &redir);
	
	// ft_printf("%s\n", redir->file);
	

	// if (get_commands(token, &command) != ER_OK)
	// {
	// 	free_commands(command);
	// 	free_tokens(token);
	// 	exit(1);
	// }
	
	// ft_printf("command: %s\n", command->args[0]);
	// ft_printf("command: %s\n", command->args[1]);
	// ft_printf("redirect type: %d\n", command->redirections->type);
	// ft_printf("redirect file: %s\n", command->redirections->file);

	
	// ft_printf("redirect type: %d\n", command->redirections->next->type);
	// ft_printf("redirect file: %s\n", command->redirections->next->file);
	// ft_printf("%s\n", command->args[2]);
	// ft_printf("%s\n", command->args[3]);

	// command = command->next;
	// ft_printf("command: %s\n", command->args[0]);
	// // // // ft_printf("command: %s\n", command->args[1]);
	// ft_printf("redirect type: %d\n", command->redirections->type);
	// ft_printf("redirect file: %s\n", command->redirections->file);
	// ft_printf("redirect type: %d\n", command->redirections->next->type);
	// ft_printf("redirect file: %s\n", command->redirections->next->file);
	// ft_printf("%s\n", command->args[1]);
	// exit (0);

	// CLEANING AND FREEING
	printf("%s\n", token->word->value);
	free_commands(command);
	free_tokens(token);
	return (0);
}

/*THINGS TO FREE
-tokens linked list
-commands linked list
*/