#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "sensor/sps30/sps30.h"

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_sps30)
#error "No sensirion,sps30 compatible node found in the device tree"
#endif
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

const struct device *sps30 = DEVICE_DT_GET_ANY(sensirion_sps30);
int main(void)
{
    printk("Sensor name: %s\n", sps30->name);
    printk("Sensor config: %s\n", sps30->config);
    printk("Sensor api: %s\n", sps30->api);
    printk("Sensor state: %p\n", sps30->state);
    printk("Sensor data: %p\n", sps30->data);

	if (!device_is_ready(sps30)) {
		printk("SPS30 device not ready\n");
		return 1;
	}
	printk("SPS30 device is ready\n");
}