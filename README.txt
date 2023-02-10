------------------------------------------------------------------
| * * * * Gruff Trick[grt26]'s CS23820 Assignment README * * * * |
------------------------------------------------------------------

The following is the basic structure, required files and libraries to build the program:-

------------------
 File Structure 
------------------
	/MAIN DIRECTORY\
		1 Header file:
		-> functions.h

		6 source files:
		-> main.c
			-> The main class containing the main function
		-> config.c
			-> Class for generating configuration files
			-> stores the min/max bounds for the data
		-> reader.c
			-> Class for reading in collar text files
		-> movements/c
			-> Takes data read in the reader and generates movement data
		-> csv.c
			-> Builds csv files from gathered data
		-> graphs.c
			-> Generates graphs from the movement data

		CMakeLists.txt
		-> Required by CMake to build the executable
		-> CMake Standard 11, Version 3.17 or later

	/CMAKE-BUILD-DEBUG\
		CMakeFiles:
		-> Required by CMake to build the executable

		Data folder:
		-> contains the Collar_x.txt files
		-> any generated CSV files are placed here too

		config.txt:
		-> A config file is required for a number of in-program-functions,
		-> however, the program is able to create its own file if non exist.


---------------------
 Standard Libraries
---------------------
	The program requires a number of standard C libraries to build. 
	Required are the following libraries:-
	
	-> stdio.h (Version 5.3)
	-> stdlib.h
	-> math.h
	-> string.h
	-> ctype.h
	-> limits.h
