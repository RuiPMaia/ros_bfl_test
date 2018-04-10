//

#ifndef __CTS_
#define __CTS_

#include <cmath>


// Sizes
#define STATE_SIZE 3 //state: x,y,z
#define INPUT_SIZE 2 //input: v*deltat, omega*deltat
#define MEAS_SIZE 3 

#define NUM_SAMPLES 500 // Default Number of Samples
#define RESAMPLE_PERIOD 1.0 // Default Resample Period
#define RESAMPLE_THRESHOLD (NUM_SAMPLES/4.0) // Threshold for Dynamic Resampling

//Initial position and orientation
#define X_0 0.0
#define Y_0 0.0
#define Z_0 0.0
// Prior:
// Initial estimate of position and orientation
#define PRIOR_MU_X 0.0
#define PRIOR_MU_Y 0.0
#define PRIOR_MU_Z 0.0
// Initial covariances of position and orientation
#define PRIOR_COV_X pow(0.01,2)
#define PRIOR_COV_Y pow(0.01,2)
#define PRIOR_COV_Z pow(0.01,2)

// System Noise
#define MU_SYSTEM_NOISE_X 0.0
#define MU_SYSTEM_NOISE_Y 0.0
#define MU_SYSTEM_NOISE_Z 0.0
#define SIGMA_SYSTEM_NOISE_X pow(0.01,2)
#define SIGMA_SYSTEM_NOISE_Y pow(0.01,2)
#define SIGMA_SYSTEM_NOISE_Z pow(0.01,2)

// Measurement noise
#define MU_MEAS_NOISE_X 0.0
#define MU_MEAS_NOISE_Y 0.0
#define MU_MEAS_NOISE_Z 0.0
#define SIGMA_MEAS_NOISE_X pow(0.1,2)
#define SIGMA_MEAS_NOISE_Y pow(0.1,2)
#define SIGMA_MEAS_NOISE_Z pow(0.1,2)

#endif //__CTS
