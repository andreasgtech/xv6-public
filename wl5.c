/* workload 5, somewhat CPU intensive, some large I/Os */
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void nuthin(unsigned long long int i)
{
	if(i>1111)
	{
		i=1111;
	}
}

int main(void)
{
	int i, j, fd_in, fd_out;
	fd_out = open("./myReadme5", O_CREATE);
	close(fd_out);
	j=1;
	unsigned long long int m,k=0;
	for (i=0; i < 6000; i++)
	{
		fd_in = open("./README", O_RDONLY);
		fd_out = open("./myReadme5", O_WRONLY);
		char buf[10000];
		int n;
		for(;;j++)
		{
			n = read(fd_in, buf, sizeof buf);
			if(!n)
			{
				break;
			}
			if(n<0)
			{
				write(2, "read error\n", 11);
				exit();
			}
			for(m=0; m < 1000000000000000; m++)
			{
				k+=m;
			}
			nuthin(k);
			if(write(fd_out, buf, (unsigned int)j)%10000 != (unsigned int)j%10000)
			{
				write(2, "write error\n", 12);
				exit();	
			}
		}
		close(fd_out);
		close(fd_in);
	}
	exit();
}