# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smassand <marvin@42.fr>                   +#+  +:+       +#+          #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/11 13:44:49 by smassand          #+#    #+#              #
#    Updated: 2016/05/09 18:45:09 by smassand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

CC =		gcc

EXT =		.c

FLAGS =		-g -Wall -Werror -Wextra
# -fsanitize=address 

FILE =		minishell 		ft_env				ft_setenv		ft_setenv_plus\
			ft_unsetenv		ft_unsetenv_plus 	ft_cd			ft_cd_plus\
			ft_exit			ft_init 			ft_path			ft_exec \
			ft_echo			ft_libft_ex			ft_error		ft_cd_plus_plus

SOURCE = 	srcs/

INCLUDE =	includes/

HEADER = 	minishell.h

FILES =		$(addprefix $(SOURCE), $(addsuffix $(EXT), $(FILE)))

OBJ = 		$(FILES:$(EXT)=.o)

LIB_DIR =	libft

EXEC=		$(LIB_DIR)/$(LIB_DIR).a

C_W=		\033[0m
C_R=		\033[38;5;124m
C_Y=		\033[38;5;214m
C_B=		\033[38;5;97m
C_N=		\033[38;5;200m
C_G=		\033[38;5;190m

all: 	$(EXEC) $(NAME) #norme

$(EXEC):
		@make -C $(LIB_DIR)
		@echo "$(C_Y)$(LIB_DIR) $(C_R)			is done !$(C_W)"

$(NAME): $(OBJ)
		@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(EXEC)
		@echo "\n$(C_Y)$(NAME) $(C_R)		is done !$(C_W)"

%.o:	%$(EXT) $(INCLUDE)
		@$(CC) $(FLAGS) -c $< -o $@ -I libft
		@printf "\033[32m.$(C_W)"

clean:
		@rm -rf $(OBJ)
		@echo "$(C_B)$(NAME)$(C_R)		All obj are cleaned$(C_W)"
		@(cd $(LIB_DIR) && $(MAKE) $@)
		@echo "$(C_B)$(LIB_DIR)$(C_R)		All obj are cleaned$(C_W)"

fclean: clean
		@rm -rf $(NAME)
		@echo "\n$(C_G)$(NAME)$(C_R)		is clean$(C_W)"
		@(cd $(LIB_DIR) && $(MAKE) $@)
		@echo "$(C_G)$(EXEC)$(C_R)	is clean$(C_W)\n"

norme:
	@echo "\nSource:$(C_N)"
	@norminette $(FILES)
	@echo "\n$(C_W)Header:$(C_N)"
	@norminette $(INCLUDE)$(HEADER)
	@echo "$(C_W)"

re: fclean all
