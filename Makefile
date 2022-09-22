CC = g++
CFLAGS = -W -Wall -ansi -g
LIBS =
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BUILDDIR ?= ./build
SRCDIRS ?= ./src

SRCS = $(shell find $(SRCDIR) -name *.cpp)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)

EXEC = sfml-app

play: $(EXEC)
	./$(BUILDDIR)/$<

$(EXEC): $(OBJS)
	$(CC) $^ -o $(BUILDDIR)/$@ $(LDFLAGS)

# Assembly
$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	-c $< -o $@

# C srcs
$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -r build/src
	rm -rf *.o
mrpropre:
	rm -r build/*

MKDIR_P ?= mkdir -p