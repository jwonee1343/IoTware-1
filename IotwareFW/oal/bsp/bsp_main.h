#ifndef BSP_MAIN_H
#define BSP_MAIN_H

#include "iw_common.h"
// #include "iw_bsp.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IW_SYSTEM_CLOCK 64 // 64 MHz

// extern UART_HandleTypeDef huart1;
// extern UART_HandleTypeDef huart2;
// extern UART_HandleTypeDef huart3;

// extern I2C_HandleTypeDef hi2c2;
// extern I2C_HandleTypeDef hi2c3;

// extern SPI_HandleTypeDef hspi2;
// extern SPI_HandleTypeDef hspi3;

//#define IW_SYSTEM_CLOCK 80 // 80 MHz
//#define STM32_ADC_MAX_NUM 3

typedef enum {
	BSP_ADC1 = 0,
	BSP_ADC2,
	BSP_ADC3,
	BSP_ADC_MAX
}bsp_adc_e;

typedef enum {
	BSP_UART1 = 0,	// debug
	BSP_UART2,		// Lora, WiFi
	BSP_UART3,
	BSP_UART_MAX
}bsp_uart_e;

typedef enum {
	BSP_I2C1 = 0,
	BSP_I2C2,
	BSP_I2C3,
	BSP_I2C_MAX
}bsp_i2c_e;

typedef enum {
	BSP_SPI1 = 0,
	BSP_SPI2,
	BSP_SPI3,
	BSP_SPI_MAX
}bsp_spi_e;

// void SystemClock_Config(void);

typedef enum{
	BANK_GPIOA=0,
	BANK_GPIOB,
	BANK_GPIOC,
	BANK_GPIOD,
	BANK_GPIOE,
	BANK_GPIOF,
	BANK_GPIOG,
	BANK_GPIOH,
	BANK_GPIO_MAX,
}stm_gpio_bank_t;

typedef enum{
	PIN_GPIO0=0,
	PIN_GPIO1,
	PIN_GPIO2,
	PIN_GPIO3,
	PIN_GPIO4,
	PIN_GPIO5,
	PIN_GPIO6,
	PIN_GPIO7,
	PIN_GPIO8,
	PIN_GPIO9,
	PIN_GPIO10,
	PIN_GPIO11,
	PIN_GPIO12,
	PIN_GPIO13,
	PIN_GPIO14,
	PIN_GPIO15,
	PIN_GPIO_MAX
}stm_gpio_t;

struct adc_gpio_info{
	stm_gpio_bank_t bank;
	stm_gpio_t gpio;
	uint32_t channel;
};

typedef enum {
	DIGITAL_INPUT_NOPULL = 0,
	DIGITAL_INPUT_PULLUP,
	DIGITAL_INPUT_PULLDOWN,
	DIGITAL_OUTPUT_PUSHPULL,
	DIGITAL_OUTPUT_OPENDRAIN
}bsp_digital_mode;

typedef enum {
	DIGITAL_LOW = 0,
	DIGITAL_HIGH
}bsp_digital_value;


#define STM_GPIO_PIN_MAP(bank, pin) ((bank << 5) | (pin & 0x1F))

#if defined(IOTWARE_BOARD)

#define PIN_TEMP_PWR_EN     STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO7)

#define PIN_BLE_PWR_EN      STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO11)
#define PIN_LORA_PWR_EN		STM_GPIO_PIN_MAP(BANK_GPIOD, PIN_GPIO2)
#define PIN_WIFI_PWR_EN     STM_GPIO_PIN_MAP(BANK_GPIOD, PIN_GPIO2)

#define PIN_RED_LED         STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO6)
#define PIN_GREEN_LED       STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO7)
#define PIN_BLUE_LED        STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO8)

#define PIN_CO2_PWR_EN   	STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO10)
#define PIN_CO2_RESET		STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO5)

#define PIN_ADC_BATT        STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO0)

#define PIN_I2C2_SCL		STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO10)
#define PIN_I2C2_SDA		STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO11)

#define PIN_I2C3_SCL		STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO0)
#define PIN_I2C3_SDA		STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO1)

#define PIN_UART2_TX		STM_GPIO_PIN_MAP(BANK_GPIOA, PIN_GPIO2)		// LORA
#define PIN_UART2_RX		STM_GPIO_PIN_MAP(BANK_GPIOA, PIN_GPIO3)

#elif defined(DISPOSAL_IOT_BOARD)
#define PIN_RED_LED			STM_GPIO_PIN_MAP(, PIN_GPIO9)
#define PIN_GREEN_LED		STM_GPIO_PIN_MAP(, PIN_GPIO8)
#define PIN_LORA_RESET		STM_GPIO_PIN_MAP(BANK_GPIOA, PIN_GPIO5)
#define PIN_LORA_POWER		STM_GPIO_PIN_MAP(BANK_GPIOB, PIN_GPIO8)
#define PIN_CO2_POWER		STM_GPIO_PIN_MAP(BANK_GPIOC, PIN_GPIO10)
#define PIN_PWR_KEY_EN		STM_GPIO_PIN_MAP(, PIN_GPIO6)
#else
#endif

struct adc_hw_info{
	// ADC_HandleTypeDef   *handle;
	uint8_t port;
	// GPIO_TypeDef * bank;
	uint16_t gpio;
};

void bsp_delay_us(uint32_t us);
//void bsp_get_mcu_info(mcu_type_t *id);
void bsp_init_mcu(void);
void bsp_init_board(void);


void bsp_init_gpio(void);
void bsp_config_gpio(uint8_t bank, uint8_t gpio, uint8_t dir, uint8_t pull, uint32_t speed, uint8_t input, uint8_t drive, uint8_t sense);
void bsp_get_gpio(uint8_t bank, uint8_t gpio, uint8_t *val );
void bsp_set_gpio(uint8_t bank, uint8_t gpio, uint8_t val);
void bsp_toggle_gpio(uint8_t bank, uint8_t gpio); 

void bsp_init_digital(uint8_t defined_pin, uint8_t mode);
void bsp_put_digital(uint8_t defined_pin, uint8_t value);
uint8_t bsp_get_digital(uint8_t defined_pin);
void bsp_toggle_digital(uint8_t defined_pin);

int bsp_init_uart( uint8_t port , uint32_t baud_rate);
int bsp_deinit_uart( uint8_t port );
int bsp_getc_uart( uint8_t port, char *pch );
int bsp_putc_uart( uint8_t port, char ch );
void bsp_printf(const char *format, ...);

/* stm32 adc func */
// #include "stm32l4xx_ll_adc.h"

/* User can use this section to tailor ADCx instance under use and associated
   resources */

/* ## Definition of ADC related resources ################################### */
/* Definition of ADCx clock resources */
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC_CLK_ENABLE()

#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

iw_error_t bsp_init_adc(uint8_t adc_num, uint8_t bank, uint8_t gpio) ; 
iw_error_t bsp_deinit_adc( uint8_t adc_num);
iw_error_t bsp_get_adc(uint8_t adc_num, uint16_t* val);
iw_error_t bsp_get_voltage(uint8_t adc_num, uint16_t* voltage);

iw_error_t bsp_init_analog(uint8_t adc_num, uint8_t defined_pin);
iw_error_t bsp_deinit_analog(uint8_t adc_num);
uint16_t bsp_get_analog(uint8_t adc_num);


// GPIO_TypeDef * stm32_get_adc_gpio_bank(ADC_HandleTypeDef *hadc);
// uint16_t stm32_get_adc_gpio_pin(ADC_HandleTypeDef *hadc);
// uint32_t stm32_get_adc_irq(ADC_HandleTypeDef *hadc);
// void stm32_enable_adc_gpio_clk(ADC_HandleTypeDef *hadc);	


// #define STM32_I2C_PORT0		0 // SENSOR
// #define STM32_I2C_PORT1		1


typedef struct
{
	uint8_t   port;
	uint8_t   addr;
	uint32_t  	tx_len;
	uint8_t	*tx_buf;
	uint32_t   	rx_len;
	uint8_t	*rx_buf;
}bsp_i2c_msg_t;


int bsp_init_i2c( uint8_t  port );
int bsp_deinit_i2c( uint8_t  port );
int bsp_xfer_i2c( bsp_i2c_msg_t *msg, uint32_t num );

typedef struct
{
	uint8_t     port;
	uint16_t    tx_len;
	uint8_t	   *tx_buf;
	uint16_t    rx_len;
	uint8_t    *rx_buf;
} bsp_spi_msg_t;

int bsp_init_spi(uint8_t port);
int bsp_deinit_spi(uint8_t port);
int bsp_xfer_spi(bsp_spi_msg_t *msg, int num);

extern volatile uint32_t iw_irq_count;
extern volatile uint32_t iw_idle_count;

#endif /* BSP_MAIN_H */