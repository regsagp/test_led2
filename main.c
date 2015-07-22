#include <tchar.h>
#include "ports.h"

void lcd_print(const char* msg, int row) {}
//void lcd_print(const char* msg) {
//    lcd_print(msg, 0);
//}

void lcd_print_timeout(const char* msg, int ms) {
    lcd_print(msg, 0);
}

int check1()
{
    reset_port(PortB, 6);
    if (get_port(PortB, 7) != 0)
    {
        set_port(PortB, 6);
        lcd_print("bla", 0);
        return 0;
    }
    else
        set_port(PortB, 6);

    return 1;
}

int usb_connected()
{
    return 0;
}

int shot()
{
    return 1;
}

int MIN_PRESSURE = 80;
int get_pressure()
{
    return -1;
}

void delay(int ms)
{}

int get_cylinder()
{
    return  -1;
}
void set_cylinder(int c)
{
}


int get_fuse()
{
    return -1;
}

int get_rammer()
{
    return 0;
}

void power_off() {}

int MIN_BATTERY_LEVEL_MV = 3400;

int battery_level_mv()
{
    return 3700;
}

void print_current_state()
{
    char str[64];
    sprintf(str, "cyl:%d", get_cylinder());
    lcd_print(str, 0);
}

int is_shot()
{
    return get_port(PortA, 5) == 0;
}

void sleep()
{
}

int make_shot()
{
    set_pa(5);

    // make_shot
    // ....

    int cyl = get_cylinder();
    if (cyl > 0)
        set_cylinder(cyl - 1);

    reset_port(PortA, 1);
    if (get_port(PortA, 2))
    {
        set_port(PortA, 1);
        lcd_print("bla2", 0);
        sleep();
        return 0;
    }
    set_port(PortA, 1);
}


#include <conio.h>
int _tmain(int argc, _TCHAR* argv[])
{
    init_hw();

    if (!check1())
        return 0;

    lcd_print_timeout("hi", 1000);

    if (usb_connected())
    {
        // do something...
        return 0;
    }

    int i = 0;
    while (1) 
    {
        if (!shot())
        {
            lcd_print("shot error", 0);
            power_off();
            return 0;
        }

        int press = get_pressure();
        if (press >= 0 && press < MIN_PRESSURE)
        {
            lcd_print("pressure is low", 0);
            delay(500);
            continue;
        }

        int cylinder = get_cylinder();
        if (cylinder == 1)
            continue;

        // концевик 
        int fuse = get_fuse();
        if (fuse == 1)
            continue;

        if (get_rammer() == 1)
            continue;

        if (battery_level_mv() < MIN_BATTERY_LEVEL_MV)
        {
            lcd_print_timeout("batt low", 3000);
            power_off();
            return 0;
        }

        print_current_state();

        if (is_shot())
        {
            make_shot();

        }





        auto c = _getch_nolock();

        printf("%d : %c\n", i++, c);


    }

    return 0;
}
