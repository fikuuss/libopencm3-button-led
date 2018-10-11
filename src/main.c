#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void Delay(uint32_t nCount)
{
    while (nCount--)
    {
    }
}

static void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	/* Manually: */
	// RCC_AHB1ENR |= RCC_AHB1ENR_IOPDEN;
	/* Using API functions: */
	rcc_periph_clock_enable(RCC_GPIOD);

	/* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
	/* Manually: */
	// GPIOD_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 4) + 2));
	// GPIOD_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((8 - 8) * 4));
	/* Using API functions: */
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);

	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13);
}

int main(void)
{
    gpio_setup();

    while (1)
    {
        if (gpio_get(GPIOA, GPIO0) == 0)
        {
            if (gpio_get(GPIOD, GPIO13))
                gpio_clear(GPIOD, GPIO13);
            else
                gpio_set(GPIOD, GPIO13);
            Delay(5000);
            while (gpio_get(GPIOA, GPIO0) == 0);
            Delay(5000);
        }
    }
}