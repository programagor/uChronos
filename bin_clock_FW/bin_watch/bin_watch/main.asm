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
TIM2_COMPB:
TIM2_OVF:
TIM1_CAPT:
TIM1_COMPA:
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
TIM2_COMPA:
rcall pendulum
reti

; =============== Refresh timer ===============
TIM0_COMPA:
;TODO: insert refresher

; =============== Initialisation routine here ===============
RESET:
;TODO: insert initialisator
;Need to initialise outputs immediately to stop FETs from floating
ldi R16,0b00111111 ;port C has only 6 pins, we want all as outputs, and initially high (disabled)
out PORTC,R16
out DDRC,R16

ldi R16,0b00000000
out PORTD,R16
ldi R16,0b11111111
out DDRD,R16

;Initialise stack
ldi R16,LOW(RAMEND)
out SPL,R16
ldi R16,HIGH(RAMEND)
out SPH,R16

;Configure RTC
ldi R16,1<<AS2 ;enable asynchronous operation (32.768 kHz crystal)
sts ASSR,R16

tbusy1:
lds R16,ASSR
sbrc R16,OCR2AUB
rjmp tbusy1

ldi R16,127 ;trigger 4 times per second
sts OCR2A,R16

ldi R16,1<<OCIE2A ;enable compare interrupt
sts TIMSK2,R16

tbusy2:
lds R16,ASSR
sbrc R16,TCR2AUB
rjmp tbusy2
 
ldi R16,1<<WGM21 ;CTC mode
sts TCCR2A,R16
 
tbusy3:
lds R16,ASSR
sbrc R16,TCR2BUB
rjmp tbusy3

ldi R16,1<<CS22 ;start clock (64 prescaler)
sts TCCR2B,R16


;All set up, ready to go.
 sei
; =============== Sleeper loop ===============
LOOP:
sleep
rjmp LOOP


; =============== Includes ===============

#include "pendulum.asm"

; =============== Global variables ===============
.dseg