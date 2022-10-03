#ifndef PYRAMID_H
#define PYRAMID_H

#include "Shape.h"
#include <vector>
using namespace std;

class Pyramid : public Shape {
public:
	Pyramid() {};
	~Pyramid() {};
    vector<vector<float>> base_points;
    vector<vector<float>> front_points;

    vector<vector<float>> my_normals;

	OBJ_TYPE getType() {
		return SHAPE_SPECIAL1;
	}

	void draw(int v) {
            int segment_x  = this->m_segmentsX;
			int segment_y = this->m_segmentsY;

            vector<vector<vector<float>>> sides = get_all_vertices(segment_x, segment_y);

            glBegin(GL_TRIANGLES);
            // glNormal3f(0.0f, 0.0f, -0.5f);

            // draw base
            for (int i = 0; i < sides[0].size(); i++) {
                // setNormal(sides[0][i][0], sides[0][i][1], sides[0][i][2]);
                cout << "(" << sides[0][i][0] << "," << sides[0][i][1] << "," << sides[0][i][2] << ")" << '\n';
                
                // one vertex of a triangle
                glVertex3f(sides[0][i][0], sides[0][i][1], sides[0][i][2]);
            }





            glEnd();
	};


	void drawNormal() {
	};

private:
    // returns vector of 5 vectors, each containing the points of one side of
    // pyramid (base, front, back, left, right)
    vector<vector<vector<float>>> get_all_vertices(int seg_x, int seg_y){
        float segmentsX_length = 1.0f / seg_x;
        float segmentsY_length = 1.0f / seg_y;
        float x, y, z, slope, z_step;
        vector<float> top_point = {0, 0.5f, 0};

        // creating vertices for base (y is constant)
        vector<vector<float>> base_points = {}; // {x, y, z, w}

        for (int i = 0; i < seg_y+1; i++){
            z = -0.5f + segmentsY_length*i;
            
            for (int j = 0; j < seg_x+1; j++){
                x = -0.5f + segmentsX_length*j;

                // cout << "(" << x << "," << -0.5f << "," << z << ")" << '\n';

                base_points.push_back({x, -0.5f, z, 1.0f, 1.0f});
            }
        }

        // creating vertices for front side

        vector<vector<float>> front_points = {}; // {x, y, z, w}
        for (int i = 0; i < seg_y+1; i++){
            segmentsX_length = (1.0f - (i / seg_y));
            y = -0.5f + segmentsY_length*i;

            for (int j = 0; j < seg_x+1; j++){
                if (i == seg_y){
                    front_points.push_back(top_point);
                }
                else {
                    front_points.push_back({-0.5f + segmentsX_length*j, y, -0.5f + ((0.5f/seg_y) * i), 1.0f});
                }
            }
        }



    return {base_points, front_points};
    }
};

#endif