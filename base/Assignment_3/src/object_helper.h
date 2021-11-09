#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



struct Vertex
{
    float x, y, z;
};

struct Normal
{
    float x, y, z;
};

struct Face
{
    int numIndex;
    int v1Index;
    int v2Index;
    int v3Index;
    Normal normal;
};

struct Mesh
{
    int numVertices{};
    int numFaces{};
    int numEdges{};
    char mType[3] = {};
    vector<Face> faces;
    vector<Vertex> vertices;
};

Mesh* LoadMesh(const string& path)
{
    ifstream input(path, ios::in);
    if (!input)
        return nullptr;


    Mesh* mesh = new Mesh;
    string line;
    stringstream ss;

    input >> mesh->mType;
    input >> mesh->numVertices >> mesh->numFaces >> mesh->numEdges;
    getline(input, line);

    int lineIndex = 0;

    while (getline(input, line))
    {
        ss.clear();
        ss.str(line);
        if (lineIndex < mesh->numVertices)
        {
            Vertex vertex{};
            ss >> vertex.x >> vertex.y >> vertex.z;
            mesh->vertices.push_back(vertex);
        }
        else
        {
            Face face{};
            ss >> face.numIndex >> face.v1Index >> face.v2Index >> face.v3Index;
            mesh->faces.push_back(face);
        }
        lineIndex++;
    }

    return mesh;
}