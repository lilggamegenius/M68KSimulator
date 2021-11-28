; ---------------------------------------------------------------------------
; RAM variables - General

RAM_Start: equ $FFFF0000

System_Stack: equ $FFFFFFFF
RAM_End: equ System_Stack
	
; >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; start of ROM

StartOfRom:
;Vectors:
	dc.l System_Stack,  EntryPoint, ErrorTrap,  ErrorTrap   ; 4
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 8
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 12
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 16
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 20
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 24
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 28
	dc.l H_Int,         ErrorTrap,  V_Int,      ErrorTrap   ; 32
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 36
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 40
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 44
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 48
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 52
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 56
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 60
	dc.l ErrorTrap,     ErrorTrap,  ErrorTrap,  ErrorTrap   ; 64
Header:
	dc.b "MEGA DRIVE      "                                 ; Console name
	dc.b "Lil-G   2021.DEC"                                 ; Copyright/Date
	dc.b "Lil-G'S MOTOROLLA 68000 SIMULATOR               " ; Domestic name
	dc.b "Lil-G'S MOTOROLLA 68000 SIMULATOR               " ; International name
	dc.b "GM 00000001-00"                                   ; Version (REV00)
Checksum:
	dc.b "NO"		                                        ; Checksum (patched later if incorrect)
	dc.b "                "                                 ; I/O Support
	dc.l StartOfRom		                                    ; ROM Start

ROMEndLoc:
	dc.l EndOfRom-1		                                    ; ROM End
	dc.l RAM_Start&$FFFFFF		                            ; RAM Start
	dc.l (RAM_End-1)&$FFFFFF		                        ; RAM End
	dc.b "    "		                                        ; Backup RAM ID
	dc.l $20202020		                                    ; Backup RAM start address
	dc.l $20202020		                                    ; Backup RAM end address
	dc.b "            "	                                    ; Modem support
	dc.b "FILLER HEADER FOR Lil-G'S M68K SIMULATOR"	        ; Notes
	dc.b "JUE             "                                 ; Country
EndOfHeader:

; ===========================================================================
; Crash/Freeze the 68000. 
ErrorTrap:
.loop:
	nop
	nop
	bra.s	.loop
	
H_Int:
	rte
	
V_Int:
	rte

; ===========================================================================
EntryPoint:
	even
EndOfRom:


	END