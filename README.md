# Flex & Bison Compiler construction

## Introduction
This project is a custom programming language designed and implemented as part of my Bachelor's degree in Computer science. The language introduces unique syntax and features that facilitate working with numbers, strings, lists, and control structures. It also provides built-in functions for mathematical operations and user interaction.

## How to Use
### Prerequisites
To use this programming language, ensure you have the following dependencies installed:
- **Flex** (for lexical analysis)
- **Bison** (for syntax parsing)
- **GCC** (for compiling the generated C code)

#### Installation on Linux (Debian-based)
```sh
sudo apt update
sudo apt install flex bison gcc
```

#### Installation on macOS (using Homebrew)
```sh
brew install flex bison
```

### Compiling the Language
To compile the language, run:
```sh
make
```
This will build the executable file

### Running a Script
Once compiled, you can run a script written in this language using:
```sh
./synthax script1.txt script2.txt ...
```

## Language Manual
### Comments
```text
/-- this is a comment
    on multiple lines --/

--- this is a comment on a single line
```

### Variable Declaration
```text
num a = 10.5;   --- Defines a number variable, it can be assigned both integer and decimal numbers
roman r = 0MCXXII;   --- Defines a roman number, a 0 is required before the numbers to identify them as roman numerals
binary b = 0B1011001;    --- Defines a binary number, 0B is required before the numbers to identify the binary sequence
```

Assignments between numerical types are allowed:
```text
a = b;
b = r;
```

### Strings
```text
str string = <<hello#j>> + <<world!#k>>;
```
- Strings are enclosed in `<< >>`
- `#j` represents a tab, `#k` represents a newline
- Strings can be concatenated using `+`

### Lists
```text
list l = [1.5,3^0III,<<hello>> + <<world!>>,10];
```
- Lists can store different data types
- Operations can be performed when declaring a list

Concatenation and element addition:
```text
l = 2 + l;  --- Adds 2 at the beginning of the list
l = l + 2;  --- Adds 2 at the end of the list
l = l + l;  --- Concatenates two lists
```

### Operators
- `+` : Concatenation (for strings and lists), Addition (for numbers)
- `-` : Difference / Unary minus
- `*` : Multiplication
- `/` : Division
- `^` : Exponentiation
- `@` : Remainder
- `|a|` : Absolute value

### Logical Operators
```text
and, or, not
```

### Comparison Operators
```text
> , < , <= , >= , <> (not equal), == (equal)
```

### Print Function
```text
print(a, b, r, <<goodnight>>, l, sqrt(5), <<a#k>>);
```
- Allows multiple arguments separated by commas
- If arguments are variables, their values are printed unless enclosed in `<< >>`

### Control Flow
#### Whether/Otherwise Syntax
```text
whether [--- condition ---] then: {
    --- statements;
} otherwise: {
    --- statements;
}
```

#### When Syntax (Loop)
```text
when [--- condition ---] {
    --- statements ---;
}
```

#### Until Syntax
```text
when {
    --- statements ---;
} until [--- condition ---]
```

#### From Loop Syntax
```text
from [num i = 0 to n !> q] {
    print(i);
}
```
- The loop variable is declared within `from`
- `to` defines the upper bound (inclusive)
- `!>` defines the step increment

### User-Defined Functions
```text
define set(n) {
    give_back n;    --- Returns the value of the function
}
```
- The `define` keyword is used to declare functions
- No need to specify the return type or parameter types

### Built-in Functions
```text
sqrt(num)          --- Returns the square root of a number
exp(num)           --- Returns e raised to the power of a number
log(num)           --- Returns the logarithm of a number
fact(num)          --- Returns the factorial of a number
sin(num)           --- Returns the sine of a number
cos(num)           --- Returns the cosine of a number
tan(num)           --- Returns the tangent of a number
size(list)         --- Returns the number of elements in a list
get(list, index)   --- Returns an element of a list at a given index
input(<<text>>)    --- Displays a prompt and reads user input
split(str)         --- Splits a string into words and returns a list
count_char(str)    --- Counts the number of characters in a string
casual(num)        --- Generates a random number within a given range
```

## Contributing
If you would like to contribute to this project, feel free to fork the repository and submit a pull request. Suggestions and improvements are always welcome!
