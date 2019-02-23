GPIO_DEF = 0

@ Включаем код из registers.inc в gpio.inc, если он не был включен раньше
.ifndef STM32F103C8T6_REGISTERS
.include "stm32f103c8t6_core/registers.inc"
.endif

@ Функция инициализирует RCC регистры для использования PORT C пинов
gpio_port_c_rcc_init:
	push {r0, r1}			@ Сохраняем регистры r0, r1  в стэк
	
	ldr r1, =RCC_CFGR		@ Загружаем адрес регистра RCC_CFGR в регистр r1
	ldr r0, =0x5000000 		@ Устанавливаем какой генератор частоты использовать (выбран high speed (clock) internal selected (HSI))
	
	@ Сохраняем значение из регистра r0 по адресу находящемуся в регистре r1
	@ В данный момент там находится адрес регистра RCC_CFGR  
	str r0, [r1]			
	
	@ Включаем тактирование PORT C пинов
	mov r0, 0x10			@ Помещаем в регистр r0 значение 0x10 или 1 0000 в двоичном виде (0x10 будет закодировано в инструкцию mov)
	
	ldr r1, =RCC_APB2ENR	@ Загружаем адрес регистра RCC_APB2ENR в регистр r1
	str r0, [r1]			@ Сохраняем значение из регистра r0 по адресу находящемуся в регистре r1
	
	pop {r0, r1}			@ Восстанавливаем регистры r0 и r1 из стэка
	bx lr