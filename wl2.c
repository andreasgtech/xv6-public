/* workload 2, not CPU intensive, many short I/Os */
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	int i, j, fd_in, fd_out;
	fd_out = open("./myReadme2", O_CREATE);
	close(fd_out);
	j=0;
	for (i=0; i < 300; i++)
	{
		fd_in = open("./README", O_RDONLY);
		fd_out = open("./myReadme2", O_WRONLY);
		char buf;
		int n;
		for(;;j++)
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
			if (j%100==0)
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