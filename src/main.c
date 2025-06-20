#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "sensor/sps30/sps30.h"
#include <zephyr/sys/printk.h>


#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_sps30)
#error "No sensirion,sps30 compatible node found in the device tree"
#endif

const struct device *sps30 = DEVICE_DT_GET_ANY(sensirion_sps30);

int main(void)
{
	if (!device_is_ready(sps30)) {
		printk("SPS30 device not ready\n");
		return 1;
	}
	printk("SPS30 device is ready\n");
	struct sensor_value pm_1p0, pm_2p5, pm_10p0, pm_4p0, pm_0p5, pm_1p0_nc, pm_2p5_nc, pm_4p0_nc, pm_10p0_nc, typical_particle_size;

	while(1) {
		sensor_sample_fetch(sps30);
		sensor_channel_get(sps30, SENSOR_CHAN_PM_1_0, &pm_1p0);
		sensor_channel_get(sps30, SENSOR_CHAN_PM_2_5, &pm_2p5);
		sensor_channel_get(sps30, SENSOR_CHAN_PM_10, &pm_10p0);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_4_0, &pm_4p0);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_0_5, &pm_0p5);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_1_0_NC, &pm_1p0_nc);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_2_5_NC, &pm_2p5_nc);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_4_0_NC, &pm_4p0_nc);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_10_NC, &pm_10p0_nc);
        sensor_channel_get(sps30, SENSOR_CHAN_PM_TYPICAL_PARTICLE_SIZE, &typical_particle_size);


     
		printk("SPS30 Sensor Data:\n");
		printk("PM 1.0: %d.%06d mg/m^3\n", pm_1p0.val1, pm_1p0.val2);
		printk("PM 2.5: %d.%06d mg/m^3\n", pm_2p5.val1, pm_2p5.val2);
		printk("PM 10.0: %d.%06d mg/m^3\n", pm_10p0.val1, pm_10p0.val2);
        printk("PM 4.0: %d.%06d mg/m^3\n", pm_4p0.val1, pm_4p0.val2);
        printk("PM 0.5: %d.%06d mg/m^3\n", pm_0p5.val1, pm_0p5.val2);
        printk("PM 1.0 NC: %d.%06d /cm^3\n", pm_1p0_nc.val1, pm_1p0_nc.val2);
        printk("PM 2.5 NC: %d.%06d /cm^3\n", pm_2p5_nc.val1, pm_2p5_nc.val2);
        printk("PM 4.0 NC: %d.%06d /cm^3\n", pm_4p0_nc.val1, pm_4p0_nc.val2);
        printk("PM 10.0 NC: %d.%06d /cm^3\n", pm_10p0_nc.val1, pm_10p0_nc.val2);
        printk("Typical Particle Size: %d.%06d µm\n", typical_particle_size.val1, typical_particle_size.val2);

		k_sleep(K_SECONDS(5));
	}
	return 0;
}

