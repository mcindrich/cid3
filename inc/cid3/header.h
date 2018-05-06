#ifndef __CID3_HEADER_H__
#define __CID3_HEADER_H__

#include <cid3/types.h>

typedef struct cid3_header {
	char id[3];
	cid3_version version;
	byte flags;
	int tag_s;
} cid3_header;

cid3_header* cid3_header_init(char* , u32* );
void cid3_header_delete();

#endif
