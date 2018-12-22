#include <cid3.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char *real_value(cid3_frame *frame) {
  int i, cnt = 0;
  char *new_str = NULL;
  for(i = 0; i < frame->size; i++) {
    if(isprint(frame->value[i])) {
      cnt++;
    }
  }
  
  new_str = (char *) malloc(sizeof(char) * (cnt + 1));
  cnt = 0;

  for(i = 0; i < frame->size; i++) {
    if(isprint(frame->value[i])) {
      new_str[cnt] = frame->value[i];
      cnt++;
    }
  }
  new_str[cnt] = 0;
  return new_str;
}

int main(int argc, char** argv) {
	cid3_file* file = cid3_file_init(argv[1]);
	cid3_frame* album_frame = cid3_file_get_artist_frame(file);
	char *str = real_value(album_frame);
	if(album_frame) {
		printf("Album name: '%s'\n", str);
	}
  free(str);
	
	cid3_file_delete(&file);
	return 0;
}
