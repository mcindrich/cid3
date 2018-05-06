#include <cid3/tag.h>

cid3_tag cid3_tag_init(char* data, u32* fpos) {
	cid3_tag tag;
	tag.header = cid3_header_init(data, fpos);
	tag.frames = cid3_frame_list_init(data, fpos, tag.header->tag_s);
	return tag;
}

void cid3_tag_delete(cid3_tag* tag) {
	if(tag->header) cid3_header_delete(&tag->header);
	cid3_frame_list_delete(&tag->frames);
}
