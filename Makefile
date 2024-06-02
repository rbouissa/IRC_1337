CXX = c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g
RM		= rm -f
NAME	= IRCSERVER
SRC		= autentification.cpp startConnection.cpp pars_cmd_Client.cpp main.cpp\


OBJ	= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re:	fclean all