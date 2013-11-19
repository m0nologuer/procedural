#include <Eigen/Core>
#include <Eigen/Geometry>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#define CONST_PI 3.1415926
#define res 20
#define RANDOM (rand()%100)*0.01

using namespace std;

class Mesh
{
  Eigen::Vector3d* vertexBuffer;
  Eigen::Vector2d* texBuffer;
  int* indexBuffer;

  int vertex_count;
  int face_count;

public:

  Mesh();
  ~Mesh();

  void boundingBox(double &x, double &x_max, double &y, double &y_max, double &z, double &z_max);
  void boundingBoxSize(double &x, double &y, double &z);
  void translate(Eigen::Vector3d translation);
  void rotate(Eigen::Matrix3d rotation, Eigen::Vector3d about);
  void addXYNoise(double freq, double ampl);

  void write(char* out_obj_file);
  void writeSTL(char* out_file);

  static void meshFromFile(char* filename, Mesh* out_mesh);
  static void concatenate(Mesh* meshArray, int mesh_count, Mesh* out_mesh);

  static void makeDune(double intensity, double twistedness, int sample_rate, Mesh* out_mesh);xw
  static void makeCactus(double thickness, Eigen::Vector3d center, Mesh* out_mesh);
  static void makePetal(double width, double height, double pointiness, Mesh* out_mesh);
  static void makeFlower(int count, double width, double height, double center, double spacing, double pointiness_min, 
    double pointiness_max, double non_flatness, double curvature, Mesh* out_mesh);
};
