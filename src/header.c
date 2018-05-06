#include <cid3/header.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int decode_tag_s(char* data, int pos) {
	return data[pos] << 21 | data[pos+1] << 14 | data[pos+2] << 7 | data[pos+3]; // every 7th bit is ignored	
}

cid3_header* cid3_header_init(char* data, u32* fpos) {
	cid3_header* head = (cid3_header*) malloc(sizeof(cid3_header));
	memcpy(head->id, data, *fpos += CID3_HEADER_ID_LENGTH); // copy 3 bytes ==> "ID3"
	head->version.major = data[*fpos += 1]; // 1B
	head->version.revision = data[*fpos += 1]; // also 1B
	head->flags = data[*fpos += 1]; // flags ==> 8 bits == 1B
	head->tag_s = decode_tag_s(data, *fpos); // 4B for tag size from 
	*fpos += CID3_HEADER_TAG_SIZE;
	
	if((head->flags >> 6) & 0x1) { // check the 6th bit for extended header
		// ext. header exists
		// for now ignore
		*fpos += CID3_EXTENDED_HEADER_FLAGS + CID3_EXTENDED_HEADER_SIZE + CID3_EXTENDED_HEADER_PADDING_SIZE;
	}
	return head;
}

void cid3_header_delete(cid3_header** head) {
	if(*head) free(*head);
}
