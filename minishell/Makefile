NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes

LDFLAGS = -lreadline

HEADER = includes/minishell.h
OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, \
	main.o \
	init_shell.o \
	struct_fun.o \
	token_utils.o \
	tokenize.o \
	validate.o \
	expand1.o \
	expand2.o \
	expand3.o \
	remove_quotes.o \
	parser.o \
	parser_utils.o \
	heredoc.o \
	heredoc_expander.o \
	heredoc_signals.o \
	abs_path.o \
	child_process.o \
	executor.o \
	get_cmd_path.o \
	path.o \
	pipes.o \
	free.o \
	builtin.o \
	cd.o \
	echo.o \
	env.o \
	exit.o \
	export.o \
	pwd.o \
	unset.o \
	get_next_line.o \
	signals.o \
	cleanup.o \
	ft_split.o \
	utils.o \
	utils2.o \
	utils3.o)

vpath %.c src src/1.lexer src/2.Syntax_check src/3.Expansion \
	src/builtins src/read src/signals src/utils

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o: src/4.\ Parser/parser.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/parser_utils.o: src/4.\ Parser/parser_utils.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/heredoc.o: src/5.\ Heredoc/heredoc.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/heredoc_expander.o: src/5.\ Heredoc/heredoc_expander.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/heredoc_signals.o: src/5.\ Heredoc/heredoc_signals.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/abs_path.o: src/6.\ Execution/abs_path.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/child_process.o: src/6.\ Execution/child_process.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/executor.o: src/6.\ Execution/executor.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/get_cmd_path.o: src/6.\ Execution/get_cmd_path.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/path.o: src/6.\ Execution/path.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/pipes.o: src/6.\ Execution/pipes.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR)/free.o: src/7.\ Free/free.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c "$<" -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
