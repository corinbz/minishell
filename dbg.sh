#!/bin/bash

make
valgrind --leak-check=full --track-origins=yes ./minishell
#valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./minishell