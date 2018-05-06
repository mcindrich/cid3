#include <cid3/frame.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// function to convert 4 bytes to int ==> source http://www.cplusplus.com/forum/beginner/3076/
/*

byte MyBytes[4];  //set values to this also.
int Int32 = 0;

Int32 = (Int32 << 8) + MyBytes[3];
Int32 = (Int32 << 8) + MyBytes[2];
Int32 = (Int32 << 8) + MyBytes[1];
Int32 = (Int32 << 8) + MyBytes[0];
 
 * */

// modified

int get_frame_size(char* code, int pos) {
	int res = 0, i = 0;
	for(; i < 4; i++) {
		res = (res << 8) + ((u8) code[i + pos]); // unsigned ==> endian problem -> no negative numbers
	}
	return res;
}

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

void cid3_frame_delete(cid3_frame** frame) {
	if(*frame) {
		if((*frame)->value) free((*frame)->value);
		free(*frame);
	}
}
