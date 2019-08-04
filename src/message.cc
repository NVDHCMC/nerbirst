#include <iostream>
#include <byteswap.h>

#include "message.h"
#include "definitions.h"
#include "bbb_control/gpio.h"

#define MAX_LENGTH 1024

#define WATER_PIN   34
#define LIGHT_PIN   35
#define SPEAKER_PIN 38

char buf[MAX_LENGTH];
gateway_payload* payload;

int gateway_payload_send_to_zigbee()
{
    // send payload to zigbee

}

char* gateway_payload_reply()
{
    return buf;
}

int gateway_payload_parse(char* content)
{
    int ret_val = 0;
    unsigned int len = content[2] << 8 | content[3];

    if (len <= MAX_LENGTH)
    {
        memcpy(buf, content, len);
        std::cout << "Type ID: " << __bswap_16(payload->type_id) << std::endl;
        if (__bswap_16(payload->type_id) < TYPE_COUNT)
        {
            switch (__bswap_16(payload->type_id))
            {
            case (GET_NEIGHBORS):
            {
                // Send to zigbee
                break;
            }
            case (GET_INFO):
            {
                // Craft reply
                ret_val = 0;
                break;
            }
            case (PING):
            {
                // ping
                ret_val = 0;
                break;
            }
            case (REQ_WATER_PUMP_ON):
            {
                // water
                std::cout << "Turn pump on" << std::endl;
                ret_val = bbb_gpio_set_value(WATER_PIN, GPIO_SET_HIGH);
                std::cout << "RETVAL: " << ret_val << std::endl;
                if (ret_val == 0)
                {
                    payload->opt = REQ_SUCCESS;
                }
                else
                {
                    payload->opt = REQ_ERROR;
                }
                break;
            }
            case (REQ_WATER_PUMP_OFF):
            {
                ret_val = bbb_gpio_set_value(WATER_PIN, GPIO_SET_LOW);
                if (ret_val == 0)
                {
                    payload->opt = REQ_SUCCESS;
                }
                else
                {
                    payload->opt = REQ_ERROR;
                }
                break;
            }
            }
        }
        else
        {
            ret_val = -1;
        }
    }
    else
    {
        ret_val = -1;
    }

    return ret_val;
}

unsigned int gateway_payload_get_len()
{
    return payload->total_length;
}

int gateway_init()
{
    int ret_val = 0;
    ret_val = bbb_gpio_set_output(WATER_PIN) == -1 ? -1 : 0;
    ret_val = bbb_gpio_set_output(LIGHT_PIN) == -1 ? -1 : 0;
    ret_val = bbb_gpio_set_output(SPEAKER_PIN) == -1 ? -1 : 0;
    payload = (gateway_payload*) buf;
    return ret_val;
}