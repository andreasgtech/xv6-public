/* workload 1, CPU intensive, no I/O */
#include "types.h"
#include "stat.h"
#include "user.h"

void nuthin(unsigned long long int i)
{
	if(i>1111)
	{
		exit();
	}
}

int main(void)
{
	unsigned long long int i,j,k=0;
	int n=0;
	for(i=0; i<1000000000000000000; i++)
	{
		k--;
		for (j=0; j<1000000000000000000; j++)
		{
			k++;
			n+=k;
		}
	}
	nuthin(n);
}