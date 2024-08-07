PROJ_NAME=pokimun

C_SOURCE=$(wildcard ./src/*.c)

H_SOURCE=$(wildcard ./src/*.h)

OBJ=$(subst .c,.o,$(subst src,obj,$(C_SOURCE)))

CC=gcc

CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic  \
		 -std=c11

RM = rm -rf

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
		$(CC) $^ -o $@
		
./obj/%.o: ./src/%.c ./src/%.h
		$(CC) $< $(CC_FLAGS) -o $@
	
./obj/main.o: ./src/main.c $(H_SOURCE)
		$(CC) $< $(CC_FLAGS) -o $@
	
objFolder:
	@ mkdir -p obj

clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ rmdir obj

.PHONY: all clean
