#include <unistd.h>
#include <stdio.h>

 main()
{
    while(1)
    {
	sleep(5);
	switch (fork())
	{
	    case -1:
		perror("fork");
		return 0;
	}	
    }
    return 0;
}
