/* ps.c, call ps to run the printRunningProc syscall */

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	printRunningProc();
	exit();
}