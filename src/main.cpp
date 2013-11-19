// reading a text file
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "mesh.h"

using namespace std;

int main (int argc, char *argv[]) {

  Mesh out_mesh;

  Mesh::makeFlower(atof(argv[1]), 20, 20*atof(argv[2]), 2, 0.4, 0.6, 0.9, 1.3*atof(argv[3]), 0.7, &out_mesh);
  //Mesh::makeDune(5,4,10,&out_mesh);

  out_mesh.write(argv[4]);

  return 0;
} 