#define ACT_EXTENDED_PORT     GPIOA
#define ACT_EXTENDED_PIN      GPIO_PIN_0
 
#define ACT_SHRINKED_PORT    GPIOA
#define ACT_SHRINKED_PIN     GPIO_PIN_1
 
#define INPUT_EXTENDED_PORT      GPIOB
#define INPUT_EXTENDED_PIN       GPIO_PIN_0    
 
#define INPUT_SHRINKED_PORT     GPIOB
#define INPUT_SHRINKED_PIN      GPIO_PIN_1

/* GPIO_PinState enum (defined in stm32f4xx_hal_gpio.h):
 *   GPIO_PIN_RESET = 0  →  LOW  (0V)
 *   GPIO_PIN_SET   = 1  →  HIGH (3.3V)
 */

 static void set_extended(bool on)
{
    HAL_GPIO_WritePin(ACT_EXTENDED_PORT, ACT_EXTENDED_PIN, on ? GPIO_PIN_SET : GPIO_PIN_RESET); // void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
}

static void set_SHRINKED(bool on)
{
    HAL_GPIO_WritePin(ACT_SHRINKED_PORT, ACT_SHRINKED_PIN, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static bool read_extended_switch(void)
{
    GPIO_PinState pin_state = HAL_GPIO_ReadPin(INPUT_EXTENDED_PORT, INPUT_EXTENDED_PIN); // GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
     return pin_state == GPIO_PIN_SET; 
}

static bool read_SHRINKED_switch(void)
{
    GPIO_PinState pin_state = HAL_GPIO_ReadPin(INPUT_SHRINKED_PORT, INPUT_SHRINKED_PIN);
     return pin_state == GPIO_PIN_SET;
}