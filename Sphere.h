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
	std::vector<std::vector<float>> my_normals_vector;

	OBJ_TYPE getType() {
		return SHAPE_SPHERE;
	}

	void draw(int v) {
		this->my_normals.clear();
		this->my_normals_vector.clear();
		this->my_points.clear();
			int segment_x  = this->m_segmentsX;
			int segment_y = this->m_segmentsY;
			// if(my_points.empty()){
			vector<vector<float>> my_points_t = up_and_down(segment_x, segment_y);
			for(int p = 0; p < segment_y; p++){
				my_points_t.push_back(my_points_t[p]);
				my_normals_vector.push_back(my_normals[p]);
			}
			my_points = my_points_t;
			glBegin(GL_TRIANGLES);
			glEnable(GL_NORMALIZE);

			for(int i = 0; i < segment_x; i++){
				for(int p = 0; p < segment_y-1; p++){
						//render each square (made up of two triangles)
						int pnt_one_idx = i*segment_y+p;
						int pnt_two_idx = i*segment_y+p+1;
						int pnt_three_idx = i*segment_y+p+segment_y;
						int pnt_four_idx = i*segment_y+p+1+segment_y;
						std::vector<float> val_1_n = my_normals_vector[pnt_one_idx];
						std::vector<float> val_1 = my_points[pnt_one_idx];
						std::vector<float> val_2_n = my_normals_vector[pnt_two_idx];
						std::vector<float> val_2 = my_points[pnt_two_idx];
						std::vector<float> val_3_n = my_normals_vector[pnt_three_idx];
						std::vector<float> val_3 = my_points[pnt_three_idx];
						std::vector<float> val_4_n = my_normals_vector[pnt_four_idx];
						std::vector<float> val_4 = my_points[pnt_four_idx];

						if(p == 0){
						// glVertex3f(val_1[0], val_1[1], val_1[2]);
						// glVertex3f(val_2[0], val_2[1], val_2[2]);
						// glVertex3f(val_3[0], val_3[1], val_3[2]);

						// glVertex3f(val_1[0], -.5, val_1[2]);
						// glVertex3f(0, -.5, 0);
						// glVertex3f(val_3[0], -.5, val_3[2]);

						// glVertex3f(val_3[0], val_3[1], val_3[2]);
						// glVertex3f(val_4[0], val_4[1], val_4[2]);
						// glVertex3f(val_2[0], val_2[1], val_2[2]);
						}


						// base triangle
						if(v){
							normalizeNormal(val_1_n[0], val_1_n[1], val_1_n[2]);
							glVertex3f(val_1[0], val_1[1], val_1[2]);
							normalizeNormal(val_3_n[0], val_3_n[1], val_3_n[2]);
							glVertex3f(val_3[0], val_3[1], val_3[2]);
							normalizeNormal(val_4_n[0], val_4_n[1], val_4_n[2]);
							glVertex3f(val_4[0], val_4[1], val_4[2]);			

							normalizeNormal(val_4_n[0], val_4_n[1], val_4_n[2]);
							glVertex3f(val_4[0], val_4[1], val_4[2]);
							normalizeNormal(val_2_n[0], val_2_n[1], val_2_n[2]);
							glVertex3f(val_2[0], val_2[1], val_2[2]);
							normalizeNormal(val_1_n[0], val_1_n[1], val_1_n[2]);
							glVertex3f(val_1[0], val_1[1], val_1[2]);


						}else{

						setNormal(val_4[0], val_4[1], val_4[2],val_3[0], val_3[1], val_3[2], val_1[0], val_1[1], val_1[2]);
						glVertex3f(val_4[0], val_4[1], val_4[2]);
						glVertex3f(val_3[0], val_3[1], val_3[2]);
						glVertex3f(val_1[0], val_1[1], val_1[2]);
						
						setNormal(val_1[0], val_1[1], val_1[2], val_2[0], val_2[1], val_2[2], val_4[0], val_4[1], val_4[2]);
						glVertex3f(val_1[0], val_1[1], val_1[2]);
						glVertex3f(val_2[0], val_2[1], val_2[2]);
						glVertex3f(val_4[0], val_4[1], val_4[2]);
						
						}
						
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
			r = .5f;
			for(int j = 0; j < seg_x; j++){
				for(int i = 0; i < seg_y; i++){
					theta_v = theta * j;
					phi_v = phi * i;
					x = r * cos(theta_v) * sin(phi_v);
					y = r * sin(theta_v) * sin(phi_v);
					z = r * cos(phi_v);
					// z_normal = z+.05;
					// cout << "z is " << z << endl;
					my_vert_vals.push_back(vector<float>{x, z, y, (float)1.0});
					this->my_normals.push_back(vector<float>{x, z, y, (float)1.0});
					this->my_normals.push_back(vector<float>{x+.1f, z+.1f, y+.1f, (float)1.0});
					this->my_normals_vector.push_back(vector<float>{x+.1f, z+.1f, y+.1f, (float)1.0});
					//this->my_normals.push_back(vector<float>{x, z, y, (float)1.0});
					//this->my_normals.push_back(vector<float>{normal_x, z_normal, normal_y, (float)1.0});

				}
			}
		return my_vert_vals;
	}

	
};

#endif