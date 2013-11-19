// reading a text file
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "mesh.h"

using namespace std;

int main (int argc, char *argv[]) {

  Mesh out_mesh;

  //Mesh::makeFlower(40, 20, 20, 2, 0.4, 0.6, 0.9, 1.3, 0.7, &out_mesh);
  Mesh::makeDune(5,4,10,&out_mesh);

  out_mesh.write("out.obj");

  return 0;
} 