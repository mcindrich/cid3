#include <cid3/frame_list.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*



cid3_frame* cid3_frame_init(char* code, u32* fpos) {
	cid3_frame* frame = (cid3_frame*) malloc(sizeof(cid3_frame));	
	int cnt = 0, i = 0;
	
	memcpy(frame->id, &code[*fpos], CID3_FRAME_ID_SIZE); // get the ID
	
	if(memcmp(frame->id, "\0\0\0\0", 4) == 0) { // done with frames ==> treat as the last one
		free(frame);
		return NULL;
	}
	
	frame->size = get_frame_size(code, *fpos += CID3_FRAME_ID_SIZE); // read the code ( 4B ) and get the real frame size
	
	memcpy(frame->flags, &code[*fpos += CID3_FRAME_SIZE], CID3_FRAME_FLAGS_SIZE);
	frame->value = (char*) malloc(sizeof(char) * frame->size); // allocate value
	*fpos += CID3_FRAME_FLAGS_SIZE;
	
	// parse string correctly
	
	for(; i < frame->size; i++) {
		if(code[*fpos + i])
			frame->value[cnt] = code[*fpos + i], ++cnt;
	}
	frame->value[cnt] = 0; // end

	frame->value = (char*) realloc(frame->value, sizeof(char) * (cnt+1)); // reallocate and save space ==> dumb but why not
	
	*fpos += frame->size; // update file position
	return frame;
}
*/

int get_frame_size2(char* code, int pos) {
	int res = 0, i = 0;
	for(; i < 4; i++) {
		res = (res << 8) + ((u8) code[i + pos]); // unsigned ==> endian problem -> no negative numbers
	}
	return res;
}

cid3_frame_list cid3_frame_list_init(char* data, u32* fpos, int max) {
	cid3_frame_list frames;
	frames.data = NULL;
	frames.size = 0;
	cid3_frame new_frame;
	const int REACH_SIZE = *fpos + max;
  u32 fpos_bkp = *fpos;
  int frames_cnt = 0;

  // temp values for counting
  char id[4];
  int sz;

  // count the frames and then alloc memory for all
  while(1) {
    memcpy(id, &data[*fpos], CID3_FRAME_ID_SIZE); // get the ID
    if(memcmp(id, "\0\0\0\0", 4) == 0) { // done with frames ==> treat as the last one
      break;
    }
    sz = get_frame_size2(data, *fpos += CID3_FRAME_ID_SIZE); // read the code ( 4B ) and get the real frame size
    *fpos += CID3_FRAME_SIZE + CID3_FRAME_FLAGS_SIZE + sz;
    frames_cnt++;
  }

  *fpos = fpos_bkp;

  frames.data = (cid3_frame *) malloc(sizeof(cid3_frame) * frames_cnt);

	while(1) { // while the tag size is not reached
		new_frame = cid3_frame_init(data, fpos);
		if(!new_frame.size) break;
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
