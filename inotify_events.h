#include<sys/types.h>
#include<linux/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN   (1024 * (EVENT_SIZE + 16 ) )

typedef struct {
	int len;
	char buffer[EVENT_BUF_LEN];
}event_t;
