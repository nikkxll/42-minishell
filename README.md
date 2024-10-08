# minishell

Minishell created by [@nikkxll](https://github.com/nikkxll) and [@shatilovdr](https://github.com/shatilovdr)

## Table of Contents
- [Project Description](#project-description)
- [Implementation](#implementation)
- [Results](#results)
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

Description in progress..

❗ Disclaimer ❗

The minishell program was inspired by Bash version 3.2.

If you plan to use a different version as a reference, be aware that the behavior may vary depending on the Bash version used.

The program is fully functional on both macOS and Linux, but please note that the behavior of Linux signals may differ from the original implementation. It is not recommended to use signals as a reference if you are working on Linux.

## Results

✅ Passed with 125/100 ✅

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
Made by: dnikifor@student.hive.fi | LinkedIn: [dnikifor](https://www.linkedin.com/in/dmitriinikiforov/) | Tableau: [dmitriinikiforov](https://public.tableau.com/app/profile/nikiforov.dmitrii/vizzes)\
&emsp;&emsp;&ensp;and dshatilo@student.hive.fi | LinkedIn: [dshatilo](https://www.linkedin.com/in/shatilovdr/)
