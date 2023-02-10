//
// Created by Gruff Trick
//
#include "functions.h"


/**
 *  Reads Collar data from the provided plain text file
 *
 * @param filename Name of text file
 * @param temp_head_ptr Pointer to head of linked
 * @return The newly generated linked list containing data from the text file
 */
node_ptr read_file (char * filename, node_ptr temp_head_ptr) {
    // Initialise variables
    Position pos;
    Date date;
    Time time;
    char line[LINE_SIZE];
    node_ptr temp_node_ptr = NULL;
    int total_line = 0, total_used = 0, total_valid = 0, total_ignored = 0, total_stationary = 0;

    //Open file for reading
    char path[PATH_SIZE] = "Data/";
    strcat(path, filename);
    if (fopen(path, "r") == NULL) {
        printf("File '%s' Cannot Be read or does not exist\n", filename);
        return NULL;
    }
    FILE *file = fopen(path, "r");
    printf("Scanning File in %s\n", path);

    // Copy data from file while there is still text left
    while (feof(file) == 0) {
        fgets(line, sizeof(line), file);    // get line of text from file
        total_line++;   // increment total lines read
        //printf("\nCount: %d\n", total_line);

        if (isdigit((int) line[0]) != 0) {     // checks if start of line is valid digit
            total_valid++;
            //printf("%s\n", line);
            sscanf(line, "%lf, %lf, %d/%d/%d, %d:%d:%d",
                   &pos.lat, &pos.lng, &date.day, &date.month, &date.year, &time.hour, &time.minute, &time.second);
            //printf("Values in Line:\nLat: %lf\tLng: %lf\tDate: %d/%d/%d\tTime: %d:%d:%d\n", pos.lat, pos.lng, date.day, date.month, date.year, time.hour, time.minute, time.second);
            if (total_used == 0) {
                temp_node_ptr = make_node(pos, date, time);
                // attach the existing temp_head_ptr to new node
                temp_node_ptr->next = temp_head_ptr;
                // make temp_head_ptr new node
                temp_head_ptr = temp_node_ptr;
                total_used++;
            } else {
                if (!compare_prev(temp_node_ptr, pos)) {
                    // if positions don't repeat insert node at tail
                    temp_node_ptr = make_node(pos, date, time);
                    insert_at_tail(&temp_head_ptr, temp_node_ptr);
                    total_used++;
                } else {
                    // if positions repeat replace with newest date and time
                    temp_node_ptr->date = date;
                    temp_node_ptr->time = time;
                    //printf("Repeat Value\n");
                    total_stationary++;
                }
            }
        } else {
            total_ignored++;
        }
    }
    fclose(file);

    //display_list(temp_head_ptr);
    printf("...Finished Scanning File.\n");
    printf("Total Lines Read: %d\nTotal valid coordinates: %d\nTotal ignored lines: %d\nTotal Stationary coordinates: %d\nTotal Lines Used: %d\n\n",
           total_line, total_valid, total_ignored, total_stationary, total_used);
    return temp_head_ptr;
}

/**
 *  Compares the coordinates of a position to the last position stored in the linked list for equality
 *
 * @param temp_prev_node_ptr  The linked list
 * @param pos The position to be compared
 * @return If positions are equal returns 1
 */
int compare_prev (node_ptr temp_prev_node_ptr, Position pos) {
    //return 1 if lat and lng is the same value
    if (temp_prev_node_ptr->position.lat == pos.lat && temp_prev_node_ptr->position.lng == pos.lng) {
//        printf("\nRepeat Location\n");
        return 1;
    }
    return 0;
}


/**
 *  Creates new node for a linked list
 *
 * @param position The position
 * @param date The date
 * @param time The time
 * @return Linked list node with memory allocated
 */
node_ptr make_node(Position position, Date date, Time time) {
    node_ptr new_node_ptr;
    new_node_ptr = malloc(sizeof(node));

    if (new_node_ptr == NULL) {
        // failed to get memory, so return
        return NULL;
    } else {
        // have memory so copy in data
        new_node_ptr->position = position;
        new_node_ptr->date = date;
        new_node_ptr->time = time;
        new_node_ptr->next = NULL;
        return new_node_ptr;
    }
}


/**
 *  Inserts node to the end of the linked list
 *
 * @param ptr_to_existing_head The head of the linked list
 * @param new_node_ptr Node to be attached to the end of the linked list
 */
void insert_at_tail(node_ptr * ptr_to_existing_head, node_ptr new_node_ptr){
    // get a temporary pointer to walk through the list
    node_ptr * temp_ptr;
    temp_ptr = ptr_to_existing_head;

    // walk through list until pointing at a node with next equals to NULL
    while (*temp_ptr != NULL) {
        temp_ptr = &((*temp_ptr)->next);
    }

    // make new node point where the old link pointed
    // and then make the old last link point to us
    new_node_ptr->next = *temp_ptr;
    *temp_ptr = new_node_ptr;
}


/**
 * Displays every node in the Linked list in the stdout
 *
 * @param list_ptr The linked list
 */
__unused void display_list(node_ptr list_ptr){
    printf("The nodes in the list are as follows.\n");
    while (list_ptr != NULL){
        printf("\nLat: %lf\tLng: %lf\tDate: %d/%d/%d\tTime: %d:%d:%d\n", list_ptr->position.lat, list_ptr->position.lng,
               list_ptr->date.day, list_ptr->date.month, list_ptr->date.year,
               list_ptr->time.hour, list_ptr->time.minute, list_ptr->time.second);
        list_ptr = list_ptr->next;
    }
}


/**
 *  Removes all items in the linked list
 *
 * @param list_ptr The linked list
 */
void clear_list(node_ptr list_ptr){
    int count = 0;
    printf("\nClearing Data in List\n");
    while (list_ptr != NULL){
        node_ptr temp = list_ptr;
        list_ptr = list_ptr->next;

//        printf("Clearing: %lf, %lf, %d/%d/%d, %d:%d:%d at %p\n", temp->position.lat, temp->position.lng,
//               temp->date.day, temp->date.month, temp->date.year,
//               temp->time.hour, temp->time.minute, temp->time.second);
        free(temp);
        count++;
    }
    printf("Cleared %d entries\n", count);
}