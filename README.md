# Programming Assignment: Sloc Project 

### Table of Contents
1. [Introduction](#introduction)
2. [Input](#input)
3. [Interface](#interface)
4. [Execution](#execution)
5. [System Modeling](#system-modeling)
6. [Output](#output)
7. [Assignment Grading](#assignment-grading)
8. [Authorship and Collaboration Policy](#authorship-and-collaboration-policy)
9. [Work Submission](#work-submission)


##  Introduction

In this programming assignment you should design and develop a program that counts single lines of source code, comments, and blank lines, from a single file or a directory of files, and prints out that information on the standard output.

This program is a terminal application that should receive the C/C++ source file or directory containing source files from the Command Line Arguments (CLA). Below you will find an example of expected output for a single C++ source file provided as input.
```
$ ./build/sloc src/main.cpp
Files processed: 1
----------------------------------------------------------------------------------------------------
Filename            Language        Comments        Blank           Code            All
----------------------------------------------------------------------------------------------------
src/main.cpp        C++             140 (29.9%)     43 (9.2%)       320 (68.4%)     468
----------------------------------------------------------------------------------------------------
```
This project may help you develop your object-oriented programming skills if you choose to model this application with classes. This assignment also relies heavily on [strings](https://en.cppreference.com/w/cpp/string/basic_string) and [stream](https://en.cppreference.com/w/cpp/io/basic_ostringstream) manipulation, [file streams](https://en.cppreference.com/w/cpp/io/basic_fstream), the processing and parsing of command line arguments. Of course, you are encouraged to choose convenient data structures such as **lists** (`vector` or `array`), as well as **dictionary**, to help improve your solution and make the problem easier to solve.

## Input

The main data input for the program is either a single _file name_ of a C/C++ program or a _directory_ containing C/C++ source files. 
Feel free to add support to other languages if you so desire.

## Interface

If you run `sloc` with no arguments, or with the flag `--help` or `-h` the program should display the _usage_ message to help the client to understand how to use the program.

```
$ ./build/sloc -h
Welcome to sloc, version 1.0, (c) 2022 Selan, DIMAp, UFRN.
Usage: sloc [options] file/directory
Options:
  -h/--help   Display this information.
```


## Execution

After receiving and parsing the command-line arguments, your program may first try to create a list of valid C/C++ source files based on the input source. If the source is just a file name, you may need to _extract_  the file extension to see if it matches the accepted supported file extensions, listed below:

+ `".cpp"`: a C/C++ program.
+ `".c"`: a C program.
+ `".h"`: a C/C++ header file.
+ `".hpp"`: a C++ header file.

On the other hand, if your source is a directory name, you will need to access all the file names inside the source directory, check if they have the supported extensions listed above, and include them into the list of valid C/C++ source files.
Support code to access and retrieve a list of files present in a directory will be provided with the GitHub repository of this assignment.

After your program has created a list of valid C/C++ source files (that might have only one file, for instance), the next step is to open each of those files and begin the counting task (explained in the next section).

When the counting process is done and finished for the entire list of files, your application should print to the standard output a **table** presenting the result of the counting **per file** with a grand total at the bottom of the table, in case your program received more than one input file.

In summary, your program should:
1. read the input source and create a list of valid files to process;
2. for each file in the list, count the individual lines of code, comments, and blank lines, and;
3. display the result of the counting into a single table, with information associated with each individual file.

### Single line of code, comments, and blank lines

A **single line of code** (sloc) is a line inside a source file that contains any C/C++ piece of code. It may be a line with just a "`{`", for instance, or a line with a "`for`" loop, for example.

A **blank line** is a line that is not inside a comment block and has no code nor any type of comment marks.

Program comments are statements that you can include in the C/C++ code to help anyone reading the source code.
C++ supports single-line and multi-line comments. All characters available inside any comment are ignored by C++ compiler.
C++ comments may start with /* and end with */. For example:
```c++
/* This is a comment */

/* 
 * C++ comments can also
 * span multiple lines
 * inside a block comment.
 *
*/
```

A comment can also start with "`//`", at the beginning of a line or after a C++ statement. All that comes after the "`//`" is considered a comment.
```c++
#include <iostream>
int main(void) {
  std::cout << "Hello world!\n"; // This is a single end line comment.
  // This is a comment that occupies an entire line.
  int x{0}; // another example.
  // 

  return 0;
}
```

Within a "`/*`" and "`*/`" block comment, the "`//`" characters have no special meaning and must be ignored. Similarly, within a single line "`//`" comment, the "`/*`" and "`*/`" have no special meaning.
Thus, it is possible to _"nest"_ one kind of comment within the other kind.
For example:
```c++
/* 
  Comment out a piece of code.

  for(int i{0}; i<10; i++ )
    std::cout << "(" << i+1 << "): Hello world!\n"; // prints Hello World
  /*
  /*  another nested comment. */
  */
*/
```

Additionally, any comment mark that appears  **inside** a string literal must also be ignored.
```c++
#include <iostream>
int main(void) {
  std::cout << "A comment in C++ beging with a " << "/*"
            << " and ends with a " << "*/" << std::end;
  // Another example.
  if ( str == "//") // The double slash inside if must be ignored.
    std::cout << "Found double slash\n";

  return 0;
}
```

But your program must have special care with some situations that might happened involving block comments.
For example, the code below
```c++
/* some comment */ int x = 0;
```
should be counted **both** as a comment and as a line of code.
The same goes for the code below
```c++
int x = 0; // This is both a comment and a sloc.
```
Another situation to look out for is when a multi line block comment ends and we still have a C/C++ statement on that line.
```c++
/* one
   two
   three */ int x = 0;
```
The code above should be counted as 3 lines of comment and 1 line of code.

### Dealing with multiple lines comment and nested comments w

So far we learned that in a source code it's possible to have nested comments spanning a single line or multiple lines.
To keep track of that and compute such lines as comments correctly, we need to maintain an integer value corresponding to the
comment nesting level (CNL).
The initial value for the CNL is zero, which means that there is no unmatched block comment.

Every time a multi line opening comment mark '`/*`' is found we increase the CNL. Similarly, when we find a multi line
closing comment mark '`*/`' we decrease the CNL.

One suggestion here is to create a function that receives the current line of code and the current CNL.
Then the function traverses the string, examining each individual character to decide how it should update the overall CNL.
Another task assigned to this function is to  **trim** out all the content that lies _inside_ a comment block.

The trimming process happens as follows:
If the CNL is zero, then it copies the current string character to the trimmed string.
On the other hand, if the CNL is not zero, the content is ignored and will not be sent to the trimmed string.

The end result is an updated CNL and a new trimmed string with all comment content removed (which could produce an empty string). Then the function should return both the new trimmed string to the client as well as the updated CNL.

On the client side, after the trimming is done, we test the CNL value. If it is greater than zero, it means we are inside a block comment. Therefore we count the current line as a comment. However, if the CNL is zero, it means we are outside a comment section. So we must compare the original string with the trimmed string to decide if the current line should count as a) a sloc, b) a sloc **and** a comment, or c) a blank line only.

## System Modeling

If you intend to follow the Object-Oriented Design (OOD) paradigm the first step is to identify which **entities** might help you model the problem. Because I assuming you have little or no experience in OOD I recommend that you begin to create at least on class or struct.

### The list of source files

We may need to create a **list** of input source files and their types. Filling in this list is your program's first task. This is done based on the input source information collected via Command Line Argument. Recall that if the client sends a single file this list will have only a single element; whereas, if the client provide a directory, this list may end up with various entries, one for each valid source code file found in that directory.

### The `FileInfo` class/struct

This class or struct represents the collection of information gathered from a source file. They are the file name, file type (C, C++, C/C++ header or C++ header), number of blank lines, number of comment lines, number of single lines of code, and the total number of lines of the file.

To store the file information for each input file, we will need a **dynamic list** of `FileInfo`. This will work as the program's internal database that stores the counting result for each source file.

### Helper functions

To help you handle a line of code, you may need to create some useful functions. You might need, for instance, a function to convert a string to lowercase. This is useful if you wan to support files that may come with extension in upper case. Another useful functions are one that trims out any leading white space in a string, and another that trims out any trailing white spaces in a string.


## Output

The output of the program is a table with the counting information for each category of line, per source file.
In case the program has processed more than one source file, the table must present a summation (consolidation) of counts on the last line of the table.

The example below is from a directory with three source files.
```
$ ./build/sloc src/core
Files processed: 3
-----------------------------------------------------------------------------------------------------
Filename             Language        Comments        Blank           Code            All
-----------------------------------------------------------------------------------------------------
src/core/cowsay.h    C/C++ header    93 (56.0%)      19 (11.4%)      96 (57.8%)      166
src/core/main_.cpp   C++             41 (64.1%)      7 (10.9%)       17 (26.6%)      64
src/core/cowsay.cpp  C++             165 (35.5%)     26 (5.6%)       330 (71.0%)     465
-----------------------------------------------------------------------------------------------------
SUM                                  299             52              443             695
-----------------------------------------------------------------------------------------------------
```

Note that for each category of line you must show the number of lines **and** the percentage that this quantity represents in relation to the total number of lines of the source file. The percentage must be presented enclosed in parenthesis and must have one digit after the point.  
All the fields must be left aligned.
The columns may have a fixed width. In particular, the first column must grow in width to accommodate the largest file name found in the list.


### Error output

There are, at least, four possible errors that your program must address:

1. The client provides a non existing source file.
```
$ ./build/sloc file.cpp
  Sorry, unable to open "file.cpp".
```
2. The client provides an existing file but it is not a supported source file.
```
$ ./build/sloc file.tex
  Sorry, ".tex" files are not supported at this time.
```
3. The client provides a non existing directory.
```
$ ./build/sloc souce
  Sorry, unable to access directory "souce".
```
4. The client provides an existing directory that does not contain any supported source file.
```
$ ./build/sloc src
  Sorry, unable to find any supported source file inside directory "src".
```

In any of these cases just described the program must print the proper error message and exit the program without printing an empty table.

If you identify another error situation while developing the project feel free to treat it accordingly.
The important point here is that your program **must not crash** in any circumstance.


## Assignment Grading

This assignment has a total of **100 points**. Bellow is a table with the description of the item under consideration and the assigned grade _if the item is totally correct_. Partial grade will be considered if the item is not fully correct.

Item     | Value (points)
-------- | :-----:
Read a single source file | 10
Read a list of files from a directory | 15
Show help as requested `-h` | 4
Treat error situations | 8
Show correct number of blank lines | 5
Show correct number of comment lines | 10
Show correct number of code lines | 10
Show correct number of total lines | 5
Show the type of source file | 5
Show percentages as requested | 10
Show consolidation at the bottom of a table | 5
Table is formatted as requested | 8
The project contains at least one struct or classes | 5

The following situations may take credits out of your assignment, if they happen during the evaluation process:

Item     | Value (points)
-------- | :-----:
Compiling and/or runtime errors  | -5
Missing code documentation in Doxygen style | -10
Memory leak | -10
[`author.md`](docs/author.md) file not filled out | -10
Program crashes while testing | -5

The [`author.md`](docs/author.md) file should contain a brief description of the project, and how to run it. It also should describe possible errors, limitations, or issues found. Do not forget to include the author name!

## Extra credits
You may earn extra credits if:

 - **[10 points]** Your program support extra languages.

# Authorship and Collaboration Policy

Originally this is an *individual assignment* but if you choose, you may pair up with someone. You may be called for an interview. The purpose of the interview is to confirm the authorship of the assignment and to ask for explanations on specific points of the code. During the interview, you should be capable of explaining any piece of code. After the interview, the assignment’s credits may be reviewed.

The cooperation among students is strongly encouraged. It is accepted the open discussion of ideas or development strategies. Notice, however, that this type of interaction should not be understood as a free permission to copy and use somebody else’s code. This is may be interpreted as plagiarism.

Any two (or more) programs deemed as plagiarism will automatically receive no credits, regardless of the real authorship of the programs involved in the case. If your project uses a (small) piece of code from someone else’s, please provide proper acknowledgment in the [`author.md`](author.md) file.

# Work Submission

You may submit your work in two possible ways: via GitHub Classroom (GHC), or, via SIGAA submission task. In case you decide to send your work via GHC you _must_ also send a text file via SIGAA submission task with the github link to your repository. In case you choose to send your work via SIGAA only, send a zip file containing all the code necessary to compile and run the project.

I any of these two ways, remember to remove all the executable files (i.e. the `build` folder) from your project before handing in your work.

--------
&copy; DIMAp/UFRN 2022.
