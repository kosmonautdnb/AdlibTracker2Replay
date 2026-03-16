#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  if (argc != 4) {
    printf("Usage: sa2_exe.exe <filename.exe> <player.exe> <song.sa2>\n");
    exit(0);
  }

  FILE *out = fopen(argv[1],"wb");
  if (out == NULL) {
    printf("Couldn't open output file <%s> for write.\n", argv[1]);
    exit(0);
  }

  FILE *in1 = fopen(argv[2],"rb");
  if (in1 == NULL) {
    printf("Couldn't open player exe file <%s> for read.\n", argv[2]);
    fclose(out);
    exit(0);
  }

  FILE *in2 = fopen(argv[3],"rb");
  if (in1 == NULL) {
    printf("Couldn't open song sa2 file <%s> for read.\n", argv[3]);
    fclose(out);
    exit(0);
  }

  fseek(in1,0,SEEK_END); long int in1size = ftell(in1); fseek(in1,0,SEEK_SET);
  fseek(in2,0,SEEK_END); long int in2size = ftell(in2); fseek(in2,0,SEEK_SET);

  unsigned char *in1data = (unsigned char *)malloc(in1size);
  fread(in1data,1,in1size,in1);
  fwrite(in1data,1,in1size,out);
  free(in1data);

  unsigned char *in2data = (unsigned char *)malloc(in2size);
  fread(in2data,1,in2size,in2);
  fwrite(in2data,1,in2size,out);
  free(in1data);

  fwrite(&in2size,1,4,out);
  char *id = "PLS4";
  fwrite(id,1,4,out);

  fclose(in1);
  fclose(in2);
  fclose(out);
  return 0;
}
