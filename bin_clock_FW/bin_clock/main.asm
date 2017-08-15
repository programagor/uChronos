;
; bin_clock.asm
;
; Created: 20/07/2017 10:17:14
; Author : pmg
;


.def RSEC = R2
.def RMIN = R3
.def RHR  = R4
.def RDAY = R5
.def RMTH = R6
.def RYR  = R7

.def RLINE = R19
.def RSET  = R20
;bit 7 means SELECT is pressed
;bit 6 means INCREMENT is pressed
;bit 0-4 selects which digit is being modified (0x0 = running)

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
call inc_secl
reti

;increment lower digit of seconds
inc_secl:
mov R16,RSEC
andi R16,0x0F
mov R17,RSEC
andi R17,0xF0 ;split seconds into lower digit (R16) and upper (R17)
cpi R16,9 ;if lower digit at 9
breq inc_sech ;branch to tens increment
inc R16
or R16,R17
mov RSEC,R16
ret

;increment upper digit of seconds
inc_sech:
cpi R17,0x50 ;if upper digit at 5
breq inc_minl ;branch to minutes increment
ldi R16,0x10
add R17,R16 ;otherwise increment the upper digit
mov RSEC,R17 ;and save the thing (R17 contains 0 for lower digit)
ret


;increment lower digit of minutes
inc_minl:
clr RSEC ;move 0 to seconds

mov R16,RMIN
andi R16,0x0F
mov R17,RMIN
andi R17,0xF0 ;split minutes into lower digit (R16) and upper (R17)
cpi R16,9 ;if lower digit at 9
breq inc_minh ;branch to tens increment
inc R16
or R16,R17
mov RMIN,R16
ret

;increment upper digit of minutes
inc_minh:
cpi R17,0x50 ;if upper digit at 5
breq inc_hrl ;branch to hours increment
ldi R16,0x10
add R17,R16 ;otherwise increment the upper digit
mov RMIN,R17 ;and save the thing (R17 contains 0 for lower digit)
ret


;increment lower digit of hours
inc_hrl:
clr RMIN ;move 0 to seconds

mov R16,RHR
cpi R16,0x23 ;if 23 hours
breq inc_dayl ;increment day
andi R16,0x0F
mov R17,RHR
andi R17,0xF0 ;split hours into lower digit (R16) and upper (R17)
cpi R16,9 ;if lower digit at 9
breq inc_hrh ;branch to tens increment
inc R16
or R16,R17
mov RHR,R16
ret

;increment upper digit of hours
inc_hrh:
ldi R16,0x10
add R17,R16 ;otherwise increment the upper digit
mov RHR,R17 ;and save the thing (R17 contains 0 for lower digit)
ret


;increment lower digit of day
inc_dayl:
clr RHR ;clear hours
;TODO: days

;need a strategy here. First, let's see if month has 31 days
mov R16,RMTH
cpi R16,0x01
breq mth31
cpi R16,0x03
breq mth31
cpi R16,0x05
breq mth31
cpi R16,0x07
breq mth31
cpi R16,0x08
breq mth31
cpi R16,0x10
breq mth31
cpi R16,0x12
breq mth31
;Or if it has 30
cpi R16,0x04
breq mth30
cpi R16,0x06
breq mth30
cpi R16,0x09
breq mth30
cpi R16,0x11
breq mth30
;otherwise it's february
;is it a leap year?
mov R16,RYR
andi R16,0b11 ;divisible by 4?
brne mth28
rjmp mth29

mth31:
mov R16,RDAY
cpi R16,0x31 ;if last day of month
breq inc_mthl ;increment month
rjmp mth_cont

mth30:
mov R16,RDAY
cpi R16,0x30 ;if last day of month
breq inc_mthl ;increment month
rjmp mth_cont

mth29:
mov R16,RDAY
cpi R16,0x29 ;if last day of month
breq inc_mthl ;increment month
rjmp mth_cont

mth28:
mov R16,RDAY
cpi R16,0x28 ;if last day of month
breq inc_mthl ;increment month
rjmp mth_cont

mth_cont:
andi R16,0x0F
mov R17,RDAY
andi R17,0xF0 ;split days into lower digit (R16) and upper (R17)
cpi R16,9 ;if lower digit at 9
breq inc_dayh ;branch to tens increment
inc R16
or R16,R17
mov RDAY,R16
ret

;increment upper digit of days
inc_dayh:
ldi R16,0x10
add R17,R16 ;otherwise increment the upper digit
mov RDAY,R17 ;and save the thing (R17 contains 0 for lower digit)
ret

;increment month
inc_mthl:
ldi R16,0x01
mov RDAY,R16

mov R16,RMTH
cpi R16,0x12 ;if december
breq inc_yrl ;increment day
andi R16,0x0F
mov R17,RMTH
andi R17,0xF0 ;split hours into lower digit (R16) and upper (R17)
cpi R16,9 ;if lower digit at 9
breq inc_mthh ;branch to tens increment
inc R16
or R16,R17
mov RMTH,R16
ret

;increment upper digit of month
inc_mthh:
ldi R16,0x10
add R17,R16 ;otherwise increment the upper digit
mov RMTH,R17 ;and save the thing (R17 contains 0 for lower digit)
ret

inc_yrl:
ldi R16,0x01
mov RMTH,R16

mov R16,RYR
cpi R16,0x99 ;last year (xx99)
breq yXk ;wrap around
andi R16,0x0F
mov R17,RYR
andi R17,0xF0 ;split hours into lower digit (R16) and upper (R17)
cpi R16,9 ;if lower digit at 9
breq inc_yrh ;branch to tens increment
inc R16
or R16,R17
mov RYR,R16
ret

;increment upper digit of month
inc_yrh:
ldi R16,0x10
add R17,R16 ;otherwise increment the upper digit
mov RYR,R17 ;and save the thing (R17 contains 0 for lower digit)
ret

yXk: ;like Y2K all over again, except reallistically this is going to be Y2K1
clr RYR

ret

; =============== Refresh timer ===============
TIM0_COMPA:
inc RLINE
cpi RLINE,4
brne ref_nozero
ldi RLINE,0
ref_nozero:
ldi R16,0
mov R17,RHR
swap R17
mov R18,RLINE
rot_hrh:
tst R18
breq rot_hrl0
lsr R17
dec R18
rjmp rot_hrh
rot_hrl0:
bst R17,0
bld R16,0
mov R17,RHR
mov R18,RLINE
rot_hrl:
tst R18
breq rot_minh0
lsr R17
dec R18
rjmp rot_hrl
rot_minh0:
bst R17,0
bld R16,1

mov R17,RMIN
swap R17
mov R18,RLINE
rot_minh:
tst R18
breq rot_minl0
lsr R17
dec R18
rjmp rot_minh
rot_minl0:
bst R17,0
bld R16,2
mov R17,RMIN
mov R18,RLINE
rot_minl:
tst R18
breq rot_sech0
lsr R17
dec R18
rjmp rot_minl
rot_sech0:
bst R17,0
bld R16,3

mov R17,RSEC
swap R17
mov R18,RLINE
rot_sech:
tst R18
breq rot_secl0
lsr R17
dec R18
rjmp rot_sech
rot_secl0:
bst R17,0
bld R16,4
mov R17,RSEC
mov R18,RLINE
rot_secl:
tst R18
breq rot_end0
lsr R17
dec R18
rjmp rot_secl
rot_end0:
bst R17,0
bld R16,5

com R16
andi R16,0b00111111

ldi R17,1
mov R18,RLINE
rot_line:
tst R18
breq rot_end
lsl R17
dec R18
rjmp rot_line
rot_end:
ori R17,0b110000

ldi R18,0b110000
out PORTC,R18
out PORTD,R16
out PORTC,R17

;todo:we could also read the buttons while we're refreshing

;if RSET & 0b11000000 (buttons were pressed previously)
mov R17,RSET
andi R17,0b11000000
in R16,PINC
com R16
bst R16,4
bld RSET,6
bst R16,5
bld RSET,7
tst R17
breq nopress
;Buttons were pressed previously. see if they are released

reti ;do nothing on falling edge

nopress: ;Buttons were not pressed, see if they are
andi R16,0b00110000
brne rising
reti
rising:
sbrs R16,4
jmp select
;increment
mov R16,RSET
andi R16,0b00001111
cpi R16,1
brne inc1
ldi R18,10
loop0:
call inc_hrl
dec R18
brne loop0
reti
inc1:
cpi R16,2
brne inc2
call inc_hrl
reti
inc2:
cpi R16,3
brne inc3
ldi R18,10 ;add 10 minutes
loop2:
call inc_minl
dec R18
brne loop2
reti
inc3:
cpi R16,4
brne inc4
call inc_minl
reti
inc4:
cpi R16,5
brne inc5
ldi R18,10
loop4:
call inc_secl
dec R18
brne loop4
reti
inc5:
cpi R16,6
brne inc6
call inc_secl
inc6:
reti

select:
inc RSET
mov R16,RSET
andi R16,0b00001111
cpi R16,7
breq fullset
cpi R16,1
breq nullset

reti

nullset:
LDI R16,0b00001000 ;stop time
STS TCCR1B,R16

;Default time (reset to this)
ldi R16,0x00
mov RYR,R16
ldi R16,0x01
mov RMTH,R16
ldi R16,0x01
mov RDAY,R16
ldi R16,0x00
mov RHR,R16
ldi R16,0x00
mov RMIN,R16
ldi R16,0x00
mov RSEC,R16

reti

fullset:
andi RSET,0b11110000
LDI R16,0b00001011
STS TCCR1B,R16 ;start time again

reti

; =============== Initialisation routine here ===============
RESET:

;init stack pointer
LDI    R16, low(RAMEND)
OUT    SPL, R16
LDI    R16, high(RAMEND)
OUT    SPH, R16

;init sleep mode
LDI R16,0b00000001 ;IDLE, sleep enabled
OUT SMCR,R16

;init clock
LDI R17,0x3D
LDI R16,0x08
STS OCR1AH,R17
STS OCR1AL,R16
LDI R16,0b10
STS TIMSK1,R16
LDI R16,0b00001011
STS TCCR1B,R16

;init refresh timer
ldi RLINE,3
ldi R16,200
out OCR0A,R16
ldi R16,0b010
sts TIMSK0,R16
ldi R16,0b10
out TCCR0A,R16
ldi R16,0b10
out TCCR0B,R16

;init pins
LDI R16,0b110000
OUT PORTC,R16
LDI R16,0b001111
OUT DDRC,R16

LDI R16,0b11111111
OUT DDRD,R16
LDI R16,0b00000000
OUT PORTD,R16

;Default time (reset to this)
ldi R16,0x17
mov RYR,R16
ldi R16,0x11
mov RMTH,R16
ldi R16,0x01
mov RDAY,R16
ldi R16,0x12
mov RHR,R16
ldi R16,0x34
mov RMIN,R16
ldi R16,0x56
mov RSEC,R16

;enable interrupts
sei


; =============== Sleeper loop ===============
LOOP:
sleep
rjmp LOOP