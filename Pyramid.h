#ifndef PYRAMID_H
#define PYRAMID_H

#include "Shape.h"
#include <vector>
using namespace std;

class Pyramid : public Shape {
public:
	Pyramid() {};
	~Pyramid() {};

    vector<vector<float>> my_normals; // i vertex, i+1 is normal vector

	OBJ_TYPE getType() {
		return SHAPE_SPECIAL1;
	}

	void draw(int v) {
        int segment_x  = this->m_segmentsX;
        int segment_y = this->m_segmentsY;
        int skip_counter = 1;
        this->my_normals.clear();

        vector<vector<vector<float>>> sides = get_all_vertices(segment_x, segment_y);

        glBegin(GL_TRIANGLES);
        // glNormal3f(0.0f, 0.0f, -0.5f);

        // draw base
        for (int i = 0; i < sides[0].size() - (segment_x+1) - 1; i++) {
            // skips vertices that are on the right edge
            if (skip_counter != 0 && skip_counter % (segment_x+1) != 0) {
                
                // bottom-right triangle of square
                setNormal(sides[0][i+1][0], sides[0][i+1][1], sides[0][i+1][2], sides[0][i][0], sides[0][i][1], sides[0][i][2], sides[0][i+segment_x+2][0], sides[0][i+segment_x+2][1], sides[0][i+segment_x+2][2]);
                
                glVertex3f(sides[0][i+segment_x+2][0], sides[0][i+segment_x+2][1], sides[0][i+segment_x+2][2]);
                glVertex3f(sides[0][i][0], sides[0][i][1], sides[0][i][2]);
                glVertex3f(sides[0][i+1][0], sides[0][i+1][1], sides[0][i+1][2]);

                // top-left triangle of square
                setNormal(sides[0][i][0], sides[0][i][1], sides[0][i][2], sides[0][i+segment_x+2][0], sides[0][i+segment_x+2][1], sides[0][i+segment_x+2][2], sides[0][i+segment_x+1][0], sides[0][i+segment_x+1][1], sides[0][i+segment_x+1][2]);

                glVertex3f(sides[0][i][0], sides[0][i][1], sides[0][i][2]);
                glVertex3f(sides[0][i+segment_x+2][0], sides[0][i+segment_x+2][1], sides[0][i+segment_x+2][2]);
                glVertex3f(sides[0][i+segment_x+1][0], sides[0][i+segment_x+1][1], sides[0][i+segment_x+1][2]);
            }
            skip_counter++;
        }

        // draw front face
        skip_counter = 1;
        for (int i = 0; i < sides[1].size() - (segment_x+1) - 1; i++) {
            // skips vertices that are on the right edge
            if (skip_counter != 0 && skip_counter % (segment_x+1) != 0) {
                // bottom-right triangle of square
                setNormal(sides[1][i][0], sides[1][i][1], sides[1][i][2],
                          sides[1][i+1][0], sides[1][i+1][1], sides[1][i+1][2],
                          sides[1][i+segment_x+2][0], sides[1][i+segment_x+2][1], sides[1][i+segment_x+2][2]);

                glVertex3f(sides[1][i][0], sides[1][i][1], sides[1][i][2]);
                glVertex3f(sides[1][i+1][0], sides[1][i+1][1], sides[1][i+1][2]);
                glVertex3f(sides[1][i+segment_x+2][0], sides[1][i+segment_x+2][1], sides[1][i+segment_x+2][2]);

                // top-left triangle of square
                setNormal(sides[1][i][0], sides[1][i][1], sides[1][i][2],
                          sides[1][i+segment_x+2][0], sides[1][i+segment_x+2][1], sides[1][i+segment_x+2][2],
                          sides[1][i+segment_x+1][0], sides[1][i+segment_x+1][1], sides[1][i+segment_x+1][2]);

                glVertex3f(sides[1][i][0], sides[1][i][1], sides[1][i][2]);
                glVertex3f(sides[1][i+segment_x+2][0], sides[1][i+segment_x+2][1], sides[1][i+segment_x+2][2]);
                glVertex3f(sides[1][i+segment_x+1][0], sides[1][i+segment_x+1][1], sides[1][i+segment_x+1][2]);
            }
            skip_counter++;
        }

        // draw back face
        skip_counter = 1;
        for (int i = 0; i < sides[2].size() - (segment_x+1) - 1; i++) {
            // skips vertices that are on the right edge
            if (skip_counter != 0 && skip_counter % (segment_x+1) != 0) {

                // bottom-right triangle of square
                setNormal(sides[2][i][0], sides[2][i][1], sides[2][i][2],
                          sides[2][i+1][0], sides[2][i+1][1], sides[2][i+1][2],
                          sides[2][i+segment_x+2][0], sides[2][i+segment_x+2][1], sides[2][i+segment_x+2][2]);

                glVertex3f(sides[2][i+segment_x+2][0], sides[2][i+segment_x+2][1], sides[2][i+segment_x+2][2]);
                glVertex3f(sides[2][i+1][0], sides[2][i+1][1], sides[2][i+1][2]);
                glVertex3f(sides[2][i][0], sides[2][i][1], sides[2][i][2]);

                // top-left triangle of square
                setNormal(sides[2][i][0], sides[2][i][1], sides[2][i][2],
                          sides[2][i+segment_x+2][0], sides[2][i+segment_x+2][1], sides[2][i+segment_x+2][2],
                          sides[2][i+segment_x+1][0], sides[2][i+segment_x+1][1], sides[2][i+segment_x+1][2]);

                glVertex3f(sides[2][i+segment_x+1][0], sides[2][i+segment_x+1][1], sides[2][i+segment_x+1][2]);
                glVertex3f(sides[2][i+segment_x+2][0], sides[2][i+segment_x+2][1], sides[2][i+segment_x+2][2]);
                glVertex3f(sides[2][i][0], sides[2][i][1], sides[2][i][2]);
            }
            skip_counter++;
        }

        // draw left side
        skip_counter = 1;
        for (int i = 0; i < sides[3].size() - (segment_x+1) - 1; i++) {
            // skips vertices that are on the right edge
            if (skip_counter != 0 && skip_counter % (segment_x+1) != 0) {

                // bottom-right triangle of square
                setNormal(sides[3][i+segment_x+2][0], sides[3][i+segment_x+2][1], sides[3][i+segment_x+2][2],sides[3][i+1][0], sides[3][i+1][1], sides[3][i+1][2], sides[3][i][0], sides[3][i][1], sides[3][i][2]);

                glVertex3f(sides[3][i][0], sides[3][i][1], sides[3][i][2]);
                glVertex3f(sides[3][i+1][0], sides[3][i+1][1], sides[3][i+1][2]);
                glVertex3f(sides[3][i+segment_x+2][0], sides[3][i+segment_x+2][1], sides[3][i+segment_x+2][2]);

                // top-left triangle of square
                setNormal(sides[3][i+segment_x+1][0], sides[3][i+segment_x+1][1], sides[3][i+segment_x+1][2], sides[3][i+segment_x+2][0], sides[3][i+segment_x+2][1], sides[3][i+segment_x+2][2], sides[3][i][0], sides[3][i][1], sides[3][i][2]);

                glVertex3f(sides[3][i][0], sides[3][i][1], sides[3][i][2]);
                glVertex3f(sides[3][i+segment_x+2][0], sides[3][i+segment_x+2][1], sides[3][i+segment_x+2][2]);
                glVertex3f(sides[3][i+segment_x+1][0], sides[3][i+segment_x+1][1], sides[3][i+segment_x+1][2]);
            }
            skip_counter++;
        }

        // draw right side
        skip_counter = 1;
        for (int i = 0; i < sides[4].size() - (segment_x+1) - 1; i++) {
            // skips vertices that are on the right edge
            if (skip_counter != 0 && skip_counter % (segment_x+1) != 0) {

                // bottom-right triangle of square
                setNormal(sides[4][i][0], sides[4][i][1], sides[4][i][2],
                          sides[4][i+1][0], sides[4][i+1][1], sides[4][i+1][2],
                          sides[4][i+segment_x+2][0], sides[4][i+segment_x+2][1], sides[4][i+segment_x+2][2]);

                glVertex3f(sides[4][i+segment_x+2][0], sides[4][i+segment_x+2][1], sides[4][i+segment_x+2][2]);
                glVertex3f(sides[4][i+1][0], sides[4][i+1][1], sides[4][i+1][2]);
                glVertex3f(sides[4][i][0], sides[4][i][1], sides[4][i][2]);
                
                // top-left triangle of square
                setNormal(sides[4][i][0], sides[4][i][1], sides[4][i][2],
                          sides[4][i+segment_x+2][0], sides[4][i+segment_x+2][1], sides[4][i+segment_x+2][2],
                          sides[4][i+segment_x+1][0], sides[4][i+segment_x+1][1], sides[4][i+segment_x+1][2]);

                glVertex3f(sides[4][i+segment_x+1][0], sides[4][i+segment_x+1][1], sides[4][i+segment_x+1][2]);
                glVertex3f(sides[4][i+segment_x+2][0], sides[4][i+segment_x+2][1], sides[4][i+segment_x+2][2]);
                glVertex3f(sides[4][i][0], sides[4][i][1], sides[4][i][2]);   
            }
            skip_counter++;
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
    // returns vector of 5 vectors, each containing the points of one side of
    // pyramid (base, front, back, left, right)
    vector<vector<vector<float>>> get_all_vertices(int seg_x, int seg_y){
        float segmentsX_length = 1.0f / seg_x;
        float segmentsY_length = 1.0f / seg_y;
        float x, y, z, slope, z_step, start, segmentsX_step, d_x, d_y, d_z;
        vector<float> top_point = {0, 0.5f, 0};

        // creating vertices for base (y is constant)
        vector<vector<float>> base_points = {}; // {x, y, z, w}

        for (int i = 0; i < seg_y+1; i++){
            z = -0.5f + segmentsY_length*i;
            
            for (int j = 0; j < seg_x+1; j++){
                x = -0.5f + segmentsX_length*j;

                base_points.push_back({x, -0.5f, z, 1.0f, 1.0f});

                this -> my_normals.push_back({x, -0.5f, z, 1.0f, 1.0f});
                this -> my_normals.push_back({x, -0.55f, z, 1.0f, 1.0f});
            }
        }

        // creating vertices for front side
        vector<vector<float>> front_points = {}; // {x, y, z, w}
        float y_norm;

        for (int i = 0; i < seg_y+1; i++){
            segmentsX_length = (1.0f - ((float) i / (float) seg_y));
            segmentsX_step = segmentsX_length / (float) seg_x;
            start = -0.5f + ((1.0f - segmentsX_length) / 2.0f);
            
            y = -0.5f + segmentsY_length * (float) i;
            z = 0.5f - ((0.5f/seg_y) * i);

            for (int j = 0; j < seg_x+1; j++){
                if (i == seg_y){
                    front_points.push_back(top_point);

                    this -> my_normals.push_back(top_point);
                    this -> my_normals.push_back({0, 0.5f, 0.1f, 1.0f});
                }
                else {
                    x = start + segmentsX_step * (float) j;
                    front_points.push_back({x, y, z, 1.0f});

                    this -> my_normals.push_back({x, y, z, 1.0f});
                    this -> my_normals.push_back({x, y+0.1f, z+0.1f, 1.0f});
                }
            }
        }

        // creating vertices for back side
        vector<vector<float>> back_points = {}; // {x, y, z, w}

        for (int i = 0; i < seg_y+1; i++){
            segmentsX_length = (1.0f - ((float) i / (float) seg_y));
            segmentsX_step = segmentsX_length / (float) seg_x;
            start = -0.5f + ((1.0f - segmentsX_length) / 2.0f);

            y = -0.5f + segmentsY_length*i;
            z = -0.5f + ((0.5f/seg_y) * i);

            for (int j = 0; j < seg_x+1; j++){
                if (i == seg_y){
                    back_points.push_back(top_point);

                    this -> my_normals.push_back(top_point);
                    this -> my_normals.push_back({0, 0.5f, -0.1f, 1.0f});
                }
                else {
                    x = start + segmentsX_step * (float) j;
                    back_points.push_back({x, y, z, 1.0f});

                    this -> my_normals.push_back({x, y, z, 1.0f});
                    this -> my_normals.push_back({x, y+0.1f, z-0.1f, 1.0f});
                }
            }
        }

        // creating vertices for left side (x and z switch)
        vector<vector<float>> left_points = {}; // {x, y, z, w}

        for (int i = 0; i < seg_y+1; i++){
            segmentsX_length = (1.0f - ((float) i / (float) seg_y));
            segmentsX_step = segmentsX_length / (float) seg_x;
            start = -0.5f + ((1.0f - segmentsX_length) / 2.0f);
            
            y = -0.5f + segmentsY_length*i;
            z = -0.5f + ((0.5f/seg_y) * i);

            for (int j = 0; j < seg_x+1; j++){
                if (i == seg_y){
                    left_points.push_back(top_point);

                    this -> my_normals.push_back(top_point);
                    this -> my_normals.push_back({-0.1f, 0.5f, 0, 1.0f});
                }
                else {
                    x = start + segmentsX_step * (float) j;
                    left_points.push_back({z, y, x, 1.0f});

                    this -> my_normals.push_back({z, y, x, 1.0f});
                    this -> my_normals.push_back({z-0.1f, y+0.1f, x, 1.0f});
                }
            }
        }

        // creating vertices for right side
        vector<vector<float>> right_points = {}; // {x, y, z, w}

        for (int i = 0; i < seg_y+1; i++){
            segmentsX_length = (1.0f - ((float) i / (float) seg_y));
            segmentsX_step = segmentsX_length / (float) seg_x;
            start = -0.5f + ((1.0f - segmentsX_length) / 2.0f);
            
            y = -0.5f + segmentsY_length*i;
            z = 0.5f - ((0.5f/seg_y) * i);

            for (int j = 0; j < seg_x+1; j++){
                if (i == seg_y){
                    right_points.push_back(top_point);

                    this -> my_normals.push_back(top_point);
                    this -> my_normals.push_back({0.1f, 0.5f, 0, 1.0f});
                }
                else {
                    x = start + segmentsX_step * (float) j;
                    right_points.push_back({z, y, x, 1.0f});

                    this -> my_normals.push_back({z, y, x, 1.0f});
                    this -> my_normals.push_back({z+0.1f, y+0.1f, x, 1.0f});
                }
            }
        }

        return {base_points, front_points, back_points, left_points, right_points};
    }


};

#endif