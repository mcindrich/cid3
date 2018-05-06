#ifndef __CID3_TAG_H__
#define __CID3_TAG_H__

#include <cid3/header.h>
#include <cid3/frame_list.h>

typedef struct cid3_tag {
	cid3_header* header;
	cid3_frame_list frames;
} cid3_tag;

cid3_tag cid3_tag_init(char* , u32* );
void cid3_tag_delete(cid3_tag* );

#endif
