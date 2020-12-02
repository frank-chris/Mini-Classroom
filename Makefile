# Usage:
# make all		 # compile all files 
# make clean # cleanup

.PHONY = all clean

CC = g++

LINKERFLAG = -lpthread

S_SRCS := $(wildcard server_src/*.cpp)
C_SRCS := $(wildcard client_src/*.cpp)

S_BIN := server_src/server
C_BIN := client_src/client

all: ${S_BIN} ${C_BIN}

${S_BIN}: ${S_SRCS}
	@echo "Building..."
	${CC} -o $@ $^ ${LINKERFLAG}

${C_BIN}: ${C_SRCS}
	@echo "Building..."
	${CC} -o $@ $^ ${LINKERFLAG}

clean:
	@echo "Cleaning..."
	@rm -rvf ${S_BIN} ${C_BIN}
	@rm -rvf Users Classrooms

cleanf:
	@rm -rvf Users Classrooms