;
; main.asm
;
; Created: 16/08/2017 08:32:27
; Author : pmg
;
; This file contains the code that is to be executed every 0.25 second

#include "incrementors.asm"

pendulum:
;TODO: Every fourth execution, do this:
rcall inc1sec

;TODO: If refresher isn't running, do this
;Read buttons. If pressed, start refresher.

ret
