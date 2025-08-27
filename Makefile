# ==============================
#   Simple Makefile — main.c
# ==============================

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11
TARGET  = server
SRC     = main.c

# Colors
RESET   = \033[0m
GREEN   = \033[32m
CYAN    = \033[36m
RED     = \033[31m

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "$(CYAN)Compiling $(SRC) -> $(TARGET)...$(RESET)"
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "$(GREEN)Build successful!$(RESET)"

run: $(TARGET)
	@echo "$(CYAN)Running ./$(TARGET)$(RESET)"
	@./$(TARGET)

clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(TARGET)

re: clean all
