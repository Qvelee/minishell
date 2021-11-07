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

![ezgif com-gif-maker(5)](https://user-images.githubusercontent.com/36854467/140644290-b243ec31-8717-44d6-b3a3-3fb0ab80bdb4.gif)
