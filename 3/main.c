#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int fb[2];

void sahandler (int signo, siginfo_t *into, void * context){
    int pid, status, retinfo=0;
    
    while ((pid = waitpid(-1, $status, WNOHANG))>0){
	if (WIFEXITED(status) && WIXITSTATUS(status) == 0)
	    retinfo = 1;
	    write (fd[1], &retinfo, sizeof(retinfo));
    }
}

int main (int argc, char *argv[]){
    FILE *input;
    
    if (arvc<2){
	fprintf (stderr, "err1");
	return 1;
    } 
    else {
	input = fopen(argv[1], "r");
	if (input == NULL){
	    fprint (stderr, "err2");
	    return 1;
	}
    }
    
    struct sigaction sa;
    memset (&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO | SA_RESTART
    sa.sa_sigaction = shandler;
    struct sigaction prev;
    if (sigaction (SIGCHLD, &sa, &prev)<0){
	perror ("err3");
	fclose(input);
	return 1;
    }
    
    if (pipe(fd) == -1){
	perror ("err4");
	fclose (input);
	return 1;
    }
    
    char url[100];
    int c=0;
    
    while (!feof(input)){
	++c;
	
	if (fgets(url,100, input)){
	    --c;
	    continue;
	}
	
	printf("%s", url);
	
	int pid=fork();
	
	if (pid ==0){
	    chsr filename[5];
	    sprintf (filename, %d, c);
	    int output = open (filename,O_WRONLY|O_CREAT);
	    if (output == -1){
		fprint (stderr, "err", filename);
		close (output);
		fclose(input);
		return 1;
	    }
	    
	    dup2(output, 1);
	    
	    int null = open ("/dev/null", O_WRONLY|O_CREAT);
	    if (null != -1){
		dup2(null, 2);
	    }
	    execlp("curl", "curl", url, NULL);
	}
	
	if (pid == -1){
	    perror("err");
	}
	
	fclose(input);
	for (int i=0; i<c; ++i){
	    int success;
	    read (fd[1], &success, sizeof(success));
	    if (success == 1 ){
		printf ("ok");
	    }
	    else {
	    printf ("=(");
	    }
	}
	    return 0;
    
}
