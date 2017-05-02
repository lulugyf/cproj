#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int  GenDaemon() {
        int childpid,fd;
        int flag;

        if (getppid()==1) {
                umask(0);
                return 0;
        }
		signal(SIGALRM, SIG_IGN);
        if ((childpid = fork())<0 ) {
                exit(-1);
        }else{
			if (childpid > 0)
				exit(0);
        }
        /*for (fd=1; fd<=3;fd++)
                close (fd);
	
        chdir("/");*/
        umask(0);

		/*IgnoreAllSignal();*/
        return 0;
}
