# minishell

As beautiful as a shell

## Table of Contents
- [Project Description](#project-description)
- [Implementation](#implementation)
- [Usage](#usage)

## Project Description

### Mandatory part

This project is about creating a simple shell.
Own little bash.

Talking about specific rules that restrict the minishell's behaviour, it should:

• Display a prompt when waiting for a new command.

• Have a working history.

• Search and launch the right executable (based on the ```PATH``` variable or using a
relative or an absolute path).

**❗ Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that the signal handler will not access the
main data structures.**

• Not interpret unclosed quotes or special characters which are not required by the
subject such as ```\``` (backslash) or ```;``` (semicolon).

• Handle ```’``` (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.

• Handle ```"``` (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for ```$``` (dollar sign).

• Implement redirections:

- ```<``` should redirect input
  
- ```>``` should redirect output
  
- ```<<``` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!

- ```>>``` should redirect output in append mode.
  
• Implement pipes (```|``` character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.

• Handle environment variables (```$``` followed by a sequence of characters) which
should expand to their values.

• Handle ```$?``` which should expand to the exit status of the most recently executed
foreground pipeline.

• Handle ```ctrl-C```, ```ctrl-D``` and ```ctrl-\``` which should behave like in bash. In interactive mode:

- ```ctrl-C``` displays a new prompt on a new line.

- ```ctrl-D``` exits the shell.

- ```ctrl-\``` does nothing.

• Your shell must implement the following builtins:

- ```echo``` with option ```-n```

- ```cd``` with only a relative or absolute path

- ```pwd``` with no options

- ```export``` with no options

- ```unset``` with no options

- ```env``` with no options or arguments

- ```exit``` with no options

The ```readline()``` function can cause memory leaks. No need to fix them. But that doesn’t mean that the code can have memory leaks.

### Bonus part

The program has to implement:

• ```&&``` and ```||``` with parenthesis for priorities.

• Wildcards ```*``` should work for the current working directory.

## Implementation

### Minishell project diagram

![minishell_18_04](https://github.com/nikkxll/42-minishell/assets/125829393/f4d181ee-3213-4573-a91a-959f1277ef32)

Description in progress...

## Usage

To run the program enter
```
make && ./minishell
```
**❗ Make sure you have ```readline``` library installed**
```
brew install readline
```
or use homebrew to install it. After that, edit the ```Makefile``` READLINE section with the readline lib path.

---
Made by dnikifor: dnikifor@student.hive.fi | LinkedIn: [dnikifor](https://www.linkedin.com/in/dmitriinikiforov/) | Tableau: [dmitriinikiforov](https://public.tableau.com/app/profile/nikiforov.dmitrii/vizzes)
