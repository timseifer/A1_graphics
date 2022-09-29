#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include <vector>
using namespace std;

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};
	std::vector<std::vector<float>> my_points;

	OBJ_TYPE getType() {
		return SHAPE_CONE;
	}

	void draw() {
			int segment_x  = this->m_segmentsX;
			int segment_y = this->m_segmentsY;

			float x1 = 0;
			float y1 = 1;
			float z1 = 0;
			float w1 = 0;
			// if(my_points.empty()){
			vector<vector<float>> my_points_t = up_and_down(segment_x, segment_y);
			for(int p = 0; p < segment_y; p++){
				my_points_t.push_back(my_points_t[p]);
			}
			my_points = my_points_t;
			int index = 0;

			glBegin(GL_TRIANGLES);
			index = 0;

			for(int i = 0; i < segment_x; i++){
				for(int p = 0; p < segment_y-1; p++){
						//render each square (made up of two triangles)
						int pnt_one_idx = i*segment_y+p;
						int pnt_two_idx = i*segment_y+p+1;
						int pnt_three_idx = i*segment_y+p+segment_y;
						int pnt_four_idx = i*segment_y+p+1+segment_y;
						std::vector<float> val_1 = my_points[pnt_one_idx];
						std::vector<float> val_2 = my_points[pnt_two_idx];
						std::vector<float> val_3 = my_points[pnt_three_idx];
						std::vector<float> val_4 = my_points[pnt_four_idx];

						glVertex3f(val_1[0], val_1[1], val_1[2]);
						glVertex3f(val_2[0], val_2[1], val_2[2]);
						glVertex3f(val_3[0], val_3[1], val_3[2]);

						glVertex3f(val_3[0], val_3[1], val_3[2]);
						glVertex3f(val_2[0], val_2[1], val_2[2]);
						glVertex3f(val_4[0], val_4[1], val_4[2]);
				}
			}
			//make the bottom
			vector<float> top_cyl = {0, .5, 0};
			vector<float> bottom_cyl = {0, -.5, 0};
			for(int i = 0; i < segment_x; i++){
				int pnt_one_idx = segment_y * i;
				int pnt_two_idx = segment_y * i+segment_y;
				vector<float> pnt_one = my_points[pnt_one_idx];
				vector<float> pnt_two = my_points[pnt_two_idx];
				glVertex3f(pnt_one[0], pnt_one[1], pnt_one[2]);
				glVertex3f(pnt_two[0], pnt_two[1], pnt_two[2]);
				glVertex3f(bottom_cyl[0], bottom_cyl[1], bottom_cyl[2]);
			}


			for(int i = 0; i < segment_x; i++){
				int pnt_one_idx = (segment_y * i+segment_y)-1;
				int pnt_two_idx = (segment_y * i+segment_y+segment_y)-1;
				vector<float> pnt_one = my_points[pnt_one_idx];
				vector<float> pnt_two = my_points[pnt_two_idx];
				glVertex3f(pnt_one[0], pnt_one[1], pnt_one[2]);
				glVertex3f(top_cyl[0], top_cyl[1], top_cyl[2]);
				glVertex3f(pnt_two[0], pnt_two[1], pnt_two[2]);
			}
            glEnd();

	};

	void drawNormal() {
	};

private:
		std::vector<std::vector<float>> up_and_down(int seg_x, int seg_y){
		float x, y, z, r, z_step, slope;
		vector<vector<float>> my_vert_vals;
		z_step =1.0/(seg_y-1);
		slope = .5;
			for(int j = 0; j < seg_x; j++){
				for(int i = 0; i < seg_y; i++){
					r = -.5 + (slope/(seg_y-1))*i;
					x = r*cos(2*PI* j/seg_x );
					y = r*sin(2*PI* j/seg_x );
					z = -.5 + z_step*i;
					cout << "z is " << z << endl;
					my_vert_vals.push_back(vector<float>{x, z, y, (float)1.0});
				}
			}
		return my_vert_vals;
	}

	
};

#endif