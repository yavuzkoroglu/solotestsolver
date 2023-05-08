CC=cc
INCLUDE=-Iinclude
SRC=src/*.c
EXECUTABLE=bin/solotestsolver.out
CONSTFLAGS=-std=c99 -Weverything -Wno-poison-system-directories
release: bin compile

debug: bin; @\
    cc ${CONSTFLAGS} -g ${INCLUDE} ${SRC} -o ${EXECUTABLE}

bin: ; @\
    mkdir bin

compile: ; @\
    cc ${CONSTFLAGS} -O3 ${INCLUDE} ${SRC} -o ${EXECUTABLE}
