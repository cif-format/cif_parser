#include <stdio.h>

#include "cif.h"

int main(int argc, char* argv[]){
  if(argc != 2){
    fprintf(stderr, "usage: cif_parse [cif file]\n");
    return 2;
  }

  size_t sz = 0;
  FILE* fp = fopen(argv[1], "rb");

  fseek(fp, 0L, SEEK_END);
  sz = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  unsigned char buffer[sz];
  fread(buffer, sizeof(buffer), 1, fp);
  fclose(fp);



  // first let's check if the header is correct
  unsigned short magic_num = (buffer[0] << 8) | buffer[1]; // weird trick, but 0xfe 0xdb => 0xfedb
  int version = 0;

  switch(magic_num){
    case v0:
      version = 0;
      break;
    
    /* any other value is incorrect */
    default:
      version = -4;
      break;
  }

  // find width & height
  cif_uint8_t width = buffer[2];
  cif_uint8_t height = buffer[4]; // buffer[3] is reserved

  cif_header_t _hdr = { .magic = magic_num,
                        .width = width,
                        .reserved = RESERVED,
                        .height = height };
  printf("CIF version %d detected (magic is 0x%x)\n", version, _hdr.magic);
  printf("Dimensions of CIF file: %d by %d (width by height)\n", _hdr.width, _hdr.height);

  // now lets display pixels
  #ifdef __NON_FFREESTANDING
    // some operating systems do not implement a scanf
    

    char m = 0x59;
    printf("\nWould you like to display pixel data? (default=Y, Y/n) ");
    scanf("%c", &m);
    if(m != 0x59) return 0; // exit
  #endif
  
  for(int k = 5; k < (sizeof(buffer)/sizeof(buffer[0])); k++){
    // TODO
  }
}