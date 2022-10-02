#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

using namespace std;

class Sphere : public Shape {
public:
	Sphere() {};
	~Sphere() {};
	std::vector<std::vector<float>> my_points;
	std::vector<std::vector<float>> my_normals;

	OBJ_TYPE getType() {
		return SHAPE_SPHERE;
	}

	void draw() {

			int segment_x  = this->m_segmentsX;
			int segment_y = this->m_segmentsY;

			float x1 = 0;
			float y1 = 1;
			float z1 = 0;
			float w1 = 0;


			this->my_normals.clear();
			// if(my_points.empty()){
			vector<vector<float>> my_points_t = up_and_down(segment_x, segment_y);
			for(int p = 0; p < segment_y; p++){
				my_points_t.push_back(my_points_t[p]);
			}
			my_points = my_points_t;
			int index = 0;

			glBegin(GL_LINES);
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
						// base triangle
						// if(val_1[0] == val_3[0] && val_1[1] == val_3[1]){
						// setNormal(val_1[0], val_1[1], val_1[2], val_4[0], val_4[1], val_4[2], val_3[0], val_3[1], val_3[2]);
						// glVertex3f(val_1[0], val_1[1], val_1[2]);
						// glVertex3f(val_4[0], val_4[1], val_4[2]);
						// glVertex3f(val_3[0], val_3[1], val_3[2]);
						// }else{
						// setNormal(val_1[0], val_1[1], val_1[2], val_2[0], val_2[1], val_2[2], val_3[0], val_3[1], val_3[2]);
						glVertex3f(val_1[0], val_1[1], val_1[2]);
						glVertex3f(val_2[0], val_2[1], val_2[2]);
						// glVertex3f(val_3[0], val_3[1], val_3[2]);
						// setNormal(val_3[0], val_3[1], val_3[2], val_2[0], val_2[1], val_2[2], val_4[0], val_4[1], val_4[2]);
						// glVertex3f(val_3[0], val_3[1], val_3[2]);
						// glVertex3f(val_2[0], val_2[1], val_2[2]);
						// glVertex3f(val_4[0], val_4[1], val_4[2]);
						// }
				}
			}
            glEnd();
	};

	void drawNormal() {


	};

private:

	std::vector<std::vector<float>> up_and_down(int seg_x, int seg_y){
		float x, y, z, theta, phi, r, theta_v, phi_v;
		vector<vector<float>> my_vert_vals;
		float radial_rotation = 2*PI/seg_x;
			phi = 1.0*PI/seg_y;
			theta = 2.0*PI/seg_x;
			r = .5;
			for(int j = 0; j < seg_x; j++){
				for(int i = 0; i < seg_y; i++){
					theta_v = theta * i;
					phi_v = phi * j;
					x = r * cos(theta_v) * sin(phi_v);
					y = r * sin(theta_v) * sin(phi_v);
					z = r * cos(phi_v);
					// z_normal = z+.05;
					// cout << "z is " << z << endl;
					my_vert_vals.push_back(vector<float>{x, z, y, (float)1.0});
					//this->my_normals.push_back(vector<float>{x, z, y, (float)1.0});
					//this->my_normals.push_back(vector<float>{normal_x, z_normal, normal_y, (float)1.0});

				}
			}
		return my_vert_vals;
	}

		void setNormal(float x1, float y1, float z1, float x2, float y2, float z2,
                    float x3, float y3, float z3) {

    float v1x, v1y, v1z;
    float v2x, v2y, v2z;
    float cx, cy, cz;

    // find vector between x2 and x1
    v1x = x1 - x2;
    v1y = y1 - y2;
    v1z = z1 - z2;

    // find vector between x3 and x2
    v2x = x2 - x3;
    v2y = y2 - y3;
    v2z = z2 - z3;

    // cross product v1xv2

    cx = v1y * v2z - v1z * v2y;
    cy = v1z * v2x - v1x * v2z;
    cz = v1x * v2y - v1y * v2x;

    // normalize

    float length = sqrt(cx * cx + cy * cy + cz * cz);
    cx           = cx / length;
    cy           = cy / length;
    cz           = cz / length;

    glNormal3f(cx, cy, cz);
}
};

#endif