/* workload 4, somewhat CPU intensive, many short I/Os */
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
	int i,fd_in,fd_out,m=0;
	unsigned long long int j,k=0;
	fd_out = open("./myReadme4", O_CREATE);
	close(fd_out);
	for (i=0; i < 300; i++)
	{
		fd_in = open("./README", O_RDONLY);
		fd_out = open("./myReadme4", O_WRONLY);
		char buf;
		int n;
		for(;;)
		{
			n = read(fd_in, &buf, sizeof buf);
			if(!n)
			{
				break;
			}
			if(n<0)
			{
				write(2, "read error\n", 11);
				exit();
			}
			for(j=0; j < 1000000000000000; j++)
			{
				k+=j;
			}
			nuthin(k);
			if (m%100==0)
			{
				if(write(fd_out, &buf, n) != n)
				{
					write(2, "write error\n", 12);
					exit();	
				}
			}
		}
		close(fd_out);
		close(fd_in);
	}
	exit();
}