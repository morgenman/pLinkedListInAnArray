# Implementing a Memory Pool
Dylan Morgen
morgendc203@potsdam.edu

# Required Documentation:

## Problem
In this assignment I implemented abstractPool. 
I also setup catch2, with moderate success. 

## Testing Criteria

### Test Input
To test, run ./build/test
Not all functions are testable this way, given that there are several functions
that print to the screen. 

### Expected Output
Unfortunately, Catch2 is very weird and the pig latin function is not passing.
Maybe you could illuminate me as to what I'm doing wrong?
Everything else should pass.

### Compilation and Execution Instructions
```make``` 
will make both executables. 

 
 
# Provided Documentation: 

## Introduction 
Starting with an /abstract class/ (you can read that as /interface/ in the Java sense), you will implement the memory subsystem for a simple linked list program. The program will insert and remove elements from a linked list of strings using your memory module.

## User Interface
This is a command-loop program that loops, reading one line at a time, and using the first letter of the line as a command and interpreting the remaining parts of the line as parameters when necessary.

The commands are:
- a <str> :: add <str> to an open string location, if there is one.
- d <ndx> :: delete the string at location <ndx>, if there is one.
- f :: memory pool to print its free list node numbers in order
- i <ndx> :: translate the string in <ndx> to Pig Latin. *NOT IMPLEMENTED* - part of your assignment.
- n <ndx> :: memory pool to print the nodes that make up this string with character, and the next node number.
- p :: print the string array with indices in use and contents.
- q :: quit
- s <ndx> <str> :: set the value of an in-use string to <str>.
- t :: toggle memory pool tracing of ~newNode~ and ~deleteNode~ calls.
- ? :: Display help message (also displayed after any unknown command).

Commands are read by the line so all parameters must appear on the same line and only one command can appear per line. There is no error checking on extra parameters.

## The Assignment
1. You must implement a class that implements all of the abstract member functions in ~src/memory/AbstractMemoryPool.h~
   - All member functions are virtual and abstract.
     - An abstract member function is indicated with = 0 at the end of the declaration.
   - Look at how to /inherit/ from a class and write a header file (probably in ~src/memory~) for your class. You can add any public or private members or functions to your class.
     - Provided code interacts with a memory pool through a pointer at the abstract class. That means that it does not call any functions other than those in the base class.
     - Implement /stub/ functions that do as little as possible (return false or null or do nothing) and get that to compile. Then uncomment the setting of the ~ListString~ pool in ~src/main/igpayAtinlay.cpp~.
   - The ~ListString~ class is *almost* complete (see below): you can use it to test your memory pool.
     - Your pool has an array of the ~Node~ type. No class outside of your pool can see that type. All other classes can see ~NodePtr~ which is actually an int. The constant ~nullNodePtr~ serves the purpose of ~nullptr~ for regular C++ pointers.
     - You are to keep track of free nodes on a free list. It is possible that getting that and the method to print the free list might be a good place to start (you can see what your free list looks like).
     - You need to be able to dump the nodes in a string.
     - You need to be able to allocate and deallocate nodes in any order.
2. You must implement the ~igpayAtinlay~ member function in the ~ListString~ class.
   - English vowels are (any case) {a,e,i,o,u}
   - If the first character of a "word" is not alphabetic (look for predicate functions to make this easy to check), leave the string unchanged.
   - Given a string starting with a letter: find the first vowel. Take off the prefix *before* the vowel (it might be empty) and move it to the end of the string (the remaining string, too, might be empty).
   - If there were no consonants rotated, append "way" to the end of the string; if consonants were rotated, then append "ay":
     - "1116" -> "1116"
     - "pig" -> "igp" -> "igpay"
     - "Latin" -> "atinL" -> "atinLay"
     - "umbrella" -> "umbrella" -> "umbrellaway"
   - The member function for doing this is a stub. You will modify ~src/list/ListString.cpp~ and can test it through the commands in the driver.

## Design Requirements
* Probably no need to add modules.
* You are implementing a new class.
    * This means adding a ~.h~ and a ~.cpp~ file. Since you're implementing a memory pool, ~src/memory~ seems a good place to put your code.
* Inside your pool, you have an *array* indexed by integers
* You are not to change the type of ~NodePtr~. Given a ~NodePtr~, ~n~, you would refer to the corresponding node as ~A[n]~ (assuming ~A~ is the name of the array of ~Node~ objects in your pool class).