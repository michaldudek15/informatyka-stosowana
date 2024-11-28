#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "procinfo.h"

int procinfo(const char* name) {
	printf("nazwa procesu: %s | identyfikatory: UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d  \n",
		name, getuid(), getgid(), getpid(), getppid(), getpgrp());
	return 0;
}
