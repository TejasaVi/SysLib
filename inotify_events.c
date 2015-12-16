#include<stdio.h>
#include <string.h>
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

int init_watch_event()
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
 * Function:  add_watch_dir()
 * Description:This function will add a watch on the changes that can occur in DIRECTORY at location @path.
 * Arguements:	@fd = inotify instance number.
 * 		@path = location of directory.
 * 	       	@mask = type of events that can occur.
 * Return Value: (integer)non-negative  watch descritor or -1 on failure.
 *
 * */
int add_watch_dir(int fd ,char * path , int mask )
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
 * Function:  remove_watch()
 * Description:This function will remove  the watch on  DIRECTORY .
 * Arguements:	@fd = inotify instance number.
 * Return Value: (integer) zero on success or  -1 on failure.
 *
 * */

int remove_watch(int fd , int wd)
{	
	return	inotify_rm_watch(fd,wd);
}	

/*
 * Function:  read_dir_event()
 * Description:This function will read  the events that has occured in DIRECTORY .
 * Arguements:	@fd = inotify instance number.
 * Return Value: pointer to event or NULL.
 *
 * */
event_t* read_dir_event (int fd)
{
	event_t *e;
	
	e = malloc(sizeof(event_t));
	if (!e)
	{
		perror("read_dir_event:malloc failed\n");
		return NULL;
	}
	e->len = read(fd, e->buffer, EVENT_BUF_LEN);
	if( e->len < 0) {
		perror("read_event error\n");
        	return NULL;
	}
	
	return e;
}


/*
 * Function:  is_dir_modified()
 * Description:This function will read  the events and check if DIRECTORY is modified.
 * Arguements:	@e = event_t instance.
 * Return Value: Non-negative integer for event on -1.
 *
 * */
int is_dir_modified(event_t *e)
{
	int i=0;
	char buf[EVENT_BUF_LEN];
	strcpy(buf,e->buffer);

	while( i < e->len) {
		struct inotify_event * event = (struct inotify_event * )&buf[i];
		if (event->mask & IN_CREATE ) {
			if (event->mask & IN_ISDIR )  {
				//new directory added
				return 1 ;
			}
			else {;
				//new File added
				return 2;
			}
		}
		else if (event->mask & IN_DELETE ) {
			if (event->mask & IN_ISDIR )  {
	                        //directory deleted
        	                return 3;
                        ;
                        }
                        else {
                                //File deleted
				return 4;
                        }
		}
	i += EVENT_SIZE + event->len;	
	}

return -1; 
}


/*
 * Function: is_metadata_changed() 
 * Description:This function will read  the event and check if DIRECTORY metadata is modified.
 * Arguements:	@e = event_t instance.
 * Return Value: Non-negative integer for event on -1.
 *
 * */
int is_metadata_changed(event_t *e)
{


	return -1;
}


/*
 * Function: is_file_opened()
 * Description:This function will read  the events and check if DIRECTORY is modified.
 * Arguements:	@e = event_t instance.
 * Return Value: Non-negative integer for event on -1.
 *
 * */
int is_file_opened(event_t *e)
{
	return -1;
}

