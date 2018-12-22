#ifndef __CID3_FRAME_H__
#define __CID3_FRAME_H__

#include <cid3/types.h>

typedef struct cid3_frame {
	unsigned char id[4];
	int size;
	byte flags[2];
	char* value;
} cid3_frame;

cid3_frame cid3_frame_init(char *, u32 *);
void cid3_frame_delete(cid3_frame *);

#endif
