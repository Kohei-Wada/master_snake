OBJECTS = main.o game.o list.o ui.o getch.o snake.o
CFLAGS = -g -Wall 
LDLIBS = -pthread 
INCLUDE = -I include 
TARGET = main
SOURCES = $(OBJECTS: %c = %o)

LIBDIR = lib
OBJDIR = obj
SOURCEDIR = src
BINDIR = bin



all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET) : $(addprefix obj/, $(notdir $(OBJECTS))) 
	@if [ ! -d $(BINDIR) ]; then\
		mkdir $(BINDIR);\
	fi
	$(CC) $(CFLAGS)  -o $@ $^  $(LDLIBS)

$(OBJDIR)/%.o : $(SOURCEDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then\
		mkdir $(OBJDIR);\
	fi;
	$(CC) $(CFLAGS) $(LDLIBS) $(INCLUDE) -o $@ -c $< 

$(OBJDIR)/%.o : $(LIBDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then\
		mkdir $(OBJDIR);\
	fi;
	$(CC) $(CFLAGS) $(LDLIBS) $(INCLUDE) -o $@ -c $<
	

install:
	mkdir ~/.snake/
	touch ~/.snake/data
	cp $(BINDIR)/$(TARGET) ~/.snake/

clean :
	rm -f bin/$(TARGET) $(OBJDIR)/*
	rm -r ~/.snake
