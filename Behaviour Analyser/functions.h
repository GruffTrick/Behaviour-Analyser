//
// Created by Gruff Trick
//

#ifndef BEHAVIOUR_ANALYSER_FUNCTIONS_H
#define BEHAVIOUR_ANALYSER_FUNCTIONS_H

#define PATH_SIZE 50
#define LINE_SIZE 100
#define S_SPEED_MAX 0.02
#define F_SPEED_MAX 0.33
#define M_SPEED_MAX 12
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// Type definitions and Structs
typedef struct Node * node_ptr;
typedef struct Movements * movements_ptr;

typedef struct Position{
    double lat;
    double lng;
} Position;

typedef struct Date{
    int day;
    int month;
    int year;
} Date;

typedef struct Time{
    int hour;
    int minute;
    int second;
} Time;

typedef struct Node {
    Position position;
    Date date;
    Time time;
    node_ptr next;
} node;

typedef struct Movements {
    double distance;
    Time duration;
    double speed;
    node_ptr start_node;
    node_ptr end_node;
    movements_ptr next;
} movements;

typedef struct Range {
    float start;
    float end;
} Range;

typedef struct Config {
    char data_file_name[20];
    Range movement_duration;
    float max_speed;
    int num_bars;
    Range range_lng;
    Range range_lat;
} Config;

// Config file class
void edit_config_data (Config * cfg_data);
void update_config_file (Config * cfg_data);
Config initialise_config ();
void load_config_file (Config * cfg_data);
void print_config_data (Config * cfg_data);

// Reader class
node_ptr read_file(char * filename, node_ptr temp_head_ptr);
int compare_prev (node_ptr temp_prev_node_ptr, Position pos);
node_ptr make_node(Position position, Date date, Time time);
void insert_at_tail(node_ptr * ptr_to_existing_head, node_ptr new_node_ptr);
__unused void display_list(node_ptr list_ptr);
void clear_list(node_ptr list_ptr);

// Movements Class
movements_ptr generate_movements (node_ptr list_ptr);
double calculate_distance(Position* first, Position* second);
void calculate_duration (Time start_time, Time end_time, Time * diff);
int time_in_sec (Time time);
movements_ptr make_movements_node(double distance, Time duration, double speed, node_ptr start_node, node_ptr end_node);
void insert_movements_at_tail (movements_ptr * ptr_to_existing_head, movements_ptr new_node_ptr);
__unused void display_movements(movements_ptr list_ptr);
void clear_movements(movements_ptr list_ptr);

// CSV Builder Class
void generate_csv(char * filename, movements_ptr movements_list, Config * cfg_data);
void populate_csv(FILE * file, movements_ptr temp_mov_ptr, Config * cfg_data);
int is_allowed (movements_ptr movements_list, Config * cfg_data);

// Graph Builder Class
__unused void createTestPlot();
void generate_lat_lon_speed_graph(Config cfg_data, movements_ptr movements);

#endif //BEHAVIOUR_ANALYSER_FUNCTIONS_H
