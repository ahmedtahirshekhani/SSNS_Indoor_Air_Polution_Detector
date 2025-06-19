#include <stdint.h> 
#include "sensirion_i2c.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>


void sensorirn_sleep_usec(uint32_t useconds)
{
    int32_t remaining = useconds;
    while (remaining > 0) {
        remaining = k_usleep(remaining);
    }
}

int8_t sensorirn_i2c_read(const struct i2c_dt_spec *dev_bus, uint8_t *data, uint16_t count)
{
    return i2c_read_dt(dev_bus, data, count);
}

int8_t sensorirn_i2c_write(const struct i2c_dt_spec *dev_bus, uint8_t *data, uint16_t count)
{
    return i2c_write_dt(dev_bus, data, count);
}
