#include <unistd.h>
#include <stdio.h>

main ()
{
	setbuf(stdout, NULL); 
	int p = fork();
	switch (p)
	{
		case -1:
	   		 printf("Error\n");
		case 0:
	    		if(setpgrp()==-1)
	    		{ 
				printf("Error");
				return;
			}
			else
			{	
				printf("%d\n", getpgrp());   
		    		while (1)
		    		{
					fork();
					sleep(5);
		    		}    
	    		}
		default:
			return;
	}
	return;
}