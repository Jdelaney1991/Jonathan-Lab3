#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654

static DevI2C devI2c(PB_11, PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5); // high address

DigitalOut led1(LED1);

float computeAngle(int x, int y, int z) {
    float res = 0;

    // Calculate the angle using accelerometer data
    // You can write your angle calculation logic here based on x, y, and z values

    return res;
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res = 0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while (1) {

        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res);

        // Check if the board is lying flat (you may need to adjust the threshold values based on your observations)
        if (axes[0] > 900 && axes[0] < 1100 && axes[1] > 900 && axes[1] < 1100 && axes[2] > 19000 && axes[2] < 21000) {
            led1 = 1; // Turn ON LED1 (green LED) when the board is lying flat
        } else {
            led1 = 0; // Turn OFF LED1 otherwise
        }

        thread_sleep_for(2000);
    }
}
