//
// Created by Gruff Trick
//
#include "functions.h"

/**
 *  Allows the user to tweak the bounds for the config data.
 *
 * @param cfg_data The configuration data - contains the data bounds
 */
void edit_config_data (Config * cfg_data) {
    int i = 0;
    while (i != 9) {
        // Print current config data
        print_config_data(cfg_data);

        // Config data setup Menu
        printf("\nWhat would you like to do? - \n\n\t1 - Set config file name\n\t"
               "2 - Set movement duration\n\t3 - Set maximum speed\n\t4 - Set number of bars\n\t"
               "5 - Set Longitude Range \n\t6 - Set Latitude Range\n\n\t9 - Stop config file setup\n\n");
        scanf("%d", &i);
        switch (i) {
            case 1: // set config name
                printf("Please enter file name:\n");
                scanf("%s", cfg_data->data_file_name);
                break;
            case 2: // set movement frequency range (duration of movements)
                printf("Please enter min duration:\n");
                scanf("%f", &cfg_data->movement_duration.start);
                printf("Please enter max duration:\n");
                scanf("%f", &cfg_data->movement_duration.end);
                break;
            case 3: // set maximum speed
                printf("Please enter max speed:\n");
                scanf("%f", &cfg_data->max_speed);
                break;
            case 4: // set number of bars on histogram plot
                printf("Please enter number of bars:\n");
                scanf("%d", &cfg_data->num_bars);
                break;
            case 5: // set longitude range
                printf("Please enter min longitude:\n");
                scanf("%f", &cfg_data->range_lng.start);
                printf("Please enter max longitude:\n");
                scanf("%f", &cfg_data->range_lng.end);
                break;
            case 6: // set latitude range
                printf("Please enter min latitude:\n");
                scanf("%f", &cfg_data->range_lat.start);
                printf("Please enter max latitude:\n");
                scanf("%f", &cfg_data->range_lat.end);
                break;
            default:
                printf("Invalid Input");
                break;
        }
    }
}

/**
 *  Takes config data from program and overwrites the config.txt file with it
 *
 * @param cfg_data The configuration data - contains the data bounds
 */
void update_config_file (Config * cfg_data) {
    // open file for writing
    char path[20] = "config.txt";
    remove(path);
    FILE * file = fopen(path, "w");

    printf("Updating config file\n");

    fprintf(file, "data_file_name \"%s\"\n", cfg_data->data_file_name);
    fprintf(file, "movement_duration <%d : %d>\n", (int) cfg_data->movement_duration.start, (int) cfg_data->movement_duration.end);
    fprintf(file, "maximum_speed %f\n", cfg_data->max_speed);
    fprintf(file, "num_bars %d\n", cfg_data->num_bars);
    fprintf(file, "range_lon <%f : %f>\n", cfg_data->range_lng.start, cfg_data->range_lng.end);
    fprintf(file, "range_lat <%f : %f>\n", cfg_data->range_lat.start, cfg_data->range_lat.end);

    fclose(file);
}


/**
 *  Loads configuration data, from config.txt
 *  Contains the read data boundries.
 *
 * @param cfg_data The configuration data - contains the data bounds
 */
void load_config_file (Config * cfg_data) {
    // open file for writing
    char fp[20] = "config.txt";
    FILE *file = fopen(fp, "r");
    char line[LINE_SIZE];
    char *ptr;

    // read data file name
    fgets(line, sizeof(line), file);
    strtok(line, "\"");
    strcpy(cfg_data->data_file_name, strtok(NULL, "\""));

    // read movement duration
    fgets(line,sizeof(line), file);
    strtok(line, "<");
    cfg_data->movement_duration.start = strtof(strtok(NULL, ":"), &ptr);
    cfg_data->movement_duration.end = strtof(strtok(NULL, ">"), &ptr);

    // read max speed
    fgets(line, sizeof(line), file);
    strtok(line, " ");
    cfg_data->max_speed = strtof(strtok(NULL, " "), &ptr);

    // read num of bars
    fgets(line, sizeof(line), file);
    strtok(line, " ");
    cfg_data->num_bars = (int) strtod(strtok(NULL, " "), &ptr);

    // read longitude range
    fgets(line, sizeof(line), file);
    strtok(line, "<");
    cfg_data->range_lng.start = strtof(strtok(NULL, ":"), &ptr);
    cfg_data->range_lng.end = strtof(strtok(NULL, ">"), &ptr);

    // read latitude range
    fgets(line, sizeof(line), file);
    strtok(line, "<");
    cfg_data->range_lat.start = strtof(strtok(NULL, ":"), &ptr);
    cfg_data->range_lat.end = strtof(strtok(NULL, ">"), &ptr);

    fclose(file);
}


/**
 *  Initialises the config data stores in the struct to their default values
 *
 * @return Struct of config data
 */
Config initialise_config () {
    Config temp_cfg_data;

    strcpy(temp_cfg_data.data_file_name, " ");
    temp_cfg_data.max_speed = 50;
    temp_cfg_data.movement_duration.start = 0;
    temp_cfg_data.movement_duration.end = 604800;
    temp_cfg_data.num_bars = 20;
    temp_cfg_data.range_lng.start = 0;
    temp_cfg_data.range_lng.end = 0;
    temp_cfg_data.range_lat.start = 0;
    temp_cfg_data.range_lat.end = 0;

    return temp_cfg_data;
}


/**
 * Prints currently stored configuration data to stdout
 *
 * @param cfg_data The configuration data - contains the data bounds
 */
void print_config_data (Config * cfg_data) {
    printf("\n---Current Config Data---\n");
    printf("Data File Name: %s\n", cfg_data->data_file_name);
    printf("Movement Duration: < %d : %d >\n", (int) cfg_data->movement_duration.start, (int) cfg_data->movement_duration.end);
    printf("Maximum Speed: %fm/s\n", cfg_data->max_speed);
    printf("Number of Bars: %d\n", cfg_data->num_bars);
    printf("Longitude Range: < %lf : %lf >\n", cfg_data->range_lng.start, cfg_data->range_lng.end);
    printf("Latitude Range: < %lf : %lf >\n\n", cfg_data->range_lat.start, cfg_data->range_lat.end);
}
