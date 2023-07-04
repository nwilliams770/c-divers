#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define MAXLINE 1024
#define MAXARGS 128
#define MAXJOBS 20

typedef enum {
    INACTIVE,
    FOREGROUND,
    BACKGROUND,
    SUSPENDED
} JobState;

typedef struct {
  pid_t process_id;
  int job_id; // Job ID
  JobState state; // Job state: 0 (Foreground), 1 (Background), -1 (Stopped)
  char command_line[MAXLINE]; // Command line
} job;

// Globals
job jobs[MAXJOBS]; // Array of currently running jobs
int num_jobs = 0; // # of running jobs
int next_job_id = 1;  // Next available JID for foreground jobs

// Function prototypes
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void eval(char cmdline[MAXLINE]);
int parse_line(char *buf, char *argv[]);
int builtin_command(char *argv[]);
void jobs_handler();
void fg_handler(char *job_id);
void bg_handler(char *job_id);
void add_job(pid_t pid, int job_id, JobState state, char cmdline[MAXLINE]);
void delete_job(pid_t pid);
job* get_job_from_process_id(pid_t pid);
job* get_job_from_job_id(int jid);
job* get_foreground_job();

int main()
{
    char cmdline[MAXLINE]; // Command line

    // Register signal handlers
    struct sigaction sa_int;
    sigemptyset(&sa_int.sa_mask); // initialize mask to empty set
    sa_int.sa_flags = 0; // set flags to 0 (default behavior)
    sa_int.sa_handler = sigint_handler;

    if (sigaction(SIGINT, &sa_int, NULL) < 0)
    {
        fprintf(stderr, "Error: Failed to register SIGINT handler\n");
        exit(1);
    }

    struct sigaction sa_tstp;
    sigemptyset(&sa_tstp.sa_mask); // initialize mask to empty set
    sa_tstp.sa_flags = 0; // set flags to 0 (default behavior)
    sa_tstp.sa_handler = sigtstp_handler;

    if (sigaction(SIGTSTP, &sa_tstp, NULL) < 0)
    {
        fprintf(stderr, "Error: Failed to register SIGTSTP handler\n");
        exit(1);
    }


    while (1) {
        // Read
        printf("> ");
        fgets(cmdline, MAXLINE, stdin);

        if (feof(stdin))
        {
          exit(0);
        }

        if (num_jobs >= MAXJOBS)
        {
          printf("Cannot add job. Maximum number of jobs reached.\n");
          continue;
        }

        /* Evaluate */
        eval(cmdline);
    }
};

void sigint_handler(int sig)
{
  job* foreground_job = get_foreground_job();

  if (foreground_job != NULL)
  {
    pid_t process_id = foreground_job->process_id;

    if (kill(-(process_id), SIGINT) < 0)
    // '-' sign before fg_pid indicates that the signal should be sent to all
    // processes in the process group. Process will be reaped after termination
    {
      printf("Error: Failed to send SIGINT to process '%d'", process_id);
      return;
    }

    delete_job(process_id);
  }
};

void sigtstp_handler(int sig)
{
  job* foreground_job = get_foreground_job();

  if (foreground_job != NULL)
  {
    pid_t process_id = foreground_job->process_id;

    if (kill(-(process_id), SIGTSTP) < 0)
    // '-' sign before fg_pid indicates that the signal should be sent to all
    // processes in the process group.
    {
      printf("Error: Failed to send SIGSTP to process '%d'", process_id);
      return;
    }

    foreground_job->state = SUSPENDED;
  }
};

void eval(char cmdline[MAXLINE])
{
  char *argv[MAXARGS]; // Arg list
  char buf[MAXLINE]; // Modified command line
  int run_in_background; // Background job flag

  strcpy(buf, cmdline);
  run_in_background = parse_line(buf, argv);

  if (argv[0] == NULL)
  {
    return;
  }

  // If not built-in command...
  if (!builtin_command(argv))
  {
    pid_t process_id; // child process ID
    sigset_t mask_all, mask_child;

    sigfillset(&mask_all);
    sigemptyset(&mask_child);
    sigaddset(&mask_child, SIGCHLD);

    // Block SIGCHILD signal in parent process
    sigprocmask(SIG_BLOCK, &mask_child, NULL);

    // Child process
    if ((process_id = fork()) == 0)
    {
      // Unblock SIGCHLD signal in child process so that can handle its own
      // child processes' termination
      sigprocmask(SIG_SETMASK, &mask_child, NULL);
      // Create a new process group and make this child process as the leader
      // of that group
      setpgid(0, 0);

      if (execvp(argv[0], argv) < 0)
      {
        printf("%s: Command not found.\n", argv[0]);
        exit(1);
      }
      exit(0);
    }

    // Parent process
    if (!run_in_background)
    {
      int status;
      int job_id = next_job_id++;

      add_job(process_id, job_id, FOREGROUND, cmdline);
      sigprocmask(SIG_SETMASK, &mask_all, NULL); // Unblock all signals

      // Wait for status of specified child process to change even if it is
      // stopped (not terminated)
      waitpid(process_id, &status, WUNTRACED);

      if (WIFSTOPPED(status))
      {
        get_job_from_process_id(process_id)->state = SUSPENDED;
      }
      else
      {
        delete_job(process_id);
      }
    }
    else
    {
      int job_id = next_job_id++;
      add_job(process_id, job_id, BACKGROUND, cmdline);

      sigprocmask(SIG_SETMASK, &mask_all, NULL); // Unblock all signals
      printf("[%d] (%d) %s", get_job_from_process_id(process_id)->job_id, process_id, cmdline);
    }
  }
};

// parse_line parses through buf, populating argv which each space-separated argument.
// Each argument in buf is appended with a '/0' null terminating character. The function
// returns an int signifying whether the bg flag argument '&' was found. If it was, it is
// replace in buf with NULL.
int parse_line(char *buf, char *argv[])
{
  int argc = 0;
  char* delim;
  int bg;

  // ./myexecutable ...
  // exevcp(argv[0], argv)
  size_t buf_len = strlen(buf);
  if (buf[buf_len - 1] == '\n')
  {
    buf[buf_len - 1] = '\0';
  }

  // Trim leading white spaces
  while (*buf && (*buf == ' '))
  {
    buf++;
  }

  // Extract arguments
  while ((delim = strchr(buf, ' ')) != NULL)
  {
    argv[argc++] = buf; // Seed argv with point to first char of arg
    *delim = '\0'; // NULL character
    buf = delim + 1; // Move buf to beginning of next arg (most likely a space)

    while (*buf && (*buf == ' '))
    // Handle cases where there may be more than 1 space
    {
      buf++;
    }
  }

  // Handle the last argument
  if (*buf != '\0')
  {
    argv[argc++] = buf;
  }

  // Null-terminate the argv array
  argv[argc] = NULL;

  // Check for the background flag
  bg = (argc > 0 && argv[argc - 1][0] == '&');
  if (bg)
  {
    // If bg flag present, set that arg to NULL
    argv[--argc] = NULL;
  }

  return bg;
};

// builtin_command returns a flag signifying if the first argument of argv, <name>
// if one of the built-in commands of this program. They are "jobs" (lists all bg jobs)
int builtin_command(char *argv[])
{
  if (strcmp(argv[0], "quit") == 0)
  {
    exit(0);
  }
  else if (strcmp(argv[0], "jobs") == 0)
  {
    jobs_handler();
    return 1;
  }
  else if (strcmp(argv[0], "fg") == 0)
  {
    if (argv[1] == NULL)
    {
      printf("Error: Missing job ID or process ID for 'fg' command.\n");
      return 1;
    }
    fg_handler(argv[1]);
    return 1;
  }
  else if (strcmp(argv[0], "bg") == 0)
  {
    if (argv[1] == NULL)
    {
      printf("Error: Missing job ID or process ID for 'fg' command.\n");
      return 1;
    }
    bg_handler(argv[1]);
    return 1;
  }

  return 0;
};

void jobs_handler()
{
  int i;

  for (i = 0; i < MAXJOBS; i++)
  {
    if (jobs[i].state != INACTIVE)
    {
      printf("[%%%d] (%d)", jobs[i].job_id, jobs[i].process_id);

      switch (jobs[i].state)
      {
        case FOREGROUND:
          printf("Running ");
          break;
        case SUSPENDED:
          printf("Stopped ");
          break;
        default:
          printf("Unknown ");
          break;
      }
      printf("%s\n", jobs[i].command_line);
    }
  }
}

void bg_handler(char *arg)
{
  if (arg == NULL)
  {
    printf("Error: Invalid argument\n");
    return;
  }

  int job_id;
  pid_t process_id;
  job *job = NULL;

  if (arg[0] == '%')
  {
    // Handle job ID
    job_id = atoi(&arg[1]);
    job = get_job_from_job_id(job_id);

    if (job == NULL)
    {
      printf("No such job '%d'\n", job_id);
      return;
    }

    process_id = job->process_id;
  }
  else
  {
    // Handle process ID
    process_id = atoi(&arg[0]);
    job = get_job_from_process_id(process_id);

    if (job == NULL)
    {
      printf("No such process '%d'\n", process_id);
      return;
    }

    job_id = job->job_id;
  }

  if (kill(-process_id, SIGCONT) < 0)
  {
    printf("Error: Failed to send SIGCONT to process '%d'\n", process_id);
  }

  job->state = BACKGROUND;
  printf("[%d] (%d) %s", job->job_id, job->process_id, job->command_line);
}

void fg_handler(char *jid)
{
  if (jid == NULL)
  {
    printf("Error: Invalid argument\n");
    return;
  }

  int job_id = atoi(jid);
  job *job = get_job_from_job_id(job_id);

  if (job == NULL)
  {
    printf("No such job with ID '%s'\n", jid);
    return;
  }

  if (job->state == INACTIVE)
  {
    printf("Job '%s' has been already been terminated\n", jid);
    return;
  }

  job->state = FOREGROUND;
  pid_t process_id = job->process_id;
  if (kill(-(process_id), SIGCONT) < 0)
  {
    printf("Error: Failed to send SIGCONT to process '%d'\n", process_id);
  }

  int status;
  waitpid(process_id, &status, WUNTRACED);
  if (WIFSTOPPED(status))
  {
    job->state = SUSPENDED;
  }
  else
  {
    delete_job(process_id);
  }
}

void add_job(pid_t process_id, int job_id, JobState state, char cmdline[MAXLINE])
{
  int i;

  for (i = 0; i < MAXJOBS; i++)
  {
    if (jobs[i].process_id == INACTIVE)
    {
      // Found an empty slot, assign the new job
      jobs[i].process_id = process_id;
      jobs[i].job_id = job_id;
      jobs[i].state = state;
      strncpy(jobs[i].command_line, cmdline, MAXLINE);

      num_jobs++;

      break;
    }
  }
}

void delete_job(pid_t pid)
{
  int i;

  for (i = 0; i < MAXJOBS; i++)
  {
    if (jobs[i].process_id == pid)
    {
      jobs[i].state = INACTIVE;

      num_jobs--;

      break;
    }
  }
}

job* get_job_from_process_id(pid_t pid)
{
  int i;

  for (i = 0; i < MAXJOBS; i++)
  {
    if (jobs[i].process_id == pid)
    {
      return &jobs[i];
    }
  }

  return NULL;
}

job* get_job_from_job_id(int jid)
{
  int i;

  for (i = 0; i < MAXJOBS; i++)
  {
    if (jobs[i].job_id == jid)
    {
      return &jobs[i];
    }
  }

  return NULL;
}

job* get_foreground_job()
{
  int i;

  for (i = 0; i < MAXJOBS; i++)
  {
    if (jobs[i].state == FOREGROUND)
    {
      return &jobs[i];
    }
  }

  return NULL;
}