void lcd_print(const char* msg, int row) {}
void lcd_print(const char* msg) {
    lcd_print(msg, 0);
}

void lcd_print_timeout(const char* msg, int ms) {
    lcd_print(msg, 0);
}


void init_hw()
{}

bool check1()
{
    int pb6 = 0, pb7 = 0;
    pb6 = 0;
    if (pb7 != 0)
    {
        pb6 = 1;
        lcd_print("bla");
        return false;
    }
    else
        pb6 = 1;

    return true;
}

bool usb_connected()
{
    return false;
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
    lcd_print(str);
}

int is_shot()
{
    return 0;
}

void set_pa(int id)
{
}
void reset_pa(int id)
{
}

int get_pa(int id)
{
    return 0;
}


void sleep()
{
}

bool make_shot()
{
    set_pa(5);

    // make_shot
    // ....

    int cyl = get_cylinder();
    if (cyl > 0)
    {
        set_cylinder(cyl - 1);
    }

    reset_pa(1);
    if (get_pa(2))
    {
        set_pa(1);
        lcd_print("bla2");
        sleep();
        return false;
    }
    set_pa(1);

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
    while (true) {
        if (!shot())
        {
            lcd_print("shot error");
            power_off();
            return 0;
        }

        int press = get_pressure();
        if (press >= 0 && press < MIN_PRESSURE)
        {
            lcd_print("pressure is low");
            delay(500);
            continue;
        }

        int cylinder = get_cylinder();
        if (cylinder == 1)
            continue;

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
