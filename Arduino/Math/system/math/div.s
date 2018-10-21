.global div_16bit_int

; Функция выполняет деление 2-ух 16-и битных целых чисел
; Функция принимает 2 16-и битных параметра передаваемые через регистры r24:r25 и r22:r23 
; Функция возвращает 32-и битный параметр через регистры r22:r25
; В регистрах r24:r25 возвращается целочисленный результат деления 
; В регистрах r22:r23 возвращается целочисленный остаток от деления 
div_16bit_int:
	; r16, r17, r18, r19 будут хранить промежуточный результат деления
	; Сохраняем их текущие значения
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	
	clr r16
	clr r17
	
	mov r18, r24
	mov r19, r25
	
	ldi r20, 1
	clr r21
	
_div_16bit_int_loop:
	; Сравниваем делимое с делителем
	clc
	cp r18, r22
	cpc r19, r23
	; Переходим на _div_16bit_int_exit если Carry бит установлен (делитель больше делимого)
	brcs _div_16bit_int_exit
	
	sub r18, r22
	sbc r19, r23
	
	; Добавляем 1 к результату деления
	clc
	add r16, r20
	adc r17, r21
	rjmp _div_16bit_int_loop
	
_div_16bit_int_exit:
	; Переносим результат и остаток из временных регистров
	mov r22, r18
	mov r23, r19
	mov r24, r16
	mov r25, r17

	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	ret
	