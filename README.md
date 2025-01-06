# Letter Boxed Solver

This project is a solution checker for the New York Times puzzle **Letter Boxed**, implemented in **C**. The program validates user inputs against the puzzle rules, ensuring correctness while offering a seamless, command-line-based interface.

## Repository Name

**letter-boxed-solver**

## Overview

Letter Boxed is a word game where players form words to connect letters on a board while adhering to specific rules. This solver ensures:
- All rules of the game are followed.
- Solutions are validated against a dictionary.
- Board integrity is maintained.

## Features

- **Validation Rules**:  
  - Letters must only come from the board.  
  - Consecutive letters cannot come from the same side.  
  - Each word must start with the last letter of the previous word.  
  - Words must exist in the provided dictionary.  
  - All letters on the board must be used at least once.  
- **Dynamic Memory Management**: Handles boards, dictionaries, and user inputs of varying sizes.  
- **Trie Implementation**: Efficient dictionary lookup.  
- **Robust Error Handling**: Catches invalid boards, incorrect inputs, and missing files.  

## Learning Objectives

- Master file I/O, string processing, and memory allocation in C.  
- Re-familiarize with C's syntax and dynamic memory management.  
- Gain hands-on experience with simple data structures like tries.  
- Work in a Linux-based development environment.  

## Installation

Clone the repository and compile the code:  
```bash
git clone https://github.com/yourusername/letter-boxed-solver.git
cd letter-boxed-solver
make
```

## Usage

Run the program with a board file and a dictionary file:  
```bash
./letter-boxed <board_file> <dictionary_file>
```

### Input Format
- **Board File**: Each line represents one side of the board.  
- **Dictionary File**: Each line contains one word.  
- **Solution Input**: Provide words one per line via standard input (STDIN).  

### Example
```bash
$ cat board.txt
rok
edn
lci
wfa

$ cat dictionary.txt
flan
now
wreck
kid

$ ./letter-boxed board.txt dictionary.txt
flan
now
wreck
kid
Correct
```

## Code Structure

### Key Files
- `letter-boxed.c`: Main implementation file.  
- `Makefile`: Automates the build process.  
- `README.md`: Project documentation.  

### Compilation Flags
The code is compiled with the following flags for maximum safety and compliance:  
```bash
-std=c17 -O2 -Wall -Wextra -Werror -pedantic
```

## Implementation Details

### Board
- Read input line by line using `getline`.  
- Validate board for character uniqueness and integrity.  

### Dictionary
- Implemented using a **trie** for efficient word search.  
- Dynamically build the dictionary from the input file.  

### Solution Validation
1. Check if letters are present on the board.  
2. Ensure the first letter of a word matches the last letter of the previous word.  
3. Validate against dictionary using trie lookup.  
4. Detect consecutive usage of letters from the same side.  

### Final Validation
- Use `did_we_win` to verify if all letters on the board were used.  

## Example Output

### Invalid Board
```bash
$ ./letter-boxed invalid_board.txt dict.txt
Invalid board
```

### Incorrect Word
```bash
$ ./letter-boxed board.txt dict.txt
flan
wrecked
Used a letter not present on the board
```

### Successful Solution
```bash
$ ./letter-boxed board.txt dict.txt
flan
now
wreck
kid
Correct
```

## Acknowledgments
This project was inspired by **John Shawger**’s original assignment for **CS537, Fall 2024** at the University of Wisconsin-Madison.  

## Author
**Gaurav Batra**  
- Email: [gbatra3@wisc.edu](mailto:gbatra3@wisc.edu)  
- Wisc ID: 9087090024  
- CS Login: gbatra  
```
