# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoca <okoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 19:32:31 by okoca             #+#    #+#              #
#    Updated: 2024/07/28 08:45:33 by okoca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SHELL=  /bin/bash

MAKEFLAGS += --no-print-directory

Black           =   $(shell echo -e "\033[0;30m")
FBlack          =   $(shell echo -e "\033[1;30m")
Red             =   $(shell echo -e "\033[0;31m")
FRed            =   $(shell echo -e "\033[1;31m")
Green           =   $(shell echo -e "\033[0;32m")
FGreen          =   $(shell echo -e "\033[1;32m")
Brown/Orange    =   $(shell echo -e "\033[0;33m")
FBrown/Orange   =   $(shell echo -e "\033[1;33m")
FYellow         =   $(shell echo -e "\033[1;33m")
Yellow          =   $(shell echo -e "\033[0;33m")
Blue            =   $(shell echo -e "\033[0;34m")
FBlue           =   $(shell echo -e "\033[1;34m")
Purple          =   $(shell echo -e "\033[0;35m")
FPurple         =   $(shell echo -e "\033[1;35m")
Cyan            =   $(shell echo -e "\033[0;36m")
FCyan           =   $(shell echo -e "\033[1;36m")
FWhite          =   $(shell echo -e "\033[1;37m")
White           =   $(shell echo -e "\033[0;37m")
RESET           =   $(shell echo -e "\033[0m")
TICK            =   $(shell echo -e "\xE2\x9C\x94")

CC = cc

SRC_DIR = src/

INCLUDES_DIR = includes

MLX= mlx

LIBFT = libft

CFLAGS = -Wall -Werror -Wextra -I${INCLUDES_DIR} -I${MLX} -I${LIBFT} -g

LDFLAGS = -L${MLX} -L${LIBFT} -lmlx_Linux -lXext -lX11 -lm -lbsd -lft

LIBFT_TARGET = ${LIBFT}/libft.a

MLX_TARGET = ${MLX}/libmlx.a

SRCS_M = main.c map.c

SRCS_OTHER =

SRC 		= src/

OTHER_PATH	= src/other/

SRCS		= $(addprefix $(SRC), $(SRCS_M)) \
		  $(addprefix $(OTHER_PATH), $(SRCS_OTHER)) \

# BIN = ./bin

OBJS = ${SRCS:.c=.o}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${MLX_TARGET} ${LIBFT_TARGET}
	@echo "$$BANNER"
	@echo -e "${FRed}\n>>>Building ${FPurple}${NAME}${RESET}${Red}...${RESET}"
	@${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}
	@echo "${FGreen}   Done [${TICK}]"
	@echo "${RESET}"


all: ${NAME}

${MLX_TARGET}:
	@echo -e "\n$(FYellow)#################$(FRed) Building ${FPurple}$(MLX) $(FYellow)##################\n"
	@make -C ${MLX}
	@echo -e "${FGreen}                     Done [${TICK}]\n"
	@echo "$(FYellow)------------------------------------------------------"
	@echo "${RESET}"

${LIBFT_TARGET}:
	@echo -e "\n$(FYellow)##################$(FRed) Building ${FPurple}$(LIBFT) $(FYellow)###################\n"
	@make -C ${LIBFT}
	@echo -e "${FGreen}                     Done [${TICK}]\n"
	@echo "$(FYellow)------------------------------------------------------"
	@echo "${RESET}"

clean:
	@echo "$(FRed)Cleaning $(MLX)$(FGreen)             [$(TICK)]"
	@echo "$(FRed)Cleaning $(LIBFT)$(FGreen)                [$(TICK)]"
	@echo "$(FRed)Cleaning $(NAME)$(FGreen)              [$(TICK)]"
	@make clean -C ${MLX}
	@make clean -C ${LIBFT}
	@rm -f ${OBJS}
	@echo "${RESET}"

fclean: clean
	@echo "$(FRed)Full Cleaning $(NAME)$(FGreen)         [$(TICK)]"
	@echo "$(FRed)Full Cleaning $(LIBFT)$(FGreen)           [$(TICK)]"
	@make fclean -C ${LIBFT}
	@rm -f ${NAME}
	@echo "$(FYellow)------------------------------------------------------"
	@echo "${RESET}"

define BANNER
$(FRed)
     ___         ___                     ___         ___         ___
    /  /\       /  /\                   /  /\       /__/\       /  /\
   /  /:/_     /  /::\                 /  /::\      \  \:\     /  /:/_
  /  /:/ /\   /  /:/\:\  ___     ___  /  /:/\:\      \  \:\   /  /:/ /\
 /  /:/ /::\ /  /:/  \:\/__/\   /  /\/  /:/  \:\ _____\__\:\ /  /:/_/::\
/__/:/ /:/\:/__/:/ \__\:\  \:\ /  /:/__/:/ \__\:/__/::::::::/__/:/__\/\:\
\  \:\/:/~/:\  \:\ /  /:/\  \:\  /:/\  \:\ /  /:\  \:\~~\~~\\  \:\ /~~/:/
 \  \::/ /:/ \  \:\  /:/  \  \:\/:/  \  \:\  /:/ \  \:\  ~~~ \  \:\  /:/
  \__\/ /:/   \  \:\/:/    \  \::/    \  \:\/:/   \  \:\      \  \:\/:/
    /__/:/     \  \::/      \__\/      \  \::/     \  \:\      \  \::/
    \__\/       \__\/                   \__\/       \__\/       \__\/

$(RESET)
endef
export BANNER

re: fclean all

.PHONY: all clean fclean re
