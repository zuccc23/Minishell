#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_exex
{
    int     pipe_fd[2]; // fd[0] = lecture, fd[1] = ecriture
    int     count_cmd; // Savoir combien tu as de commande pour gerer la derniere differement
    int     input_fd;   // Ce que la commande lira (STDIN ou pipe precedent)
    int     output_fd;  // Ce que la commande ecrira (STDOUT ou pipe suivant)
    int     infile_fd;
    int     outfile_fd;
    char    **envp;
    int     last_exit_status; // Code d'exit
    pid_t   *pidarray;  // Tableau de tous les pids (si plusieurs commandes)
}   t_exec;

#endif