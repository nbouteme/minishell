NAME = minishell
TYPE = prog

MODULES = src
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS = -Wall -Wextra -Werror -flto -Ofast -march=native -mtune=native -ffinite-math-only -funsafe-math-optimizations -fno-math-errno  -ffast-math
LFLAGS = $(CFLAGS)
INCLUDE_DIRS = $(PKG_DIR)/include
DEPS = libft

OUTPUT = $(NAME)
src_CC = gcc
