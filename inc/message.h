#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdlib.h>
#include <string.h>

typedef struct
{
	char version;
	char header_length;
	unsigned int total_length;
	unsigned int type_id;
	unsigned int mess_id;
	unsigned int opt;
	char source_uuid[36];
	char dest_uuid[36];
	char data[942];
} gateway_payload;

int gateway_init();
int gateway_payload_parse(char *content);
unsigned int gateway_payload_get_len();
char* gateway_payload_reply();


#endif
