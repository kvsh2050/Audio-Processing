#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define SAMPLE_RATE 44100

int main(){

    //WAV file varibles
    const float SampleRate = 44100.0; //Samples per second

    //Main variables
    double sine_wave_val;
    double theta;
    double phase_radians;
    double time;
    double freq_w;

    //parameters from user 
    float Amplitude;
    float Frequency;            //In Hertz
    float Phase;                //In Degrees
    float duration_in_sec;

    //User inputs
    printf("Enter Amplitude of Sine wave: ");
    scanf("%f", &Amplitude);    
    printf("Enter Frequency of Sine wave (in Hertz): ");
    scanf("%f", &Frequency);
    printf("Enter Phase of Sine wave (in Degrees): ");
    scanf("%f", &Phase);
    printf("Enter Duration for which Sine wave is to be generated (in seconds): ");
    scanf("%f", &duration_in_sec);

    //Converting into correct format
    freq_w = 2*PI*Frequency;
    phase_radians = (PI/180)*Phase;
    int num_sample = (int)(SampleRate*duration_in_sec);

    //PCM
    short int pcm_array[num_sample];

    //For generating sine wave
    for (int n = 0; n < num_sample; n++){
        theta  = (freq_w * n * (1/SampleRate)) + phase_radians;     // t = nTs
        sine_wave_val = (Amplitude)*sin(theta);
        printf("DEBUG: n: %d sine values: %f\n", n, sine_wave_val);
        //Storing in PCM array
        pcm_array[n]= (short int)sine_wave_val;
        printf("Value stored in array at %d is %d\n", n, pcm_array[n]);
    }
    //How can i scale up this ? from -1 to 1
    //I did not use any ptr here
    int status = 0;

    //Store as a .raw file.
    FILE* file_ptr;
    file_ptr = fopen("sine.raw", "wb");
    
    status = fwrite(&pcm_array, 2 ,sizeof(pcm_array),file_ptr);
    if (status){
         printf("Success!!\n");
    }
    fclose(file_ptr);
    return 0;
}


//    for (time = 0 ; time < duration_in_sec; time += (1/SampleRate))
//noticed some discrepanices at the last after 5 seconds some data is beign added?