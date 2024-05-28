
### execve(char *program_path, char **program_name + args, envp);

1. check if executable is inside path
2. execute

test cases:

### exec_cmd(t_cmd *cmd)

1. check type of cmd
    1. if type is EXEC: just execute
	2. if type is REDIR
		1. close fd that we wanna redirect to
		2. create new file with aproapiate mode
		3. exec_cmd
	3. if type is PIPE
		1. fork left and exec_cmd left cmd;
		2. fork right and exec_cmd left cmd;
