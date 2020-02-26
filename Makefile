CC=gcc
SRC_DIR=src/
HDR_DIR=include/
OBJ_DIR=bin/
EXE_DIR=
TEST_DIR=test/
INC_FLAG=-I./$(HDR_DIR)
CFLAGS= -g

DEPS=board_generator.h boggle.h dictionary.h scoreboard.h word_checker.h test.h
_DEPS=$(patsubst %,$(HDR_DIR)%,$(DEPS))

OBJS=board_generator.o boggle.o dictionary.o scoreboard.o word_checker.o main.o
_OBJS=$(patsubst %,$(OBJ_DIR)%,$(OBJS))

TEST_OBJS=harness.o structureCheck.o boundaryCheck.o flowCheck.o board_generator.o boggle.o dictionary.o scoreboard.o word_checker.o
_TEST_OBJS=$(patsubst %,$(OBJ_DIR)%,$(TEST_OBJS))

boggle: $(OBJS)
	$(CC) -o $(EXE_DIR)$@ $(CFLAGS) $(_OBJS)

%.o: $(SRC_DIR)%.c $(_DEPS)
	$(CC) -c -o $(OBJ_DIR)$@ $< $(CFLAGS) $(INC_FLAG)

test: harness
	./harness

harness: $(TEST_OBJS)
	$(CC) -o $(EXE_DIR)$@ $(CFLAGS) $(_TEST_OBJS)

%.o: $(TEST_DIR)%.c $(_DEPS)
	$(CC) -c -o $(OBJ_DIR)$@ $< $(CFLAGS) $(INC_FLAG)


clean:
	rm $(EXE_DIR)boggle $(OBJ_DIR)*.o

help:
	#
	#  to use: type "make" to compile the ".o" files and the executable
	#
	#  "Makefile" should be in the root of the project.
	#  if all of the ".c" files are in "src/" and all of the headers
	#  are in "include/" and there's an empty "bin/" directory, 
	#  the makefile should work with no modification.  
	#
	#  Otherwise, open "Makefile" and set SRC_DIR to the directory containing
	#  the ".c" files, set "HDR_DIR" to the directory containing the ".h" files
	#  and set OBJ_DIR to the directory where you'd like the .o files to be produced.
	#
	#  When setting the "DIR" variables, end the directory name with a "/" and make sure
	#  there are no trailing spaces.
	#  ex: good: "SRC_DIR=source/" bad: "SRC_DIR=source/ " or "SRC_DIR=source"
	#
	#  type "make clean" to delete all of the ".o" files and the executable
	#
