# Compiler and flags
CC = mpicc
CFLAGS = -Wall -g -O2
LDFLAGS = -lm

# Source and object files
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = array_gen.h bitonicMPI.h serial_qsort.h sortnmerge.h

# Output binary
TARGET = main

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Help target for usage information
help:
	@echo "Usage:"
	@echo "  make           - Build the program."
	@echo "  make clean     - Clean up build files."
	@echo "  mpirun -np <num_processes> ./main <arg1> <arg2>"
	@echo "    - <num_processes>: Number of MPI processes."
	@echo "    - <arg1>, <arg2>: User-supplied arguments."

# Phony targets
.PHONY: all clean help

