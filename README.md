## how to compile and run the files:

compile all files using the makefile i.e, using command `make` and then run it using `./a.out` 

Assumptions--

-> input given to prompt will not exceed 1000 characters.

->Number of commands given at a time cannot exceed 1000.

->Hostname, Username <= 100 characters.

->Directory names doesn't contain spaces, nullcharacters in between.

->ls will not work if a filename is given. i didnot implement this case.

->if a background process gets finished, it immediately prints the information. This is slightly different from original shell behaviour. 

--------------------------------------------------------------------------------------------------------

-> assumed that a command can contain i) one input redirection or ii) one iput+ one output redirection 
shell doesn't execute commands which have multiple input and redirection symbols.

-> also assumed that input redirection comes first and then output/append redirection
shell fails to execute if output redirection symbol comes first

->when a specific job has completed its execution, we don't decrease job_count. next job will have count+1 as jobid.

--------------------------------------------------------------------------------------------------------

signals--

-> ctrl+c : it interupts any fg process and resumes shell execution. (used sigint)

->ctrl+z : it makes any current fg process stop and go background. (used sigtstp)

->ctrl+d : exits from current shell (checked if getline returns <0 or +ve) 


--main.c

this contains infinite loop of taking input and giving prompt. 
everytime it takes input, it reads it byline (getline) ,it tokenises the command with ";" as delimiter.
according to number of output strings after tokenising, it runs a loop where, each command is further tokenised with " " (space) as delimiter. then, accordingly, it identifies which function to be executed after going through few if, else statements. Then, it executes appropriate function.

--prompt.c
here, it displays the string for prompt (user@sysname) and according to current working directory, it displays relative or absolute path of directory.

--pwd.c
this gets executed whenever pwd is called. here it outputs the path of current working directory.

--pinfo.c
this gets executed whenever pinfo command is given and dispalys process information.

--ls.c
whenever we call ls, this gets executed. here, we pass command (list of arguments which are tokenised with " " ). according to number of -l, -a flags different functions get executed.

--fore.c 
this contains function for foreground processes. whenever it identifies a command as foreground, child process gets created and then we implement that command using execvp. parent process waits till child process gets terminated . it gets control back, once child processes gets finished.

--background.c
this contains implementation for background processes. whenever it identifies & in command, it implements the command as background process. here, we store the pid, process name of each background process in array of structs. this will be useful when we want to display a process name once it gets finshed. 
the difference between froeground and background implementation is that parent waits till child finisghes execution in foreground whereas it doesn't in backgound.

--repeat.c
this contains the function whenever it encounters repeat as first word in a command and runs the command given number of times.

-replayd.c
this contains implementation of replay command.

-bg.c
when `bg <jobid>` is given, if the bg process is in stopped state, it resumes its execution in background.

-fg.c
when `fg <jobid>` is given, <jobid> which is in background comes to foreground and starts executing.

-io_redirect.c
contains implementation of input output redirection command. we consider words till '<' and change input,output file descriptors accordingly. then execute command using execvp.

-pipe.c
contains implementation of pipe. here, we first tokenise command using '|' and then, loop through each command , further tokenise them using " ", then create pipe and change filedescriptors, finally execute using execvp. at the end, change the file descriptors to original ones.

-jobs.c
when jobs command is given, it goes through list of jobs (declared globally) and check whether it has terminated or not. if its not terminated, we print it else discard it. further, check -r -s flags and display  accordingly.

sig.c
it sends specific signal to specific job which is mentioned in command.


