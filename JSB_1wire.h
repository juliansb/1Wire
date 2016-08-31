/**
******************************************************
* @file JSB_1Wire.h
* @brief Conjunto de funciones para tratamioento de String
* @author Oscar Salas Mestres & Julian Salas Bartolome
* @version 1.0
* @date Agosto 2012
*
*
*******************************************************/
#ifndef _JSB1WIRE
#define _JSB1WIRE

#include <stdlibm.h>     

/** @defgroup group1 Funciones para control del bus 1Wire
 *  @brief Funciones para control del bus 1Wire
 *  @{
 */

/** @defgroup group2 Funciones basicas
 *  @brief Conjunto de funciones basicas del bus, reset, transmision bit, recepcion bit, transmision byte, recepcion byte
 *  @{
 */

int1 OneWire_Reset (void);
void OneWire_Write (int1 lBit);
void OneWire_Write_1 (void);
void OneWire_Write_0 (void);
int1 OneWire_LeeBit (void);
void OneWire_SendByte (byte cDato); 
byte OneWire_ReceiveByte();

/** @} */ // end of group2

/** @defgroup group3 Comandos Bus
 *  @brief Conjunto de comandos gnéricos del bus 1Wire
 *  @{
 */

int* OneWire_ReadROM(void);
void OneWire_MatchROM (int8* aId);
void OneWire_SkipROM (void);
int* OneWire_SearchROM (void);
int  OneWire_CuentaDispositivos();
int OneWire_CRC ( int crc, int nData );

/** @} */ // end of group3

/** @defgroup group4 Funciones de uso interno
 *  @brief Conjunto de rutinas de uso interno 
 *  @{
 */

void _OneWire_LimpiaMapaColisiones ( int nPosBit, int* HBit );
int1 _OneWire_LeeBitColision ( int nPosBit, int* HBit );
void _OneWire_SetBitColision ( int nPosBit, int* HBit );
void _OneWire_IniciaMapaColisiones (int* HBit);

/** @} */ // end of group4

/** @} */ // end of group1

#include "jsb_1wire.c"


#endif
