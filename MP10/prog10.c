#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prog10.h"

/*
INTRO: I first read the file to complete the request output. 
As a result, I store each byte in wav and that each byte belongs to a certain category.
Based on the location of the byte, I can print the required text. Hi pass and Low pass are 
basically the same algorithm except for a few small details. I used a temp array to
get out(n). For sound_bite I used the algorithm given to us in lab, adding the two
types of data together.




*/

WAV *read_file(char *wavfile)
{

	FILE *fileWave= fopen(wavfile, "r");
	WAV *wav = malloc(sizeof(*wav));
	
	//stored the required bytes into memory
    fread(wav->RIFF, sizeof(char), 36, fileWave);
    
    int charAlloc = wav->Subchunk1Size - 16;
   
    wav->extra = malloc(charAlloc);
    fread(wav->extra, sizeof(char), charAlloc, fileWave);
    fread(wav->Subchunk2ID, sizeof(int), 2, fileWave);
    
    int dataAlloc = wav->Subchunk2Size * 8 / wav->bitsPerSample;
    wav->data = malloc(dataAlloc * sizeof(short int));
    fread(wav->data, sizeof(short int), dataAlloc, fileWave);

    //prints the requested output
	printf("ChunkID: %c%c%c%c\n",wav->RIFF[0],wav->RIFF[1],wav->RIFF[2],wav->RIFF[3]);
	printf("ChunkSize: %d\n", wav->ChunkSize);
	printf("Format: %c%c%c%c\n",wav->WAVE[0],wav->WAVE[1],wav->WAVE[2],wav->WAVE[3]);
	printf("Subchunk1ID: %c%c%c%c\n", wav->fmt[0], wav->fmt[1], wav->fmt[2], wav->fmt[3]);
	printf("Subchunk1Size: %d\n", wav->Subchunk1Size);
	printf("AudioFormat: %d\n", wav->AudioFormat);
	printf("NumChannels: %d\n", wav->NumChan);
	printf("SampleRate: %d\n", wav->SamplesPerSec);
	printf("ByteRate: %d\n", wav->bytesPerSec);
	printf("BlockAlign: %d\n", wav->blockAlign);
	printf("BitsPerSample: %d\n",wav->bitsPerSample);
	printf("Subchunk2ID: %c%c%c%c\n", wav->Subchunk2ID[0],
            wav->Subchunk2ID[1], wav->Subchunk2ID[2], wav->Subchunk2ID[3]);
	printf("Subchunk2Size: %d\n", wav->Subchunk2Size);
	fclose(fileWave);
		return wav;
}

void hi_pass(WAV *inwav, char *outfile, int freq)
{

	FILE *fileWave= fopen(outfile, "w");
	
	double pi = 3.1415926535897932384626433832795028841971693993751058209749;
	
	fwrite(inwav, sizeof(char), 36, fileWave);
    inwav->extra = malloc(inwav->Subchunk1Size - 16);
    fwrite(inwav->extra, sizeof(char), inwav->Subchunk1Size-16, fileWave);
    fwrite(inwav->Subchunk2ID, sizeof(int), 2, fileWave);
    
    //given formulas
	int sample_rate = inwav->bitsPerSample;
	double r = 0.5;
	int f = freq;
	int x;
	double c = tan(pi * f / sample_rate);
	 
	double a1 = 1.0 / ( 1.0 + r * c + c * c);
	double a2 = (-2.0) * a1;
	double a3 = a1;
	double b1 = 2.0 * ( c*c - 1.0) * a1;
	double b2 = ( 1.0 - r * c + c * c) * a1;
	
	short int *temp = malloc(sizeof(short int)*(inwav->Subchunk2Size));
	short int in, in1, in2, out1, out2;
    temp[0] = inwav->data[0];// the first four values are set in stone, so they will not be changed
    temp[1] = inwav->data[1];
    temp[2] = inwav->data[2];
    temp[3] = inwav->data[3];
     for(x = 4; x < inwav->Subchunk2Size /** 8 / inwav->bitsPerSample*/  ; x++)
    {
        in = inwav->data[x];
        in1 = inwav->data[x-2];// this is -2 and -4 because it goes left-right-left-right. therefore, it shoudl be every other previous value
        in2 = inwav->data[x-4];
        out1 = temp[x-2];
        out2 = temp[x-4];
        temp[x] = (a1 * in) + (a2 * in1) + (a3 * in2) - (b1 * out1) - (b2 * out2);
    }
    fwrite(temp, sizeof(short int), inwav->Subchunk2Size/* * 8 / inwav->bitsPerSample*/, fileWave);
	temp = NULL;

    fclose(fileWave);
    

}

void lo_pass(WAV *inwav, char *outfile, int freq)
{

	double pi = 3.1415926535897932384626433832795028841971693993751058209749;
	FILE *fileWave= fopen(outfile, "w");
	fwrite(inwav, sizeof(char), 36, fileWave);
    inwav->extra = malloc(inwav->Subchunk1Size - 16);
    fwrite(inwav->extra, sizeof(char), inwav->Subchunk1Size-16, fileWave);
    fwrite(inwav->Subchunk2ID, sizeof(int), 2, fileWave);
    //given formulas
	int sample_rate = inwav->bitsPerSample;
	
	double r = 0.5;
	int f = freq;
	int x;
	double c = 1.0 / tan( pi * f / sample_rate);
	 
	double a1 = 1.0 / ( 1.0 + r * c + c * c);
	double a2 = (2.0) * a1;
	double a3 = a1;
	double b1 = 2.0 * ( 1.0 - c*c) * a1;
	double b2 = ( 1.0 - r * c + c * c) * a1;
	
	short int *temp = malloc(sizeof(short int)*(inwav->Subchunk2Size /* * 8 / inwav-> bitsPerSample*/ ));
	short int in, in1, in2, out1, out2;
    temp[0] = inwav->data[0];// the first four values are set in stone, so they will not be changed
    temp[1] = inwav->data[1];
    temp[2] = inwav->data[2];
    temp[3] = inwav->data[3];
	for(x = 4; x < inwav->Subchunk2Size /* * 8 / inwav->bitsPerSample*/; x++)
    {
        in = inwav->data[x];
        in1 = inwav->data[x-2];// this is -2 and -4 because it goes left-right-left-right. therefore, it shoudl be every other previous value
        in2 = inwav->data[x-4];
        out1 = temp[x-2];
        out2 = temp[x-4];
        temp[x] = (a1 * in) + (a2 * in1) + (a3 * in2) - (b1 * out1) - (b2 * out2);
    }
    fwrite(temp, sizeof(short int), inwav->Subchunk2Size /* * 8 / inwav->bitsPerSample */ , fileWave);
  	fclose(fileWave);
    
    temp = NULL;
    
 
}

void sound_bite(WAV *inwav, WAV *bitewav, char *outfile, double time)
{
	FILE* fileWave = fopen(outfile, "w");
    fwrite(inwav, sizeof(char), 36, fileWave);
    int extraAlloc = inwav->Subchunk1Size - 16;
    inwav->extra = malloc(extraAlloc);
    fwrite(inwav->extra, sizeof(char), extraAlloc, fileWave);
    fwrite(inwav->Subchunk2ID, sizeof(char), 8, fileWave);
    int bData = bitewav->Subchunk2Size  * 8 / bitewav->bitsPerSample;
	int dataAlloc = inwav->Subchunk2Size  * 8 / inwav->bitsPerSample;    
    
  
    int x;
    short int *new = malloc(dataAlloc * sizeof(short int));
    int bStart = 2 * time * inwav -> SamplesPerSec;
    
    for(x = 0; x < dataAlloc; x++)
    {
        new[x] = inwav->data[x];
    }
    for(x = bStart; x < bStart + bData; x++)
    {
        new[x] = new[x] + bitewav->data[x - bStart];
    }
    fwrite(new, sizeof(short int), extraAlloc, fileWave);
    fclose(fileWave);
}

void noise_cancel(WAV *inwav, WAV *noisewav, char *outfile, double time)
{

}
void roundSong(WAV * inwav, char *outfile)
{
}
