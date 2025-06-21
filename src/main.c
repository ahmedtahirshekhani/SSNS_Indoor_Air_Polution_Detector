#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "sensor/sps30/sps30.h"
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor/ccs811.h>

#include "sensor/scd4x/scd4x.h"

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_scd41)
#error "No sensirion,scd4x compatible node found in the device tree"
#endif

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_sps30)
#error "No sensirion,sps30 compatible node found in the device tree"
#endif

const struct device *scd41 = DEVICE_DT_GET_ANY(sensirion_scd41);
const struct device *ccs811 = DEVICE_DT_GET_ANY(ams_ccs811);
const struct device *sps30 = DEVICE_DT_GET_ANY(sensirion_sps30);

int main(void)
{

	if (!device_is_ready(scd41))
	{
		printk("SCD41 device is not ready\n");
		return 1;
	}
	if (!device_is_ready(ccs811))
	{
		printk("CCS811 device is not ready\n");
		return 1;
	}
	if (!device_is_ready(sps30))
	{
		printk("SPS30 device not ready\n");
		return 1;
	}
	struct sensor_value pm_1p0, pm_2p5, pm_10p0, pm_4p0, pm_0p5, pm_1p0_nc, pm_2p5_nc, pm_4p0_nc, pm_10p0_nc, typical_particle_size;

	struct sensor_value co2, temo, humi;
	struct sensor_value eco2, tvoc;
	while (true)
	{

		sensor_sample_fetch(scd41);
		sensor_channel_get(scd41, SENSOR_CHAN_CO2_SCD, &co2);
		sensor_channel_get(scd41, SENSOR_CHAN_AMBIENT_TEMP, &temo);
		sensor_channel_get(scd41, SENSOR_CHAN_HUMIDITY, &humi);
		// printk("CO2: %d.%06d ppm, Temperature: %d.%06d C, Humidity: %d.%06d %%\n",
			//    co2.val1, co2.val2, temo.val1, temo.val2, humi.val1, humi.val2);

		int ret = sensor_sample_fetch(ccs811);
		if (ret)
		{
			printk("Failed to fetch CCS811 sensor data: %d\n", ret);
			k_sleep(K_SECONDS(5));
			continue;
		}

		ret = sensor_channel_get(ccs811, SENSOR_CHAN_CO2, &eco2);
		if (ret)
		{
			printk("Failed to get eCO2 data: %d\n", ret);
		}

		ret = sensor_channel_get(ccs811, SENSOR_CHAN_VOC, &tvoc);
		if (ret)
		{
			printk("Failed to get TVOC data: %d\n", ret);
		}

		// printk("eCO2: %d ppm, TVOC: %d ppb\n", eco2.val1, tvoc.val1);
		// print json with unit
		printk("{\n");
		printk("  \"co2\": \"%d.%06d\",\n", co2.val1, co2.val2);
		printk("  \"co2_unit\": \"ppm\",\n");
		printk("  \"temperature\": \"%d.%06d\",\n", temo.val1, temo.val2);
		printk("  \"temperature_unit\": \"C\",\n");
		printk("  \"humidity\": \"%d.%06d\",\n", humi.val1, humi.val2);
		printk("  \"humidity_unit\": \"%%\",\n");
		printk("  \"eco2\": \"%d.%06d\",\n", eco2.val1, eco2.val2);
		printk("  \"eco2_unit\": \"ppm\",\n");
		printk("  \"tvoc\": \"%d.%06d\",\n", tvoc.val1, tvoc.val2);
		printk("  \"tvoc_unit\": \"ppb\",\n");
		// printk("}\n");
		

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

		// make json with unit and print
		// printk("{\n");
		printk("  \"pm_1_0\": \"%d.%06d\",\n", pm_1p0.val1, pm_1p0.val2);
		printk("  \"pm_1_0_unit\": \"mg/m^3\",\n");
		printk("  \"pm_2_5\": \"%d.%06d\",\n", pm_2p5.val1, pm_2p5.val2);
		printk("  \"pm_2_5_unit\": \"mg/m^3\",\n");
		printk("  \"pm_10_0\": \"%d.%06d\",\n", pm_10p0.val1, pm_10p0.val2);
		printk("  \"pm_10_0_unit\": \"mg/m^3\",\n");
		printk("  \"pm_4_0\": \"%d.%06d\",\n", pm_4p0.val1, pm_4p0.val2);
		printk("  \"pm_4_0_unit\": \"mg/m^3\",\n");
		printk("  \"pm_0_5\": \"%d.%06d\",\n", pm_0p5.val1, pm_0p5.val2);
		printk("  \"pm_0_5_unit\": \"mg/m^3\",\n");
		printk("  \"pm_1_0_nc\": \"%d.%06d\",\n", pm_1p0_nc.val1, pm_1p0_nc.val2);
		printk("  \"pm_1_0_nc_unit\": \"/cm^3\",\n");
		printk("  \"pm_2_5_nc\": \"%d.%06d\",\n", pm_2p5_nc.val1, pm_2p5_nc.val2);
		printk("  \"pm_2_5_nc_unit\": \"/cm^3\",\n");
		printk("  \"pm_4_0_nc\": \"%d.%06d\",\n", pm_4p0_nc.val1, pm_4p0_nc.val2);
		printk("  \"pm_4_0_nc_unit\": \"/cm^3\",\n");
		printk("  \"pm_10_0_nc\": \"%d.%06d\",\n", pm_10p0_nc.val1, pm_10p0_nc.val2);
		printk("  \"pm_10_0_nc_unit\": \"/cm^3\",\n");
		printk("  \"typical_particle_size\": \"%d.%06d\",\n", typical_particle_size.val1, typical_particle_size.val2);
		printk("  \"typical_particle_size_unit\": \"µm\"\n");
		printk("}\n");

		k_sleep(K_SECONDS(5));
	}
	return 0;
}
