## How to Build and Run the Compiler

Follow these steps to compile and execute the compiler using the commands provided in `commands.bat`:

### 1. Compile the Source Files

```sh
bison -d parser.y           # Generate parser source and header files
flex lexical.l              # Generate lexical analyzer source file
gcc -c SymbolTable.c -o SymbolTable.o   # Compile symbol table module
gcc -c parser.tab.c -o parser.o         # Compile parser module
gcc -c lex.yy.c -o lexical.o            # Compile lexical analyzer module
gcc -o compilateur SymbolTable.o lexical.o parser.o -lfl  # Link all modules into executable
```

### 2. Run the Compiler

To test the compiler with an example input file:

```sh
./compilateur < exemple.txt
```
<div align="center">

| ![Symbol Table](images/image.png) | ![Quadruplets Table](images/image-1.png) |
|:-------------------------:|:----------------------------------:|
| **Symbol Table**          | **Quadruplets Table (Before optimization)**              |

| ![Avant optimisation](images/image-2.png) | ![Apres optimisation](images/image-3.png) |
|:----------------------------------:|:----------------------------------:|
| **During optimization**             | **After optimization**             |

![Code Objet](images/image-4.png)
<br>
**Code Objet**

</div>


> **Note:** Make sure all dependencies (Bison, Flex, GCC) are installed and available in your system's PATH.
