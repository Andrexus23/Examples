// этот загаловок всегда стоит включать при программировании Arduino на Си
// в он среди прочего включает в себя адреса регистров Arduino 
// так что нам не придеться дефинировать их самостоятельно
#include <avr/io.h>	
#include "..\system\uart\uart.h"

static void init(void);
static void printHelloWorld(void);