#include <stdio.h>

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

}