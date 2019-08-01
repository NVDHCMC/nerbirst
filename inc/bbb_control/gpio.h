#ifndef BBB_GPIO_H
#define BBB_GPIO_H

#include <stdio.h>
#include <stdlib.h>

#define GPIO_DIR_IN     0
#define GPIO_DIR_OUT    1

#define GPIO_SET_HIGH   1
#define GPIO_SET_LOW    0

int bbb_gpio_set_export(int pin)
{
    int ret_val = 0;
    FILE *fd;
    fd = fopen("/sys/class/gpio/export", "w");
    if (fd < 0)
    {
        ret_val = -1;
    }
    fseek(fd, 0, SEEK_SET);
    if (ret_val == 0)
    {
        fprintf(fd, "%d", pin);
    }
    fflush(fd);
    fclose(fd);

    return ret_val;
}

int bbb_gpio_set_direction(int pin, int dir)
{
    int ret_val = 0;
    FILE *fd;
    char path[255];
    sprintf(path, "/sys/class/gpio/gpio%d/direction", pin);
    fd = fopen(path, "w");
    if (fd < 0)
    {
        ret_val = -1;
    }
    fseek(fd, 0, SEEK_SET);
    if (ret_val == 0)
    {
        if (dir == GPIO_DIR_IN) 
        {
            fprintf(fd, "in");
        }
        else if (dir == GPIO_DIR_OUT)
        {
            fprintf(fd, "out");
        }
    }
    fflush(fd);
    fclose(fd);
    return ret_val;
}

int bbb_gpio_set_input(int pin)
{
    if (bbb_gpio_set_export(pin))
    {
        return bbb_gpio_set_direction(pin, GPIO_DIR_IN);
    }
    
    return -1;
}

int bbb_gpio_set_output(int pin)
{
    if (bbb_gpio_set_export(pin))
    {
        return bbb_gpio_set_direction(pin, GPIO_DIR_OUT);
    }
    
    return -1;
}

int bbb_gpio_get_value(int pin)
{
    int ret_val = -1;
    FILE *fd;
    char path[255];
    sprintf(path, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(path, "r");
    fseek(fd, 0, SEEK_SET);

    char val[1];
    if (fread(val, 1, 1, fd))
    {
        fflush(fd);
        fclose(fd);
        return atoi(val);
    }
    else
    {
        fflush(fd);
        fclose(fd);
        return -1;
    }
}

int bbb_gpio_set_value(int pin, int value)
{
    int ret_val = 0;
    FILE *fd;
    char path[255];
    sprintf(path, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(path, "w");
    fseek(fd, 0, SEEK_SET);

    if (value == GPIO_SET_HIGH)
    {
        fprintf(fd, "%d", GPIO_SET_HIGH);
    }
    else if (value == GPIO_SET_LOW)
    {
        fprintf(fd, "%d", GPIO_SET_LOW);
    }
    else
    {
        ret_val = -1;
    }

    fflush(fd);
    fclose(fd);
    return ret_val;
}

#endif // BBB_GPIO_H
