NAME = computor

CC = c++
DEBUG_FLAG = -g -Wfatal-errors -Wpedantic -Wconversion -Wshadow
CC_FLAGS = -Wall -Wextra -Werror


SRCS =	main.cpp \
		input_char_check.cpp \
		polynomial_parser.cpp


OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs
DEP = $(OBJS:%.o=%.d)
HEADER = -I .

all				: 	${NAME}
$(NAME) 		: 	$(OBJS)	
						mkdir -p $(@D)
						echo Compiling...
						$(CC) $(CC_FLAGS) $^ -o $@
-include $(DEP)
$(OBJS_DIR)/%.o	:	%.cpp
						mkdir -p $(@D)
						$(CC) $(CC_FLAGS) ${HEADER} -MMD -c $< -o $@


clean	:
				rm -rf $(OBJS_DIR) 
fclean	:	clean
				rm -rf ${NAME}  
			echo fclean
re		:	fclean
				make all

PHONY : all clean fclean re