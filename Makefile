# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoca <okoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 19:32:31 by okoca             #+#    #+#              #
#    Updated: 2024/08/02 17:54:57 by okoca            ###   ########.fr        #
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

CUSTOM_FLAGS = -D USE_CUSTOM_FONT=1

CFLAGS = -O3 -funroll-loops -std=c99 -Wall -Werror -Wextra -MMD -I${INCLUDES_DIR} -I${MLX} -I${LIBFT} -g

LDFLAGS = -L${MLX} -L${LIBFT} -lmlx_Linux -lXext -lX11 -lm -lbsd -lft

LIBFT_TARGET = ${LIBFT}/libft.a

MLX_TARGET = ${MLX}/libmlx.a

SRCS_M = main.c

SRCS_INIT = ctx.c map.c textures.c

SRCS_HELP = free.c utils.c

SRCS_REND = render.c raytracer.c pixel.c extra.c

SRCS_INPUT = keys.c mouse.c

SRCS_PARSER = input_validation.c \
		 pars_cleanup.c \
		 parse.c \
		 process_cub.c \
		 read_utils.c \
		 init_parser.c \
		 map_utils.c \
		 process_map.c \
		 flood_map.c

SRC 		= src/

INIT_PATH	= src/init/

HELP_PATH	= src/helper/

REND_PATH	= src/render/

PARSER_PATH	= src/parser/

INPUT_PATH	= src/input/

SRCS		= $(addprefix $(SRC), $(SRCS_M)) \
		  $(addprefix $(INIT_PATH), $(SRCS_INIT)) \
		  $(addprefix $(HELP_PATH), $(SRCS_HELP)) \
		  $(addprefix $(REND_PATH), $(SRCS_REND)) \
		  $(addprefix $(PARSER_PATH), $(SRCS_PARSER)) \
		  $(addprefix $(INPUT_PATH), $(SRCS_INPUT)) \

OBJS = ${SRCS:.c=.o}

DEP = ${OBJS:%.o=%.d}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${MLX_TARGET} ${LIBFT_TARGET}
	@echo "$$BANNER"
	@echo -e "${FRed}\n>>>Building ${FPurple}${NAME}${RESET}${Red}...${RESET}"
	@${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}
	@echo "${FGreen}   Done [${TICK}]"
	@echo "${RESET}"

-include $(DEP)

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
	@rm -f ${DEP}
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
 ██████╗ ██████╗ ██████╗ ██████╗ ██████╗
██╔════╝██╔═══██╗██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝
$(RESET)
endef
export BANNER

re: fclean all

.PHONY: all clean fclean re
