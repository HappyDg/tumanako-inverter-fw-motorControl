/*
 * This file is part of the tumanako_vc project.
 *
 * Copyright (C) 2010 Johannes Huebner <contact@johanneshuebner.com>
 * Copyright (C) 2010 Edward Cheeseman <cheesemanedward@gmail.com>
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <libopencm3/cm3/common.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/rtc.h>
#include "hwdefs.h"
#include "hwinit.h"

/**
* Start clocks of all needed peripherals
*/
void clock_setup(void)
{
   RCC_CLOCK_SETUP();

	rcc_set_ppre1(RCC_CFGR_PPRE1_HCLK_DIV2);
	rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV6);

   //The reset value for PRIGROUP (=0) is not actually a defined
   //value. Explicitly set 16 preemtion priorities
   SCB_AIRCR = SCB_AIRCR_VECTKEY | SCB_AIRCR_PRIGROUP_GROUP16_NOSUB;

   rcc_periph_clock_enable(RCC_GPIOA);
   rcc_periph_clock_enable(RCC_GPIOB);
   rcc_periph_clock_enable(RCC_GPIOC);
   rcc_periph_clock_enable(RCC_GPIOD);
   rcc_periph_clock_enable(RCC_USART3);
   rcc_periph_clock_enable(RCC_TIM1); //Main PWM
   rcc_periph_clock_enable(RCC_TIM2); //Scheduler
   rcc_periph_clock_enable(RCC_TIM3); //Rotor Encoder
   rcc_periph_clock_enable(RCC_TIM4); //Overcurrent / AUX PWM
   rcc_periph_clock_enable(RCC_DMA1);  //ADC and Encoder
   rcc_periph_clock_enable(RCC_ADC1);
   rcc_periph_clock_enable(RCC_CRC);
   rcc_periph_clock_enable(RCC_AFIO); //CAN
   rcc_periph_clock_enable(RCC_CAN1); //CAN
}

/**
* Setup UART3 115200 8N1
*/
char* usart_setup(void)
{
   static char inBuf[TERM_BUFSIZE];

   gpio_set_mode(TERM_USART_TXPORT, GPIO_MODE_OUTPUT_50_MHZ,
               GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, TERM_USART_TXPIN);

   usart_set_baudrate(TERM_USART, USART_BAUDRATE);
   usart_set_databits(TERM_USART, 8);
   usart_set_stopbits(TERM_USART, USART_STOPBITS_2);
   usart_set_mode(TERM_USART, USART_MODE_TX_RX);
   usart_set_parity(TERM_USART, USART_PARITY_NONE);
   usart_set_flow_control(TERM_USART, USART_FLOWCONTROL_NONE);
   usart_enable_rx_dma(TERM_USART);

   dma_disable_channel(DMA1, TERM_USART_DMACHAN);
   dma_set_peripheral_address(DMA1, TERM_USART_DMACHAN, (uint32_t)&TERM_USART_DR);
   dma_set_memory_address(DMA1, TERM_USART_DMACHAN, (uint32_t)inBuf);
   dma_set_peripheral_size(DMA1, TERM_USART_DMACHAN, DMA_CCR_PSIZE_8BIT);
   dma_set_memory_size(DMA1, TERM_USART_DMACHAN, DMA_CCR_MSIZE_8BIT);
   dma_set_number_of_data(DMA1, TERM_USART_DMACHAN, sizeof(inBuf));
   dma_enable_memory_increment_mode(DMA1, TERM_USART_DMACHAN);
   dma_enable_channel(DMA1, TERM_USART_DMACHAN);

   usart_enable(TERM_USART);

   return inBuf;
}

/**
* Enable Timer refresh and break interrupts
*/
void nvic_setup(void)
{
   nvic_enable_irq(PWM_TIMER_IRQ); //Main PWM
   nvic_set_priority(PWM_TIMER_IRQ, 1 << 4); //Set second-highest priority

   nvic_enable_irq(NVIC_TIM1_BRK_IRQ); //Emergency shut down
   nvic_set_priority(NVIC_TIM1_BRK_IRQ, 0); //Highest priority

   nvic_enable_irq(NVIC_EXTI2_IRQ); //Encoder Index pulse
   nvic_set_priority(NVIC_EXTI2_IRQ, 0); //Set highest priority

   nvic_enable_irq(NVIC_TIM2_IRQ); //Scheduler
   nvic_set_priority(NVIC_TIM2_IRQ, 0xe << 4); //second lowest priority

	nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ); //CAN RX
	nvic_set_priority(NVIC_USB_LP_CAN_RX0_IRQ, 0xf << 4); //lowest priority

	nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ); //CAN TX
	nvic_set_priority(NVIC_USB_HP_CAN_TX_IRQ, 0xf << 4); //lowest priority
}

void rtc_setup()
{
   //Base clock is HSE/128 = 8MHz/128 = 62.5kHz
   //62.5kHz / (624 + 1) = 100Hz
   rtc_auto_awake(RCC_HSE, 624); //10ms tick
   rtc_set_counter_val(0);
}

/**
* Setup main PWM timer and timer for generating over current
* reference values and external PWM
*/
void tim_setup()
{
   /*** Setup over/undercurrent and PWM output timer */
   timer_disable_counter(OVER_CUR_TIMER);
   //edge aligned PWM
   timer_set_alignment(OVER_CUR_TIMER, TIM_CR1_CMS_EDGE);
   timer_enable_preload(OVER_CUR_TIMER);
   /* PWM mode 1 and preload enable */
   timer_set_oc_mode(OVER_CUR_TIMER, TIM_OC2, TIM_OCM_PWM1);
   timer_set_oc_mode(OVER_CUR_TIMER, TIM_OC3, TIM_OCM_PWM1);
   timer_set_oc_mode(OVER_CUR_TIMER, TIM_OC4, TIM_OCM_PWM1);
   timer_enable_oc_preload(OVER_CUR_TIMER, TIM_OC2);
   timer_enable_oc_preload(OVER_CUR_TIMER, TIM_OC3);
   timer_enable_oc_preload(OVER_CUR_TIMER, TIM_OC4);

   timer_set_oc_polarity_high(OVER_CUR_TIMER, TIM_OC2);
   timer_set_oc_polarity_high(OVER_CUR_TIMER, TIM_OC3);
   timer_set_oc_polarity_high(OVER_CUR_TIMER, TIM_OC4);
   timer_enable_oc_output(OVER_CUR_TIMER, TIM_OC2);
   timer_enable_oc_output(OVER_CUR_TIMER, TIM_OC3);
   timer_enable_oc_output(OVER_CUR_TIMER, TIM_OC4);
   timer_generate_event(OVER_CUR_TIMER, TIM_EGR_UG);
   timer_set_prescaler(OVER_CUR_TIMER, 0);
   /* PWM frequency */
   timer_set_period(OVER_CUR_TIMER, OCURMAX);
   timer_enable_counter(OVER_CUR_TIMER);

   /** setup gpio */
   gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO7 | GPIO8 | GPIO9);
   //Early initialization of main PWM timer pins to make sure they are at a defined state
   gpio_clear(GPIOA, GPIO8 | GPIO9 | GPIO10);
   gpio_clear(GPIOB, GPIO13 | GPIO14 | GPIO15);
   gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, GPIO8 | GPIO9 | GPIO10);
   gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, GPIO13 | GPIO14 | GPIO15);
}

