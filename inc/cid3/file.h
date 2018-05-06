#ifndef __CID3_FILE_H__
#define __CID3_FILE_H__

#include <cid3/tag.h>

typedef struct cid3_file {
	char* data;
	cid3_tag tag;
	u32 fpos;
} cid3_file;

cid3_file* cid3_file_init(const char*);
cid3_frame* cid3_file_get_album_frame(cid3_file*);
cid3_frame* cid3_file_get_artist_frame(cid3_file*);
void cid3_file_delete(cid3_file**);

#endif

