/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15323
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
 #include <string.h>
/*
                         Main application
 */
uint16_t raw_data=0, prepare_data=0;
uint8_t arr_string[32];

 /* reverse:  переворачиваем строку s на месте */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
 /* itoa:  конвертируем n в символы в s */
 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* записываем знак */
         n = -n;          /* делаем n положительным числом */
     i = 0;
     do {       /* генерируем цифры в обратном порядке */
         s[i++] = n % 10 + '0';   /* берем следующую цифру */
     } while ((n /= 10) > 0);     /* удаляем */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
 void Uart_Write_Arr(char s[],int n)
 {
     for(uint8_t i=0; i< n; i++)
     {
         EUSART1_Write(s[i]);
     }
 }
 
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
    raw_data=ADC_GetConversion(channel_ANA5);
    prepare_data=raw_data*4-2730;
    
   //itoa(prepare_data,arr_string);
    Uart_Write_Arr("\r\ntemp= ",8);
    itoa(prepare_data/10,arr_string);
    Uart_Write_Arr(arr_string,strlen(arr_string));
     Uart_Write_Arr(".",1);
     itoa(prepare_data%10,arr_string);
   Uart_Write_Arr(arr_string,strlen(arr_string));
     
   // printf("data from LM335 = %d.%d°C\t",b/10,b%10); 
    raw_data=ADC_GetConversion(channel_ANA2);    
    
    //b=FLASH_ReadWord(0x811A);  
   // printf("data from TL431 = %d\r\n",raw_data); 
   /* printf("USER_ID,REV,CONFIG\r\n");
    for(uint8_t i=0;i<0x0C;i++)
    {
    b=FLASH_ReadWord(0x8000+i);
    printf("%d\r\n",prepare_data);
    }
     printf("DIA and DCI\r\n");
    for(uint8_t i=0;i<0x20;i++)
    {
    b=FLASH_ReadWord(0x8100+i);
    printf("%d\r\n",b);
    }
     printf("\r\n\r\n");*/
    __delay_ms(1000);
        // Add your application code
    }
}
/**
 End of File
*/