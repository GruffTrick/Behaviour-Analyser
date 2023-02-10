#include "functions.h"


int main() {
    node_ptr head = NULL;
    movements_ptr movements = NULL;
    Config config_data = initialise_config();
    int i = 0;
    char filename[20];

    printf("Please Enter File Name:\nEnter other value to go to advanced configuration:\n");
    scanf("%s", filename);
    // Read in file
    if ((head = read_file(filename, head)) != NULL) {
        // Create movements list
        movements = generate_movements(head);
        // display_movements(movements);
        generate_csv(config_data.data_file_name, movements, NULL);
        // Generate Graphs
        generate_lat_lon_speed_graph(config_data, movements);
    }else
        {
        // Main Menu Interface
        while (i != 9) {
            print_config_data(&config_data);

            i = 0;
            printf("\nWhat would you like to do? - \n\n\t1 - Load configuration file\n"
                   "\t2 - Load collar data, generate csv file and graphs\n"
                   "\t3 - Change current configuration information\n\t"
                   "4 - Update the configuration file with config info\n"
                   "\n9 - Quit Program\n\n");

            scanf("%d", &i);
            switch (i) {
                case 1: // load a config file
                    load_config_file(&config_data);
                    break;
                case 2: // load collar data, generate csv and graphs
                    // clear list to make new linked list
                    clear_list(head);
                    clear_movements(movements);
                    head = NULL;
                    movements = NULL;
                    // Read in file
                    if ((head = read_file(config_data.data_file_name, head)) == NULL) { break; }
                    // Create movements list
                    movements = generate_movements(head);
                    // display_movements(movements);
                    generate_csv(config_data.data_file_name, movements, &config_data);
                    // Generate Graphs
                    generate_lat_lon_speed_graph(config_data, movements);
                    break;
                case 3: // change current config info
                    edit_config_data(&config_data);
                    break;
                case 4: // Update the configuration file
                    update_config_file(&config_data);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
