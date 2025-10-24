# Basic Memory Management
A very basic and barebones memory management library in C89, POSIX compliant and only for Linux.
It is for educational purposes and it's not production ready.


## Dependencies
1. Git
2. C compiler that supports inline assembly


## Supported Architectures
1. x86-64
2. x86-32
3. ARM64
4. ARM32
5. RISC-V 64
6. RISC-V 32


## Download/Installation
1. Choose a folder where to download it
2. Open Git Bash in it
3. Type or copy and paste: git clone https://github.com/iivanov444/Basic-Memory-Management


## Usage
There is a "headers" subfolder in each folder containing the library used.
The name of the main header file is "custom_unistd.h", it's enough to include only it.


## Notes
"custom_" and "CUSTOM_" prefixes are used to avoid conflicts with standard variables, functions and macros.
Compiles with flags -std=c89 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion
-Wnull-dereference -fsanitize=address -fsanitize=leak with no warnings on GCC 15.2.1 20250813 and Clang 21.1.4 desktop Linux x86-64.
Also in "3. first fit malloc/first_fit_malloc.c" you can add #include <stdio.h> and an int main() section
with printf("%ld\n", BLOCK_SIZE); to see what memory block size (with alignment) you have.


## License
BSD Clause 3
