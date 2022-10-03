#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include <vector>
#include "math.h"
using namespace std;

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};
	std::vector<std::vector<float>> my_points;
	std::vector<std::vector<float>> my_normals;
	std::vector<std::vector<float>> my_normals_vector;

	OBJ_TYPE getType() {
		return SHAPE_CONE;
	}

	void draw(int v) {

			int segment_x  = this->m_segmentsX;
			int segment_y = this->m_segmentsY;

			float x1 = 0;
			float y1 = 1;
			float z1 = 0;
			float w1 = 0;

			this->my_points.clear();
			this->my_normals.clear();
			this->my_normals_vector.clear();
			// if(my_points.empty()){
			vector<vector<float>> my_points_t = up_and_down(segment_x, segment_y);
			for(int p = 0; p < segment_y; p++){
				my_points_t.push_back(my_points_t[p]);
				my_normals_vector.push_back(my_normals_vector[p]);
			}
			my_points = my_points_t;
			int index = 0;

			glBegin(GL_TRIANGLES);
			glEnable(GL_NORMALIZE);
			index = 0;

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


						if(v){
							normalizeNormal(val_1_n[0], val_1_n[1], val_1_n[2]);
							glVertex3f(val_1[0], val_1[1], val_1[2]);
							normalizeNormal(val_3_n[0], val_3_n[1], val_3_n[2]);
							glVertex3f(val_3[0], val_3[1], val_3[2]);
							normalizeNormal(val_4_n[0], val_4_n[1], val_4_n[2]);
							glVertex3f(val_4[0], val_4[1], val_4[2]);			

							normalizeNormal(val_1_n[0], val_1_n[1], val_1_n[2]);
							glVertex3f(val_1[0], val_1[1], val_1[2]);
							normalizeNormal(val_2_n[0], val_2_n[1], val_2_n[2]);
							glVertex3f(val_2[0], val_2[1], val_2[2]);
							normalizeNormal(val_4_n[0], val_4_n[1], val_4_n[2]);
							glVertex3f(val_4[0], val_4[1], val_4[2]);
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
				//adding the extra normals
				this->my_normals.push_back(pnt_one);
				this->my_normals.push_back(vector<float>{pnt_one[0], pnt_one[1]-(float).1, pnt_one[2]});
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
		glBegin(GL_LINES);
		for(int i = 0; i < this->my_normals.size(); i+=2){
			vector<float> f_val = this->my_normals[i];
			vector<float> s_val = this->my_normals[i+1];
			glVertex3f(f_val[0], f_val[1], f_val[2]);
			glVertex3f(s_val[0], s_val[1], s_val[2]);
		}
		glEnd();

	};

private:
		std::vector<std::vector<float>> up_and_down(int seg_x, int seg_y){
		float x, y, z, r, z_step, slope, normal_r, normal_x, normal_y, z_normal, slope_normal;
		vector<vector<float>> my_vert_vals;
		float radial_rotation = 2*PI/seg_x;
		vector<vector<float>> rotation_matrix = {{cos(radial_rotation), -sin(radial_rotation), 0},{sin(radial_rotation), cos(radial_rotation), 0},{0, 0, 1}};
		z_step = 1.0/(seg_y-1);
		slope = .5;
		slope_normal =.6;
			for(int j = 0; j < seg_x; j++){
				for(int i = 0; i < seg_y; i++){
					r = -.5 + (slope/(seg_y-1))*i;
					normal_r = r-.1;
					x = r*cos(2*PI* j/seg_x );
					y = r*sin(2*PI* j/seg_x );
					normal_x = normal_r * cos(2*PI* j/seg_x );
					normal_y = normal_r * sin(2*PI* j/seg_x );
					z = -.5 + z_step*i;
					z_normal = z + .06;
					// cout << "z is " << z << endl;
					my_vert_vals.push_back(vector<float>{x, z, y, (float)1.0});
					this->my_normals.push_back(vector<float>{x, z, y, (float)1.0});
					this->my_normals.push_back(vector<float>{normal_x, z_normal, normal_y, (float)1.0});
					this->my_normals_vector.push_back(vector<float>{normal_x, z, normal_y, (float)1.0});

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


// #ifndef CONE_H
// #define CONE_H

// #include <vector>
// #include <map>
// #include <set>
// #include <cmath>
// #include "Shape.h"

// using namespace std;

// class Cone : public Shape {
// public:
// 	Cone() {};
// 	~Cone() {};

// 	OBJ_TYPE getType() {
// 		return SHAPE_CONE;
// 	}

// 	void draw(int v) {
// 		float m_segmentsX_angle = 2 * PI / m_segmentsX;
// 		float m_segmentsY_length = 1.0f / m_segmentsY;

// 		normals_by_vertex.clear();
// 		vector<vector<float>> bottom_points = {};

// 		for (int x_index = 0; x_index < m_segmentsX; x_index++) {
// 			bottom_points.push_back({ 0.0f, -0.5f, 0.0f, 1.0f });
// 			bottom_points.push_back({ 0.5f * cos(m_segmentsX_angle * x_index), -0.5f, 0.5f * sin(m_segmentsX_angle * x_index), 1.0f });
// 			bottom_points.push_back({ 0.5f * cos(m_segmentsX_angle * (x_index + 1)), -0.5f, 0.5f * sin(m_segmentsX_angle * (x_index + 1)), 1.0f });

// 			normals_by_vertex[{ 0.0f, -0.5f, 0.0f, 1.0f }].insert({ 0.0f, -1.0f, 0.0f });
// 			normals_by_vertex[{ 0.5f * cos(m_segmentsX_angle * x_index), -0.5f, 0.5f * sin(m_segmentsX_angle * x_index), 1.0f }].insert({ 0.0f, -1.0f, 0.0f });
// 			normals_by_vertex[{ 0.5f * cos(m_segmentsX_angle * (x_index + 1)), -0.5f, 0.5f * sin(m_segmentsX_angle * (x_index + 1)), 1.0f }].insert({ 0.0f, -1.0f, 0.0f });
// 		}
// 		normals_by_vertex[{ 0.0f, -0.5f, 0.0f, 1.0f }].insert({ 0.0f, -1.0f, 0.0f });

// 		map<vector<float>, vector<vector<float>>> side_points = {};

// 		for (int x_index = 0; x_index < m_segmentsX; x_index++) {
// 			vector<float> each_side_normal = getNormal(0.5f * cos(m_segmentsX_angle * x_index), -0.5f, 0.5f * sin(m_segmentsX_angle * x_index), 0.0f, 0.5f, 0.0f, 0.5f * cos(m_segmentsX_angle * (x_index + 1)), -0.5f, 0.5f * sin(m_segmentsX_angle * (x_index + 1)));
// 			vector<vector<float>> each_side_points = {};

// 			for (int y_index = 0; y_index < m_segmentsY; y_index++) {
// 				each_side_points.push_back({ (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * x_index), -0.5f + m_segmentsY_length * y_index, (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * x_index), 1.0f });
// 				each_side_points.push_back({ (float)(m_segmentsY - (y_index + 1)) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * x_index), -0.5f + m_segmentsY_length * (y_index + 1), (float)(m_segmentsY - (y_index + 1)) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * x_index), 1.0f });
// 				each_side_points.push_back({ (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * (x_index + 1)), -0.5f + m_segmentsY_length * y_index, (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * (x_index + 1)), 1.0f });
				

// 				each_side_points.push_back({ (float)(m_segmentsY - (y_index + 1)) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * x_index), -0.5f + m_segmentsY_length * (y_index + 1), (float)(m_segmentsY - (y_index + 1)) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * x_index), 1.0f });
// 				each_side_points.push_back({ (float)(m_segmentsY - (y_index + 1)) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * (x_index + 1)), -0.5f + m_segmentsY_length * (y_index + 1), (float)(m_segmentsY - (y_index + 1)) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * (x_index + 1)), 1.0f });
// 				each_side_points.push_back({ (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * (x_index + 1)), -0.5f + m_segmentsY_length * y_index, (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * (x_index + 1)), 1.0f });
				
// 				// TODO: need to calc the correct side normals
// 				normals_by_vertex[{  (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * cos(m_segmentsX_angle * x_index), -0.5f + m_segmentsY_length * y_index, (float)(m_segmentsY - y_index) / (float)m_segmentsY * 0.5f * sin(m_segmentsX_angle * x_index)}].insert(each_side_normal);
// 			}
// 			side_points[each_side_normal] = each_side_points;
// 		}

// 		glBegin(GL_TRIANGLES);
// 		glNormal3f(0.0f, -1.0f, 0.0f);
// 		for (int index = 0; index < bottom_points.size(); index++) {
// 			glVertex3f(bottom_points[index][0], bottom_points[index][1], bottom_points[index][2]);
// 		}

// 		for (map<vector<float>, vector<vector<float>>>::iterator iter = side_points.begin(); iter != side_points.end(); iter++) {
// 			glNormal3f(iter->first[0], iter->first[1], iter->first[2]);

// 			for (int index = 0; index < iter->second.size(); index++) {
// 				glVertex3f(iter->second[index][0], iter->second[index][1], iter->second[index][2]);
// 			}
// 		}
// 		glEnd();
// 	};

// 	void drawNormal() {
// 		float length_factor = 0.1f;

// 		glBegin(GL_LINES);
// 		glColor3f(1.0, 0.0, 0.0);
// 		for (map<vector<float>, set<vector<float>>>::iterator iter = normals_by_vertex.begin(); iter != normals_by_vertex.end(); iter++) {
// 			for (auto it = iter->second.cbegin(); it != iter->second.cend(); it++) {
// 				glVertex3f(iter->first[0], iter->first[1], iter->first[2]);
// 				glVertex3f(iter->first[0] + (*it)[0] * length_factor, iter->first[1] + (*it)[1] * length_factor, iter->first[2] + (*it)[2] * length_factor);
// 			}
// 		}
// 		glEnd();
// 	};

// private:
// 	map<vector<float>, set<vector<float>>> normals_by_vertex;
// };

// #endif

#endif