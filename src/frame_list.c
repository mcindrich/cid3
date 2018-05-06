#include <cid3/frame_list.h>
#include <stdlib.h>
#include <stdio.h>

cid3_frame_list cid3_frame_list_init(char* data, u32* fpos, int max) {
	cid3_frame_list frames;
	frames.data = NULL;
	frames.size = 0;
	cid3_frame* new_frame = NULL;
	const int REACH_SIZE = *fpos + max;
	
	while(*fpos < REACH_SIZE) { // while the tag size is not reached
		new_frame = cid3_frame_init(data, fpos);
		if(!new_frame) break;
		frames.data = (cid3_frame**) realloc(frames.data, sizeof(cid3_frame*) * (frames.size+1));
		*(frames.data + frames.size) = new_frame;
		++frames.size;
	}
	return frames;
}

void cid3_frame_list_delete(cid3_frame_list* frames) {
	// free every frame
	int i = 0;
	if(frames->data) {
		for(; i < frames->size; i++) {
			cid3_frame_delete(&frames->data[i]);	
		}
		free(frames->data);
	}
}
