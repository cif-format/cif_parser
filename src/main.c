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
  unsigned short hdr = (buffer[0] << 8) | buffer[1]; // weird trick, but 0xfe 0xdb => 0xfedb
  int version = 0;

  switch(hdr){
    case v0:
      version = 0;
      break;
    
    /* any other value is incorrect */
    default:
      version = -4;
      break;
  }

  printf("CIF version %d detected\n", version);
}