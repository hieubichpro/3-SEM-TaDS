.PHONY : all run clean objdir

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

CC := gcc
CFLAGS := -std=gnu99 -I$(INC_DIR) -Wall -Werror -pedantic

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

EXEC := app.exe


all: $(EXEC)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

objdir:
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c objdir
	@$(CC) $(CFLAGS) -c $< -o $@

$(INC_DIR)/%.h:

clean:
	@$(RM) $(EXEC) ${OUT_DIR}/*
	@rm -rf $(OUT_DIR)