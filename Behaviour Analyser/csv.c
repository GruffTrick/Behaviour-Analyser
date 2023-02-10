//
// Created by Gruff Trick
//
#include "functions.h"


/**
 *  Generates a CSV file from the data
 *
 * @param filename Filename of collar text file used
 * @param movements_list The linked list containing movement data
 * @param cfg_data The configuration data containing data boundaries
 */
void generate_csv(char * filename, movements_ptr movements_list, Config * cfg_data) {
    //Makes file writable, if no file exists one is created
    char f[20];
    strcpy(f, filename);
    strcat(f, ".csv");
    char path[PATH_SIZE] = "Data/";
    strcat(path, f);
    remove(path);
    FILE *file = fopen(path, "w");

    printf("\nCSV File - %s - created\n...Populating CSV file...\n", filename);
    populate_csv(file, movements_list, cfg_data);
    fclose(file);
}


/**
 *  Populates the CSV file with the provided data
 *
 * @param file The CSV file
 * @param movements_list The linked list containing movement data
 * @param cfg_data The configuration data containing data boundaries
 */
void populate_csv(FILE * file, movements_ptr movements_list, Config * cfg_data) {
    int stationary_time = 0, foraging_time = 0, moving_time = 0, implausable_time = 0, i = 0;
    movements_ptr temp_mov_ptr = movements_list;

    while (temp_mov_ptr != NULL) {
        // if config file is passed, checks if values are within provided ranges
        if (cfg_data != NULL && !is_allowed(temp_mov_ptr, cfg_data)) {
            temp_mov_ptr = temp_mov_ptr->next;
            continue;
        }
        i++;
        // print movement number
        fprintf(file, "Movement:%d, ", i);

        // print start position date
        if (temp_mov_ptr->start_node->date.day < 10) {fprintf(file, "0");}
        fprintf(file, "%d/", temp_mov_ptr->start_node->date.day);
        if (temp_mov_ptr->start_node->date.month < 10) {fprintf(file, "0");}
        fprintf(file, "%d/%d, ", temp_mov_ptr->start_node->date.month, temp_mov_ptr->start_node->date.year);

        // print start position time
        if (temp_mov_ptr->start_node->time.hour < 10) {fprintf(file, "0");}
        fprintf(file, "%d:", temp_mov_ptr->start_node->time.hour);
        if (temp_mov_ptr->start_node->time.minute < 10) {fprintf(file, "0");}
        fprintf(file, "%d:", temp_mov_ptr->start_node->time.minute);
        if (temp_mov_ptr->start_node->time.second < 10) {fprintf(file, "0");}
        fprintf(file, "%d, ", temp_mov_ptr->start_node->time.second);

        // print start and end coordinates
        fprintf(file, "%lf, %lf, %lf, %lf, ", temp_mov_ptr->start_node->position.lat, temp_mov_ptr->start_node->position.lng,
                temp_mov_ptr->end_node->position.lat, temp_mov_ptr->end_node->position.lng);

        // print distance travelled, duration of travel and travel speed
        fprintf(file, "%lfm, %ds, %lfm/s, ", temp_mov_ptr->distance, time_in_sec(temp_mov_ptr->duration), temp_mov_ptr->speed);



        // print category
        if (temp_mov_ptr->speed >= 0 && temp_mov_ptr->speed < S_SPEED_MAX) {
            fprintf(file, "Stationary\n");
            stationary_time += time_in_sec(temp_mov_ptr->duration);
        } else if (temp_mov_ptr->speed >= S_SPEED_MAX && temp_mov_ptr->speed < F_SPEED_MAX) {
            fprintf(file, "Foraging\n");
            foraging_time += time_in_sec(temp_mov_ptr->duration);
        } else if (temp_mov_ptr->speed >= F_SPEED_MAX && temp_mov_ptr->speed < M_SPEED_MAX) {
            fprintf(file, "Moving\n");
            moving_time += time_in_sec(temp_mov_ptr->duration);
        } else if (temp_mov_ptr->speed >= M_SPEED_MAX) {
            fprintf(file, "Implausible\n");
            implausable_time += time_in_sec(temp_mov_ptr->duration);
        }

        temp_mov_ptr = temp_mov_ptr->next;
    }

    //
    printf("Finished.\n\nSummary of total time spent:\nStationary: %d seconds\nForaging: %d seconds\nMoving: %d seconds"
           "\nImplausible: %d seconds\n", stationary_time, foraging_time, moving_time, implausable_time);
}


/**
 *  Check if the data is within provided data boundaries in the configuration data
 *
 * @param temp_mov_ptr The movements data
 * @param cfg_data The configuration data containing data boundaries
 * @return Returns 1 if data is allowed
 */
int is_allowed (movements_ptr temp_mov_ptr, Config * cfg_data) {
    // Check if duration is within range
    if ((float) time_in_sec(temp_mov_ptr->duration) < cfg_data->movement_duration.start
    || (float) time_in_sec(temp_mov_ptr->duration) > cfg_data->movement_duration.end) {
        return 0;
    }
    if (temp_mov_ptr->speed > cfg_data->max_speed) {
        return 0;
    }

    // Check if Longitude is within range
    if (temp_mov_ptr->start_node->position.lng < cfg_data->range_lng.start ||
    temp_mov_ptr->start_node->position.lng > cfg_data->range_lng.end) {
        return 0;
    }if (temp_mov_ptr->end_node->position.lng < cfg_data->range_lng.start ||
        temp_mov_ptr->end_node->position.lng > cfg_data->range_lng.end) {
        return 0;
    }

    // Check if Latitude is within range
    if (temp_mov_ptr->start_node->position.lat < cfg_data->range_lat.start ||
        temp_mov_ptr->start_node->position.lat > cfg_data->range_lat.end) {
        return 0;
    }if (temp_mov_ptr->end_node->position.lat < cfg_data->range_lat.start ||
        temp_mov_ptr->end_node->position.lat > cfg_data->range_lat.end) {
        return 0;
    }

    // Data is within chosen config parameters
    return 1;
}