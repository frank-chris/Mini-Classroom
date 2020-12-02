# Usage:
# make all		 # compile all files 
# make clean # cleanup

.PHONY = all clean mininet cleanf

CC = g++
PYTHON = python3

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

mininet: all
	@mkdir mininet_test/workloads
	${PYTHON} mininet_test/create_workload.py
	sudo ${PYTHON} mininet_test/mininet_testing.py

clean:
	@echo "Cleaning..."
	@sudo rm -rvf ${S_BIN} ${C_BIN}
	@sudo rm -rvf Users Classrooms mininet_test/workloads

cleanf:
	@sudo rm -rvf Users Classrooms mininet_test/workloads