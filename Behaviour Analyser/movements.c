//
// Created by Gruff Trick
//
#include "functions.h"


/**
 *  Generates a linked list with the necessary values for movement data
 *  Important for use in printing to  a CSV file.
 *
 * @param list_ptr Linked list containing positions, dates and times
 * @return The movements linked list
 */
movements_ptr generate_movements (node_ptr list_ptr) {
    node_ptr temp_node_start_ptr = list_ptr;
    node_ptr temp_node_end_ptr = list_ptr->next;
    movements_ptr temp_mov_head_ptr = NULL;

    printf("Generating movements...\n");

    // count for movement id
    int count = 1;
    // generate the movements list, iterate until no more end positions
    while (temp_node_end_ptr != NULL) {
        // get distance, duration and speed
        double distance = calculate_distance(&temp_node_start_ptr->position, &temp_node_end_ptr->position);
        Time duration;
        calculate_duration(temp_node_start_ptr->time, temp_node_end_ptr->time, &duration);
        double speed = distance / (double) time_in_sec(duration);

        // omit movements over 50m/s due to likely being a gps error
        if (speed <= 50) {
            // make movements node using the gathered data
            movements_ptr temp_mov_list_ptr = make_movements_node(distance, duration, speed, temp_node_start_ptr,
                                                                  temp_node_end_ptr);
            // if no existing head...
            if (count == 1) {
                // attach the existing temp_head_ptr to new node
                temp_mov_list_ptr->next = temp_mov_head_ptr;
                // make temp_mov_head_ptr new node
                temp_mov_head_ptr = temp_mov_list_ptr;
            } else {    // ...else, insert at end of the linked list
                insert_movements_at_tail(&temp_mov_head_ptr, temp_mov_list_ptr);  // inserts at tail of linked list
            }
            count++;
        }
        // move onto next pair of positions
        temp_node_start_ptr = temp_node_start_ptr->next;
        temp_node_end_ptr = temp_node_end_ptr->next;
    }
    printf("Done.\n");
    //display_movements(temp_mov_head_ptr);
    return temp_mov_head_ptr;   // return the movements linked list
}

/**
	 * The great circle distance or the orthodromic distance is the shortest distance
	 * between two points on a sphere
	 *
	 * @param other
	 * @return distance in m
	 */
double calculate_distance(Position* first, Position* second){

    double lon1 = degToRad(first->lng);
    double lon2 = degToRad(second->lng);
    double lat1 = degToRad(first->lat);
    double lat2 = degToRad(second->lat);

    // Haversine formula (alt. vincenties formula)
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2)
               + cos(lat1) * cos(lat2)
                 * pow(sin(dlon / 2),2);

    double c = 2 * asin(sqrt(a));

    // Radius of earth in kilometers. Use 3956
    // for miles
    double r = 6371;

    // calculate the result (in m)
    return((c * r)*1000);
}

/**
 * Calculates difference between two different times
 * Original algorithm written by Shirish Kadam
 * https://shirishkadam.com/2014/01/04/time-difference-calculator-c-program/
 *
 * @param start_time The first time
 * @param end_time the second time
 * @param diff the difference between start and end time
 */
void calculate_duration (Time start_time, Time end_time, Time * diff) {
    if (start_time.hour < end_time.hour) {
        diff->hour=end_time.hour-start_time.hour;
    } else {diff->hour=start_time.hour-end_time.hour;}

    if (start_time.minute < end_time.minute) {
        diff->minute=end_time.minute-start_time.minute;
    } else {diff->minute=start_time.minute-end_time.minute;}

    if (start_time.second < end_time.second) {
        diff->second=end_time.second-start_time.second;
    } else {diff->second=start_time.second-end_time.second;}
}


/**
 *  Converts time type to seconds as double
 *
 * @param time the time in hours, minutes and seconds
 * @return Time in seconds
 */
int time_in_sec (Time time) {
    double time_sec = 0;

    time_sec += time.second;
    time_sec += time.minute * 60;
    time_sec += time.hour * 60 * 60;

    return (int) time_sec;
}


/**
 *  Creates a new node in the linked list
 *
 * @param distance The distance
 * @param duration The time taken to move between positions
 * @param speed travel speed
 * @param start_node start position
 * @param end_node end position
 * @return The newly generated node after memory allocation
 */
movements_ptr make_movements_node(double distance, Time duration, double speed, node_ptr start_node, node_ptr end_node) {
    movements_ptr new_mov_ptr;
    new_mov_ptr = malloc(sizeof(movements));

    if (new_mov_ptr == NULL) {
        // failed to get memory, so return
        return NULL;
    } else {
        // have memory so copy in data
        new_mov_ptr->distance = distance;
        new_mov_ptr->duration = duration;
        new_mov_ptr->speed = speed;
        new_mov_ptr->start_node = start_node;
        new_mov_ptr->end_node = end_node;
        new_mov_ptr->next = NULL;
        return new_mov_ptr;
    }
}


/**
 *  Inserts node to the end of the linked list
 *
 * @param ptr_to_existing_head Head of the linked list
 * @param new_mov_ptr New node to at to end of linked list
 */
void insert_movements_at_tail (movements_ptr * ptr_to_existing_head, movements_ptr new_mov_ptr) {
    // get a temporary pointer to walk down the list
    movements_ptr * temp_ptr;
    temp_ptr = ptr_to_existing_head;

    // walk until pointing at a link containing NULL
    while (*temp_ptr != NULL) {
        temp_ptr = &((*temp_ptr)->next);
    }

    // make new node point where the old link pointed
    // and then make the old last link point to it
    new_mov_ptr->next = *temp_ptr;
    *temp_ptr = new_mov_ptr;
}


/**
 * Displays all the nodes in the linked list
 *
 * @param list_ptr The linked list
 */
__unused void display_movements(movements_ptr list_ptr) {
    printf("The nodes in the list are as follows.\n");
    int i = 0;
    // Iterate through the linked list until no more nodes
    while (list_ptr != NULL){
        i++;
        // Print the movement data
        printf("\nMovement: %d\tDate: %d/%d/%d\tTime: %d:%d:%d\n lat1: %lf\t Lng1: %lf\t Lat2: %lf\t Lng2: %lf\nDistance: %lf\tDuration: %d:%d:%d\tSpeed: %lf\n", i,
               list_ptr->start_node->date.day,list_ptr->start_node->date.month, list_ptr->start_node->date.year,
               list_ptr->start_node->time.hour, list_ptr->start_node->time.minute, list_ptr->start_node->time.second,
               list_ptr->start_node->position.lat, list_ptr->start_node->position.lng,
               list_ptr->end_node->position.lat, list_ptr->end_node->position.lng,
               list_ptr->distance, list_ptr->duration.hour, list_ptr->duration.minute, list_ptr->duration.second, list_ptr->speed);
        list_ptr = list_ptr->next;
    }
}

/**
 *  Removes all items in the linked list
 *
 * @param list_ptr The linked list
 */
void clear_movements(movements_ptr list_ptr){
    int count = 0;
    printf("\nClearing Data in List\n");
    // Step through each node in linked list
    while (list_ptr != NULL){
        movements_ptr temp = list_ptr;
        list_ptr = list_ptr->next;
        // clear the node
        free(temp);
        count++;
    }
    printf("Cleared %d entries\n\n", count);
}