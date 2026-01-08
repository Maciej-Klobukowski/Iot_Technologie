#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "pigpio-master/pigpio.h"


static volatile int keep_running = 1;

static void handle_sigint(int sig)
{
    (void)sig;
    keep_running = 0;
}

int main(void)
{
    // 4 LEDs links -> rechts (BCM GPIO nummers)
    static const unsigned int LED_PINS[4] = {17, 27, 22, 26};
    const int NUM_LEDS = 4;

    signal(SIGINT, handle_sigint);

    if (gpioInitialise() < 0)
    {
        fprintf(stderr, "gpioInitialise() failed\n");
        return 1;
    }

    // Zet pins als output en alles uit
    for (int i = 0; i < NUM_LEDS; i++)
    {
        gpioSetMode(LED_PINS[i], PI_OUTPUT);
        gpioWrite(LED_PINS[i], PI_OFF);
    }

    printf("4 LEDs links -> rechts op GPIOs: %d, %d, %d, %d (Ctrl+C om te stoppen)\n",
           LED_PINS[0], LED_PINS[1], LED_PINS[2], LED_PINS[3]);

    while (keep_running)
    {
        for (int i = 0; i < NUM_LEDS && keep_running; i++)
        {
            // Alles uit (zodat er maar 1 LED tegelijk aan is)
            for (int j = 0; j < NUM_LEDS; j++)
                gpioWrite(LED_PINS[j], PI_OFF);

            // Huidige LED aan
            gpioWrite(LED_PINS[i], PI_ON);

            usleep(250000); // 250 ms per LED (pas aan naar smaak)
        }
    }

    // Opruimen: alles uit en pigpio stoppen
    for (int i = 0; i < NUM_LEDS; i++)
        gpioWrite(LED_PINS[i], PI_OFF);

    gpioTerminate();
    puts("Gestopt.");
    return 0;
}
