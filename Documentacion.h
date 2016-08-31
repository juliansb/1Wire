/**
******************************************************
* @file Documentacion.h
* @brief Conjunto de funciones para control y gestion del bus 1Wire
* @author Julian Salas Bartolome
* @version 1.0
* @date Agosto 2012
*
*
*******************************************************/




/**
 * \mainpage Bus 1Wire
 *
 * \section introduccion_seccion Introduccion
 *
 * Estas funciones se han diseñado para gestionar un bus 1Wire mediante un PIC
 *  
 * Aunque este paquete de funciones es ampliamente utilizado en los proyectos editados, se puede ver \ref Ejemplo1Wire.c 
 * para mas detalles de como usarlas  
 *
 * \section Seccion_Protocolo Protocolo 1Wire
 *
 * Este apartado no pretende explicar de forma detallada el protocolo 1Wire, para eso existen muchos documentos especializados, tan
 * solo se pretende hacer una breve introducción a la forma de funcionamiento del bus.
 *
 * El bus 1Wire permite la comunicación asincrona ente 1 maestro y 1 o varios esclavos mediante un hilo de datos mas 1 o 2 de alimentación
 *  
 * La transmisión de cada dispositivo puede ser bidireccional si bien solo se puede hacer en una dirección simultanea.
 * 
 * Los esclavos tienen la posibilidad de ser alimentados rectificando la tensión del propio bus por lo que en caso de usar esa facilidad
 * solo se emplearian dos hilos ( datos + masa ) para una comunicacion entre maestro y esclavo.
 *
 * Cada esclavo dispone de un identificador único ( id ) para poder ser identificado en el bus. El identificador consta de 8 bytes
 * con la siguiente estructura:
 *
 *	00      -> Tipo dispositivo ( 10 para el DS1820,.... )
 *	01 a 06 -> 48 bit del Id del dispositivo ( unico pra cada chip )     
 *	07      -> CRC
 *
 * El maestro se dirigirá a un esclavo del bus mediante ese identificador y, mediante los comandos adecuados, ordenara actuar al 
 * esclavo y le solictará la información que precise el maestro
 * 
 * \subsection SubSeccion_Inicio 1.- Inicio del bus
 * 
 * Para iniciar el bus, el maestro pone a nivel bajo el hilo de datos durante 480 us para dejarlo despuesen estado de alta impedancia. A
 * los 60 us ( como maximo ), los escalvos deben responder poniendo el bus a nivel bajo por lo que transcurrido ese tiempo, el maestro lee 
 * el estado del bus y, si esta a nivel bajo es que hay al menos un esclavo conectado al bus.
 * 
 * \subsection SubSeccion_Transferencia 2. Transferencia de datos
 * 
 * Como se ha comentado anteriormente, la transfernecia de información es bidireccional pero solo se permite una dirección y un dispositivo
 * de forma simultanea. El maestro es el arbitro del bus y se encargara de asignar los instantes en los que cada dispositivo debe
 * poner información en el bus.
 *
 * 
 * \subsection SubSeccion_Transmision 2.1.-Transmision Maestro->Esclavo
 * 
 * Para transmitir un bit, el maestro pone el hilo de datos a nivel bajo durante 10 us, posteriormente, durante 70 us pone el hilo
 * a 1 o 0 en función del bit que se quiera transmitir y transcurrido ese tiempo, se deja el hilo en estado de alta impedancia durante
 * 2 us como mínimo.
 * 
 * Evidentmente, para transmitir un byte se enviará bit a bit empezando por el bit menos significativo
 *
 * \subsection SubSeccion_Recepcion 2.2.- Transmision Esclavo->Maestro
 *
 * Como se dijo anteriormente, el maestro es el abitro del bus, el que indicara quien debe leer y quien y cuando debe escribir
 * 
 * Para que un esclavo pueda escribir en el bus, en primer lugar el maestro le debe autorizar, una vez auorizado, la secuenca se inicia 
 * cuando el maestro pone el hilo de datos a nivel bajo durante 2 us para inmediatament pasar a estado de alta impedancia durante 15 us 
 * que es el tiempo maximo que el esclavo tardará en poner el bit en el hilo de datos, transcurrido ese tiempo el maestro lee el dato 
 * que el esclavo ha puesto en el bus
 *
 * Cuando el maestro solicite un byte al esclaco, este proceso se realizará bit a bit empezando por el menos significativo
 *
 * \subsection Comandos 2.3.-Comandos genéricos
 *
 *  Además de los comandos particulares de cada dispositivo, esxiste un grupo de comandos comunes a todos que se pueden considerar
 *  parte del protocolo
 *
 *
 * \subsection Comandos_1 2.3.1.- Read ROM
 *
 * Este comando ordena al esclavo que mande al bus su Id. Este comando solo se podra utilizar cuando haya un solo esclavo.
 *
 * \subsection Comandos_2 2.3.2.- Match ROM
 *
 * Mediante este comando el maestro direcciona un esclavo. Cuando el maestro envia el Id, el esclavo que coincida con la identificación
 * espera una orden del maestro, el resto se queda de ser identificados
 *
 * \subsection Comandos_3 2.3.3.- Skip ROM
 *
 * Este comando sirve para direccionar de forma directa un esclavo sin necesidad de enviar el Id. Evidentemente solo se puede
 * utilizar si hay un solo esclavo.
 *
 * \subsection Comandos_4 2.3.4.- Search ROM
 *
 * Con este comando, el maestro pide a todos los esclavos que se identifiquen. Mediante un proceso complejo, el maestro obtiene
 * los Id's de todos los esclavos conectados al bus
 *
 *
 */








/** 
 *
 * En este ejemplo se puede observar 
*/
/** \example Ejemplo1Wire.c 
 * @brief Ejemplo 1.- Ejemplo uso del bus 1Wire
 */

