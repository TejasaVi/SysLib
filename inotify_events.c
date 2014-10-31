#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<linux/inotify.h>
#include "inotify_events.h"
/*
 * Function:  init_event()
 * Description:This function will initialize the inotify instance.
 * Return Value: (integer) instance number.
 *
 *
 * */

int init_event()
{
	int fd;
	fd = inotify_init();
	if(fd <0) {
		perror("inotify_init error\n");
		return -1;	
	}
	return fd;
}

/*
 * Function:  watch_dir()
 * Description:This function will add a watch on the changes that can occur in DIRECTORY at location @path.
 * Arguements:	@fd = inotify instance number.
 * 		@path = location of directory.
 * 	       	@mask = type of events that can occur.
 * Return Value: (integer)non-negative  watch descritor or -1 on failure.
 *
 * */
int watch_dir(int fd ,char * path , int mask )
{
	int wd;
	
	wd = inotify_add_watch(fd,path, mask );
	if(wd <0) {
                perror("inotify_add_watch  error\n");
                return -1;
        }
        return wd;
}


/*
 * Function:  read_dir_event()
 * Description:This function will read  the changes that has occured in DIRECTORY .
 * Arguements:	@fd = inotify instance number.
 * Return Value: (integer)non-negative  Type of event or -1 on failure.
 *
 * */
int read_dir_event (int fd)
{
	int len=0;
	int i=0;
	char buffer[EVENT_BUF_LEN];
	len = read(fd, buffer, EVENT_BUF_LEN);
	if( len < 0) {
		perror("read_event error\n");
        	return -1;
	}
	while( i < len) {
		struct inotify_event * event = (struct inotify_event * )&buffer[i];
		if (event->mask & IN_CREATE ) {
			if (event->mask & IN_ISDIR )  {
			//new directory added
			;
			}
			else {;
				//new File added
			}	
		}
		else if (event->mask & IN_DELETE ) {
			if (event->mask & IN_ISDIR )  {
                        //directory deleted
                        ;
                        }
                        else {;
                                //File deleted
                        }
		}
	i += EVENT_SIZE + event->len;	
	} 
}


int main ()
{

	return 0;
}
