/**
 * Figure 3.33
 */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
int main()
{
pid_t pid;
	/* fork a child process */
	pid = fork();
	if (pid < 0) { /* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		return 1;
	}
	else if (pid == 0) { /* child process */
		static const int BUFFSIZE = 200;
		char string1[BUFFSIZE] = {0};
		cout<<"CustomShell>";
		fgets(string1, BUFFSIZE, stdin);
		string1[strcspn(string1,"\n")] = 0;
		char *parsed_string = strtok(string1," ");
		char *args[BUFFSIZE];
		int i = 0;
		while (parsed_string != NULL)
		{
			args[i++] = parsed_string; 
			parsed_string = strtok (NULL, " ");
		}
		int status_code = execvp(args[0],args);
		if (status_code == -1)
		{
			printf("Error!");
		}
		return 0;
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
		printf("Child Complete");
	}

	return 0;
}
