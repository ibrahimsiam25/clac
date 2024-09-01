#include "main.h"

int main() {
    /* Initializations */
	LCD_8_bit_init();
    Keypad_enu_Init();

    /* Variables Declarations */
    u8 key;
    u8 counter = 0;
    while (1) {

        u8 operator = '\0';
        u8 num1[10] = {0};
        u8 num2[10] = {0};
        u16 result[10] = {0};

        while (key != '+' && key != '-' && key != '*' && key != '/' && key != '=') {
            if (Keypad_enu_getKey(&key) == STATE_OK) {
                if (key != KEYPAD_U8_NO_KEY_PRESSED) {
                	if (key != '+' && key != '-' && key != '*' && key != '/' && key != '='){
                		 num1[counter++] = key;
                		 if(counter == 1){
                			 LCD_CLR();
						 }
                	}
                	LCD_8_bit_sendChar(key);
                }
            }

        }

        operator = key;
        key = KEYPAD_U8_NO_KEY_PRESSED;
        counter = 0;

        while (key != '+' && key != '-' && key != '*' && key != '/' && key != '=') {
            if (Keypad_enu_getKey(&key) == STATE_OK) {
                if (key != KEYPAD_U8_NO_KEY_PRESSED) {
                	LCD_8_bit_sendChar(key);
                	if (key != '+' && key != '-' && key != '*' && key != '/' && key != '='){
                		 num2[counter++] = key;
                	}
                }
            }

        }

		switch (operator) {
			case '+':
				sprintf(result, "%i", atoi(num1) + atoi(num2));
				break;
			case '-':
				sprintf(result, "%i", atoi(num1) - atoi(num2));
				break;
			case '*':
				sprintf(result, "%i", atoi(num1) * atoi(num2));
				break;
			case '/':
				if (atoi(num2) != 0) {
					sprintf(result, "%i", atoi(num1) / atoi(num2));
				} else {
					strcpy(result, "Error: Division by zero");
				}
				 break;
			default:
				strcpy(result, "Error: Invalid operator");
				break;
		}

		LCD_CLR();
		LCD_8_bit_sendString(result);
		key = KEYPAD_U8_NO_KEY_PRESSED;
		counter = 0;
    }

    return 0;
}
