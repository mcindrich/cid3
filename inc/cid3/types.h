#ifndef __CID3_TYPES_H__
#define __CID3_TYPES_H__

// #defines

#define CID3_HEADER_ID_LENGTH 3
#define CID3_HEADER_TAG_SIZE 4
#define CID3_EXTENDED_HEADER_SIZE 4
#define CID3_EXTENDED_HEADER_FLAGS 2
#define CID3_EXTENDED_HEADER_PADDING_SIZE 4

#define CID3_FRAME_ID_SIZE 4
#define CID3_FRAME_SIZE 4
#define CID3_FRAME_FLAGS_SIZE 2

typedef char byte;
typedef byte cid3_flags;

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned int u32;
typedef signed int s32;

typedef unsigned long long u64;
typedef signed long long s64;

typedef struct cid3_version {
	byte major;
	byte revision;
} cid3_version;

#endif
