#ifndef SERIAL_CONFIG_H
#define SERIAL_CONFIG_H

#include <stdint.h>
/*
typedef enum{
	
	PA_0=0x00,	PA_1=0x01, PA_2=0x02, PA_3=0x03,
	PA_4=0x04,	PA_5=0x05, PA_6=0x06,	PA_7=0x07,
	PA_8=0x08,	PA_9=0x09,	PA_10=0x0A,	PA_11=0x0B,
	PA_12=0x0C,	PA_13=0x0D,	PA_14=0x0E,	PA_15=0x0F,
	
	PB_0=0x10,	PB_1=0x11, PB_2=0x12, PB_3=0x13,
	PB_4=0x14,	PB_5=0x15, PB_6=0x16,	PB_7=0x17,
	PB_8=0x018,	PB_9=0x19,	PB_10=0x1A,	PB_11=0x1B,
	PB_12=0x1C,	PB_13=0x1D,	PB_14=0x1E,	PB_15=0x1F,

	PC_0=0x20,	PC_1=0x21, PC_2=0x22, PC_3=0x23,
	PC_4=0x24,	PC_5=0x25, PC_6=0x26,	PC_7=0x27,
	PC_8=0x28,	PC_9=0x29,	PC_10=0x2A,	PC_11=0x2B,
	PC_12=0x2C,	PC_13=0x2D,	PC_14=0x2E,	PC_15=0x2F,

}
PinName;
*/
// Définition des ports COM avec COMDEFAULT à la fin
typedef enum {
    COM1 = 1,       // COM1
    COM2 = 2,       // COM2
    COM3 = 3,       // COM3
    COMDEFAULT = COM2  // COMDEFAULT est par défaut COM1
} COMPort;

// Définition des vitesses de communication avec SPEEDDEFAULT à la fin
typedef enum {
    SPEED_9600 = 9600,    // 9600 bauds
    SPEED_19200 = 19200,  // 19200 bauds
    SPEED_115200 = 115200,// 115200 bauds
    SPEEDDEFAULT = SPEED_9600 // SPEEDDEFAULT est par défaut 9600 bauds
} Speed;

// Définition des configurations de communication avec CONFIGDEFAULT à la fin
typedef enum {
    CONFIG_8N1 = 0x00,   // 8 bits de données, Pas de parité, 1 bit de stop
    CONFIG_8N2 = 0x01,   // 8 bits de données, Pas de parité, 2 bits de stop
    CONFIG_8E1 = 0x10,   // 8 bits de données, Parité paire, 1 bit de stop
    CONFIG_8E2 = 0x11,   // 8 bits de données, Parité paire, 2 bits de stop
    CONFIG_8O1 = 0x20,   // 8 bits de données, Parité impaire, 1 bit de stop
    CONFIG_8O2 = 0x21,   // 8 bits de données, Parité impaire, 2 bits de stop
    CONFIG_9N1 = 0x30,   // 9 bits de données, Pas de parité, 1 bit de stop
    CONFIG_9N2 = 0x31,   // 9 bits de données, Pas de parité, 2 bits de stop
    CONFIG_9E1 = 0x40,   // 9 bits de données, Parité paire, 1 bit de stop
    CONFIG_9E2 = 0x41,   // 9 bits de données, Parité paire, 2 bits de stop
    CONFIG_9O1 = 0x50,   // 9 bits de données, Parité impaire, 1 bit de stop
    CONFIG_9O2 = 0x51,   // 9 bits de données, Parité impaire, 2 bits de stop
    CONFIGDEFAULT = CONFIG_8N1  // CONFIGDEFAULT est par défaut 8 bits, Pas de parité, 1 bit de stop
} Config;

// Définition des modes de communication avec MODEDEFAULT à la fin
typedef enum {
    TX_MODE = 0x01,      // Mode transmission
    RX_MODE = 0x02,      // Mode réception
    TXRX_MODE = 0x03,    // Mode transmission et réception
    MODEDEFAULT = TXRX_MODE // MODEDEFAULT est par défaut transmission et réception
} Mode;

#endif // SERIAL_CONFIG_H
