int pressure_to_delay_data[] = {
    // num of rows	// power
    3, 0, 5, 10, 			// 1st row is power

    //	pressure, delay for power
    0, 0, 0, 0,
    100, 0, 1000, 2000,
    200, 0, 500, 700
};

int get_delay()
{
    int pressure = 350;
    int power = 2;

    int power_cols = pressure_to_delay_data[0];
    int total_cols = power_cols + 1;

    int n_pressure = sizeof(pressure_to_delay_data) / (total_cols * sizeof(*pressure_to_delay_data)) - 1; // skip 1st power row
    if (n_pressure < 2)
        return 0;

    int power_col1 = 1, power_col2 = 2;
    int i = 1;

    if (power < pressure_to_delay_data[1])
        power_col1 = power_col2 = 1;
    else
    {
        for (; i < power_cols; i++)
        {
            int pow = pressure_to_delay_data[i];
            if (power > pow)
                continue;

            power_col1 = i - 1;
            power_col2 = i;
            break;
        }
    }

    if (pressure <= pressure_to_delay_data[0])
        return pressure_to_delay_data[1];

    int * pressure_to_delay_data_it = pressure_to_delay_data + 2 * total_cols;
    int p1, p2;

    i = 1;
    for (; i < n_pressure; i++, pressure_to_delay_data_it += total_cols)
    {
        p2 = pressure_to_delay_data_it[0];
        if (pressure > p2)
            continue;

        p1 = *(pressure_to_delay_data_it - total_cols);
        if (p2 == p1)
            continue;

        break;
    }

    int* pressure_to_delay_data_it_prev = pressure_to_delay_data_it - total_cols;
    if (i == n_pressure)
        pressure_to_delay_data_it = pressure_to_delay_data_it_prev;

    p2 = *pressure_to_delay_data_it;
    p1 = *pressure_to_delay_data_it_prev;

    int v_p1_1 = pressure_to_delay_data_it_prev[power_col1];
    int v_p2_1 = pressure_to_delay_data_it[power_col1];

    int v_p1_2 = pressure_to_delay_data_it_prev[power_col2];
    int v_p2_2 = pressure_to_delay_data_it[power_col2];

    float v1, v2;
    if (p1 == p2)
    {
        v1 = v_p1_1;
        v2 = v_p1_2;
    }
    else
    {
        v1 = v_p1_1 + 1.0f * (v_p2_1 - v_p1_1) * (pressure - p1) / (p2 - p1);
        v2 = v_p1_2 + 1.0f * (v_p2_2 - v_p1_2) * (pressure - p1) / (p2 - p1);
    }

    if (power_col1 == power_col2)
        return v1;
    else
    {
        int pow1 = pressure_to_delay_data[power_col1];
        int pow2 = pressure_to_delay_data[power_col2];
        return (int)(v1 + 1.0f * (v2 - v1) * (power - pow1) / (pow2 - pow1) + 0.5f);
    }
}
