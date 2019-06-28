SRC		=		src/main.cpp					\
				src/Aspirateur.cpp				\

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++14 -I ./include

CC		=	g++

NAME	=	aspirateur

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)  $(CXXFLAGS)

clean:
		rm -f $(OBJ)

fclean: 	clean
		rm -f $(NAME)

re:		fclean all
