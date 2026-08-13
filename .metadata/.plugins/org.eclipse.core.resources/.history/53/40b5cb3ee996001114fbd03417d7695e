/*
 * main.c
 *
 * Integrated Robot:
 *  - Autonomous mode
 *      * 2 obstacle IR sensors
 *      * 2 TCRT5000 line sensors
 *
 *  - Manual mode
 *      * Bluetooth commands
 *
 * Sensor connections:
 *  - Left obstacle IR  -> PB4
 *  - Right obstacle IR -> PB5
 *  - Left TCRT5000     -> PD2
 *  - Right TCRT5000    -> PD3
 *
 * Motor connections:
 *  - MOTOR_1 -> Left motor
 *  - MOTOR_2 -> Right motor
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/TIMER/TIMER_int.h"

#include "../HAL/MOTOR/MOTOR_int.h"
#include "../HAL/BLUETOOTH/BLUETOOTH_int.h"

#include <util/delay.h>


/* ========================================================= */
/*                    SENSOR CONFIGURATION                   */
/* ========================================================= */

/* Obstacle IR sensors */

#define IR_PORT                 DIO_PORTB

#define IR_LEFT_PIN             DIO_PIN4
#define IR_RIGHT_PIN            DIO_PIN5


/* Line-following TCRT5000 sensors */

#define LINE_PORT               DIO_PORTD

#define LINE_LEFT_PIN           DIO_PIN2
#define LINE_RIGHT_PIN          DIO_PIN3


/* ========================================================= */
/*                    SENSOR LOGIC                           */
/* ========================================================= */

/*
 * Obstacle IR:
 *
 * LOW  -> obstacle detected
 * HIGH -> path clear
 */

/*
 * TCRT5000:
 *
 * HIGH -> BLACK
 * LOW  -> WHITE
 */


/* ========================================================= */
/*                    MOTOR SPEEDS                           */
/* ========================================================= */

#define FORWARD_LEFT_SPEED      55
#define FORWARD_RIGHT_SPEED     50

#define TURN_SPEED              45

#define BACKWARD_LEFT_SPEED     50
#define BACKWARD_RIGHT_SPEED    50


/* ========================================================= */
/*                    MODES                                  */
/* ========================================================= */

#define MODE_AUTONOMOUS         0
#define MODE_MANUAL             1


/* ========================================================= */
/*                    BLUETOOTH COMMANDS                     */
/* ========================================================= */

#define CMD_AUTO                'A'
#define CMD_MANUAL              'M'

#define CMD_FORWARD             'F'
#define CMD_BACKWARD            'B'
#define CMD_LEFT                'L'
#define CMD_RIGHT               'R'
#define CMD_STOP                'S'


/* ========================================================= */
/*                    MOTOR FUNCTIONS                        */
/* ========================================================= */

static void Robot_vForward(void)
{
    HMOTOR_vSetDirection(
        MOTOR_1,
        MOTOR_FORWARD
    );

    HMOTOR_vSetDirection(
        MOTOR_2,
        MOTOR_FORWARD
    );

    HMOTOR_vSetSpeed(
        MOTOR_1,
        FORWARD_LEFT_SPEED
    );

    HMOTOR_vSetSpeed(
        MOTOR_2,
        FORWARD_RIGHT_SPEED
    );
}


static void Robot_vBackward(void)
{
    HMOTOR_vSetDirection(
        MOTOR_1,
        MOTOR_BACKWARD
    );

    HMOTOR_vSetDirection(
        MOTOR_2,
        MOTOR_BACKWARD
    );

    HMOTOR_vSetSpeed(
        MOTOR_1,
        BACKWARD_LEFT_SPEED
    );

    HMOTOR_vSetSpeed(
        MOTOR_2,
        BACKWARD_RIGHT_SPEED
    );
}


static void Robot_vTurnLeft(void)
{
    HMOTOR_vSetDirection(
        MOTOR_1,
        MOTOR_BACKWARD
    );

    HMOTOR_vSetDirection(
        MOTOR_2,
        MOTOR_FORWARD
    );

    HMOTOR_vSetSpeed(
        MOTOR_1,
        TURN_SPEED
    );

    HMOTOR_vSetSpeed(
        MOTOR_2,
        TURN_SPEED
    );
}


static void Robot_vTurnRight(void)
{
    HMOTOR_vSetDirection(
        MOTOR_1,
        MOTOR_FORWARD
    );

    HMOTOR_vSetDirection(
        MOTOR_2,
        MOTOR_BACKWARD
    );

    HMOTOR_vSetSpeed(
        MOTOR_1,
        TURN_SPEED
    );

    HMOTOR_vSetSpeed(
        MOTOR_2,
        TURN_SPEED
    );
}


static void Robot_vStop(void)
{
    HMOTOR_vStop(MOTOR_1);
    HMOTOR_vStop(MOTOR_2);
}


/* ========================================================= */
/*                AUTONOMOUS CONTROL                         */
/* ========================================================= */

static void Robot_vAutonomousControl(
    u8 A_u8LeftIR,
    u8 A_u8RightIR,
    u8 A_u8LeftLine,
    u8 A_u8RightLine
)
{
    /*
     * =====================================================
     * PRIORITY 1:
     * OBSTACLE AVOIDANCE
     * =====================================================
     *
     * The obstacle sensors have priority over
     * the line sensors.
     */


    /* Both obstacle sensors detect obstacle */

    if ((A_u8LeftIR == DIO_LOW) &&
        (A_u8RightIR == DIO_LOW))
    {
        /*
         * Obstacle directly in front.
         *
         * Stop first, then turn.
         */

        Robot_vStop();

        _delay_ms(100);

        Robot_vBackward();

        _delay_ms(200);

        Robot_vTurnRight();

        _delay_ms(400);

        Robot_vStop();
    }


    /* Left obstacle detected */

    else if (A_u8LeftIR == DIO_LOW)
    {
        /*
         * Obstacle on the left.
         *
         * Turn right.
         */

        Robot_vTurnRight();

        _delay_ms(150);
    }


    /* Right obstacle detected */

    else if (A_u8RightIR == DIO_LOW)
    {
        /*
         * Obstacle on the right.
         *
         * Turn left.
         */

        Robot_vTurnLeft();

        _delay_ms(150);
    }


    /*
     * =====================================================
     * PRIORITY 2:
     * LINE FOLLOWING
     * =====================================================
     */


    /* Both line sensors see WHITE */

    else if ((A_u8LeftLine == DIO_LOW) &&
             (A_u8RightLine == DIO_LOW))
    {
        /*
         * No black line detected.
         *
         * Continue forward according to the
         * existing line-following behavior.
         */

        Robot_vForward();
    }


    /* Left sensor sees BLACK */

    else if ((A_u8LeftLine == DIO_HIGH) &&
             (A_u8RightLine == DIO_LOW))
    {
        /*
         * Line is under the left sensor.
         *
         * Turn left.
         */

        Robot_vTurnLeft();
    }


    /* Right sensor sees BLACK */

    else if ((A_u8LeftLine == DIO_LOW) &&
             (A_u8RightLine == DIO_HIGH))
    {
        /*
         * Line is under the right sensor.
         *
         * Turn right.
         */

        Robot_vTurnRight();
    }


    /* Both line sensors see BLACK */

    else
    {
        /*
         * Both sensors see black.
         *
         * Continue forward.
         */

        Robot_vForward();
    }
}


/* ========================================================= */
/*                    MANUAL CONTROL                         */
/* ========================================================= */

static void Robot_vManualControl(u8 A_u8Command)
{
    switch (A_u8Command)
    {
        case 'F':
        case 'f':
            Robot_vForward();
            break;

        case 'B':
        case 'b':
            Robot_vBackward();
            break;

        case 'L':
        case 'l':
            Robot_vTurnLeft();
            break;

        case 'R':
        case 'r':
            Robot_vTurnRight();
            break;

        case 'S':
        case 's':
            Robot_vStop();
            break;

        default:
            Robot_vStop();
            break;
    }
}


/* ========================================================= */
/*                         MAIN                              */
/* ========================================================= */

int main(void)
{
    u8 L_u8Mode = MODE_AUTONOMOUS;

    u8 L_u8LeftIR;
    u8 L_u8RightIR;

    u8 L_u8LeftLine;
    u8 L_u8RightLine;

    u8 L_u8Command;


    /* ===================================================== */
    /*                    INITIALIZATION                     */
    /* ===================================================== */

    MTIMER_vINIT();

    HMOTOR_vINIT();

    HBLUETOOTH_vINIT();


    /* ===================================================== */
    /*                 OBSTACLE IR INPUTS                   */
    /* ===================================================== */

    MDIO_vSetPinDir(
        IR_PORT,
        IR_LEFT_PIN,
        DIO_INPUT
    );

    MDIO_vSetPinDir(
        IR_PORT,
        IR_RIGHT_PIN,
        DIO_INPUT
    );


    /* ===================================================== */
    /*                 LINE SENSOR INPUTS                   */
    /* ===================================================== */

    MDIO_vSetPinDir(
        LINE_PORT,
        LINE_LEFT_PIN,
        DIO_INPUT
    );

    MDIO_vSetPinDir(
        LINE_PORT,
        LINE_RIGHT_PIN,
        DIO_INPUT
    );


    /* ===================================================== */
    /*                 INITIAL ROBOT STATE                  */
    /* ===================================================== */

    Robot_vStop();


    /*
     * Start in autonomous mode.
     */

    L_u8Mode = MODE_AUTONOMOUS;


    /* ===================================================== */
    /*                      MAIN LOOP                        */
    /* ===================================================== */

    while (1)
    {
        /*
         * =================================================
         * Check Bluetooth first.
         * =================================================
         *
         * This allows the user to change between
         * autonomous and manual operation at any time.
         */

    	if (HBLUETOOTH_u8DataAvailable())
    	{
    	    L_u8Command = HBLUETOOTH_u8ReceiveChar();

    	    /* Ignore ENTER characters sent by the phone */
    	    if ((L_u8Command != '\r') &&
    	        (L_u8Command != '\n'))
    	    {
    	        /* AUTO */
    	        if ((L_u8Command == 'A') ||
    	            (L_u8Command == 'a'))
    	        {
    	            L_u8Mode = MODE_AUTONOMOUS;

    	            Robot_vStop();

    	            HBLUETOOTH_vSendString(
    	                (const u8 *)"AUTO\r\n"
    	            );
    	        }

    	        /* MANUAL */
    	        else if ((L_u8Command == 'M') ||
    	                 (L_u8Command == 'm'))
    	        {
    	            L_u8Mode = MODE_MANUAL;

    	            Robot_vStop();

    	            HBLUETOOTH_vSendString(
    	                (const u8 *)"MANUAL\r\n"
    	            );
    	        }

    	        /* MANUAL MOVEMENT COMMAND */
    	        else if (L_u8Mode == MODE_MANUAL)
    	        {
    	            Robot_vManualControl(L_u8Command);
    	        }
    	    }
    	}

        /* ================================================= */
        /*                AUTONOMOUS MODE                    */
        /* ================================================= */

        if (L_u8Mode == MODE_AUTONOMOUS)
        {
            /*
             * Read obstacle sensors.
             */

            L_u8LeftIR = MDIO_u8GetPinVal(
                IR_PORT,
                IR_LEFT_PIN
            );

            L_u8RightIR = MDIO_u8GetPinVal(
                IR_PORT,
                IR_RIGHT_PIN
            );


            /*
             * Read TCRT5000 sensors.
             */

            L_u8LeftLine = MDIO_u8GetPinVal(
                LINE_PORT,
                LINE_LEFT_PIN
            );

            L_u8RightLine = MDIO_u8GetPinVal(
                LINE_PORT,
                LINE_RIGHT_PIN
            );


            /*
             * Execute autonomous decision.
             */

            Robot_vAutonomousControl(
                L_u8LeftIR,
                L_u8RightIR,
                L_u8LeftLine,
                L_u8RightLine
            );
        }


        /*
         * Small loop delay.
         */

        _delay_ms(10);
    }


    return 0;
}
