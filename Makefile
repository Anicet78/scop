CXX			= c++
CXXFLAGS	= -std=c++20 -MMD -MP -ggdb -Wall -Wextra

PARSER_DIR	= ./objParser
PARSER_LIB	= $(PARSER_DIR)/libobjparser.a

HEADERS		= -I./headers -I./headers/math -I./headers/utils -I$(PARSER_DIR)/headers
SRC_DIR		= ./srcs
OBJ_DIR		= ./objs

LIBS		= -lglfw -lGL

CXXFLAGS += $(HEADERS)

SRCS		=	main.cpp \
				openGL/openGL.cpp

OBJS		= $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS		= $(OBJS:.o=.d)

NAME		= scop

all: $(PARSER_LIB) $(NAME)

$(PARSER_LIB):
	@$(MAKE) -C $(PARSER_DIR)

$(NAME): $(PARSER_LIB) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) -L$(PARSER_DIR) -lobjparser -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(PARSER_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(PARSER_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
