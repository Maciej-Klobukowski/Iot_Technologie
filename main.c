#include <stdio.h>
#include <pigpio.h>

#define LED_PIN 17   // GPIO17 = pin 11 op Raspberry Pi

int main() {
    if (gpioInitialise() < 0) {
        printf("Pigpio initialisatie mislukt!\n");
        return 1;
    }

    gpioSetMode(LED_PIN, PI_OUTPUT);

    printf("LED knipperen op GPIO %d\n", LED_PIN);

    for (int i = 0; i < 10; i++) {
        gpioWrite(LED_PIN, 1);
        time_sleep(0.5);
        gpioWrite(LED_PIN, 0);
        time_sleep(0.5);
    }

    gpioTerminate();
    printf("Klaar.\n");

    return 0;
}
