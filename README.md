# cid3
ID3v2 tag parser in C.

### Include a header
```c
#include <cid3.h>
```
### Init a file
```c
cid3_file* file = cid3_file_init(argv[1]);
if(file) {
    // file parsed correctly
    cid3_file_delete(&file); // free the file when done working with it
} else {
    // error while parsing file
}
```

### Frame examples
```c
#include <cid3.h>
#include <stdio.h>

int main(int argc, char** argv) 
{
    cid3_file* file = cid3_file_init(argv[1]);
    if(file) {
        // frame values are defined in cid3/types.h header file
        
        cid3_frame* album_frame = cid3_file_get_frame(file, CID3_ALBUM_NAME_ID);
        cid3_frame* artist = cid3_file_get_frame(file, CID3_ARTIST_NAME_ID);

        if(album_frame) {
            printf("Album name: '%s'\n", album_frame->value);
        }
        cid3_file_delete(&file);
    } else {
        printf("Error while parsing\n");
    }
    return 0;
}
```
