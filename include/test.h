#ifndef TEST_H
# define TEST_H

// CLEAN QUOTES, GET WORDS IN A LINKED LIST, CHECK EXPAND
int		clean_words(char *input, t_word **final_word);
t_word	*new_word(int size);
int		get_partial_value(char *input, t_word **word, int *i);

// UTILS
int		get_word_dq(t_word **word, char *input, int *i);
int		get_word_sq(t_word **word, char *input, int *i);
int		get_word_nq(t_word **word, char *input, int *i);
int		check_empty_quotes(char c, char c_next);
int		count_word_size(char *input, int i);

#endif
