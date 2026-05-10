*This project has been created as part of the 42 curriculum by fjose-hi.*

# Description

`get_next_line` is a project developed as part of the 42 curriculum that consists of creating a function capable of reading and returning one line at a time from a file descriptor.

The goal of this project is to deepen the understanding of:

- Static variables
- File descriptors
- Memory management
- Buffer handling
- Reading from files efficiently
- String manipulation in C

The project reproduces behavior commonly required in low-level systems programming, where data must be processed incrementally instead of loading an entire file into memory at once.

The final result is a reusable function:

```c
char *get_next_line(int fd);


which reads a file descriptor line by line, returning one line per function call until the end of the file is reached.

---

# Features

## Main Functionality

- Reads one line at a time from a file descriptor
- Handles files of any size
- Supports multiple consecutive calls
- Correctly handles newline characters
- Efficient memory usage through buffered reading
- Works with standard input, files, and pipes

---

# Project Structure

```text
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_bonus.h
└── get_next_line_utils_bonus.c
```

---

# Algorithm & Data Structure Explanation

## Buffered Reading Algorithm

The implementation uses a buffered incremental reading algorithm.

Instead of reading the entire file at once, the function reads chunks of data using the read() system call and stores them temporarily until a complete line is found.

The algorithm works as follows:

1. Allocate a buffer of size BUFFER_SIZE
2. Read data from the file descriptor
3. Store the read content into a static variable
4. Continue reading until a newline (\\n) or EOF is found
5. Extract the next complete line
6. Preserve remaining unread content for the next function call
7. Return the extracted line

This approach was chosen because:

- It minimizes memory usage
- It efficiently handles large files
- It avoids unnecessary reads
- It allows continuous sequential reading
- It mirrors real-world stream processing behavior

---

## Static Variable Usage

A static variable is used to preserve unread content between function calls.

This is necessary because a line may not be fully read in a single read() operation, especially when:

- The line is larger than BUFFER_SIZE
- Multiple lines are read at once
- Reading from streams or pipes

The static buffer ensures continuity between calls while maintaining correct line extraction behavior.

---

## Bonus Part

The bonus implementation supports multiple file descriptors simultaneously.

This is achieved by:

- Using independent static storage for each file descriptor
- Managing separate buffered states
- Allowing interleaved reads between multiple files

This approach improves scalability and flexibility.

---

# Instructions

## Clone the Repository

```bash
git clone https://github.com/felipehillebrand-ops/get_next_line.git
cd get_next_line
```

---

## Compilation

This project does not include a Makefile.
You must compile the files manually using cc.

Basic compilation example:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

If you are using the bonus version, compile it with:

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

---

## Using the Function

Include the header in your project:

```c
#include "get_next_line.h"
```

Compile your project:

```bash
cc main.c get_next_line.c get_next_line_utils.c
```

---

## Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

---

# Technical Choices

This project follows the requirements defined by the 42 subject:

- Written entirely in C
- Compiled with the flags:

```bash
-Wall -Wextra -Werror
```

- No global variables
- Fully compliant with the 42 Norm
- Uses buffered reading with read()
- Dynamic memory allocation handled manually
- Static variables used for persistent state management

---

# Testing

The project can be tested using:

- `norminette`
- Custom test files
- Community get_next_line testers

Example:

```bash
norminette
```

---

# Resources

## Documentation & References

- Linux Manual Pages (man read)
- Linux Manual Pages (man open)
- 42 Subject PDF for get_next_line

---

## AI Usage Disclosure

AI tools were used during this project for:

- Reviewing README structure and formatting
- Clarifying concepts related to buffered reading
- Improving documentation quality and wording
- Verifying explanations of file descriptor behavior

All implementation, debugging, testing, and final validation of the code were completed manually.

---

# Learning Outcomes

Through this project, the following concepts were strengthened:

- File descriptor manipulation
- Buffered reading
- Static variables
- Dynamic memory allocation
- String manipulation
- Sequential data processing
- Defensive programming
- Resource management

---

# License

This project was developed for educational purposes as part of the 42 curriculum.

---

# Author

Felipe José Hillebrand

GitHub: https://github.com/felipehillebrand-ops
