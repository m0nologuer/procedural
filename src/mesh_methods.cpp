#include "mesh.h"

void Mesh::addXYNoise(double freq, double ampl){
	double offset = (rand()%1000)*0.001;
	for (int i = 0; i < vertex_count; ++i)
	{
		vertexBuffer[i](2) += (sin(vertexBuffer[i](0)*freq+offset)+cos(vertexBuffer[i](1)*freq+offset))*ampl;
	}
}
void Mesh::makeCactus(double thickness, Eigen::Vector3d center, Mesh* out_mesh){

}
void Mesh::makeDune(double intensity, double twistedness, int sample_rate, Mesh* out_mesh){
	
	out_mesh->vertex_count = res*res;
	out_mesh->face_count =  (res-1)*(res-1)*2;

	out_mesh->vertexBuffer = new Eigen::Vector3d[res*res];
	out_mesh->indexBuffer = new int[(res-1)*(res-1)*6];

	double points[res*res];
	for (int i = 0; i < res*res; ++i)
		points[i] = RANDOM*intensity;

	int k = 0;
	for (int i = 0; i < res; ++i)
		for (int j = 0; j < res; ++j)
		{
			int a = i/sample_rate;
			int b = j/sample_rate;

			double x = (i%sample_rate)/(double)sample_rate;
			double y = (j%sample_rate)/(double)sample_rate;

			out_mesh->vertexBuffer[k] = Eigen::Vector3d(i,j,0);
			out_mesh->vertexBuffer[k](2) += (x*points[a*res+b] + (1-x)*points[a*res+b+1])*y;
			out_mesh->vertexBuffer[k](2) += (x*points[(a+1)*res+b] + (1-x)*points[(a+1)*res+b+1])*(1-y);
			k++;
		}

	k = 0;
	for (int i = 0; i < res-1; ++i)
		for (int j = 0; j < res-1; ++j)
		{
			int next_i = (i+1)%res;

			out_mesh->indexBuffer[k*6] = i*res+j+1;
			out_mesh->indexBuffer[k*6+1] = i*res+j+1+1;
			out_mesh->indexBuffer[k*6+2] = next_i*res+j+1+1;
			out_mesh->indexBuffer[k*6+3] = i*res+j+1;
			out_mesh->indexBuffer[k*6+4] = next_i*res+j+1+1;
			out_mesh->indexBuffer[k*6+5] = next_i*res+j+1;
			k++;
		}

}

void Mesh::makeFlower(int count, double width, double height, double center, double spacing, double pointiness_min, 
    double pointiness_max, double non_flatness, double curvature, Mesh* out_mesh)
{
  Mesh petals[count];
  for (int i = 0; i < count; ++i)
  {
    Mesh::makePetal(width,height,RANDOM*(pointiness_max-pointiness_min)+pointiness_min,&petals[i]);
    petals[i].addXYNoise(0.5+RANDOM*0.1,0.4+RANDOM*0.1);
    Eigen::Vector3d offset = Eigen::Vector3d(-sin(i*spacing)*(height+center), cos(i*spacing)*(height+center),0);
    petals[i].rotate(Eigen::AngleAxisd(i*spacing, Eigen::Vector3d(0,0,1))*Eigen::Scaling(1.0), Eigen::Vector3d(0,0,0));
    petals[i].rotate(Eigen::AngleAxisd((RANDOM*(1-curvature)+curvature)*non_flatness,Eigen::Vector3d(cos(i*spacing), sin(i*spacing),0))*Eigen::Scaling(1.0),-offset);
    petals[i].translate(offset);
  }
  Mesh::concatenate(petals, count, out_mesh);

}
void Mesh::makePetal(double width, double height, double pointiness, Mesh* out_mesh){
	out_mesh->vertex_count = res*res;
	out_mesh->face_count = (res-1)*res*2;

	out_mesh->vertexBuffer = new Eigen::Vector3d[res*res];
	out_mesh->indexBuffer = new int[res*(res-1)*6];

	int k = 0;
	for (int i = 0; i < res; ++i)
		for (int j = 0; j < res; ++j)
		{
			double x = (double)j*CONST_PI/(res-1);
			double y = (double)i*2*CONST_PI/res;
			double pointiness_scale = pointiness+x*(1-pointiness)/(CONST_PI);
			out_mesh->vertexBuffer[k] = Eigen::Vector3d(width*cos(y)*sin(x*x/CONST_PI),height*sin(y)*sin(x)*pointiness_scale ,cos(x) );
			k++;
		}

	k = 0;
	for (int i = 0; i < res; ++i)
		for (int j = 0; j < res-1; ++j)
		{
			int next_i = (i+1)%res;

			out_mesh->indexBuffer[k*6] = i*res+j+1;
			out_mesh->indexBuffer[k*6+1] = i*res+j+1+1;
			out_mesh->indexBuffer[k*6+2] = next_i*res+j+1+1;
			out_mesh->indexBuffer[k*6+3] = i*res+j+1;
			out_mesh->indexBuffer[k*6+4] = next_i*res+j+1+1;
			out_mesh->indexBuffer[k*6+5] = next_i*res+j+1;

			k++;
		}
}