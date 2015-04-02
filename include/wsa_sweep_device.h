#ifndef __WSA_SWEEP_DEVICE_H__
#define __WSA_SWEEP_DEVICE_H__

#include "wsa_lib.h"
#include "wsa_api.h"

/// a struct for holding sweep device properties
struct wsa_sweep_device_properties {
	uint32_t mode;
	uint32_t sample_type;
	uint64_t min_tunable;
	uint64_t max_tunable;
	uint32_t tuning_resolution;
	uint32_t full_bw;
	uint32_t usable_bw;
	uint32_t passband_center;
	uint32_t usable_left;
	uint32_t usable_right;
	uint32_t min_decimation;
	uint32_t max_decimation;
	uint8_t fshift_available;
};

/// a sweep plan entry struct
struct wsa_sweep_plan {


};

/// this struct represents our sweep device object
struct wsa_sweep_device {
	/// a reference to the wsa we're connected to
	struct wsa_device *real_device;
};

/// struct representing a configuration that we are going to sweep with and capture power spectrum data
struct wsa_power_spectrum_config {
	/// the mode to perform the sweep in
	uint32_t mode;

	/// the start frequency
	uint64_t fstart;

	/// the stop frequency
	uint64_t fstop;

	/// the rbw
	uint32_t rbw;

	/// a sweep plan that achieves capturing the spectrum requested
	struct wsa_sweep_plan *sweep_plan;

	/// the float buffer 
	float *buf;

	/// the length of the float buffer
	uint32_t buflen;
};


struct wsa_sweep_device *wsa_sweep_device_new(struct wsa_device *device);
void wsa_sweep_device_free(struct wsa_sweep_device *sweepdev);
int wsa_power_spectrum_alloc(
	struct wsa_sweep_device *sweep_device,
	uint64_t fstart,
	uint64_t fstop,
	uint32_t rbw,
	char const *mode,
	struct wsa_power_spectrum_config **pscfg
);
void wsa_power_spectrum_free(struct wsa_power_spectrum_config *cfg);
int wsa_capture_power_spectrum(
	struct wsa_sweep_device *sweep_device,
	struct wsa_power_spectrum_config *pscfg,
	float **buf
);
#endif
