#include <cid3/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cid3_file* cid3_file_init(const char* fn) {
	FILE* file = fopen(fn, "rb");
	size_t fsize;
	cid3_file* cid = (cid3_file*) malloc(sizeof(cid3_file));
	char* raw_data;
	
	if(!file) {
		return NULL;
	}
	
	cid->fpos = 0;
	
	fseek(file, 0, SEEK_END);
	fsize = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	raw_data = (char*) malloc(sizeof(char) * fsize);
	fread(raw_data, sizeof(char), fsize, file);
	cid->data = raw_data;
	fclose(file);
	
	cid->tag = cid3_tag_init(cid->data, &cid->fpos);
	
	return cid;
}

cid3_frame* cid3_file_get_album_frame(cid3_file* file) {
	cid3_tag* tag = &file->tag;
	for(int i = 0; i < tag->frames.size; i++) 
		if(tag->frames.data[i]->value && (memcmp("TALB", tag->frames.data[i]->id, 4) == 0)) 
			return tag->frames.data[i];
	return NULL;
}

cid3_frame* cid3_file_get_artist_frame(cid3_file* file) {
	cid3_tag* tag = &file->tag;
	for(int i = 0; i < tag->frames.size; i++) 
		if(tag->frames.data[i]->value && (memcmp("TPE1", tag->frames.data[i]->id, 4) == 0)) 
			return tag->frames.data[i];
	return NULL;
}

void cid3_file_delete(cid3_file** file) {
	if(*file) {
		if((*file)->data) free((*file)->data);
		cid3_tag_delete(&(*file)->tag);
		free(*file);
	}
}
