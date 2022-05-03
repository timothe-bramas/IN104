#include <unistd.h>
#include <stdio.h>
#include "magnitude.h"
#include <stdlib.h>
#include "stft.h"
#include <string.h>
#define TRUE 1 
#define FALSE 0

// WAVE header structure

unsigned char buffer4[4];
unsigned char buffer2[2];


char* seconds_to_time(float seconds);


 FILE *ptr;
 char *filename;
 struct HEADER header;




double* magnitude (char * sound, int* height, int* weight) {
    


 filename = (char*) malloc(sizeof(char) * 1024);
 if (filename == NULL) {
   printf("Error in malloc\n");
   exit(1);
 }

 // get file path
 char cwd[1024];
 if (getcwd(cwd, sizeof(cwd)) != NULL) {
   
    strcpy(filename, cwd);

    
    strcat(filename, "/");
    strcat(filename, sound);
 }

 // open file
 printf("Opening  file\n");
 ptr = fopen(filename, "rb");
 if (ptr == NULL) {
    printf("Error opening file\n");
    exit(1);
 }
 
 int read = 0;
 
 // read header parts

 read = fread(header.riff, sizeof(header.riff), 1, ptr);


 read = fread(buffer4, sizeof(buffer4), 1, ptr);

 
 // convert little endian to big endian 4 byte int
 header.overall_size  = buffer4[0] | 
                        (buffer4[1]<<8) | 
                        (buffer4[2]<<16) | 
                        (buffer4[3]<<24);



 read = fread(header.wave, sizeof(header.wave), 1, ptr);


 read = fread(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker), 1, ptr);


 read = fread(buffer4, sizeof(buffer4), 1, ptr);


 // convert little endian to big endian 4 byte integer
 header.length_of_fmt = buffer4[0] |
                            (buffer4[1] << 8) |
                            (buffer4[2] << 16) |
                            (buffer4[3] << 24);


 read = fread(buffer2, sizeof(buffer2), 1, ptr);
 
 header.format_type = buffer2[0] | (buffer2[1] << 8);
 char format_name[10] = "";
 if (header.format_type == 1)
   strcpy(format_name,"PCM"); 
 else if (header.format_type == 6)
  strcpy(format_name, "A-law");
 else if (header.format_type == 7)
  strcpy(format_name, "Mu-law");



 read = fread(buffer2, sizeof(buffer2), 1, ptr);


 header.channels = buffer2[0] | (buffer2[1] << 8);
 double* wav_data=malloc(header.channels*sizeof(double));


 read = fread(buffer4, sizeof(buffer4), 1, ptr);


 header.sample_rate = buffer4[0] |
                        (buffer4[1] << 8) |
                        (buffer4[2] << 16) |
                        (buffer4[3] << 24);



 read = fread(buffer4, sizeof(buffer4), 1, ptr);


 header.byterate  = buffer4[0] |
                        (buffer4[1] << 8) |
                        (buffer4[2] << 16) |
                        (buffer4[3] << 24);


 read = fread(buffer2, sizeof(buffer2), 1, ptr);


 header.block_align = buffer2[0] |
                    (buffer2[1] << 8);


 read = fread(buffer2, sizeof(buffer2), 1, ptr);


 header.bits_per_sample = buffer2[0] |
                    (buffer2[1] << 8);


 read = fread(header.data_chunk_header, sizeof(header.data_chunk_header), 1, ptr);


 read = fread(buffer4, sizeof(buffer4), 1, ptr);


 header.data_size = buffer4[0] |
                (buffer4[1] << 8) |
                (buffer4[2] << 16) | 
                (buffer4[3] << 24 );
 


 // calculate no.of samples
 long num_samples = (8 * header.data_size) / (header.channels * header.bits_per_sample);


 long size_of_each_sample = (header.channels * header.bits_per_sample) / 8;


 // calculate duration of file
 float duration_in_seconds = (float) header.overall_size / header.byterate;




 // read each sample from data chunk if PCM
 if (header.format_type == 1) { // PCM
        long i =0;
        char data_buffer[size_of_each_sample];
        int  size_is_correct = TRUE;

        // make sure that the bytes-per-sample is completely divisible by num.of channels
        long bytes_in_each_channel = (size_of_each_sample / header.channels);

        if ((bytes_in_each_channel  * header.channels) != size_of_each_sample) {
            printf("Error: %ld x %ud <> %ldn", bytes_in_each_channel, header.channels, size_of_each_sample);
            size_is_correct = FALSE;
        }
 
        if (size_is_correct) { 
                    // the valid amplitude range for values based on the bits per sample
    
            for (i =1; i <= 10; i++) {

                read = fread(data_buffer, sizeof(data_buffer), 1, ptr);
                if (read == 1) {
                
                    // dump the data read
                    unsigned int  xchannels = 0;
                    int data_in_channel = 0;
                    int offset = 0; // move the offset for every iteration in the loop below
                    for (xchannels = 0; xchannels < header.channels; xchannels ++ ) {
                        // convert data from little endian to big endian based on bytes in each channel sample
                        if (bytes_in_each_channel == 4) {
                            data_in_channel = (data_buffer[offset] & 0x00ff) | 
                                                ((data_buffer[offset + 1] & 0x00ff) <<8) | 
                                                ((data_buffer[offset + 2] & 0x00ff) <<16) | 
                                                (data_buffer[offset + 3]<<24);
                        }
                        else if (bytes_in_each_channel == 2) {
                            data_in_channel = (data_buffer[offset] & 0x00ff) |
                                                (data_buffer[offset + 1] << 8);
                        }
                        else if (bytes_in_each_channel == 1) {
                            data_in_channel = data_buffer[offset] & 0x00ff;
                            data_in_channel -= 128; //in wave, 8-bit are unsigned, so shifting to signed
                        }

                        offset += bytes_in_each_channel;

                        wav_data[xchannels]=data_in_channel;
                    }

                }
                else {
                    printf("Error reading file. %d bytesn", read);
                    break;
                }

            } // 	for (i =1; i <= num_samples; i++) {

        } // 	if (size_is_correct) { 

    } //  if (header.format_type == 1) { 

 fclose(ptr);

  // cleanup before quitting
 free(filename);



 int length = header.channels;
 int windowSize = 512;
 int hop_size = 512;
 int n_elements = (length/(windowSize/2))*((windowSize/2)+1);
 int sample_freq = header.sample_rate;
 double* magnitude = malloc(n_elements*sizeof(double));
 *height=length/(windowSize/2);
 *weight=(windowSize/2)+1;
 printf("avant stft\n");
 stft(wav_data,n_elements,windowSize,hop_size,magnitude,sample_freq,header.channels);
 return magnitude;
}




/**
 * Convert seconds into hh:mm:ss format
 * Params:
 *	seconds - seconds value
 * Returns: hms - formatted string
 **/
 char* seconds_to_time(float raw_seconds) {
  char *hms;
  int hours, hours_residue, minutes, seconds, milliseconds;
  hms = (char*) malloc(100);

  sprintf(hms, "%f", raw_seconds);

  hours = (int) raw_seconds/3600;
  hours_residue = (int) raw_seconds % 3600;
  minutes = hours_residue/60;
  seconds = hours_residue % 60;
  milliseconds = 0;

  // get the decimal part of raw_seconds to get milliseconds
  char *pos;
  pos = strchr(hms, '.');
  int ipos = (int) (pos - hms);
  char decimalpart[15];
  memset(decimalpart, ' ', sizeof(decimalpart));
  strncpy(decimalpart, &hms[ipos+1], 3);
  milliseconds = atoi(decimalpart);	

  
  sprintf(hms, "%d:%d:%d.%d", hours, minutes, seconds, milliseconds);
  return hms;
}