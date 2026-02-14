# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 16:54:30 by lomont            #+#    #+#              #
#    Updated: 2026/02/14 05:32:39 by lomont           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

C++ = g++-15
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g

RM = rm -f

SRC = ./main.cpp \
		./PmergeMe.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(C++) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(C++) $(CFLAGS) -c $< -o $@

make: make all

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
