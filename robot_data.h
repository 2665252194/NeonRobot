#ifndef ROBOT_DATA_H
#define ROBOT_DATA_H


//Why would you come here?
//Go to that c file please

int random_num(int min, int max);
void initialize_arena_dimensions();


extern const int width;
extern const int height;
extern int arena_width;
extern int arena_height;
extern const int unit_size;
extern int arena_start_x;
extern int arena_start_y;

extern int O_x;
extern int O_y;
extern int max_x;
extern int max_y;


extern int inside_width;
extern int inside_height;

extern int unit_array[32][32];




extern int marker_x;
extern int marker_y;
extern int obs_x;
extern int obs_y;
extern int robot_start_x;
extern int robot_start_y;
extern int robot_start_orientation;

#endif