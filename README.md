*This project has been created as part of the 42 curriculum by buehara and thfernan.*

## Description
This project is a mini version of a shell program. It has no intention of be a full shell project, but only a beginner tentative to understand the underlying mechanisms of this key program, onipresent in the tech world. The main goal is to understang the structure of a shell program and all its relations with other computer systems.

## Instructions
### Compilation
First, do the command:
```
git clone https://github.com/project42sp/minishell.git
```

The program you will get is not ready to be run like it is, it needs to be compiled first, you can compile the program using:
```
make
```

Makefile is a type of program that will orchestrate the compilation and make it easy for anybody to test this.
After compilation the program is ready to run with the command:
```
./minishell
```

Is is possible to test the program with valgring. For that you can run:
```
make val
```
And Makefile will run valgrind with all the related flags needed for this project.


### Usage
This 42's minishell project was developed with only mandatory features asked by the program. This means that the project can run:

* simple commands, for example: ls, wc, grep
* builtin commands:
	* echo with a simple implementation of the -n flag
	* cd with ".", "-", "/" parameters
	* env no flags
	* export no flags
	* unset no flags
	* pwd no flags
	* exit
* redirections:
	* "<" input
	* ">" output
	* ">>" append
	* "<<" heredoc
* pipe
* environment variable expansion

## Resources
* We used [Notion](https://app.notion.com/p/MINISHELL-M3-2e0d6b81a38780e09ea4e21f2abe674e) to organize our notes
* [SystemsProgrammingBook - Chapter 5](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) is also a solid reference
* [Grammars, parsing, and recursive descent - Kay Lack (YouTube)](https://www.youtube.com/watch?v=ENKT0Z3gldE&sttick=1)
* [Recursive Descent Parsing - hhp3(YouTube)](https://www.youtube.com/watch?v=SToUyjAsaFk) And several others from this channel, actually.
* [Let's built a super simple shell in C - Oceano](https://www.youtube.com/watch?v=yTR00r8vBH8)
* Algo created the initial logic in this [Figma](https://www.figma.com/board/MV06Q0ifAnXaXxjW54K91i/minishell?node-id=40-1715&t=CaYIutfbl4flRdsN-0)
* [Recursive descent parser - Wikipedia Article](https://en.wikipedia.org/wiki/Recursive_descent_parser)
* Several linux manual pages

### Algorithm and project references

* 42 Subject PDF — *minishell*

### AI usage

AI tools were used during the development of this project to:

* Assist with debugging runtime errors (segmentation faults, invalid free)
* Help structure and validate the Makefile
* Organization of this README

All algorithmic decisions, implementations, and final code were written and validated by the authors.

---

## Notes

* The project follows the Norm of 42.
* Error handling is implemented according to the bash.
