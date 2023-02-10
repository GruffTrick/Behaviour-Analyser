//
// Created by Gruff Trick
//
#include "functions.h"


/**
 *  Test function for generating spiral graphs graphs
 */
__unused void createTestPlot() {
    // note that gnuplot can produce an enormous range of plots and is extremely
    // configurable. See http://www.gnuplot.info/documentation.html
    char filename[] = "test_plot.gnuplot";

    int sizex = 1024;
    int sizey = 768;

    // note all these items need double quotes around them in the output
    // so they have been added here
    char charttitle[] = "\"This is an example GnuPlot using vectors\"";
    char plot1title[] = "\"test data sequence\"";
    char xlabel[] = "\"horizontal axis\"";
    char ylabel[] = "\"vertical axis\"";
    char cblabel[] = "\"3rd axis (colour)\"";

    FILE* datafile;

    // create the output file for writing
    if ((datafile = fopen(filename, "w")) == NULL) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    // set up the output to produce an svg file output - lots of other possibilities
    fprintf(datafile, "set terminal svg noenhanced linewidth 0.75 size %i,%i\n", sizex, sizey);

    //set the file to save the graph into (without this it goes to the terminal)
    fprintf(datafile, "set output \"%s.svg\"\n", filename);

    // set the chart title
    fprintf(datafile, "set title %s\n", charttitle);

    //make the axis scale sutomatically based on the range of the data
    fprintf(datafile, "set autoscale\n");

    //set the axis labels and make them visible
    fprintf(datafile, "set xlabel %s\nshow xlabel\n", xlabel);
    fprintf(datafile, "set ylabel %s\nshow ylabel\n", ylabel);

    // set the colour banding label
    fprintf(datafile, "set cblabel %s\n", cblabel);

    // define a set of colours, and the values for those colours
    // the colours mix proportionately for values between those specified
    fprintf(datafile, "set palette defined (0 \"black\", 2.5 \"blue\", 5 \"red\", 10 \"yellow\")\n");

    // plot a set of vectors i.e. (startx, starty, lengthx, lengthy)
    // '-' means the data follows in the file (it could also be in an external file)
    // nohead means no arrows on the lines
    // linecolor palette z means use the data item after the vector to produce the colour
    fprintf(datafile, "plot '-' with vectors nohead linecolor palette z title %s\n", plot1title);

    // draw a spiral shape...
    for (int i=1; i<10; i++){
        fprintf(datafile, "%i, %i, %i, %i, %f\n", i, i-1, 0, 21-(i*2),(double)i/2);
        fprintf(datafile, "%i, %i, %i, %i, %f\n", i, 20-i, 20-(i*2),0,(double)i/2);
        fprintf(datafile, "%i, %i, %i, %i, %f\n", 20-i, 20-i, 0, -(20-(i*2)),(double)i/2);
        fprintf(datafile, "%i, %i, %i, %i, %f\n", 20-i, i, -(19-(i*2)), 0,(double)i/2);
    }
    fclose(datafile);
}


/**
 *  Generates graph from movement data as a gnuplot file
 *  The output file can be put into the gnuplot to generate a graph
 *
 * @param cfg_data  The configuration data containing data boundaries
 * @param movements The movement data stored in a linked list
 */
void generate_lat_lon_speed_graph(Config cfg_data, movements_ptr movements) {
    printf("\nGenerating graph plot data from %s\n", cfg_data.data_file_name);
    // note that gnuplot can produce an enormous range of plots and is extremely
    // configurable. See http://www.gnuplot.info/documentation.html
    char filename[] = "lat_lon_speed.gnuplot";
    movements_ptr temp_mov_ptr = movements;

    int sizex = 1024;
    int sizey = 768;

    // note all these items need double quotes around them in the output
    // so they have been added here
    char charttitle[] = "\"Animal Movement Plot\"";
    char plot1title[] = "\"\"";
    strtok(plot1title, cfg_data.data_file_name);
    char xlabel[] = "\"longitude\"";
    char ylabel[] = "\"latitude\"";
    char cblabel[] = "\"speed (m/s)\"";

    FILE* datafile;

    // create the output file for writing
    if ((datafile = fopen(filename, "w")) == NULL) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    // set up the output to produce an svg file output - lots of other possibilities
    fprintf(datafile, "set terminal svg noenhanced linewidth 0.75 size %i,%i\n", sizex, sizey);

    //set the file to save the graph into (without this it goes to the terminal)
    fprintf(datafile, "set output \"%s.svg\"\n", filename);

    // set the chart title
    fprintf(datafile, "set title %s\n", charttitle);

    //make the axis scale sutomatically based on the range of the data
    fprintf(datafile, "set autoscale\n");

    //set the axis labels and make them visible
    fprintf(datafile, "set xlabel %s\nshow xlabel\n", xlabel);
    fprintf(datafile, "set ylabel %s\nshow ylabel\n", ylabel);

    // set the colour banding label
    fprintf(datafile, "set cblabel %s\n", cblabel);

    // define a set of colours, and the values for those colours
    // the colours mix proportionately for values between those specified
    fprintf(datafile, "set palette defined (0 \"green\", 2.5 \"blue\", 12.5 \"red\", 20 \"orange\", 30 \"yellow\")\n");

    // plot a set of vectors i.e. (startx, starty, lengthx, lengthy)
    // '-' means the data follows in the file (it could also be in an external file)
    // nohead means no arrows on the lines
    // linecolor palette z means use the data item after the vector to produce the colour
    fprintf(datafile, "plot '-' with vectors nohead linecolor palette z title %s\n", plot1title);

    // Iterate until no more node in linked list
    while (temp_mov_ptr != NULL) {
        // Writes the data to the gnuplot file in the graph plot format
        fprintf(datafile, "%f, %f, %f, %f, %f\n", temp_mov_ptr->start_node->position.lng, temp_mov_ptr->start_node->position.lat,
                temp_mov_ptr->start_node->position.lng - temp_mov_ptr->end_node->position.lng, temp_mov_ptr->start_node->position.lat - temp_mov_ptr->end_node->position.lat, temp_mov_ptr->speed);
        temp_mov_ptr = temp_mov_ptr->next;
    }

    fclose(datafile);
}