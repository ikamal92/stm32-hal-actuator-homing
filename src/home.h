typedef enum
{
    IDLE = 0,      /**< Not started. */
    SHRINKING,  /**< Phase 1 – retract to find origin switch. */
    EXTENDING,     /**< Phase 2 – extend, measure full travel time. */
    HOME,          /**< Actuator is at the mid-point. */
    ERROR,         /**< Fault: timeout or invalid configuration. */
} HomingState_t;

/**
 * @brief I/O pin descriptor – maps a logical signal to STM32 HAL GPIO.
 */
typedef struct
{
    GPIO_TypeDef *port;   /**< e.g. GPIOA */
    uint16_t      pin;    /**< e.g. GPIO_PIN_5 */
} HomingPin_t;

/**
 * @brief Complete I/O configuration for one homing instance.
 */
typedef struct
{
    HomingPin_t pinExtend;        /**< Output: drives actuator to extend. */
    HomingPin_t pinRetract;       /**< Output: drives actuator to retract. */
    HomingPin_t pinSwitchExtend;  /**< Input: extend end-switch / button. */
    HomingPin_t pinSwitchRetract; /**< Input: retract end-switch / button. */
} HomingIoConfig_t;
