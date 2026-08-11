#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "DIO_int.h"
#include "DIO_prv.h"


void MDIO_vInit(void)
{
    /* Initialize all ports as inputs with LOW output values */

    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;

    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
}


/* =========================================================
 * PIN FUNCTIONS
 * ========================================================= */

void MDIO_vSetPinDir(
    u8 A_u8PortNo,
    u8 A_u8PinNo,
    u8 A_u8PinDir
)
{
    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            if (A_u8PinDir == DIO_OUTPUT)
                SET_BIT(DDRA, A_u8PinNo);
            else
                CLR_BIT(DDRA, A_u8PinNo);
            break;

        case DIO_PORTB:
            if (A_u8PinDir == DIO_OUTPUT)
                SET_BIT(DDRB, A_u8PinNo);
            else
                CLR_BIT(DDRB, A_u8PinNo);
            break;

        case DIO_PORTC:
            if (A_u8PinDir == DIO_OUTPUT)
                SET_BIT(DDRC, A_u8PinNo);
            else
                CLR_BIT(DDRC, A_u8PinNo);
            break;

        case DIO_PORTD:
            if (A_u8PinDir == DIO_OUTPUT)
                SET_BIT(DDRD, A_u8PinNo);
            else
                CLR_BIT(DDRD, A_u8PinNo);
            break;

        default:
            break;
    }
}


void MDIO_vSetPinVal(
    u8 A_u8PortNo,
    u8 A_u8PinNo,
    u8 A_u8PinVal
)
{
    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            if (A_u8PinVal == DIO_HIGH)
                SET_BIT(PORTA, A_u8PinNo);
            else
                CLR_BIT(PORTA, A_u8PinNo);
            break;

        case DIO_PORTB:
            if (A_u8PinVal == DIO_HIGH)
                SET_BIT(PORTB, A_u8PinNo);
            else
                CLR_BIT(PORTB, A_u8PinNo);
            break;

        case DIO_PORTC:
            if (A_u8PinVal == DIO_HIGH)
                SET_BIT(PORTC, A_u8PinNo);
            else
                CLR_BIT(PORTC, A_u8PinNo);
            break;

        case DIO_PORTD:
            if (A_u8PinVal == DIO_HIGH)
                SET_BIT(PORTD, A_u8PinNo);
            else
                CLR_BIT(PORTD, A_u8PinNo);
            break;

        default:
            break;
    }
}


u8 MDIO_u8GetPinVal(
    u8 A_u8PortNo,
    u8 A_u8PinNo
)
{
    u8 L_u8PinVal = DIO_LOW;

    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            L_u8PinVal = GET_BIT(PINA, A_u8PinNo);
            break;

        case DIO_PORTB:
            L_u8PinVal = GET_BIT(PINB, A_u8PinNo);
            break;

        case DIO_PORTC:
            L_u8PinVal = GET_BIT(PINC, A_u8PinNo);
            break;

        case DIO_PORTD:
            L_u8PinVal = GET_BIT(PIND, A_u8PinNo);
            break;

        default:
            break;
    }

    return L_u8PinVal;
}


void MDIO_vTogglePinVal(
    u8 A_u8PortNo,
    u8 A_u8PinNo
)
{
    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            TOG_BIT(PORTA, A_u8PinNo);
            break;

        case DIO_PORTB:
            TOG_BIT(PORTB, A_u8PinNo);
            break;

        case DIO_PORTC:
            TOG_BIT(PORTC, A_u8PinNo);
            break;

        case DIO_PORTD:
            TOG_BIT(PORTD, A_u8PinNo);
            break;

        default:
            break;
    }
}


/* =========================================================
 * PORT FUNCTIONS
 * ========================================================= */

void MDIO_vSetPortDir(
    u8 A_u8PortNo,
    u8 A_u8PortDir
)
{
    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            DDRA = A_u8PortDir;
            break;

        case DIO_PORTB:
            DDRB = A_u8PortDir;
            break;

        case DIO_PORTC:
            DDRC = A_u8PortDir;
            break;

        case DIO_PORTD:
            DDRD = A_u8PortDir;
            break;

        default:
            break;
    }
}


void MDIO_vSetPortVal(
    u8 A_u8PortNo,
    u8 A_u8PortVal
)
{
    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            PORTA = A_u8PortVal;
            break;

        case DIO_PORTB:
            PORTB = A_u8PortVal;
            break;

        case DIO_PORTC:
            PORTC = A_u8PortVal;
            break;

        case DIO_PORTD:
            PORTD = A_u8PortVal;
            break;

        default:
            break;
    }
}


u8 MDIO_u8GetPortVal(
    u8 A_u8PortNo
)
{
    u8 L_u8PortVal = 0;

    switch (A_u8PortNo)
    {
        case DIO_PORTA:
            L_u8PortVal = PINA;
            break;

        case DIO_PORTB:
            L_u8PortVal = PINB;
            break;

        case DIO_PORTC:
            L_u8PortVal = PINC;
            break;

        case DIO_PORTD:
            L_u8PortVal = PIND;
            break;

        default:
            break;
    }

    return L_u8PortVal;
}