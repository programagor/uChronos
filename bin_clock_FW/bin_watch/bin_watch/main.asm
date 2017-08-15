;
; bin_watch.asm
;
; Created: 16/08/2017 08:32:27
; Author : pmg
;
; Thi is the main file

; Interrupt Vector Table
.ORG $000
jmp RESET			; Reset Handler
jmp EXT_INT0		; IRQ0 Handler
jmp EXT_INT1		; IRQ1 Handler
jmp PC_INT0
jmp PC_INT1
jmp PC_INT2
jmp WDT
jmp TIM2_COMPA		; Timer2 Compare Handler
jmp TIM2_COMPB
jmp TIM2_OVF		; Timer2 Overflow Handler
jmp TIM1_CAPT		; Timer1 Capture Handler
jmp TIM1_COMPA		; Timer1 CompareA Handler
jmp TIM1_COMPB		; Timer1 CompareB Handler
jmp TIM1_OVF		; Timer1 Overflow Handler
jmp TIM0_COMPA
jmp TIM0_COMPB
jmp TIM0_OVF		; Timer0 Overflow Handler
jmp SPI_STC			; SPI Transfer Complete Handler
jmp USART_RXC		; USART RX Complete Handler
jmp USART_UDRE		; UDR Empty Handler
jmp USART_TXC		; USART TX Complete Handler
jmp ADCC			; ADC Conversion Complete Handler
jmp EE_RDY			; EEPROM Ready Handler
jmp ANA_COMP		; Analog Comparator Handler
jmp TWSI			; Two-wire Serial Interface Handler
jmp SPM_RDY		; Store Program Memory Ready Handler

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
;TODO: insert pendulum

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