AR			= ar rcs

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++20 -ggdb -MMD -MP

HEADERS		= ./headers
SRC_DIR		= ./srcs
OBJ_DIR		= ./objs

CXXFLAGS += -I$(HEADERS) -I../headers/math -I../headers/utils

SRCS		=	ObjParser.cpp		\
				MtlParser.cpp		\
				Elements.cpp		\
				Groups.cpp			\
				Material.cpp		\
				MtlMapOptions.cpp	\
				error.cpp

OBJS		= $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS		= $(OBJS:.o=.d)

NAME		= libobjparser.a

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
