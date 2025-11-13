# ==============================
#            CONFIG
# ==============================

NAME        := cub3D
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -MMD -MP
IFLAGS      := -Iincludes -Ilibft -Iminilibx-linux
LFLAGS      := -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz
BUILD_DIR   := build

# ==============================
#            FILES
# ==============================

SRC := \
  src/main.c \
  src/core/loop.c \
  src/core/run.c \
  src/events/events.c \
  src/init/init_game.c \
  src/init/init_mlx.c \
  src/init/init_player.c \
  src/init/init_textures.c \
  src/movement/movement.c \
  src/movement/movement_utils.c \
  src/movement/movement_sliding.c \
  src/movement/movement_subdiv.c \
  src/movement/movement_collision.c \
  src/movement/movement_player_loop.c \
  src/parser/parser.c \
  src/parser/parser_utils.c \
  src/parser/header_scan.c \
  src/parser/map_reader.c \
  src/parser/map_rect.c \
  src/parser/map_checker.c \
  src/parser/map_checker_utils.c \
  src/parser/color_parser.c \
  src/parser/player_spawn.c \
  src/parser/texture_checker.c \
  src/rendering/raycaster.c \
  src/rendering/raycaster_utils.c \
  src/rendering/render_walls.c \
  src/rendering/render_textures.c \
  src/rendering/render_floor_ceiling.c \
  src/utils/errors.c \
  src/utils/mlx_utils.c \
  src/utils/texture_utils.c \
  src/utils/timer.c

OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(BUILD_DIR)/, $(OBJ))
DEP := $(OBJ:.o=.d)

# ==============================
#            COLORS
# ==============================

BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

-include $(DEP)

# ==============================
#            RULES
# ==============================

all: $(NAME)

$(NAME): libft/libft.a minilibx-linux/libmlx.a $(OBJ)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)\n"
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LFLAGS)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

libft/libft.a:
	@$(MAKE) -C libft

minilibx-linux/libmlx.a:
	@$(MAKE) -C minilibx-linux

clean:
	@printf "$(YELLOW)\r🧹 Limpiando objetos...                $(RESET)\n"
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C libft clean || true
	@$(MAKE) -C minilibx-linux clean || true

fclean: clean
	@printf "$(YELLOW)\r🗑️  Borrando ejecutable...              $(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean || true
	@printf "$(GREEN)\r✅  Limpieza completa.                  $(RESET)\n"

re: fclean all

norm:
	@printf "$(YELLOW)\n🔍 Revisando con norminette...$(RESET)\n"
	norminette includes
	norminette $(SRC)

run: all
	@if [ -z "$(MAP)" ]; then \
		echo "Uso: make run MAP=maps/archivo.cub"; \
	else \
		./$(NAME) $(MAP); \
	fi

.PHONY: all clean fclean re norm run
.DEFAULT_GOAL := all
