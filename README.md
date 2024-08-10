resources:
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

TO FIX AFTER EVAL:
- not trimmming the content inside double quotes "";
- signals functions -extra testing; [fixed]
- export with no parameters; [fixed]
- all the errors should go to STDERR; [fixed]
- do not display the ?= parameter inside ft_env; [fixed]
- cd /noe --free invalid pointer; [fixed]


# Allowed functions
## text input output utils
- printf
- readline
- rl_clear_history
- rl_on_new_line
- rl_replace_line
- rl_redisplay
- add_history
## memory management
- malloc
- free
## file utils
- write
- access
- open
- read
- close
- dup
- dup2
## directory utils
- opendir
- readdir
- closedir
- chdir
## processes
- fork
- wait
- waitpid
- wait3
- wait4
- signal
- sigaction
- sigemptyset
- sigaddset
- kill
- pipe
- execve
## terminal util
- getcwd
- stat
- lstat
- fstat
- unlink
- isatty
- ttyslot
- ioctl
- getenv
- tcsetattr
- tcgetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs
## error handling
- strerror
- perror
- ttyname
## other?
- exit
