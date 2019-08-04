#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef union {
	struct
	{
		uint8_t version;
		uint8_t header_length;
		uint16_t total_length;
		uint16_t type_id;
		uint16_t mess_id;
		uint16_t opt;
		char source_uuid[36];
		char dest_uuid[36];
		char data[942];
	};
	char buffer[1024];
} gateway_payload;

int gateway_init();
int gateway_payload_parse(char *content);
unsigned int gateway_payload_get_len();
char* gateway_payload_reply();


#endif
