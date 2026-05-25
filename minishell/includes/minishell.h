#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD_NOT_EXECUTABLE 126

extern volatile sig_atomic_t g_signo;

// ===== TOKEN STRUCT =====

typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

// ===== COMMAND STRUCT =====

typedef struct s_cmd
{
    char            **argv;
    char            *infile;
    int             infile_fd;
    char            *outfile;
    char            *heredoc_delim;
    int             heredoc_fd;
    int             append;
    int             heredoc_expand;
    char            *heredoc_input;
    char            *full_path;
    struct s_cmd    *next;
} t_cmd;

typedef struct s_shell
{
	char	    **envp;
	int		    last_exit_status;
    int         stop;
    char        *input;
    t_token		*tokens;
	t_cmd		*cmds;
}	t_shell;

// ===== LEXER =====

t_token    *tokenize(char *input);

// ===== TOKEN UTILS =====

t_token    *new_token(char *value, t_token_type type);
void        add_token(t_token **list, t_token *new);

// ===== TOKENIZE UTILS =====

void        skip_spaces(char *s, int *i);
int         is_operator(char c);
void        handle_operator(char *input, int *i, t_token **tokens);
void        handle_word(char *input, int *i, t_token **tokens);

// ===== FREE =====

void        free_tokens(t_token *tokens);
void        free_cmds(t_cmd *cmds);

// ===== WORD HANDLING =====

char        *extract_word(char *s, int start, int end);

// ===== QUOTES =====

void        handle_quotes(char *s, int *i);

// ===== VALIDATION =====

int         validate_tokens(t_token *tokens);
int         check_unclosed_quotes(char *input);

// ===== PARSER =====

t_cmd       *parser(t_token *tokens);
t_cmd       *new_cmd(void);
void        add_cmd(t_cmd **list, t_cmd *new);
void        add_arg(t_cmd *cmd, char *value);
void        remove_quotes_from_tokens(t_token *token);

// ===== EXECUTOR =====

void        execute_pipe(t_cmd *cmd_list, t_shell *data);
void        setup_child(t_cmd *cmd, t_shell *data, int prev_fd, int fd[2]);
void        handle_output_redir(t_cmd *cmd);
void        exec_external(t_cmd *cmd, t_shell *data);
void        execute_commands(t_cmd *cmd, t_shell *data);

// ===== BUILTINS =====

int         is_builtin(t_cmd *cmd);
int         exec_builtin(t_cmd *cmd, t_shell *data);
int         builtin_echo(t_cmd *cmd);
int         builtin_cd(t_cmd *cmd, t_shell *data);
int         builtin_pwd(void);
int         builtin_env(t_shell *data);
int         builtin_export(t_cmd *cmd, t_shell *data);
int         builtin_unset(t_cmd *cmd, t_shell *data);
int         builtin_exit(t_cmd *cmd, t_shell *data);
int         set_env_var(t_shell *data, char *name, char *value);

// ===== PATH =====

char        **find_path(t_shell *data);
char        *join_path_cmd(char *path, char *cmd);
int         get_cmd_path(t_cmd *cmd, t_shell *data);
int         is_abs_path(char *cmd);
int         check_access(t_shell *data, t_cmd *cmd, char *path);

// ===== UTILS =====

char        *ft_strjoin(char *s1, char *s2);
char        **ft_split(char *s, char c);
int         count_words(char *s, char c);
char        *word_dup(char *s, int start, int end);
int         ft_strlen(char *s);
int         syntax_error(char *msg);
char        *ft_strremove(char *str, const char *remove);
void        ft_putstr_fd(char *s, int fd);
void        cleanup_shell(t_shell *data);
void        free_2d(char **str);

// ===== SIGNALS =====

int         handle_eof(char *input);
void        handle_sigint(int sig);
void        setup_signal_handlers(void);

// ===== GET LINE =====

char        *get_next_line(int fd);

// ===== INIT =====

void        init_shell(t_shell *data, char **envp);
void        free_env(char **envp);

// ===== LIBFT =====

char        *ft_strdup(const char *s);
char        *ft_substr(char const *s, unsigned int start, size_t len);
char        *ft_itoa(int n);
int         ft_isalpha(int c);
int         ft_isdigit(int c);
int         ft_isalnum(int c);
int         ft_strcmp(const char *s1, const char *s2);
int         ft_strncmp(const char *s1, const char *s2, size_t n);
char        *ft_strchr(const char *s, int c);

// ===== EXPANSION =====

char        *build_result(char *before, char *env, char *after);
char        *extract_env_name(char *s);
char        *get_env_value(t_shell *data, char *var_name);
char        *separate_parts(char *content, int i, char **after);
void        handle_expansion_quotes(char c, int *in_single, int *in_double);
char        *replace_env_var(t_shell *data, char *content, int i);
int         process_env_var(t_token *current, int *i, t_shell *data);
int         process_env_if_needed(t_token *current, int *i, t_shell *data);
int         process_node(t_token *current, t_shell *data);
int         expand_each_token(t_shell *data, t_token *token);
int         expander_tokens(t_shell *data, t_token *token);
void        remove_quotes_from_tokens(t_token *token);
char        *remove_quotes_from_str(char *s);

// ===== HEREDOC =====

int         handle_heredoc(t_cmd *cmd, t_shell *data);
char        *expand_heredoc_content(char *content, t_shell *data);
void        setup_heredoc_signals(void);

#endif
