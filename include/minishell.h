#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>

# include "../libft/libft.h"
# include "token.h"
# include "redirection.h"
# include "command.h"
# include "builtins.h"
# include "env.h"
# include "expand.h"
# include "defines.h"
# include "utils.h"
# include "parser.h"
# include "executor.h"
# include "lexer.h"
# include "signals.h"
# include "preprocess.h"
# include "test.h"
# include "path.h"
# include "heredoc.h"

#endif
