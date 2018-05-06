#include <cid3.h>
#include <stdio.h>

int main(int argc, char** argv) {
	cid3_file* file = cid3_file_init(argv[1]);
	cid3_frame* album_frame = cid3_file_get_artist_frame(file);
	
	if(album_frame) {
		printf("Album name: '%s'\n", album_frame->value);
	}
	
	cid3_file_delete(&file);
	return 0;
}
