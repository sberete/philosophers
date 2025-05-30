CFLAGS = -Werror -Wextra -Wall -MMD -g3 -pthread

INCLUDES = -Iincludes

SRC_DIR = src_bonus

OBJ_DIR = objs_bonus

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(notdir $(basename $(SRCS)))))

DEPENDS = $(OBJS:.o=.d)

NAME = philo_bonus

-include $(DEPEND)

.PHONY: all
all: $(NAME) 

$(NAME): $(OBJS)
			$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

re: fclean all