/**
******************************************************
* @file JSB_1Wire.c
* @brief Conjunto de funciones del protocolo 1 Wire
* @author Oscar Salas Mestres & Julian Salas Bartolome
* @version 1.0
* @date Agosto 2012
*
*
*******************************************************/



/**
******************************************************
* @brief Resetea el bus 1 Wire
* @return Devuelve 0 si hay algun dispositivo conectado, 1 en caso contrario
*
* Ejemplo:
*
*	int lEstado = 0;
*
*	lEstado = OneWire_Reset();
*
* Resultado:
*
*	lEstado = 0
*
* @see OneWire_Write(), OneWire_Write_1(), OneWire_Write_0(), OneWire_LeeBit()  
*/
int1 OneWire_Reset (void)
{
	//-------------------------------------------------------------   
   	//Definicion de variables
   	//-------------------------------------------------------------   
   	int lEstadoPin1W;                                       
   	//-------------------------------------------------------------   
   	output_low (Pin1W);													//Ponemos la salida a 0 durante 480 us
   	delay_us (480);
   	output_float (Pin1W);												//Nos ponemos en modo entrada y esperamos 60 us para que se estabilicen los esclavos
   	delay_us(60);
   	lEstadoPin1W = input (Pin1W);										//A los 60 us, leemos el bus
   	delay_us(240);	
   	return (lEstadoPin1W);												//Retornamos el estado del bus  1, si no había esclavo y 0 si había esclavo                                  
}
/**
******************************************************
* @brief Envia un bit por el bus 1 Wire
*
* @param lBit Bit a transmitir
*
* Ejemplo:
*
*	int1 lBit;
*	lBit=0;
*	OneWire_Write( lBit );
*
* Resultado:
*
*	Envia 0 por el bus 1 Wire
*
* @see OneWire_Reset(), OneWire_Write_1(), OneWire_Write_0(), OneWire_LeeBit()   
*/
void OneWire_Write  (int1 lBit)
{
	if ( lBit )
	{
		output_low (Pin1W);													//Ponemos durante 10 us el bus a 0 para indicar que se inicia un bit
		delay_us (10);
		output_high (Pin1W);												//Ponemos el bus a 1 durante 70 us
		delay_us(70);
		output_float (Pin1W);												//Dejamos el bus en alta impedancia
		delay_us(2);
	}else{
		output_low (Pin1W);													//Ponemos durante 10 us el bus a 0 para indicar que se inicia un bit
		delay_us (10);
		output_low (Pin1W);													//Ponemos el bus a 0 durante 70 us
		delay_us(70);
		output_float (Pin1W);												//Dejamos el bus en alta impedancia
		delay_us(2);
	}
}
/**
******************************************************
* @brief Envia un 1 por el bus 1 Wire
*
* Ejemplo:
*
*	OneWire_Write_1();
*
* Resultado:
*
*	Envia 1 por el bus 1 Wire
*
* @see OneWire_Reset(), OneWire_Write(), OneWire_Write_0(), OneWire_LeeBit()   
*/
void OneWire_Write_1 (void)
{
	output_low (Pin1W);													//Ponemos durante 10 us el bus a 0 para indicar que se inicia un bit
	delay_us (10);
	output_high (Pin1W);												//Ponemos el bus a 1 durante 70 us
	delay_us(70);
	output_float (Pin1W);												//Dejamos el bus en alta impedancia
	delay_us(2);
}
/**
******************************************************
* @brief Envia un 0 por el bus 1 Wire
*
* Ejemplo:
*
*	OneWire_Write_0();
*
* Resultado:
*
*	Envia 0 por el bus 1 Wire
*
* @see OneWire_Reset(), OneWire_Write_1(), OneWire_Write(), OneWire_LeeBit()   
*/
void OneWire_Write_0 (void)
{
	output_low (Pin1W);													//Ponemos durante 10 us el bus a 0 para indicar que se inicia un bit
	delay_us (10);
	output_low (Pin1W);													//Ponemos el bus a 0 durante 70 us
	delay_us(70);
	output_float (Pin1W);												//Dejamos el bus en alta impedancia
	delay_us(2);
}
/**
******************************************************
* @brief Lee un bit recibido por el bus 1 Wire
*
* @return Retorna el bit leido en el Bus
*
* Ejemplo:
*
*	int1 lBit = OneWire_Write_0();
*
* Resultado:
*
*	Recibe en lBit el bit enviado por un esclavo al bus 1 Wire --> lBit=1
*
* @see OneWire_Reset(), OneWire_Write_1(), OneWire_Write_0(), OneWire_Write()  
*/
int1 OneWire_LeeBit (void)
{
	int1 lBitLeido;
	output_low (Pin1W);													//Ponemos el bus a 0 durante 2 us para indicar al escalvo que puede poner el bit que quiere transmitir
	delay_us(2);
   	output_float (Pin1W);												//Dejamos al bus en escucha durante 15 us para que el escalvo estabilice su salida
   	delay_us(15);
	lBitLeido=input(Pin1W);												//Leemos el bus 
	delay_us(50);														//Temporizamos 50 us para leer el siguiente bit

	return lBitLeido;													//Devolvemos el bit leido	
}
/**
******************************************************
* @brief Envia un byte el bus 1 Wire
*
* @param cDato Byte a transmitir
*
* Funciones utilizadas
*	- OneWire_Write_1()
*	- OneWire_Write_0()
*
* Ejemplo:
*
*	byte cDato = 32;
*	OneWire_SendByte (cDato);
*
* Resultado:
*
*	Envia el Byte 32 por el bus 1 Wire
*
* @see OneWire_ReceiveByte()
*/
void OneWire_SendByte(byte cDato)
{
	//-------------------------------------------------------------   
	//Definicion de variables
	//-------------------------------------------------------------   
	int nBit;
	//-------------------------------------------------------------   

	for ( nBit = 0; nBit < 8; nBit++ )					 				//Escribimos 8 bits empezando por el de menor peso		
	{
		if ( cDato & (1<<nBit) )										//Si el bit a transmitir es 1
		{
			OneWire_Write_1();											//Transmitimos 1
		}else{															//En caso contrario
			OneWire_Write_0();											//Transmitimos 0
		}
	}
	output_float (Pin1W);												//Dejamos al bus en alta impedancia

}
/**
******************************************************
* @brief  recibe 1 byte el bus 1 Wire
*
* @return Retorna el Byte recibido por el bus
*
* Ejemplo:
*
*	byte cDato;
*	cDato = OneWire_ReceiveByte ();
*
* Resultado:
*
*	cDato = 28
*
* @see OneWire_SendByte()
*/
byte OneWire_ReceiveByte()
{
	//-------------------------------------------------------------   
	//Definicion de variables
	//-------------------------------------------------------------   
	int nBit;
	byte bDato=0;
	//-------------------------------------------------------------   
	
	for ( nBit = 0; nBit < 8; nBit++ )									//Vamos a leer 8 bits
	{
		output_low (Pin1W);												//Ponemos el bus a 0 durante 2 us para indicar al escalvo que puede poner el bit que quiere transmitir
		delay_us(2);
   		output_float (Pin1W);											//Dejamos al bus en escucha durante 15 us para que el escalvo estabilice su salida
   		delay_us(15);
		shift_right(&bDato,1,input(Pin1W));								//Lo añadimos al byte que con 
   		delay_us(50);													//Temporizamos 50 us para leer el siguiente bit
	}
	return (bDato);														//Retornamos el byte leido
}
/**
******************************************************
* @brief Lee la memoria ROM con el Id del dispositivo 1 Wire 
*
* Esta funcion solo se puede usar cuando hay un unico dispositivo en el bus
*
* @post  Debe liberarse la memoria con free
* @return Devuelve el puntero a un array de 8 elementos con el contenido de la ROM
*
* La estructura de la ROM es la siguiente:
*	
*	00      -> Tipo dispositivo ( 10 para el DS1820,.... )
*	01 a 06 -> 48 bit del Id del dispositivo ( unico pra cada chip )     
*	07      -> CRC
*
*
* Ejemplo:
*
*
*	int8 aId[8]
*
*	aId = OneWire_ReadROM();
*
* Resultado:
*
*	aId -> 10 30 C5 C8 00 00 00 C3
*
*
* @see OneWire_MatchROM(), OneWire_SkipROM (), OneWire_SearchROM ()
*/
int* OneWire_ReadROM(void)
{
	//-------------------------------------------------------------	
	//Definicion de variables
	//-------------------------------------------------------------	
	int8 nByte;
	char *aRomId = malloc(8);											//Reservamos 8 bytes para almacenar la informacion de la ROM
	//-------------------------------------------------------------		

	if (!OneWire_Reset ())
	{
		OneWire_SendByte(0x33);											//Mandamos el Byte 33 para que el dispositivo nos envie el contenido de la ROM
		for (nByte=0;nByte<8;nByte++)									//Leemos los 8 Bytes del dispositivo y los almacenamos en el array declarado
		{
			aRomId[nByte]= OneWire_ReceiveByte();
		}
	}

	return aRomId;														//Retrnamos l puntero al array con la informacion solicitada
}
/**
******************************************************
* @brief Direcciona un dispositivo del Bus
*
* El Dispositivo que contenga el Id enviado esperara la siguiente instruccion, el resto de los esclavos esperaran un pulso reset
*
* @param aId Puntero al array con los 8 bytes de Id correspondientes al dispositivo a direccionar
*
* Ejemplo:
*
*	int aId = {0x10,0x30,0xC5,0xC8,0x00,0x00,0xC3};
*
*	OneWire_MatchROM ( aId );
*
* Resultado:
*
*	Envia por el Bus la dirección del dispositivo aId
*
* @see OneWire_ReadROM(), OneWire_SkipROM (), OneWire_SearchROM () 
*/
void OneWire_MatchROM (int8* aId)
{
	//-------------------------------------------------------------	
	//Definicion de variables
	//-------------------------------------------------------------	
	int8 nByte;
	//-------------------------------------------------------------	

	if (!OneWire_Reset ())
	{
		OneWire_SendByte(0X55);
		for (nByte=0;nByte<8;nByte++)
		{
			OneWire_SendByte(aId[nByte]);
		}
	}
}
/**
******************************************************
* @brief Direcciona de forma directa un dispositivo del Bus
*
* Esta funcion permite direccionar un dispositivo de forma directa sin enviar la identificacion
*
* Solo debe utilizarse cuando existe un unico esclavo en el Bus
*
* Ejemplo:
*
*	OneWire_SkipROM ( );
*
* Resultado:
*
*	Envia por el Bus la dirección 0xCC para direccionar el unico dispositivo esclavo conectado al Bus 
*
* @see OneWire_ReadROM(), OneWire_MatchROM(), OneWire_SearchROM () 
*/
void OneWire_SkipROM ()
{

	if (!OneWire_Reset ())
	{
		OneWire_SendByte(0XCC);
	}
}
/**
******************************************************
* @brief Permite leer los 64 bits de identificacion de todos los esclavos conectados al Bus
*
* @post Es necesario liberar memoria con free()
*
* @return Devuelve un puntero a un array con todos los Id's de los distintos esclavos
* 
* Por cada esclavo se almacenan 8 Bytes con la siguiente estructura
*	
*	00      -> Tipo dispositivo ( 10 para el DS1820,.... )
*	01 a 06 -> 48 bit del Id del dispositivo ( unico pra cada chip )     
*	07      -> CRC
*
* Cada una de estas secuencas de 8 Bytes es la que se utiliza en el MatchROM para direccionar un dispositivo unico
*
* Funciones internas utilizadas
*	- _OneWire_IniciaMapaColisiones()
*	- _OneWire_SetBitColision()
*	- _OneWire_LeeBitColision()
*	- _OneWire_LimpiaMapaColisiones()

*
* Ejemplo:
*
*	int* aId;
*
*	aId = OneWire_SearchROM ();
*	.
*	.
*	.
*	free (aId);
*
*
* Resultado:
*
*	Se alamacena en aId todas las direcciones de los esclavos
*
* @see OneWire_ReadROM(), OneWire_MatchROM(), OneWire_SkipROM() 
*/
int* OneWire_SearchROM (void)
{
	//Esta funcion es compleja y es necesario interpretar la informacion de las especificaciones del protocolo para poder entnederla
	//Cuando se envia el comando 0XF0 todos los escalvos responden con el primer bit de su Id y el siguiente bit que envian es el complemento de ese bit.
	//Si todos tienen el primer bit igual, el complemento que se leera será lo contario del inicial ( Ej, si el primer bit es un 1 para todos, el complemento es 0 )
	//El maestro responde con el mismo bit y todos los esclavos pasan a enviar el siguiente bit
	//Si algun esclavo tiene el bit distinto al resto, en el bit principal se recibira un 0 y en el complemento tambien se recibira 0
	//En ese caso lo tratamos como una colision
	//Enviamos primero un 0 con lo que solo responderan al siguiente bit todos los que tengan ese 0, los que tengan 1 se quedan a la espera de un reset
	//pero tenemos que tener en cuenta que en la siguiente vuelta tenemos qu eponer un 1
	//En la funcion, recorremos todo el id y primero tartamos la colision mas lejana y vamos recorriendo los id hacia el primer bit. 
	//-------------------------------------------------------------	
	//Definicion de variables
	//-------------------------------------------------------------	
	int8 aMapaColisiones[8];
	int1 lBitLeido, lBitComplemento, lColision, lBusqueda;
	int8 nPosBit, nBitColisionActual, nBitColisionAnterior;
	int8 nByte, nBit, nDispositivo, nDispTmp, nColisiones ;
	byte Pruebal;
	int8 *aRomId = malloc(8);						//Reservamos 8 bytes para almacenar la informacion de la ROM
	//-------------------------------------------------------------		
	_OneWire_IniciaMapaColisiones (aMapaColisiones);
	nDispositivo=0;

	if (!OneWire_Reset ())
	{

		Pruebal=0;
		nBitColisionActual=0;
		lBusqueda=1;
		nDispTmp=1;
		nColisiones=0;

		while (lBusqueda)
		{
			Pruebal=0;
			lColision=0;
			OneWire_Reset ();
			nPosBit = 0;
			OneWire_SendByte(0XF0);
			nBitColisionAnterior=0;
			nBitColisionActual=0;
			for (nByte=0;nByte<8;nByte++)
			{
				for (nBit=0;nBit<8;nBit++)
				{
					lBitLeido=OneWire_LeeBit();														//Recibimos bit principal 
					lBitComplemento=OneWire_LeeBit();												//Recibimos bit complemento
					if ( lBitLeido == 0  & lBitComplemento == 0 )									//Si el Bit principal y su complemento son iguales, hay coision
					{
						lBitLeido = _OneWire_LeeBitColision ( nPosBit, aMapaColisiones );			//Leemos del mapa de colisiones el bit que tenemos que enviar ( al principio es 0 )
						nBitColisionAnterior=nBitColisionActual;									//En nBitCilisionAnterior nos quedara la posicion de la penultima colision									
						nBitColisionActual=nPosBit;													//En nBitColisionActual nos quedara la ultima colision 
						if ( lBitLeido )															//Si el bit a enviar es 1, hemos terminado con esta colision y debemos tratar
						{																			//la anterio	
							nBitColisionActual = nBitColisionAnterior;								//por lo que ponemos en colision actual la anteior ya que hemso llegado al final de la actual
						}
					}
					OneWire_Write  ( lBitLeido );													//Escribimos en el bus el bit leido del bus o del mapa de colisiones segun corresponda
					shift_right(&Pruebal,1,lBitLeido);												//Grabamos ese bit en el byte del id correspondiente al dispositivo actual
					nPosBit++;	
				}
				aRomId[nByte+(nDispositivo*8)]=Pruebal;												//Cuando hemos recorrido un paquete de 8 bits, almacenamos en aRomId el Byte leido
			} 
			if ( nBitColisionActual == 0 & nBitcolisionAnterior == 0)
			{
				lBusqueda=0;
			}else{

				nDispositivo++;
   				aRomId = realloc (aRomId, (nDispositivo+1)*8);										//Cuando hemos obtenido los 8 Bytes, 
				_OneWire_SetBitColision (nBitColisionActual, aMapaColisiones);						//Grabamos 1 en el bit de colision que si hemos enviado el 0, estara en la ultima colision
																									//Pero si era un 1 , esa colision se ha finalizado y pasamos a la colision anterior
				_OneWire_LimpiaMapaColisiones (nBitColisionActual, aMapaColisiones);					//Borramos el mapa da colisiones delde el bit que hemos marcado como 1 pra poder buscar colisiones
			}																						//en esta nueva rama
		}
	}
			delay_ms(10);
			return aRomId;

}
/**
******************************************************
* @brief Permite leer los 64 bits de identificacion de todos los esclavos conectados al Bus
*
* @post Es necesario liberar memoria con free()
*
* @return Devuelve un puntero a un array con todos los Id's de los distintos esclavos
* 
* Por cada esclavo se almacenan 8 Bytes con la siguiente estructura
*	
*	00      -> Tipo dispositivo ( 10 para el DS1820,.... )
*	01 a 06 -> 48 bit del Id del dispositivo ( unico pra cada chip )     
*	07      -> CRC
*
* Cada una de estas secuencas de 8 Bytes es la que se utiliza en el MatchROM para direccionar un dispositivo unico
*
* Funciones internas utilizadas
*	- _OneWire_IniciaMapaColisiones()
*	- _OneWire_SetBitColision()
*	- _OneWire_LeeBitColision()
*	- _OneWire_LimpiaMapaColisiones()

*
* Ejemplo:
*
*	int* aId;
*
*	aId = OneWire_SearchROM ();
*	.
*	.
*	.
*	free (aId);
*
*
* Resultado:
*
*	Se alamacena en aId todas las direcciones de los esclavos
*
* @see OneWire_ReadROM(), OneWire_MatchROM(), OneWire_SkipROM() 
*/
int* OneWire_CuentaDispositivos(void)
{
	//Esta funcion es similar a OneWire_SearchROM, la filosofia es la misma pero solo devuelve el Numero de Dispositivos
	//-------------------------------------------------------------	
	//Definicion de variables
	//-------------------------------------------------------------	
	int8 aMapaColisiones[8];
	int1 lBitLeido, lBitComplemento, lColision, lBusqueda;
	int8 nPosBit, nBitColisionActual, nBitColisionAnterior;
	int8 nByte, nBit, nDispositivo, nDispTmp, nColisiones ;
	_OneWire_IniciaMapaColisiones (aMapaColisiones);

	if (!OneWire_Reset ())
	{

		nDispositivo=1;

		nBitColisionActual=0;
		lBusqueda=1;
		nDispTmp=1;
		nColisiones=0;
		while (lBusqueda)
		{
			lColision=0;
			OneWire_Reset ();
			nPosBit = 0;
			OneWire_SendByte(0XF0);
			nBitColisionAnterior=0;
			nBitColisionActual=0;
			for (nByte=0;nByte<8;nByte++)
			{
				for (nBit=0;nBit<8;nBit++)
				{
					lBitLeido=OneWire_LeeBit();														//Recibimos bit principal 
					lBitComplemento=OneWire_LeeBit();												//Recibimos bit complemento
					if ( lBitLeido == 0  & lBitComplemento == 0 )							//Si el Bit principal y su complemento son iguales, hay coision
					{
						lBitLeido = _OneWire_LeeBitColision ( nPosBit, aMapaColisiones );	//Leemos del mapa de colisiones el bit que tenemos que enviar ( al principio es 0 )
						nBitColisionAnterior=nBitColisionActual;							//En nBitCilisionAnterior nos quedara la posicion de la penultima colision									
						nBitColisionActual=nPosBit;											//En nBitColisionActual nos quedara la ultima colision 
						if ( lBitLeido )													//Si el bit a enviar es 1, hemos terminado con esta colision y debemos tratar
						{																	//la anterio	
							nBitColisionActual = nBitColisionAnterior;						//por lo que ponemos en colision actual la anteior ya que hemso llegado al final de la actual
						}
					}
					OneWire_Write  ( lBitLeido );											//Escribimos en el bus el bit leido del bus o del mapa de colisiones segun corresponda
					nPosBit++;	
				}
			} 
			if ( nBitColisionActual == 0 & nBitcolisionAnterior == 0)
			{
				lBusqueda=0;
			}else{

				nDispositivo++;
				_OneWire_SetBitColision (nBitColisionActual, aMapaColisiones);					//Grabamos 1 en el bit de colision que si hemos enviado el 0, estara en la ultima colision
																							//Pero si era un 1 , esa colision se ha finalizado y pasamos a la colision anterior
				_OneWire_LimpiaMapaColisiones (nBitColisionActual, aMapaColisiones);				//Borramos el mapa da colisiones delde el bit que hemos marcado como 1 pra poder buscar colisiones
			}																				//en esta nueva rama
		}
	}
			delay_ms(10);
			return nDispositivo;

}
/**
******************************************************
* @brief Funcion utilizada para el calculo del CRC 1 Wire
*
* @param crc Este Byte es el dato del calculo del CRC con el byte anterior, inicialmente debe ser 0
* @param nData Nuevo Byte de la cadena para el calculo del CRC 
*
*
* Ejemplo:
*
*	int cDirDS1820[] = {16, 192, 196, 197, 198, 0, 0 };
*	int nCRC = 0;
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[0] );
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[1] );
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[2] );
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[3] );
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[4] );
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[5] );
*	nCRC = OneWire_CRC ( nCRC, cDirDS1820[6] );
*
* Resultado:
*
*	nCRC = 99
*/
int OneWire_CRC ( int crc, int nData )
{

	int nBit = 0;

	crc ^= nData;
	for ( nBit = 0; nBit < 8; nBit++ )
	{
		if (crc & 0x01)
		{
	    	crc = (crc >> 1) ^ 0x8C;
		}else{
	        crc >>= 1;			
		}
	    
	}
	return crc;
}
/**
******************************************************
* @brief Inicializa el array del Mapa de Colisiones
*
* Funcion interna. 
*
* Pone a 0 todos los bits del mapa de colisiones
*	
* @param HBIt Array con los 64 bits del Mapa de Colisiones ( 8 Bytes )
*
* Ejemplo:
*
*		int8 aMapaColisiones[8];
*
*		_OneWire_IniciaMapaColisiones (aMapaColisiones);
*	.
*
* Resultado:
*
*	Pone a 0 todos los bits de aMapaColisiones
*
*
* @see _OneWire_SetBitColision(), _OneWire_LeeBitColision, _OneWire_LimpiaMapaColisiones()
*/
void _OneWire_IniciaMapaColisiones (int* HBit)
{
	int8 nBitLoop, nByteLoop;
	for ( nByteLoop = 0; nByteLoop < 8; nByteLoop++ )
	{
		for ( nBitLoop = 0; nBitLoop < 8; nBitLoop++)
		{
			bit_clear (HBit[nByteLoop], nBitLoop);
		}
	}
}
/**
******************************************************
* @brief Limpia el array del Mapa de Colisiones a partir de un determinado Bit
*
* Funcion interna. 
*
* Cuando se detecta una posicion de bit con colision, se ponen a 0 todos los bits posteriores
* a la posicion con colision para iniciar una nueva rama
*
* @param nPosBit Posicion de bit desde donde se quiere limpiar	
* @param HBIt Array con los 64 bits del Mapa de Colisiones ( 8 Bytes )
*
* Ejemplo:
*
*		int8 aMapaColisiones[8];
*
*		_OneWire_LimpiaMapaColisiones ( 45, aMapaColisiones);
*	.
*
* Resultado:
*
*	Pone a 0 todos los bits siguientes a la posicion 45
*
*
* @see _OneWire_SetBitColision(), _OneWire_LeeBitColision(), _OneWire_IniciaMapaColisiones()
*/

void _OneWire_LimpiaMapaColisiones ( int nPosBit, int* HBit )
{
	int8 nBit, nByte;
	int8 nBitLoop, nByteLoop;
	nPosBit++;
	nByte = nPosBit/8;
	nBit = nPosbit-(nByte*8);
	for ( nByteLoop = nByte; nByteLoop < 8; nByteLoop++ )
	{
		for ( nBitLoop = nBit; nBitLoop < 8; nBitLoop++)
		{
			bit_clear (HBit[nByteLoop], nBitLoop);
		}
		nBit=0;
	}

}

/**
******************************************************
* @brief Lee un bit del mapa de colisiones
*
* Funcion interna. 
*
* @param nPosBit Posicion del bit que se quiere leer
* @param HBIt Array con los 64 bits del Mapa de Colisiones ( 8 Bytes )
*
* Ejemplo:
*
*		int8 aMapaColisiones[8];
*		int1 lBit;
*
*		lBit=_OneWire_LeeBitColision (45, aMapaColisiones);
*	.
*
* Resultado:
*
*	lBit = 1
*
*
* @see _OneWire_SetBitColision(), _OneWire_LimpiaMapaColisiones(), _OneWire_IniciaMapaColisiones()
*/

int1 _OneWire_LeeBitColision ( int nPosBit, int* HBit )
{
	int8 nBit, nByte;
	nByte = nPosBit/8;
	nBit = nPosbit-(nByte*8);
	return bit_test (HBit[nByte], nBit);	
}
/**
******************************************************
* @brief Pone a 1 un bit en el mapa de colisiones
*
* Funcion interna. 
*
* @param nPosBit Posicion del bit que se quiere poner a 1
* @param HBIt Array con los 64 bits del Mapa de Colisiones ( 8 Bytes )
*
* Ejemplo:
*
*		int8 aMapaColisiones[8];
*
*		_OneWire_SetBitColision (45, aMapaColisiones);
*	.
*
* Resultado:
*
*	Pone a 1 el bit 45 dentro del mapa de colisines ( 64 Bit )
*
*
* @see _OneWire_LeeBitColision(), _OneWire_LimpiaMapaColisiones(), _OneWire_IniciaMapaColisiones()
*/
void _OneWire_SetBitColision ( int nPosBit, int* HBit )
{
	//-------------------------------------------------------------	
	//Definicion de variables
	//-------------------------------------------------------------	
	int8 nBit, nByte;
	//-------------------------------------------------------------	

	nByte = nPosBit/8;
	nBit = nPosbit-(nByte*8);
	bit_set (HBit[nByte], nBit);
	return;
}
