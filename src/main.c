#include "../include/minishell.h"

//creating a node with proper values
t_token	*new_token(char *value1, char *value2, t_token_type type, int expandable, int expandable2) // fonction temporaire
{
	t_token *new = NULL;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = NULL;
	new->next = NULL;

	new->type = type;

	if (value1 && value2)
	{
		new->word = malloc(sizeof(t_word));
		if (!new->word)
			return (NULL);
		new->word->value = ft_strdup(value1);
		if (!new->word->value)
			return (NULL);

		new->word->next = malloc(sizeof(t_word));
		if (!new->word->next)
			return (NULL);
		new->word->next->value = ft_strdup(value2);
		if (!new->word->next->value)
			return (NULL);

		new->word->expandable = expandable;
		new->word->next->expandable = expandable2;

		new->word->next->next = NULL;
	}

	return (new);
}

//creating a temporary linked list of tokens
t_token	*temp_tokens(void) // fonction temporaire
{
	t_token *head = NULL;
	t_token *token = NULL;

	token = new_token("l", "s", TOKEN_WORD, 0, 0);
	if (!token)
		return (NULL);
	head = token;

	token->next = new_token("$USER", "$PATHf", TOKEN_WORD, 1, 1);
	if (!token->next)
		return (NULL);
	token = token->next;

	token->next = new_token(NULL, NULL, TOKEN_REDIRECT_OUT, 0, 0);
	if (!token->next)
		return (NULL);
	token = token->next;

	token->next = new_token("$USER", "$_", TOKEN_WORD, 1, 1);
	if (!token->next)
		return (NULL);
	token = token->next;

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
			if (token->word->next)
				ft_printf("%s", token->word->next->value);
			ft_printf(" ");
		}
		if (token->type == TOKEN_HEREDOC)
			ft_printf("<< ");
		if (token->type == TOKEN_REDIRECT_OUT)
			ft_printf("> ");
		if (token->type == TOKEN_REDIRECT_IN)
			ft_printf("< ");
		if (token->type == TOKEN_REDIRECT_APPEND)
			ft_printf(">> ");
		token = token->next;
	}
	ft_printf("\n");
	ft_printf("----------------------------\n");
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env = NULL;
	t_command	*command = NULL;
	(void)ac;
	(void)av;
	(void)envp;
	// int i = 0;

	// input = "ls -l";
    // printf("\n%s\n", input);
    // t_token *head = NULL;
    // head = tokenize(input);
    // if (!head)
    // {
    //     return (1);
    // }
    // printf("\n\n\n\n");
    // ft_print_list(head);
    // ft_free_list(head);
    // return (0);

	// Initialisation du shell + a proteger
	init_env(&env, envp);
	handle_signal();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write (1, "exit\n", 5);
			free_env(env);
			break;
		}
		if (*input)
		{
			add_history(input);
			// printf("\n%s\n", input);
			t_token *head = NULL;
			head = tokenize(input);
			if (!head)
			{
				free(input);
				return (1);
			}
			// printf("\n\n\n\n\n");
			// ft_print_list(head);
			init_parser(&env, &head, &command);
			// while (command)
			// {
			// 	i = 0;
			// 	while (command->args[i])
			// 	{
			// 		printf("%s ", command->args[i]);
			// 		i++;
			// 	}
			// 	printf("\n");
			// 	if (command->redirections)
			// 	{
			// 		printf("type: %d\n", command->redirections->type);
			// 		if (command->redirections->file)
			// 			printf("%s\n", command->redirections->file);
			// 	}
			// 	command = command->next;
			// }
			char *str = get_path(command, envp);
			if (str)
			{
				printf("path: %s\n", str);
				free(str);
			}
			ft_free_list(head);
			free_commands(command);
		}
		free(input);
	}
	return (0);
}
