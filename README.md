# minishell

### Description

This project is implementation of linux command line shell. Supports quotes, redirects, pipes, ctrl-C, ctrl-D, ctrl-\ signals, enviroment variables and 6 built-in commands:

1. echo
2. cd
3. pwd
4. export.
5. unset
6. env

Also supports commands history, wildcards `*`, `;`. `&&`, `||` as commands separators and some kinds of command line editing. 

### Build

Run `make` in project root directory to create executable `minishell`.
 
To remove all files created by program run `make fclean`, or `make clean` to remove all except executable.
 
### Usage

Just run `minishell` and use like usual command line shell.

![ezgif com-gif-maker(6)](https://user-images.githubusercontent.com/36854467/140644770-6a8eb7b3-d672-4165-9504-aa70338742b3.gif)
