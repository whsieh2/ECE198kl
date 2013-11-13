#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prog10.h"

int main(int argc, char **argv){

  int choice = atoi(argv[1]);
  WAV *wav1;
  WAV *wav2;

  switch(choice){

    case 1:
      if(argc != 5) return -1;
      wav1 = read_file(argv[2]);
      hi_pass(wav1, argv[3], atoi(argv[4]));
      break;
    case 2:
      if(argc != 5) return -1;
      wav1 = read_file(argv[2]);
      lo_pass(wav1, argv[3], atoi(argv[4]));
      break;
    case 3:
      if(argc != 6) return -1;
      wav1 = read_file(argv[2]);
      wav2 = read_file(argv[3]);
      sound_bite(wav1, wav2, argv[4], atof(argv[5]));
      break;
    case 4:
      if(argc != 6) return -1;
      wav1 = read_file(argv[2]);
      wav2 = read_file(argv[3]);
      noise_cancel(wav1, wav2, argv[4], atof(argv[5]));
      break;
   	case 5:
      if(argc != 4) return -1; 
      wav1 = read_file(argv[2]);
      roundSong(wav1, argv[3]);
      break;
    default:
      printf("Choice not in range.\n");
  }

  return 0;

}
 
