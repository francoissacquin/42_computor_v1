NAME = computor

CC = c++
CC_FLAGS = -Wall -Wextra -Werror


SRCS =	main.cpp \
		polynomial_parsing/input_char_check.cpp \
		polynomial_parsing/polynomial_parser.cpp \
		polynomial_solver/polynomial_solver.cpp


OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs
DEP = $(OBJS:%.o=%.d)
HEADER = -I ./includes/

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