#include "Model.h"
#include <fstream>
#include <sstream>

Model::Model()
{

}

int Model::numTriangles()
{
	return triangles.size();
}

Triangle3D Model::operator[](int i)
{
	return triangles[i];
}

void Model::transform(Matrix4 matrix)
{
    for (int i = 0; i < numTriangles(); i++) {
        if (triangles[i].shouldDraw == true) {
            triangles[i].transform(matrix);
        }
    }
}

void Model::readfromObj(string filepath, Color pFillColor)
{
    vector<Vector4>verticies;
    ifstream file(filepath);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            vector<string> words;
            istringstream s(line);
            string word;
            while (getline(s, word, ' '))
            {
                words.push_back(word);
            }
            if (words[0] == "v")
            {
                Vector4 v(atof(words[1].c_str()), atof(words[2].c_str()), atof(words[3].c_str()), 1.0f);
                verticies.push_back(v);
            }
            else if (words[0] == "f")
            {
                if (words.size() == 4)
                {
                    Triangle3D t(verticies[atoi(words[1].c_str()) - 1], verticies[atoi(words[2].c_str()) - 1], verticies[atoi(words[3].c_str()) - 1], pFillColor, pFillColor, pFillColor);
                    triangles.push_back(t);
                }
                else if (words.size() == 5)
                {
                    Triangle3D t1(verticies[atoi(words[1].c_str()) - 1], verticies[atoi(words[2].c_str()) - 1], verticies[atoi(words[3].c_str()) - 1], pFillColor, pFillColor, pFillColor);
                    Triangle3D t2(verticies[atoi(words[1].c_str()) - 1], verticies[atoi(words[3].c_str()) - 1], verticies[atoi(words[4].c_str()) - 1], pFillColor, pFillColor, pFillColor);
                    triangles.push_back(t1);
                    triangles.push_back(t2);
                }
            }
        }
    }
}

void Model::homogenize()
{
    for (int i = 0; i < numTriangles(); i++)
    {
        triangles[i].v1 = triangles[i].v1 * (1.0 / triangles[i].v1.z);
        triangles[i].v2 = triangles[i].v2 * (1.0 / triangles[i].v2.z);
        triangles[i].v3 = triangles[i].v3 * (1.0 / triangles[i].v3.z);
    }
}
 
void Model::performBackfaceCulling(Vector4 eye, Vector4 spot)
{
    for (int i = 0; i < numTriangles(); i++)
    {
        Vector4 look = spot - eye;
        look.normalize();
        
        Vector4 normal = (triangles[i].v2 - triangles[i].v3).cross(triangles[i].v1 - triangles[i].v2);
        normal.normalize(); 

        if (normal.dot(look) > 0)
        {
            triangles[i].shouldDraw = false;
        }
        else
        {
            triangles[i].shouldDraw = true;
        }
        
    }
}