# Set the base image to use
FROM gcc:latest
# Copy the C program into the container
COPY lab9_cprogram.c .
# Compile the C program
RUN gcc -o lab9 lab9_cprogram.c
# Set the command to run when the container starts
CMD ["./lab9"]
