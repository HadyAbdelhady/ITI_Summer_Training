#include "mcal_gpio_avr.h" // Your GPIO driver header
#include "hal_lcd.h"       // Your LCD driver header
void _delay_ms(uint64_t x)
{
    for (uint8_t i = 0; i < x * 10; i++)
        ;
}
// Function to print the name in a sinusoidal wave pattern on LCD
void printNameInWavePattern(char *name)
{
    uint8_t length = 0;
    while (name[length] != '\0')
    {
        length++;
    }

    uint8_t i;

    Clear_LCD();      // Clear the LCD
    GotoXY_LCD(0, 0); // Set position for the character in the upper row

    for (i = 0; i < length; i++)
    {
        GotoXY_LCD(i + 1, 0);    // Set position for the character in the upper row
        Write_char_LCD(name[i]); // Display the character on the LCD

        GotoXY_LCD(i + 1, 1);    // Set position for the next character in the lower row
        Write_char_LCD(name[i]); // Display the character on the LCD

        _delay_ms(300); // Delay for smooth animation (adjust as needed)
    }
}

typedef enum
{
    OFF = 0,
    RIGHT = 1,
    LEFT = 2
} Direction;
uint8_t main(void)
{
    ///////////////////////////////////// Sinusoidal Name Wave ///////////////////////////////////////
    // Initialize GPIO and LCD
    MCAL_GPIO_SET_Pin(LCD_PORT, Output, RS);
    MCAL_GPIO_SET_Pin(LCD_PORT, Output, RW);
    MCAL_GPIO_SET_Pin(LCD_PORT, Output, E);

    init_LCD();

    // Clear the LCD screen
    Clear_LCD();

    // Get the user's name
    uint8_t name[16] = "HADYABDELHADY";
    // Clear the LCD screen
    Clear_LCD();
    // Print the name in a sinusoidal wave pattern
    printNameInWavePattern(name);

    ///////////////////////////////////// LEDS 1 ///////////////////////////////////////

    MCAL_GPIO_Set_Port_Direction(GPIOA, 0b00000111);
    MCAL_GPIO_Set_Port_Direction(GPIOA, 0b11111111);
    // Define the patterns for digits 0-9
    uint32_t arr[10] = {
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111, // 9
        0b00111111  // 0
    };

    // Define the patterns for selecting the output
    uint32_t out[3] = {0x01, 0x02, 0x04};
    uint32_t sec[3] = {10, 3, 10};
    uint32_t cont = 0;

    while (1)
    {
        // Set the output pins for PORTA
        MCAL_GPIO_WritePort(GPIOA, out[cont]);
        // Display the patterns on PORTD
        for (uint32_t i = 0; i < sec[cont]; i++)
        {
            MCAL_GPIO_WritePort(GPIOD, arr[i]);
            _delay_ms(1000);
        }
        cont++;
        cont %= 3;
    }

    return 0;

    ///////////////////////////////////// LEDS 2 ///////////////////////////////////////
    MCAL_GPIO_Set_Port_Direction(GPIOA, 0b11111111);
    MCAL_GPIO_WritePort(GPIOA, 0b0000000);
    uint32_t arr[8] = {
        0b00000001, // pin0
        0b00000010, // pin1
        0b00000100, // pin2
        0b00001000, // pin3
        0b00010000, // pin4
        0b00100000, // pin5
        0b01000000, // pin6
        0b10000000, // pin7
    };
    uint32_t i = 0;
    uint32_t snk = 0;
    uint32_t inp = 0;
    uint32_t Png = 0;
    uint32_t size = sizeof(arr) / sizeof(uint32_t);
    MCAL_GPIO_Set_Port_Direction(GPIOB, 0b00000000);
    MCAL_GPIO_WritePort(GPIOB, 0b00000111);
    while (1)
    {
        inp = (~MCAL_GPIO_ReadPORT(GPIOB)) & 0x07;
        inp++;
        switch (inp)
        {
        case 1: // Flashing Every 500ms
            MCAL_GPIO_WritePort(GPIOA, 0xFF);
            _delay_ms(500);
            MCAL_GPIO_WritePort(GPIOA, 0x00);
            _delay_ms(500);
            break;
        case 2: // Shifting Left Every 250ms
            MCAL_GPIO_WritePort(GPIOA, arr[i]);
            _delay_ms(250);
            i++;
            i = i % size;
            break;
        case 3: // Shifting Right Every 250ms
            MCAL_GPIO_WritePort(GPIOA, arr[i]);
            _delay_ms(250);
            i--;
            if (i == -1)
                i = size - 1;
            break;
        case 4: // 2-LEDs Converging Every 300ms
            for (uint32_t con = 0; con < 4; con++)
            {
                MCAL_GPIO_WritePort(GPIOA, arr[size - 1 - con] | arr[con]);

                _delay_ms(300);
            }
            break;
        case 5: // 2-LEDs Diverging Every 300ms
            for (uint32_t div = 0; div < 4; div++)
            {
                MCAL_GPIO_WritePort(GPIOA, arr[(size / 2) + div] | arr[(size / 2) - 1 - div]);

                _delay_ms(300);
            }
            break;
        case 6: // Ping Pong Effect Every 250ms
            if (Png == 0)
            {
                for (uint32_t pp = 0; pp < size; pp++)
                {
                    MCAL_GPIO_WritePort(GPIOA, arr[pp]);

                    _delay_ms(250);
                }
            }
            else
            {
                for (uint32_t pp = size - 1; pp >= 0; pp--)
                {
                    MCAL_GPIO_WritePort(GPIOA, arr[pp]);
                    _delay_ms(250);
                }
            }
            Png++;
            Png = Png % 2;
            break;
        case 7: // Increment (Snake Effect) Every 300ms
            MCAL_GPIO_WritePin(GPIOA, HIGH, arr[snk]);
            _delay_ms(300);
            snk++;
            if (snk == size)
            {
                MCAL_GPIO_WritePort(GPIOA, 0x00);
                snk = 0;
            }
            break;
        case 8: // // 2-LEDs Converging/Diverging Every 300ms
            for (uint32_t con = 0; con < 4; con++)
            {
                MCAL_GPIO_WritePort(GPIOA, arr[size - 1 - con] | arr[con]);

                _delay_ms(300);
            }
            for (uint32_t div = 0; div < 4; div++)
            {
                MCAL_GPIO_WritePort(GPIOA, arr[(size / 2) + div] | arr[(size / 2) - 1 - div]);
                _delay_ms(300);
            }
            break;
        }
    }
    ///////////////////////////////////// Motors  ///////////////////////////////////////
    S_GPIO_t PORTC, PORTB;

    MCAL_GPIO_Set_Port_Direction(&PORTC, GPIO_PIN_0 | GPIO_PIN_1);
    MCAL_GPIO_Set_Port_Direction(&PORTB, GPIO_PIN_3 | GPIO_PIN_4);
    MCAL_GPIO_WritePin(&PORTB, GPIO_PIN_3, HIGH);
    MCAL_GPIO_WritePin(&PORTB, GPIO_PIN_4, HIGH);

    init_LCD();

    Direction Dir = OFF;
    Direction Prev_Dir = OFF;

    while (1)
    {
        if (MCAL_GPIO_ReadPin(&PORTB, GPIO_PIN_3) == LOW)
        {
            MCAL_GPIO_WritePin(&PORTC, GPIO_PIN_0, HIGH);
            Dir = RIGHT;
        }
        if (MCAL_GPIO_ReadPin(&PORTB, GPIO_PIN_4) == LOW)
        {
            MCAL_GPIO_WritePin(&PORTC, GPIO_PIN_1, HIGH);
            Dir = LEFT;
        }

        if (Dir != Prev_Dir)
        {
            Clear_LCD();
            switch (Dir)
            {
            case RIGHT:
                MCAL_GPIO_WritePin(&PORTC, GPIO_PIN_1, LOW);
                Write_String_LCD("Right");
                break;
            case LEFT:
                MCAL_GPIO_WritePin(&PORTC, GPIO_PIN_0, LOW);
                Write_String_LCD("Left");
                break;
            default:
                MCAL_GPIO_WritePin(&PORTC, GPIO_PIN_1, LOW);
                MCAL_GPIO_WritePin(&PORTC, GPIO_PIN_0, LOW);
                Write_String_LCD("Off");
                break;
            }
        }

        Prev_Dir = Dir;
        Dir = OFF;
    }
    return 0;
}
