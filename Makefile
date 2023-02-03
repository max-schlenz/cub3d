# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 12:57:52 by mschlenz          #+#    #+#              #
#    Updated: 2023/02/03 12:14:22 by mschlenz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL 			=	/bin/bash
UNAME			=	$(shell uname)
MAKEFLAGS 		=	--no-print-directory
CFLAGS			=	#-Wall -Wextra -Werror #-g #-fsanitize=address 

#FORMAT----------------------------------#
DEFCL			=	$(shell echo -e "\033[0m")
RED				=	$(shell echo -e "\033[0;31m")
GREEN			=	$(shell echo -e "\033[0;32m")
BGREEN			=	$(shell echo -e "\033[1;32m")
YELLOW			=	$(shell echo -e "\033[0;33m")
BLUE			=	$(shell echo -e "\033[0;34m")
BBLUE			=	$(shell echo -e "\033[1;34m")
PURPLE			=	$(shell echo -e "\033[0;35m")
CYAN			=	$(shell echo -e "\033[0;36m")
BCYAN			=	$(shell echo -e "\033[1;36m")
GRAY			=	$(shell echo -e "\033[0m\033[38;5;239m")
DEL_R			=	\033[K
# ---------------------------------------#

NAME			=	cub3D

SRC_DIR			=	src
OBJ_DIR			=	obj
LIB_DIR			=	lib
INC_DIR			=	inc

SRC				= 	${NAME}													\

INC				=	${NAME}													\
					data													\
					strings													\
					libft								

LIB				=	libft 

SRC_FILES		=	$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRC)))
LIB_FILES		=	$(addsuffix .a, $(addprefix $(LIB_DIR)/, $(LIB)))
OBJ_FILES		=	$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(SRC)))
INC_FILES		=	$(addsuffix .h, $(addprefix $(INC_DIR)/, $(INC)))

MLX_DIR			=	MLX42
MLX_LIB			=	$(MLX_DIR)/build/libmlx42.a
INCLUDES		= 	-I $(INC_DIR) -I $(MLX_DIR)/include/MLX42
LINKER			=	-L lib -l ft 

MAC_BREW		=	~/.brewconfig.zsh
MAC_GLFW		=	~/.brew/opt/glfw/lib/

GLFW			=	~/.brew/opt/glfw/lib
MLX_LINKER		=	-L $(GLFW) -l glfw -L $(MLX_DIR)/build  -framework Cocoa -framework OpenGL -framework IOKit

HEADER			=	./.header

all: $(NAME)

$(LIB_FILES):
	@echo -n "compile..."
	@touch .tmp
	@$(MAKE) MAKEFLAGS+=-j1 CFLAGS+="$(CFLAGS)" -C src/libft
	@ar -rc $(LIB_FILES) $$(find ./src/libft -type f -name '*.o')

$(OBJ_DIR):
	@mkdir -p $(shell find src -type d | sed \s/src/obj/g)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c header_c 
	@if [ ! -f .tmp ]; then														\
		echo -n "compile...";													\
		touch .tmp;\
	fi
	@echo -en "\\r		➜  ${BCYAN}$(NAME)${DEFCL}...    »  $@${DEL_R}"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MAC_INCLUDES) -c $< -o $@ 
	
ifeq ($(UNAME), Darwin)
$(NAME): $(MAC_BREW) $(MAC_GLFW) $(HEADER) $(MLX_DIR) $(MLX_LIB) $(LIB_FILES) $(OBJ_DIR) $(OBJ_FILES)
	@echo -en "\\r		  ${BGREEN}$(NAME)${DEFCL}        ✔  ${BGREEN}./$(NAME)${DEFCL}${DEL_R}\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(MLX_LIB) $(INCLUDES) $(LINKER) $(MLX_LINKER)
	@rm -f .tmp
else	
$(NAME): $(HEADER) $(MAC_GLFW) $(LIB_FILES) $(OBJ_DIR) $(OBJ_FILES)
	@echo -en "\\r		  ${BGREEN}$(NAME)${DEFCL}        ✔  ${BGREEN}./$(NAME)${DEFCL}${DEL_R}\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(INCLUDES) $(LINKER)
	@rm -f .tmp
endif

$(MLX_DIR):
	@git clone https://github.com/codam-coding-college/MLX42.git
	@mkdir -p MLX42/build

$(MLX_LIB):
	@cmake -B $(MLX_DIR)/build $(MLX_DIR)
	@$(MAKE) -C MLX42/build

$(MAC_BREW):
	@echo "${CYAN}installing brew...${DEFCL}"
	@curl -fsL https://rawgit.com/kube/42homebrew/master/install.sh | zsh;
	@source ~/.zshrc
	@brew install readline
	@echo ""

$(MAC_GLFW):
	@echo "${CYAN}installing glfw...${DEFCL}"
	@brew install glfw
	@echo ""

${HEADER}:
# @if [ ! -f ".header" ]; then												\
# 	echo 	"$(BLUE) __  __ _       _     _          _ _ ";					\
# 	echo 	"|  \/  (_)_ __ (_)___| |__   ___| | $(CYAN)|";					\
# 	echo 	"$(BLUE)| |\/| | | '_ \| / __| '_ \ / $(CYAN)_ \ | |";			\
# 	echo 	"$(BLUE)| |  | | | | | | \$(CYAN)__ \ | | |  __/ | |";			\
# 	echo 	"$(BLUE)|_|  |_|$(CYAN)_|_| |_|_|___/_| |_|\___|_|_|";			\
# 	echo	"$(BCYAN)	    	       by Talea & Max$(DEFCL)";				\
# 	echo	"";																\
# 	touch .header;															\
# fi

clean: ${HEADER}
	@rm -f .header
	@echo -en "clean objs";
	@$(MAKE) clean -C src/libft
	@if find $(OBJ_DIR) -type f -name '*.o' -delete > /dev/null 2>&1; then		\
		echo -en "\\r		  $(NAME)   	   🗑  ${RED}$(OBJ_DIR)/${DEFCL}${DEL_R}";\
	fi
	@echo -e "\n";
	@if find $(OBJ_DIR) -type d -empty -delete > /dev/null 2>&1; then			\
		:;																		\
	fi

fclean: clean ${HEADER}
	@echo -en "clean bins"
	@$(MAKE) fclean -C src/libft
	@if find $(LIB_DIR) -type d -empty -delete > /dev/null 2>&1; then			\
		:; \
	fi
	@if [ -f "${NAME}" ]; then													\
 		rm -f ${NAME};															\
		echo -e "\\r		  $(NAME)   	   🗑  ${RED}$(NAME)${DEFCL}${DEL_R}"; \
	fi
	@echo -en "\n";


header_c:
	@rm -f .header

# test:
# 	@cd tests && bash tester.sh a

re: fclean all

.INTERMEDIATE: header_c

.PHONY: all clean fclean re bonus