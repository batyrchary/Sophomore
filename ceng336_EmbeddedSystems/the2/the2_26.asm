	;Grup No:26
	;BATYR CHARYYEV  2001527
	;KAD?R BERKAY AYDEM?R  1941780
LIST    P=18F8722

#INCLUDE <p18f8722.inc>
CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

counter udata 0x23
counter

level udata 0x24
level

random1x udata 0x25
random1x

random1y udata 0x26
random1y
 
random2x udata 0x27
random2x

random2y udata 0x28
random2y 

random3x udata 0x29
random3x

random3y udata 0x30
random3y 
 
random1y_yedek udata 0x31
random1y_yedek

random1x_yedek udata 0x32
random1x_yedek 
 
;;;;;;;;;;;;;;;;;;;;;;;;;; save_restore icin
w_temp  udata 0x33
w_temp

status_temp udata 0x34
status_temp

pclath_temp udata 0x35
pclath_temp
;;;;;;;;;;;;;;;;;;;;;;;;;;

portb_var   udata 0x36
portb_var

secs   udata 0x37
secs

state   udata 0x38
state

randNumber udata 0x39      
randNumber

secs_random udata 0x40
secs_random

numx udata 0x41
numx

numy udata 0x42
numy

temp udata 0x43
temp
 
dis1 udata 0x44
dis1

dis0 udata 0x45
dis0

dis3 udata 0x46
dis3

dis2 udata 0x47
dis2

L1 udata 0x48
L1

L2 udata 0x49
L2   
temp_level udata 0x50
temp_level
 
p_c udata   0x51
p_c
 
p_d udata   0x52
p_d

p_e udata   0x53
p_e

p_f udata   0x54
p_f
 
ten udata 0x55
ten
 
isEnd	udata 0x56
isEnd
basildi1x udata 0x57
basildi1x

basildi1y udata 0x58
 basildi1y 
 basildi2x udata 0x59
 basildi2x
basildi2y udata 0x60
 basildi2y
basildi3x udata 0x61
 basildi3x
basildi3y udata 0x62
 basildi3y
yendimi	    udata 0x63
yendimi
kacbutton   udata 0x64
kacbutton
   
true_num udata 0x65
true_num
 
press_num udata 0x66
press_num 
 
led_on_random1x udata 0x67
led_on_random1x

led_on_random1y udata 0x68
led_on_random1y
 
led_on_random2x udata 0x69
led_on_random2x

led_on_random2y udata 0x70
led_on_random2y 

led_on_random3x udata 0x71
led_on_random3x

led_on_random3y udata 0x72
led_on_random3y
 
led_on_p_c udata   0x73
led_on_p_c
 
led_on_p_d udata   0x74
led_on_p_d

led_on_p_e udata   0x75
led_on_p_e

led_on_p_f udata   0x76
led_on_p_f
 
led_on_level udata   0x77
led_on_level
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ORG     0x00
goto    init

org     0x08
goto    isr             ;go to interrupt service routine    
  
org	0x18
goto	low_isr    

Table1:
    ADDWF PCL;this table if used for showing remaining rigths. The Logic is same with the upper one.
    RETLW b'00000001' ;0
    RETLW b'00000010' ;1
    RETLW b'00000100' ;2
    RETLW b'00001000' ;3
    RETLW b'00010000' ;4
    RETLW b'00100000' ;5
 
    
Table2:
    ADDWF PCL ;this table helps to display numbers and hyphen character.According to the number it matches the binary sequence and returns it.
    RETLW b'00111111' ;0
    RETLW b'00000110' ;1
    RETLW b'01011011' ;2
    RETLW b'01001111' ;3
    RETLW b'01100110' ;4
    RETLW b'01101101' ;5
    RETLW b'01111101' ;6
    RETLW b'00000111' ;7
    RETLW b'01111111' ;8
    RETLW b'01100111' ;9
    RETLW b'00000000' ;
    RETLW b'01111001' ;E
    RETLW b'01010100' ;n
    RETLW b'01011110' ;d
   
   
init:

    CLRF   LATA
    CLRF   LATC
    CLRF   LATD
    CLRF   LATE
    CLRF   LATF

    movlw d'9'
    movwf counter
    movlw d'10'
    movwf ten
    
    CLRF	PORTA
    CLRF	PORTC
    CLRF	PORTD
    CLRF	PORTE
    CLRF	PORTF
    CLRF	PORTB ;ekstra olabilir	
    CLRF	PORTH
    CLRF	PORTJ
    
    CLRF led_on_p_c
    CLRF led_on_p_d
    CLRF led_on_p_e
    CLRF led_on_p_f
    CLRF	p_c
    CLRF	p_d
    CLRF	p_e
    CLRF	p_f
    CLRF led_on_random1x
    CLRF led_on_random1y 
    CLRF led_on_random2x
    CLRF led_on_random2y
    CLRF led_on_random3x
    CLRF led_on_random3y 
    
    MOVLW   0x00
    MOVWF   TRISC
    MOVWF   TRISD
    MOVWF   TRISE
    MOVWF   TRISF
    MOVWF   TRISH
    MOVWF   TRISJ
    
    
    MOVLW   0xFF
    MOVWF   TRISA
    ;MOVWF   TRISB
	
    CLRF   LATA
    CLRF   LATC
    CLRF   LATD
    CLRF   LATE
    CLRF   LATF
    CLRF   LATH
    CLRF   LATJ
    
  ;;;;;;;;;;;; randomerden alindi
    clrf random1x
    clrf random2x
    clrf random3x
    clrf random1y
    clrf random2y
    clrf random3y
    clrf numx
    clrf numy
    clrf dis0
    clrf dis1
    clrf dis2
    clrf dis3
    clrf true_num
    clrf press_num
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    clrf led_on_level
    MOVLW   d'1'
    MOVWF   level
    MOVWF   led_on_level
    movwf   isEnd
    movlw   d'0'
    movwf   basildi1x
    movwf   basildi1y
    movwf   basildi2x
    movwf   basildi2y
    movwf   basildi3x
    movwf   basildi3y
    movwf   yendimi
    movwf   kacbutton
;;;;;;;;;;;;;;;;;;;;;;;;benden ayar	
	CLRF INTCON ;hersey 0;
	
	bsf RCON, 7  	; IPEN is set=Enable priority level interrupts
	
	bsf INTCON, 7	; when IPEN is 1 = enables all high-priority interrupts
	bsf INTCON, 6	;when IPEN is 1 = enables all low-priority interrupts
	bsf INTCON, 5	; TMR0IE is set = enables TMR0 overflow-interrupt
	bsf INTCON, 3	; enables RB Port change interrupt - ilerde lazim olur
	bcf INTCON, 2	; TMR0 register has overflowed bilemedim
	bcf INTCON, 0	; at least one of the RB&:RB4 pins changed state	
	
	;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	

;;;;;;;;;;;;;;;;;;call initTimer0 yerine alttaki kod
	bcf		INTCON2, 2	;TMR0IP  is cleared = TMR0 low-priority
	bcf		INTCON2, 0
	bsf		T0CON, 7 	;TMR0ON	 is set = enables Timer0
        bsf		T0CON, 6	;TMR0ON	 is set = Timer0 is configured as an 8-bit timer/counter
	bcf		T0CON, 5	; 0=internal instruction clock cycle
	bcf		T0CON, 4	; 0=increment on low-to-high transition on TOCKI pin
	bsf		T0CON, 3	; 1=timer0 prescaler isNOT assigned Timer0 clock input bypasses prescaler
	
	bsf		T0CON, 2
	bsf		T0CON, 1	;1:256 timer0 prescaler vale 
	bsf		T0CON, 0
    
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; initTimer1

    MOVLW d'95' ; Preload TMR1 register pair
    MOVWF TMR1H ; for 1 second overflow
    CLRF TMR1L
	
    MOVLW b'00110001' 	;enables timer1 8-bit operation and 1:8 prescaler value
    MOVWF T1CON ; 
    BSF PIE1, 0			;TMR1IE ; Enable Timer1 interrupt
	bsf IPR1, 0			;TMR1 high-priority
	
    CLRF secs 			;Initialize timekeeping registers
    CLRF state
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    
 
 
    ;Disable interrupts
	BCF PIE1, 0			;TMR1IE disable Timer1 interrupt						;clrf    INTCON	
	bcf INTCON,	3		; disables RB Port change interrupt - ilerde lazim olur	;clrf    PIR1
    
	
    ;Configure Input/Interrupt Ports
    movlw   b'11110000'
    movwf   TRISB
   ; bcf     INTCON2, 7  ;Pull-ups are enabled
    clrf    PORTB
    goto main
  
main:
call ListenRA4
movlw d'0'
movwf PORTA
call assignRandomNumber
call disable_timer0
call rnd_generate
movlw d'3'
movwf	state
call enable_timer1
call encoding
movlw d'9'
movwf dis1 
call sondurucu
;call disable_timer1
movlw d'0'
movwf state
;call enable_timer1
call enable_portb
clrf dis2
clrf dis3
goto play   

goto main


  play
    call display
    
    ;;;;;;;;; 90 dan 00 a indimi
    movlw d'0'
    xorwf dis1, 0	;result is stored in working register
    btfsc  STATUS, Z	; is result is zero which means same
    xorwf dis0, 0	; 
    btfsc STATUS, Z	; if result again same 
    goto end_state		;then make isEnd=0
    ;;;;;;;;;;;;;;;;;	; else isEnd will be 1
    
    
    btfsc	PORTA, 4	    
    goto	Released  
    
  goto play

    Released
	call display
	btfsc	PORTA, 4	
	goto	Released
	movlw d'0'
	movwf PORTA
	incf	kacbutton, 1
	call checker
     
    
    checker
	call display
	movlw d'1'
	xorwf level,w
	btfsc STATUS,Z ;level1_da ise
	goto level1_checker

	movlw d'2'
	xorwf level,w
	btfsc STATUS,Z ;level2_da ise
	call level2_checker

	movlw d'3'
	xorwf level,w
	btfsc STATUS,Z ;level3_da ise
	call level3_checker
     
    
    level1_checker
	call display
	movf dis3, 0
	xorwf random1x,w
	btfsc STATUS,Z ;level3_da ise
	goto y1_checker
	movff dis3,led_on_random1x
	movff dis2,led_on_random1y
	call led_on
    goto end_state
    
    y1_checker
	call display
	movf dis2, 0
	xorwf random1y,w ;ikisi ayni ise working register 0 olcak
	btfsc STATUS, Z ; shurda dikkat ss
	goto wait
	movff dis3,led_on_random1x
	movff dis2,led_on_random1y
	call led_on
    goto end_state
    
    
    level2_checker
	
	movlw d'1'
	xorwf true_num,w
	btfsc STATUS,Z
	call is_pressed
	
	movf dis3, 0
	xorwf random1x,w
	btfsc STATUS,Z ;level3_da ise
	call y2_checker
    	call level2_x2_checker
	
	
	movlw d'2'
	xorwf true_num,w
	btfsc STATUS,Z
	goto wait
	
	movff dis3,led_on_random1x
	movff dis2,led_on_random1y
	call led_on
	
	movlw d'1'
	xorwf true_num,w
	btfsc STATUS,Z
	goto end_state
	
	movlw d'0'
	xorwf true_num,w
	btfsc STATUS,Z
	goto end_state
	
    is_pressed
	movf dis3,w
	xorwf basildi1x,w
	btfsc STATUS,Z
	Incf press_num
	movf dis2,w
	xorwf basildi1y,w
	btfsc STATUS,Z
	Incf press_num
	movlw d'2'
	xorwf press_num,w
	btfsc STATUS,Z
	goto end_state
	return
	
    y2_checker
	movf dis2, 0
	xorwf random1y,w
	btfsc STATUS,Z ;level3_da ise
	goto inc_true_num 
    return
    
    inc_true_num
	movff dis3,led_on_random1x
	movff dis2,led_on_random1y
	call led_on
	Incf true_num,f
	movlw d'2'
	xorwf true_num,w
	btfsc STATUS,Z
	goto wait
	goto bridge
	
    bridge
	movff dis3,basildi1x
	movff dis2,basildi1y
	goto play
	
    level2_x2_checker
	movf dis3,0
	xorwf random2x,w
	btfsc STATUS,Z
	call level2_y2_checker	
	return
	
    level2_y2_checker
	movf dis2,0
	xorwf random2y,w
	btfsc STATUS,Z
	call inc_true_num
	return
	
    is_pressed_2
	movf dis3,w
	xorwf basildi1x,w
	btfsc STATUS,Z
	Incf press_num
	movf dis2,w
	xorwf basildi1y,w
	btfsc STATUS,Z
	Incf press_num
	movlw d'2'
	xorwf press_num,w
	btfsc STATUS,Z
	goto end_state
	clrf press_num	
	movf dis3,w
	xorwf basildi2x,w
	btfsc STATUS,Z
	Incf press_num
	movf dis2,w
	xorwf basildi2y,w
	btfsc STATUS,Z
	Incf press_num
	movlw d'2'
	xorwf press_num,w
	btfsc STATUS,Z
	goto end_state
	return
	
    level3_checker
	clrf press_num
	movlw d'1'
	xorwf true_num,w
	btfsc STATUS,Z
	call is_pressed
	clrf press_num
	movlw d'2'
	xorwf true_num,w
	btfsc STATUS,Z
	call is_pressed_2
	
	movf dis3, 0
	xorwf random1x,w
	btfsc STATUS,Z ;level3_da ise
	call level3_y1_checker
	movf dis3, 0
	xorwf random2x,w
	btfsc STATUS,Z
    	call level3_x2_checker
	call level3_x3_checker
	
	movlw d'3'
	xorwf true_num,w
	btfsc STATUS,Z
	goto finito
	
	movff dis3,led_on_random1x
	movff dis2,led_on_random1y
	call led_on
	
	movlw d'2'
	xorwf true_num,w
	btfsc STATUS,Z
	goto end_state
	
	movlw d'1'
	xorwf true_num,w
	btfsc STATUS,Z
	goto end_state
	
	movlw d'0'
	xorwf true_num,w
	btfsc STATUS,Z
	goto end_state
	
    level3_y1_checker
	movf dis2, 0
	xorwf random1y,w
	btfsc STATUS,Z ;level3_da ise
	goto inc_true_num_2
    return
    
    append
	movff dis3,basildi1x
	movff dis2,basildi1y
	goto play
    
    append_2
	movff dis3,basildi2x
	movff dis2,basildi2y
	goto play
	
    level3_brigde
	movlw d'1'
	xorwf true_num,w
	btfsc STATUS,Z
	goto append
	movlw d'2'
	xorwf true_num,w
	btfsc STATUS,Z
	goto append_2	

    inc_true_num_2
	movff dis3,led_on_random1x
	movff dis2,led_on_random1y
	call led_on
	Incf true_num,f
	movlw d'3'
	xorwf true_num,w
	btfsc STATUS,Z
	goto finito
	goto level3_brigde
	
    level3_x2_checker
	movf dis3,0
	xorwf random2x,w
	btfsc STATUS,Z
	call level3_y2_checker
	;call level3_x3_checker
	return
	
    level3_y2_checker
	movf dis2, 0
	xorwf random2y,w
	btfsc STATUS,Z ;level3_da ise
	goto inc_true_num_2
    return
    
    level3_x3_checker
	movf dis3,0
	xorwf random3x,w
	btfsc STATUS,Z
	call level3_y3_checker
	return
	
    level3_y3_checker
	movf dis2, 0
	xorwf random3y,w
	btfsc STATUS,Z ;level3_da ise
	goto inc_true_num_2
	return
    
    
    
    wait
	call sondurucu
	call disable_timer1
	clrf true_num
	call disable_portb
	clrf press_num
	movlw d'10'
	movwf dis3
	movwf dis1
	movwf dis2
	movwf dis0
	call display
	movlw d'9'
	movwf counter
	Incf level,f
	clrf kacbutton
	goto main
    
end_state	
	call disable_portb
	call disable_timer1
	clrf true_num
	clrf press_num
	movlw d'11'
	movwf dis3
	
	movlw d'12'
	movwf dis2
	
	movlw d'13'
	movwf dis1
	decf level,0
	movwf dis0
	movlw d'1'
	movwf level
	call display
	goto end_listen
finito
	call disable_portb
	call disable_timer1
	clrf true_num
	clrf press_num
	movlw d'11'
	movwf dis3
	
	movlw d'12'
	movwf dis2
	
	movlw d'13'
	movwf dis1
	movff level,dis0
	movlw d'1'
	movwf level
	call display
	goto end_listen
	
end_listen
	call display
	btfss	PORTA, 4	    
	goto	end_listen   
	goto end_release
end_release
	call display
	btfsc	PORTA, 4	
	goto	end_release
	movlw d'10'
	movwf dis3
	movwf dis1
	movwf dis2
	movwf dis0
	call display
	movlw d'9'
	movwf counter
	movlw d'0'
	movwf PORTA
	call sondurucu
	goto main

	
    
    
ListenRA4
	btfss	PORTA, 4	    
	goto	ListenRA4   
	;goto RA4Released 
RA4Released
	btfsc	PORTA, 4	
	goto	RA4Released
	return
	
assignRandomNumber

    movf   TMR0,W
    movwf  randNumber
    return

rnd_generate
   movff level,temp_level
   movf randNumber,0
   andlw b'11110000'
   movwf numx
   movf randNumber,0
   andlw b'00001111'
   movwf numy
   rlncf numx
   rlncf numx
   rlncf numx
   rlncf numx
   movf numx,0
   call case1x
   movf numy,0
   call case1y
   movf temp_level,0
   dcfsnz WREG,0
   return;first return
   decf temp_level, F
   movf numx,0
   comf WREG,0
   andlw b'00001111'
   call case2x
   movff random1y,random2y
   movf temp_level,0
   dcfsnz WREG,0
   return;second return
   movff random1x,random3x
   movf numy,0
   comf WREG,0
   andlw b'00001111'
   call case3y
   return;last return
      
   
case1x
   movwf temp
   movlw d'6'
   subwf temp,0
   btfss STATUS,N
   goto case1x
   movff temp,random1x
   return
case1y
   movwf temp
   movlw d'4'
   subwf temp,0
   btfss STATUS,N
   goto case1y
   movff temp,random1y
   return

case2x
   movwf temp
   movlw d'6'
   subwf temp,0
   btfss STATUS,N
   goto case2x
   movff temp,random2x
   return   

case3y
   movwf temp
   movlw d'4'
   subwf temp,0
   btfss STATUS,N
   goto case3y
   movff temp,random3y
   return
    
encoding
    movlw d'10'
    movwf dis3
    movwf dis2
    movwf dis1	
    call display	
    movlw d'3'
    xorwf state,w
    btfsc STATUS,Z ;level3_da ise
    call yakici
    movff p_c, LATC;PORTC
    movff p_d, LATD;PORTD
    movff p_e, LATE;PORTE
    movff p_f, LATF;PORTF
    ;call display
    call before_sondurucu
	
before_sondurucu
    movlw d'10'
    movwf dis1 
    call display
    movff state,dis0
    movlw d'0'
    xorwf state,w
    btfsc STATUS,Z ;level3_da ise
    return
    goto before_sondurucu    
   
  

display
    clrf LATH
    movf dis3,0
    ADDWF dis3,0
    call Table2
    MOVWF LATJ,0
    BSF   LATH,0
    call DELAY
			;in this function we displays the numbers which are provided by dis3,dis2,dis1,dis0. We foten call it
    clrf LATH
    movf dis2,0
    ADDWF dis2,0
    call Table2
    MOVWF LATJ,0
    BSF   LATH,1
    call DELAY

    clrf LATH
    movf dis1,0
    ADDWF dis1,0
    call Table2
    MOVWF LATJ,0
    BSF   LATH,2
    call DELAY

    clrf LATH
    movf dis0,0
    ADDWF dis0,0
    call Table2
    MOVWF LATJ,0
    BSF   LATH,3
    call DELAY
    return 
   
   
   
   
   
   
   

 

yakici
    movlw d'1'
    xorwf level,w
    btfsc STATUS,Z ;level1_da ise
    ;level1_ayarlayci
    call level1_yakici

    movlw d'2'
    xorwf level,w
    btfsc STATUS,Z ;level2_da ise
    ;level2_ayarlayci
    call level2_yakici

    movlw d'3'
    xorwf level,w
    btfsc STATUS,Z ;level3_da ise
    ;level3_ayarlayci
    call level3_yakici

    return
    
level1_yakici
    
    movlw d'0'
    xorwf random1y, w
    btfsc STATUS,Z ; 0 inci row-da ise
    ;bsf PORTC, random1y
    call yak_C

    movlw d'1'
    xorwf random1y, w
    btfsc STATUS,Z ; 1 inci row-da ise
    ;bsf PORTD, random1y
    call yak_D
    
    movlw d'2'
    xorwf random1y, w
    btfsc STATUS,Z ; 1 inci row-da ise
    ;bsf PORTE, random1y
    call yak_E
    
    movlw d'3'
    xorwf random1y, w
    btfsc STATUS,Z ; 1 inci row-da ise
    ;bsf PORTF, random1y
    call yak_F
    
    return
    
    
    
yak_C
    movf random1x,0
    ADDWF random1x,0
    call Table1
    IORWF p_c, 1
    ;MOVWF PORTC
    return
	

yak_D
    movf random1x,0
    ADDWF random1x,0
    call Table1
    ;MOVWF PORTD
    IORWF p_d, 1
    return
	
    
    yak_E
	movf random1x,0
	ADDWF random1x,0
	call Table1
	;MOVWF PORTE
	IORWF p_e, 1
	return
    
yak_F
    movf random1x,0
    ADDWF random1x,0
    call Table1
    ;MOVWF PORTF
    IORWF p_f, 1
    return
    
    
    
level2_yakici
    
    call level1_yakici
    
    MOVF random1y,0 ; en sonunda restore edyom
    MOVWF random1y_yedek
    MOVF random1x,0 ; en sonunda restore edyom
    MOVWF random1x_yedek
    
    
    MOVF random2y,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF random1y
    MOVF random2x,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF random1x
    
    call level1_yakici

    MOVF random1y_yedek, 0 ; en sonunda restore edyom
    MOVWF random1y
    MOVF random1x_yedek, 0 ; en sonunda restore edyom
    MOVWF random1x
return

level3_yakici

    ;call level1_yakici
    call level2_yakici
    
    MOVF random1y,0 ; en sonunda restore edyom
    MOVWF random1y_yedek
    MOVF random1x,0 ; en sonunda restore edyom
    MOVWF random1x_yedek
    
    
    MOVF random3y,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF random1y
    MOVF random3x,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF random1x
    
    call level1_yakici

    MOVF random1y_yedek, 0 ; en sonunda restore edyom
    MOVWF random1y
    MOVF random1x_yedek, 0 ; en sonunda restore edyom
    MOVWF random1x
    
    
    
return
    

    
low_isr:
    call save_registers
    btfss INTCON, 2       
    goto    rb_interrupt    ;No. Goto PORTB on change interrupt handler part
    goto    timer_interrupt
    
isr:
    call    save_registers  ;Save current content of STATUS and PCLATH registers to be able to restore them later

    btfss   PIR1, 0;INTCON, 2       ;Is this a timer interrupt?
    call restore_registers
    btfss   PIR1, 0
    retfie
    goto    RTCisr;timer_interrupt ;Yes. Goto timer interrupt handler part

;;;;;;;;;;;;;;;;;;;;;;;; Timer interrupt handler part ;;;;;;;;;;;;;;;;;;;;;;;;;;
timer_interrupt:
	clrf TMR0
        bcf	    INTCON,TMR0IF   
	call restore_registers
retfie
    
 

 
RTCisr:
BSF TMR1H, 7 ; Preload for 1 sec overflow
BCF PIR1, 0 ; Clear interrupt flag
INCF secs, F ; Increment seconds

movf secs, w
sublw d'38'
btfss STATUS, Z
goto	timer_interrupt_exit    ;No, then exit from interrupt service routine
clrf	secs                 ;Yes, then clear count variable
    
movlw d'0'
xorwf state,0
btfsc STATUS,Z
movff ten,state    
decf state, F;comf	state, f
movff state,dis0
    
movlw d'9'
xorwf state,0
btfsc STATUS,Z 
decf counter,f 
movff counter,dis1
  
    
bcf     PIR1, 0           ;Clear TMROIF
;movlw	d'200'               ;256-61=195; 195*256*5 = 249600 instruction cycle;
;movwf	TMR1
MOVLW d'95' ; Preload TMR1 register pair
MOVWF TMR1H ; for 1 second overflow
CLRF TMR1L
call restore_registers
retfie 
 
 sondurucu
    CLRF   LATC
    CLRF   LATD
    CLRF   LATE
    CLRF   LATF
 
    CLRF   PORTC
    CLRF   PORTD
    CLRF   PORTE
    CLRF   PORTF
    clrf    p_c
    clrf    p_d
    clrf    p_e
    clrf    p_f
    clrf    led_on_p_c 
    clrf    led_on_p_d
    clrf    led_on_p_e
    clrf    led_on_p_f
return
 
 
 
 
timer_interrupt_exit:
    bcf     PIR1, 0           ;Clear TMROIF
	movlw	d'95'               ;256-61=195; 195*256*5 = 249600 instruction cycle;
	movwf	TMR1
	
    call restore_registers
    
	retfie

	


	
rb_interrupt:
	btfss   INTCON, 0           ;Is this PORTB on change interrupt
	goto	rb_interrupt_exit0  ;No, then exit from interrupt service routine
	movf	PORTB, w            ;Read PORTB to working register
	movwf	portb_var           ;Save it to shadow register
	btfsc	portb_var, 4        ;Test its 4th bit whether it is cleared
	goto	rb_interrupt_exit4  ; RB4 is 1
	btfsc	portb_var, 5
	goto	rb_interrupt_exit5
	btfsc	portb_var, 6
	goto	rb_interrupt_exit6
	btfsc	portb_var, 7
	goto	rb_interrupt_exit7
	
	
rb_interrupt_exit1:
	movf	portb_var, w        ;Put shadow register to W
	movwf	PORTB               ;Write content of W to actual PORTB, so that we will be able to clear RBIF
	bcf     INTCON, 0           ;Clear PORTB on change FLAG
	call	restore_registers   ;Restore STATUS and PCLATH registers to their state before interrupt occurs
	retfie
rb_interrupt_exit4:
	movf dis2,0
	decf WREG,0
	btfsc STATUS,N
	movlw d'3'
	movwf dis2	
	movf	portb_var, w        ;Put shadow register to W
	movwf	PORTB               ;Write content of W to actual PORTB, so that we will be able to clear RBIF
	bcf     INTCON, 0           ;Clear PORTB on change FLAG

	call	restore_registers   ;Restore STATUS and PCLATH registers to their state before interrupt occurs
	clrf PORTB
	retfie
rb_interrupt_exit5:
	incf dis2,f
	movlw d'4'
	xorwf dis2,0
	btfsc STATUS,Z
	clrf dis2	            
	movf	portb_var, w        ;Put shadow register to W
	movwf	PORTB               ;Write content of W to actual PORTB, so that we will be able to clear RBIF
	bcf     INTCON, 0           ;Clear PORTB on change FLAG
	call	restore_registers   ;Restore STATUS and PCLATH registers to their state before interrupt occurs
	clrf PORTB
	retfie
rb_interrupt_exit6:
	movf dis3,0
	decf WREG,0
	btfsc STATUS,N
	movlw d'5'
	movwf dis3
	movf	portb_var, w        ;Put shadow register to W
	movwf	PORTB               ;Write content of W to actual PORTB, so that we will be able to clear RBIF
	bcf     INTCON, 0           ;Clear PORTB on change FLAG
	call	restore_registers   ;Restore STATUS and PCLATH registers to their state before interrupt occurs
	clrf PORTB
	retfie
rb_interrupt_exit7:
	incf dis3,f
	movlw d'6'
	xorwf dis3,0
	btfsc STATUS,Z
	clrf dis3
	movf	portb_var, w        ;Put shadow register to W
	movwf	PORTB               ;Write content of W to actual PORTB, so that we will be able to clear RBIF
	bcf     INTCON, 0           ;Clear PORTB on change FLAG
	call	restore_registers   ;Restore STATUS and PCLATH registers to their state before interrupt occurs
	clrf PORTB
	retfie
	

rb_interrupt_exit0:
    call    restore_registers   ;Restore STATUS and PCLATH registers to their state before interrupt occurs
    retfie
	
	
	
	
	

	
	


	
	
	
	
	
	
	
	
	
	
;;;;;;;;;;;; Register handling for proper operation of main program ;;;;;;;;;;;;
save_registers:
    movwf 	w_temp          ;Copy W to TEMP register
    swapf 	STATUS, w       ;Swap status to be saved into W
    clrf 	STATUS          ;bank 0, regardless of current bank, Clears IRP,RP1,RP0
    movwf 	status_temp     ;Save status to bank zero STATUS_TEMP register
    movf 	PCLATH, w       ;Only required if using pages 1, 2 and/or 3
    movwf 	pclath_temp     ;Save PCLATH into W
    clrf 	PCLATH          ;Page zero, regardless of current page
	return

restore_registers:
    movf 	pclath_temp, w  ;Restore PCLATH
    movwf 	PCLATH          ;Move W into PCLATH
    swapf 	status_temp, w  ;Swap STATUS_TEMP register into W
    movwf 	STATUS          ;Move W into STATUS register
    swapf 	w_temp, f       ;Swap W_TEMP
    swapf 	w_temp, w       ;Swap W_TEMP into W
    return

disable_timer1
    	BCF PIE1, 0			;TMR1IE disable Timer1 interrupt						;clrf    INTCON
    return
enable_timer1
	BSF PIE1, 0			;TMR1IE disable Timer1 interrupt						;clrf    INTCON
    return
disable_timer0
    bcf INTCON,5
    return
 enable_timer0
    bsf INTCON,5
    return
disable_portb	
    bcf INTCON,	3
    return
enable_portb
    bsf INTCON,	3
    return  

    
    DELAY                            ; Time Delay Routines
     MOVLW 50                        ; Copy 50 to W
     MOVWF L2                    ; Copy W into L2
 LOOP2
     MOVLW 255                   ; Copy 255 into W
     MOVWF L1                    ; Copy W into L1
 LOOP1
     decfsz L1,F                    ; Decrement L1. If 0 Skip next instruction
         GOTO LOOP1                ; ELSE Keep counting down
     decfsz L2,F                    ; Decrement L2. If 0 Skip next instruction
         GOTO LOOP2                ; ELSE Keep counting down
     return
    
led_on
    movlw d'1'
    xorwf led_on_level,w
    btfsc STATUS,Z ;level1_da ise
    ;level1_ayarlayci
    call level1_led_on
    movff led_on_p_c, LATC;PORTC
    movff led_on_p_d, LATD;PORTD
    movff led_on_p_e, LATE;PORTE
    movff led_on_p_f, LATF;PORTF
    movlw d'2'
    xorwf led_on_level,w
    btfsc STATUS,Z ;level2_da ise
    ;level2_ayarlayci
    call level2_led_on

    movlw d'3'
    xorwf led_on_level,w
    btfsc STATUS,Z ;level3_da ise
    ;level3_ayarlayci
    call level3_led_on

    return
    
level1_led_on
    
    movlw d'0'
    xorwf led_on_random1y, w
    btfsc STATUS,Z ; 0 inci row-da ise
    ;bsf PORTC, random1y
    call led_on_yak_C

    movlw d'1'
    xorwf led_on_random1y, w
    btfsc STATUS,Z ; 1 inci row-da ise
    ;bsf PORTD, random1y
    call led_on_yak_D
    
    movlw d'2'
    xorwf led_on_random1y, w
    btfsc STATUS,Z ; 1 inci row-da ise
    ;bsf PORTE, random1y
    call led_on_yak_E
    
    movlw d'3'
    xorwf led_on_random1y, w
    btfsc STATUS,Z ; 1 inci row-da ise
    ;bsf PORTF, random1y
    call led_on_yak_F
    
    return
    
    
    
led_on_yak_C
    movf led_on_random1x,0
    ADDWF led_on_random1x,0
    call Table1
    IORWF led_on_p_c, 1
    ;MOVWF PORTC
    return
	

led_on_yak_D
    movf led_on_random1x,0
    ADDWF led_on_random1x,0
    call Table1
    ;MOVWF PORTD
    IORWF led_on_p_d, 1
    return
	
    
    led_on_yak_E
	movf led_on_random1x,0
	ADDWF led_on_random1x,0
	call Table1
	;MOVWF PORTE
	IORWF led_on_p_e, 1
	return
    
led_on_yak_F
    movf led_on_random1x,0
    ADDWF led_on_random1x,0
    call Table1
    ;MOVWF PORTF
    IORWF led_on_p_f, 1
    return
    
    
    
level2_led_on
    
    call level1_led_on
    
    MOVF led_on_random1y,0 ; en sonunda restore edyom
    MOVWF random1y_yedek
    MOVF led_on_random1x,0 ; en sonunda restore edyom
    MOVWF random1x_yedek
    
    
    MOVF led_on_random2y,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF led_on_random1y
    MOVF led_on_random2x,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF led_on_random1x
    
    call level1_led_on

    MOVF random1y_yedek, 0 ; en sonunda restore edyom
    MOVWF led_on_random1y
    MOVF random1x_yedek, 0 ; en sonunda restore edyom
    MOVWF led_on_random1x
return

level3_led_on

    ;call level1_yakici
    call level2_led_on
    
    MOVF led_on_random1y,0 ; en sonunda restore edyom
    MOVWF random1y_yedek
    MOVF led_on_random1x,0 ; en sonunda restore edyom
    MOVWF random1x_yedek
    
    
    MOVF led_on_random3y,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF led_on_random1y
    MOVF led_on_random3x,0 ; onemli cunku yak_c de random1y kullanyom
    MOVWF led_on_random1x
    
    call level1_led_on

    MOVF random1y_yedek, 0 ; en sonunda restore edyom
    MOVWF led_on_random1y
    MOVF random1x_yedek, 0 ; en sonunda restore edyom
    MOVWF led_on_random1x   
return
    
end
     
   