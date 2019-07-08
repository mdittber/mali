CC=g++
CFLAGS=-Wall --std=c++17
PROGS=eigen get_pid monte_carlo_pi random_generator_class run_without_main while

all: eigen get_pid monte_carlo_pi random_generator_class run_without_main while
	@echo "Compiling finished!"

eigen: eigen.cpp
	${CC} ${CFLAGS} -o eigen eigen.cpp

get_pid: get_pid.cpp
	${CC} ${CFLAGS} -o get_pid get_pid.cpp

monte_carlo_pi: monte_carlo_pi.cpp
	${CC} ${CFLAGS} -pthread -o monte_carlo_pi monte_carlo_pi.cpp

random_generator_class: random_generator_class.cpp
	${CC} ${CFLAGS} -o random_generator_class random_generator_class.cpp

run_without_main: run_without_main.cpp
	${CC} ${CFLAGS} -nostartfiles -o run_without_main run_without_main.cpp

while: while.cpp
	${CC} ${CFLAGS} -pthread -o while while.cpp

clean:
	@rm -rf *.o
	@echo "Removed object files."
	@rm -f ${PROGS}
	@echo "Removed prgram files."
