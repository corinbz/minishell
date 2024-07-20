#include "minishell.h"

void print_indent(int indent)
{
    for (int i = 0; i < indent; i++)
    {
        printf("  ");  // Two spaces per level
    }
}

void print_exec_cmd(t_exec_cmd *cmd, int indent)
{
    print_indent(indent);
    printf("EXEC Command:\n");
    for (int i = 0; cmd->arg_start[i] != NULL; i++)
    {
        print_indent(indent + 1);
        printf("Arg[%d]: %s\n", i, cmd->arg_start[i]);
    }
}

void print_redir_cmd(t_redir_cmd *cmd, int indent)
{
    print_indent(indent);
    printf("REDIR Command:\n");
    print_indent(indent + 1);
    printf("File: %s\n", cmd->token_start_pos);
    print_indent(indent + 1);
    printf("Mode: %d\n", cmd->mode);
    print_indent(indent + 1);
    printf("FD: %d\n", cmd->fd);
    print_indent(indent + 1);
    printf("Sub-command:\n");
    print_cmd_structure(cmd->sub_cmd, indent + 2);
}

void print_pipe_cmd(t_pipe_cmd *cmd, int indent)
{
    print_indent(indent);
    printf("PIPE Command:\n");
    print_indent(indent + 1);
    printf("Left:\n");
    print_cmd_structure(cmd->left, indent + 2);
    print_indent(indent + 1);
    printf("Right:\n");
    print_cmd_structure(cmd->right, indent + 2);
}

void print_heredoc_cmd(t_heredoc_cmd *cmd, int indent)
{
    print_indent(indent);
    printf("HEREDOC Command:\n");
    print_indent(indent + 1);
    printf("EOF Start: %s\n", cmd->eof_start);
    print_indent(indent + 1);
    printf("EOF End: %s\n", cmd->eof_end);
    print_indent(indent + 1);
    printf("Temp FD: %d\n", cmd->temp_fd);
    print_indent(indent + 1);
    printf("Sub-command:\n");
    print_cmd_structure(cmd->sub_cmd, indent + 2);
}

void print_cmd_structure(t_cmd *cmd, int indent)
{
    if (!cmd)
    {
        print_indent(indent);
        printf("NULL Command\n");
        return;
    }

    switch (cmd->type)
    {
        case EXEC:
            print_exec_cmd((t_exec_cmd *)cmd, indent);
            break;
        case REDIR:
            print_redir_cmd((t_redir_cmd *)cmd, indent);
            break;
        case PIPE:
            print_pipe_cmd((t_pipe_cmd *)cmd, indent);
            break;
        case HEREDOC:
            print_heredoc_cmd((t_heredoc_cmd *)cmd, indent);
            break;
        default:
            print_indent(indent);
            printf("Unknown Command Type: %d\n", cmd->type);
            break;
    }
}
