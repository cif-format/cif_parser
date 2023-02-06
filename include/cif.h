#pragma once

enum CIF_MAGIC {
  v0 = 0xdbfe
};

#define RESERVED 0x20        // reserved or spacing.
#define CIF_EOF  0xFFFFFFFF  // the signal that the file

typedef unsigned short cif_uint16_t;
typedef unsigned int   cif_uint32_t;
typedef unsigned char  cif_uint8_t;
typedef int            cif_int16_t;

typedef struct {
  cif_uint16_t magic;  // dependent on version
  cif_uint8_t  width;  // self explanatory
  char reserved;       // set to 0x20
  cif_uint8_t  height;
}__attribute__((packed)) cif_header_t;

// structure is as follows:
// 0xRRGGBB and it can be formulated from these
// three unsigned chars in a very weird way:
//    0xRR << 16 | ((0xGG << 8) | 0xBB)
typedef struct {
  cif_uint8_t r;  
  cif_uint8_t g;
  cif_uint8_t b;
}__attribute__((packed)) cif_pixel_t;