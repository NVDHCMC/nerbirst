#ifndef DEFINITIONS_H
#define DEFINITIONS_H

enum TypeID
{
	GET_NEIGHBORS = 1,
	GET_INFO,
	PING,
	REQ_WATER_PUMP_ON,
	REQ_WATER_PUMP_OFF,
	REQ_LIGHT_ON,
	REQ_LIGHT_OFF,
	GET_TEMPERATURE,
	GET_LIGHT_INTENSITY,
	GET_HUMIDITY_DATA,
	GET_AIR_HUMIDITY_DATA,
	TYPE_COUNT
};

#ifndef BIG_ENDIAN

#define REQUEST 		(uint16_t) 0x01
#define REQ_SUCCESS 	(uint16_t) 0x02
#define REQ_ERROR 		(uint16_t) 0x03
#define REQ_WARNING 	(uint16_t) 0x04

#else

#define REQUEST 		__bswap_16((uint16_t) 0x01)
#define REQ_SUCCESS 	__bswap_16((uint16_t) 0x02)
#define REQ_ERROR 		__bswap_16((uint16_t) 0x03)
#define REQ_WARNING 	__bswap_16((uint16_t) 0x04)

#endif

#endif // DEFINITIONS_H
