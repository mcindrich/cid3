#ifndef __CID3_FRAME_LIST_H__
#define __CID3_FRAME_LIST_H__

#include <cid3/frame.h>

typedef struct cid3_frame_list {
	cid3_frame* data;
	u32 size;
} cid3_frame_list;

cid3_frame_list cid3_frame_list_init(char* , u32* , int);
void cid3_frame_list_delete(cid3_frame_list* );

#endif
