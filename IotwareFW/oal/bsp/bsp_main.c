#include "bsp_main.h"

// #include "zephyr.h"
// #include "device.h"
// #include "gpio.h"

void bsp_delay_us(uint32_t us)
{
    // nrf_delay_us(us);
}

void bsp_init_mcu(void)
{
	
}

void bsp_init_board(void)
{
	bsp_init_mcu();
}

/*
 * gpio
 */

void bsp_init_gpio(void)
{
	
}

void bsp_config_gpio(uint8_t port, uint8_t gpio, uint8_t direction, 
					 uint8_t pull, uint32_t speed, uint8_t input, 
					 uint8_t drive, uint8_t sense)
{
	// gpio_pin_configure(dev, 2, GPIO_DIR_OUT);
}

void 
bsp_set_gpio(uint8_t port, uint8_t gpio, uint8_t value)
{

}

void 
bsp_get_gpio(uint8_t port, uint8_t gpio, uint8_t * p_value)
{

}

void 
bsp_toggle_gpio(uint8_t port, uint8_t gpio) 
{
	
}

/*
	Digital
 */

void 
bsp_init_digital(uint8_t pin, uint8_t mode)
{

}

void 
bsp_put_digital(uint8_t pin, uint8_t value)
{
	
}

uint8_t 
bsp_get_digital(uint8_t pin)
{
	
	return 0;
}

void 
bsp_toggle_digital(uint8_t pin)
{
	
}

/*
   --- uart ---
 */

int bsp_init_uart( uint8_t port , uint32_t baud_rate)
{
    return 0;
}

int bsp_deinit_uart(uint8_t port)
{
	return 0;
}

int bsp_putc_uart(uint8_t port, char ch)
{
	return 0;
}

extern char ugetch();

int bsp_getc_uart(uint8_t port, char *pch)
{
    return 0;
}

void bsp_printf(const char *format, ...)
{
}

iw_error_t bsp_init_adc(uint8_t adc_num, uint8_t bank, uint8_t gpio)  
{
	return IW_FAIL;
}

iw_error_t bsp_deinit_adc(uint8_t adc_num)
{
	return IW_FAIL;
}

iw_error_t bsp_get_voltage(uint8_t adc_num, uint16_t *voltage)
{
    /* not supported... */
	return IW_FAIL;
}

iw_error_t bsp_get_adc(uint8_t adc_num, uint16_t *val)
{
    /* not supported... */
	return IW_FAIL;
}

iw_error_t bsp_init_analog(uint8_t adc_num, uint8_t defined_pin)
{
    /* not supported... */
	return IW_FAIL;
}

iw_error_t bsp_deinit_analog(uint8_t adc_num)
{
    /* not supported... */
	return IW_FAIL;
}

uint16_t bsp_get_analog(uint8_t adc_num)
{
    /* not supported... */
    return -1;
}

int bsp_init_i2c(uint8_t port)
{
	return 0;
}

int bsp_deinit_i2c( uint8_t port )
{
	return 0;
	// int r = -1;
	
	// if( port == BSP_I2C1 )
	// {
	//     nrf_drv_twi_uninit( &i2c_0_inst );
	// 	r = 0;
	// }
	// else if( port == BSP_I2C2 )
	// {
	//     nrf_drv_twi_uninit( &i2c_1_inst );
	// 	r = 0;
	// }
    // else
    // {
	// 	iw_printf("CHECK I2C PORT Deinit(%d)\n", port);
	// 	return -1;
	// }    
	
	// return r;
}

// #define I2C_RETRY_NUM (0x1Fu)
int bsp_xfer_i2c(bsp_i2c_msg_t *msg, uint32_t num)
{
	return 0;
// 	int r = 0;
// 	int retry = I2C_RETRY_NUM;
    
// 	for(int i = 0; i < num && r == 0; i++) {
// 		bsp_i2c_inst_t *pinst = &i2c_inst[ msg[i].port ];
// 		uint8_t start_addr  = (uint8_t)((msg[i].addr & 0xfe) >> 1);

// 		if((0 < msg[i].tx_len) && (msg[i].tx_buf)) {
// 			bool no_stop = (0 < msg[i].rx_len) && (msg[i].rx_buf);
// #if 0
// 			pinst->xfer_done = false;

// 			if( nrf_drv_twi_tx( pinst->instance, start_addr, msg[i].tx_buf, msg[i].tx_len, no_stop ) == NRF_SUCCESS )
// 			{
// 				while( (pinst->xfer_done == false) && retry )
//                 {            
//                     retry--;
//                 	iw_sleep(1);
//                 }
//                 if(retry)   r = 0;
//                 else        r = -1;
// 			}
// #else
// 			do {
// 				pinst->xfer_done = false;
// 				if(nrf_drv_twi_tx(pinst->instance, start_addr, msg[i].tx_buf, msg[i].tx_len, no_stop) != NRF_SUCCESS) {
// 					r = -1;
// 					break;
// 				}
// 				while(!pinst->xfer_done);
			
// 				if(pinst->result == NRF_DRV_TWI_EVT_DONE) {
// 					r = 0;
// 					break;
// 				}
// 				iw_sleep(1);
				
// 				r = -1;
// 			} while(retry--);
// #endif				
// 		}

// 		if((0 < msg[i].rx_len) && (msg[i].rx_buf)) {
// 	        retry = I2C_RETRY_NUM;
// #if 0
// 			pinst->xfer_done = false;

// 			if( nrf_drv_twi_rx( pinst->instance, start_addr, msg[i].rx_buf, msg[i].rx_len ) == NRF_SUCCESS )
// 			{
// 				while( (pinst->xfer_done == false) && retry )
//                 {            
//                     retry--;
//                 	iw_sleep(1);
//                 }
//                 if(retry)   r = 0;
//                 else        r = -1;
// 			}
// #else
// 			do {
// 				pinst->xfer_done = false;
// 				if(nrf_drv_twi_rx(pinst->instance, start_addr, msg[i].rx_buf, msg[i].rx_len) != NRF_SUCCESS) {
// 					r = -1;
// 					break;
// 				}
// 				while(!pinst->xfer_done);

// 				if(pinst->result == NRF_DRV_TWI_EVT_DONE) {
// 					r = 0;
// 					break;
// 				}
// 				iw_sleep(1);
				
// 				r = -1;
// 			} while(retry--);
// #endif
// 		}
// 	}
	
// 	return r;
}

// typedef struct
// {
// 	const nrf_drv_spi_t *instance;
// 	volatile bool xfer_done;

// } bsp_spi_inst_t;

// static bsp_spi_inst_t spi_inst[2];

// #define SPI_0_INSTANCE			0 /**< SPI instance index. */
// #define SPI_0_IRQ_PRIORITY		1

// static const nrf_drv_spi_t spi_0_inst = NRF_DRV_SPI_INSTANCE(SPI_0_INSTANCE);

// static void spi_0_event_handler(const nrf_drv_spi_evt_t *p_event)
// {
// 	//iw_irq_count += 1;
//     spi_inst[ 0 ].xfer_done = true;
// }

// #define SPI_1_INSTANCE			1 /**< SPI instance index. */
// #define SPI_1_IRQ_PRIORITY		7

// static const nrf_drv_spi_t spi_1_inst = NRF_DRV_SPI_INSTANCE(SPI_1_INSTANCE);

// static void spi_1_event_handler(const nrf_drv_spi_evt_t *p_event)
// {
// 	//wdk_irq_count += 1;
//     spi_inst[ 1 ].xfer_done = true;
// }

int bsp_init_spi( uint8_t port )
{
	return 0;
	// int r = -1;
	
	// if( port == BSP_SPI1 )
	// {
	// 	spi_inst[ 0 ].instance = &spi_0_inst;

	//     ret_code_t err_code;
	//     nrf_drv_spi_config_t spi_0_config = NRF_DRV_SPI_DEFAULT_CONFIG;

	// 	// SPI_DEFAULT_CONFIG_IRQ_PRIORITY
	// 	// NRF_DRV_SPI_FREQ_4M
	// 	// NRF_DRV_SPI_MODE_0
	// 	// NRF_DRV_SPI_BIT_ORDER_MSB_FIRST

	//     spi_0_config.ss_pin       = PIN_SPI_0_SS;//NRF_DRV_SPI_PIN_NOT_USED;
	//     spi_0_config.miso_pin     = PIN_SPI_0_MISO;
	//     spi_0_config.mosi_pin     = PIN_SPI_0_MOSI;
	//     spi_0_config.sck_pin      = PIN_SPI_0_SCK;
	//     spi_0_config.irq_priority = SPI_0_IRQ_PRIORITY;
	// 	spi_0_config.frequency    = NRF_DRV_SPI_FREQ_4M;

	//     //err_code = nrf_drv_spi_init( &( spi_0_inst ), &( spi_0_config ), spi_0_event_handler );	// non-block
	// 	err_code = nrf_drv_spi_init(&( spi_0_inst ), &( spi_0_config ), 0);							// block
	// 	if(err_code == NRF_SUCCESS)	
	// 		r = 0;		
	// 	//APP_ERROR_CHECK(err_code);
	// 	//r = 0;
	// }
	// else if( port == BSP_SPI2 )
	// {
	// 	spi_inst[ 1 ].instance = &spi_1_inst;

	//     ret_code_t err_code;
	//     nrf_drv_spi_config_t spi_1_config = NRF_DRV_SPI_DEFAULT_CONFIG;

	// 	nrf_gpio_cfg_output(PIN_SPI_1_SS);
	// 	nrf_gpio_pin_set(PIN_SPI_1_SS);

	// 	// SPI_DEFAULT_CONFIG_IRQ_PRIORITY
	// 	// NRF_DRV_SPI_FREQ_4M
	// 	// NRF_DRV_SPI_MODE_0
	// 	// NRF_DRV_SPI_BIT_ORDER_MSB_FIRST

	//     spi_1_config.ss_pin       = PIN_SPI_1_SS;//NRF_DRV_SPI_PIN_NOT_USED;
	//     spi_1_config.miso_pin     = PIN_SPI_1_MISO;
	//     spi_1_config.mosi_pin     = PIN_SPI_1_MOSI;
	//     spi_1_config.sck_pin      = PIN_SPI_1_SCK;
	//     spi_1_config.irq_priority = SPI_1_IRQ_PRIORITY;

	//     //err_code = nrf_drv_spi_init( &( spi_1_inst ), &( spi_1_config ), spi_1_event_handler );	// non-block
	// 	err_code = nrf_drv_spi_init( &( spi_1_inst ), &( spi_1_config ), 0 );						// block
	// 	if(err_code == NRF_SUCCESS)	
	// 		r = 0;
	// 	//APP_ERROR_CHECK(err_code);
	// 	//r = 0;
	// }

	// return r;
}

int bsp_deinit_spi(uint8_t port)
{
	return 0;
	// int r = -1;

	// if( port == BSP_SPI1 )
	// {
	// 	nrf_drv_spi_uninit( &( spi_0_inst ) );
	// 	r = 0;
	// }
	// else if( port == BSP_SPI2 )
	// {
	// 	nrf_drv_spi_uninit( &( spi_1_inst ) );
	// 	r = 0;
	// }

	// return r;
}

int 
bsp_xfer_spi(bsp_spi_msg_t *msg, int num)
{
	return 0;
	// int r = 0;

	// for( int i = 0; i < num && r == 0; i++ )
	// {
	// 	bsp_spi_inst_t *pinst = &spi_inst[ msg[i].port ];

	// 	pinst->xfer_done = false;

	// 	if( nrf_drv_spi_transfer( pinst->instance, msg[i].tx_buf, msg[i].tx_len, msg[i].rx_buf, msg[i].rx_len ) == NRF_SUCCESS )
	// 	{
	// 		while( pinst->xfer_done == false )
	// 		{
	// 			__WFE();
	// 		}
	// 		r = 0;
	// 	}
	// }
	// return r;
}

// static uint8_t       m_tx_buf[2];    /**< TX buffer. */
// static uint8_t       m_rx_buf[2];    /**< RX buffer. */
// static ret_code_t 	 err_code;

int 
bsp_get_spi(uint8_t port, uint8_t regAddress, uint8_t *data) 
{
	return 0;
	// int r = -1;
	// m_tx_buf[0] = regAddress | 0x80; 
	// m_tx_buf[1] = 0; 					// don't care

	// if( port == BSP_SPI1 )
	// {
	// 	err_code = nrf_drv_spi_transfer(&(spi_0_inst), ( uint8_t* )&m_tx_buf, 2, ( uint8_t* )&m_rx_buf, 2);
	// }
	// else if( port == BSP_SPI2 )
	// {
	// 	err_code = nrf_drv_spi_transfer(&(spi_1_inst), ( uint8_t* )&m_tx_buf, 2, ( uint8_t* )&m_rx_buf, 2);
	// }

	// if(err_code == NRF_SUCCESS)	
	// 	r = 0;

	// *data = m_rx_buf[1];		// Discard m_rx_buf[0]
    // return r;
}

int bsp_set_spi(uint8_t port, uint8_t regAddress, uint8_t value) 
{
    /* not supported ... */
	return 0;
}
