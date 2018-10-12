#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void Delay(int j)
{
    for (int i = 0; i < j; i++) {	/* Wait a bit. */
				__asm__("nop");
			}
}

static void gpio_setup(void)
{
    /* Enable GPIOD clock. */
    /* Manually: */
    // RCC_AHB1ENR |= RCC_AHB1ENR_IOPDEN;
    /* Using API functions: */
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_GPIOA);

    /* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
    /* Manually: */
    // GPIOD_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 4) + 2));
    // GPIOD_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((8 - 8) * 4));
    /* Using API functions: */
    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);

    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

uint16_t changeLED(uint16_t currentLED)
{
    switch (currentLED)
    {
    case GPIO12:
        gpio_toggle(GPIOD, GPIO12);
        gpio_toggle(GPIOD, GPIO13);
        return GPIO13;
    case GPIO13:
        gpio_toggle(GPIOD, GPIO13);
        gpio_toggle(GPIOD, GPIO14);
        return GPIO14;
    case GPIO14:
        gpio_toggle(GPIOD, GPIO14);
        gpio_toggle(GPIOD, GPIO15);
        return GPIO15;
    case GPIO15:
        gpio_toggle(GPIOD, GPIO15);
        gpio_toggle(GPIOD, GPIO12);
        return GPIO12;
    }

    return GPIO12;
}

int main(void)
{
    uint16_t currentLED = GPIO12;

    gpio_setup();

    gpio_set(GPIOD, GPIO12);

    while (1)
    {
        if (gpio_get(GPIOA, GPIO0) == 0)
        {
            currentLED = changeLED(currentLED);

            Delay(10000);
            while (gpio_get(GPIOA, GPIO0) == 0)
            {
                Delay(10000);
            }
        }
    }
}