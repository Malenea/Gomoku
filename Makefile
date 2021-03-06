CC		:= gcc

CFLAGS		+= -O2 -Wno-unused-parameter -Wno-sign-compare

DFLAGS		:= -g3 -W -Wall -Wextra -Werror

LDFLAGS		+= -lpthread -lncurses

RM		:= rm -rf

NAME		:= gomoku

DEBUG		:= gomoku_debug

HEADER_PATH	:= include/

SRCS_P		:= srcs/

COMM_SRCS_P	:= $(SRCS_P)common/

COMM_MSGS_P	:= $(COMM_SRCS_P)msgs/

OBJS_P		:= $(SRCS_P)objs/

COMM_OBJS_P	:= $(COMM_SRCS_P)objs/

SRCS		:= $(SRCS_P)gomoku.c\
		   $(SRCS_P)title.c\
		   $(SRCS_P)init.c\
		   $(SRCS_P)cmds.c\
		   $(SRCS_P)ia_preprocess.c\
		   $(SRCS_P)ia_process.c\
		   $(SRCS_P)arbitrary.c\
		   $(SRCS_P)rule_of_three.c\
		   $(SRCS_P)rule_of_two.c\
		   $(SRCS_P)key.c\
		   $(SRCS_P)print.c\
		   $(SRCS_P)close.c

COMM_SRCS	:= $(COMM_MSGS_P)trace.c\
		   $(COMM_MSGS_P)usage.c

TMP		:= gomoku.o\
		   title.o\
		   init.o\
		   cmds.o\
		   ia_preprocess.o\
		   ia_process.o\
		   arbitrary.o\
		   rule_of_three.o\
		   rule_of_two.o\
		   key.o\
		   print.o\
		   close.o

COMM_TMP	:= trace.o\
		   usage.o

OBJS		:= $(OBJS_P)gomoku.o\
		   $(OBJS_P)title.o\
		   $(OBJS_P)init.o\
		   $(OBJS_P)cmds.o\
		   $(OBJS_P)ia_preprocess.o\
		   $(OBJS_P)ia_process.o\
		   $(OBJS_P)arbitrary.o\
		   $(OBJS_P)rule_of_three.o\
		   $(OBJS_P)rule_of_two.o\
		   $(OBJS_P)key.o\
		   $(OBJS_P)print.o\
		   $(OBJS_P)close.o

COMM_OBJS	:= $(COMM_OBJS_P)trace.o\
		   $(COMM_OBJS_P)usage.o

red=`tput setaf 1`
green=`tput setaf 2`
blue=`tput setaf 6`
bold=`tput bold`
uline=`tput smul`
reset=`tput sgr0`

all: 		$(NAME)

$(NAME):
		@echo "${bold}${green}Compiling binary${reset}"
		@if [ -d "./srcs/objs" ]; then \
		echo "${red}server objs exists, proceeding with make${reset}"; else \
		mkdir "./srcs/objs"; \
		fi
		@if [ -d "./srcs/common/objs" ]; then \
		echo "${red}common objs exists, proceeding with make${reset}"; else \
		mkdir "./srcs/common/objs"; \
		fi
		@echo "${green}======================================================================${reset}"
		$(CC) -c $(SRCS) $(COMM_SRCS) $(CFLAGS) -I$(HEADER_PATH)
		@mv $(TMP) $(OBJS_P)
		@mv $(COMM_TMP) $(COMM_OBJS_P)
		$(CC) -o $(NAME) $(OBJS) $(COMM_OBJS) $(LDFLAGS)
		@echo "${green}======================================================================${reset}"

debug:		$(DEBUG)

$(DEBUG):
		@echo "${bold}${green}Compiling debug binary all warnings treated as errors${reset}"
		@if [ -d "./srcs/objs" ]; then \
		echo "${red}server objs exists, proceeding with make${reset}"; else \
		mkdir "./srcs/objs"; \
		fi
		@if [ -d "./srcs/common/objs" ]; then \
		echo "${red}common objs exists, proceeding with make${reset}"; else \
		mkdir "./srcs/common/objs"; \
		fi
		@echo "${green}======================================================================${reset}"
		$(CC) -c $(SRCS) $(COMM_SRCS) $(CFLAGS) -I$(HEADER_PATH)
		@mv $(TMP) $(OBJS_P)
		@mv $(COMM_TMP) $(COMM_OBJS_P)
		$(CC) -o $(DEBUG) $(OBJS) $(COMM_OBJS) $(LDFLAGS) $(DFLAGS)
		@echo "${green}======================================================================${reset}"

clean:
		@echo "${blue}Cleaning objects .o${reset}";
		@$(RM) $(OBJS) $(COMM_OBJS)
		@if [ -d "./srcs/common/objs" ]; then \
		rm -rf "./srcs/common/objs"; else \
		echo "${red}common objs not found, proceeding${reset}"; \
		fi
		@if [ -d "./srcs/objs" ]; then \
		rm -rf "./srcs/objs"; else \
		echo "${red}objs not found, proceeding${reset}"; \
		fi
		@echo "${blue}Cleaning temporary objects ~ and #${reset}";
		@echo "${blue}======================================================================${reset}"
		@find . -name '*~' -print -delete -o -name '#*#' -print -delete
		@echo "${blue}======================================================================${reset}"

fclean:		clean
		@echo "${blue}Cleaning objects binary${reset}";
		@$(RM) $(NAME)

debugclean:	clean
		@echo "${blue}Cleaning objects binary${reset}";
		@$(RM) $(DEBUG)

re: 		fclean all

red:		debugclean debug

.PHONY: 	all debug clean flcean debugclean re red
