;
; main.asm
;
; Created: 16/08/2017 08:32:27
; Author : pmg
;
; This is the main file of the Binary Watch project

; Interrupt Vector Table
.ORG $000
rjmp RESET			; Reset Handler
rjmp EXT_INT0		; IRQ0 Handler
rjmp EXT_INT1		; IRQ1 Handler
rjmp PC_INT0
rjmp PC_INT1
rjmp PC_INT2
rjmp WDT
rjmp TIM2_COMPA		; Timer2 Compare Handler
rjmp TIM2_COMPB
rjmp TIM2_OVF		; Timer2 Overflow Handler
rjmp TIM1_CAPT		; Timer1 Capture Handler
rjmp TIM1_COMPA		; Timer1 CompareA Handler
rjmp TIM1_COMPB		; Timer1 CompareB Handler
rjmp TIM1_OVF		; Timer1 Overflow Handler
rjmp TIM0_COMPA
rjmp TIM0_COMPB
rjmp TIM0_OVF		; Timer0 Overflow Handler
rjmp SPI_STC			; SPI Transfer Complete Handler
rjmp USART_RXC		; USART RX Complete Handler
rjmp USART_UDRE		; UDR Empty Handler
rjmp USART_TXC		; USART TX Complete Handler
rjmp ADCC			; ADC Conversion Complete Handler
rjmp EE_RDY			; EEPROM Ready Handler
rjmp ANA_COMP		; Analog Comparator Handler
rjmp TWSI			; Two-wire Serial Interface Handler
rjmp SPM_RDY		; Store Program Memory Ready Handler

; Unused interrupts
EXT_INT0:
EXT_INT1:
PC_INT0:
PC_INT1:
PC_INT2:
WDT:
TIM2_COMPA:
TIM2_COMPB:
TIM2_OVF:
TIM1_CAPT:
TIM1_COMPB:
TIM1_OVF:
TIM0_COMPB:
TIM0_OVF:
SPI_STC:
USART_RXC:
USART_UDRE:
USART_TXC:
ADCC:
EE_RDY:
ANA_COMP:
TWSI:
SPM_RDY:
reti

; =============== 1 second timer ===============
TIM1_COMPA:
#include "pendulum.asm"
reti

; =============== Refresh timer ===============
TIM0_COMPA:
;TODO: insert refresher

; =============== Initialisation routine here ===============
RESET:
;TODO: insert initialisator

; =============== Sleeper loop ===============
LOOP:
sleep
rjmp LOOP


; =============== Global variables ===============
.dseg