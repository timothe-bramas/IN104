double hamming(int windowLength, double *buffer);
double* stft(double *wav_data, int samples, int windowSize, int hop_size, double *magnitude, int sample_freq, int length);