#ifndef PLYREADER_H_
#define PLYREADER_H_
#include <iostream>
using namespace std;

struct SModelData{
	Vector vecFaceTriangles;
	Color vecFaceTriangleColors;
	Vector vecNormals;
	int iTotalConnectedTriangles;
};

class CPLYLoader{
public:
	CPLYLoader();
	int LoadModel(char *filename);
	void DrawPoints();

	float* mp_vertexXYZ;
	float* mp_vertexNorm;
	float* mp_vertexRGB;
	int* mp_triangle;
	int m_totalConnectedQuads;
	int m_totalConnectedPoints;
	int m_totalFaces;
	SModelData m_ModelData;
};

CPLYLoader::CPLYLoader(){
	this -> m_totalConnectedQuads = 0;
	this -> m_totalConnectedPoints = 0;
	m_ModelData.iTotalConnectedTriangles = 0;
}

int CPLYLoader::LoadModel(char* filename){
	printf("Loading %s...\n",filename);
	char* pch = strstr(filename,".ply");
	if(pch != NULL){
		FILE* file = fopen(filename,"r");
		if(!file){
			printf("load PLY file %s failed\n",filename);
			return false;
		}
		fseek(file,0,SEEK_END);
		long fileSize = ftell(file);

		try{
			mp_vertexXYZ = (float*) malloc(ftell(file));
			mp_vertexNorm = (float*) malloc(ftell(file));
			mp_vertexRGB = (float*) malloc(ftell(file));
			mp_triangle = (int*) malloc(ftell(file));
		}
		catch(char* ){return -1;}

		if(mp_vertexXYZ == NULL) return -1;
		if(mp_vertexNorm == NULL) return -2;
		if(mp_vertexNorm == NULL) return -3;
		fseek(file,0,SEEK_SET);

		if(file){
			int i=0;
			int temp = 0;
			int quads_index = 0;
			int triangle_index =0;
			int normal_index = 0;
			int colorIndex = 0;
			char buffer[1000];

			fgets(buffer,300,file);

			while(strncmp("element vertex", buffer, strlen("element vertex"))!= 0)
				fgets(buffer,300,file);
			strcpy(buffer,buffer+strlen("element vertex"));
			sscanf(buffer,"%i", &this->m_totalConnectedPoints);
			printf("%d",m_totalConnectedPoints);

			fseek(file,0,SEEK_SET);
			while(strncmp("element face", buffer, strlen("element face"))!=0)
				fgets(buffer,300,file);
			strcpy(buffer,buffer+strlen("element face"));
			sscanf(buffer,"%i", &this->m_totalFaces);
			printf("\n%d",m_totalFaces);

			while(strncmp("end_header", buffer, strlen("end_header"))!=0)
				fgets(buffer,300,file);

			i=0;
			/*
			for(int iterator = 0; iterator < this->m_totalConnectedPoints;iterator++){
				char tmp[1];
				fgets(buffer,300,file);
				sscanf(buffer, "%f %f %f %f %f %f %f %c %f %f %f", &mp_vertexXYZ[i],
					&mp_vertexXYZ [i+1], &mp_vertexXYZ[i+2], &mp_vertexNorm[i],
					&mp_vertexNorm[i+1], &mp_vertexNorm[i+2], &mp_vertexRGB[i],
					&mp_vertexRGB [i+1], &mp_vertexRGB[i+2]);
				i+=3;
			}
			*/
			for(int iterator = 0; iterator < this->m_totalConnectedPoints;iterator++){
				char tmp[1];
				fgets(buffer,300,file);
				sscanf(buffer, "%f %f %f %f %f %f %f", &mp_vertexXYZ[i],
					&mp_vertexXYZ [i+1], &mp_vertexXYZ[i+2], &mp_vertexNorm[i],
					&mp_vertexNorm[i+1], &mp_vertexNorm[i+2]);
				mp_vertexRGB[i] = mp_vertexRGB[i+1] = mp_vertexRGB[i+2] = 200;
				i+=3;
			}

			i=0;

			for(int iterator = 0; iterator < this->m_totalFaces; iterator++){
				fgets(buffer,300,file);
				if(buffer[0] == '3'){
					int vertex1 = 0, vertex2 = 0, vertex3 = 0;
					//buffer[0]=' ';
					sscanf(buffer,"%d %d %d %d", &vertex1, &mp_triangle[i], &mp_triangle[i+1], &mp_triangle[i+2]);

					/* m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex1]);
				     m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex1+1]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex1+2]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex2]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex2+1]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex2+2]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex3]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex3+1]);
					 m_ModelData.vecFaceTriangles.push_back( mp_vertexXYZ[3*vertex3+2]);

					 
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex1]  / 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex1+1]/ 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex1+2]/ 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex2]  / 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex2+1]/ 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex2+2]/ 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex3]  / 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex3+1]/ 255.0f);
					 m_ModelData.vecFaceTriangleColors.push_back( mp_vertexRGB[3*vertex3+2]/ 255.0f);
					 
 
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex1]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex1+1]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex1+2]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex2]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex2+1]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex2+2]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex3]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex3+1]);
					 m_ModelData.vecNormals.push_back( mp_vertexNorm[3*vertex3+2]);
					 */

					 triangle_index += 9;
					 m_ModelData.iTotalConnectedTriangles += 3;
			 }
 
 
		 i += 3;
		}
 
			  fclose(file);
			  printf("%s Loaded!\n",filename);
    
			}
 
			  else 
			{ 
			  printf("File can't be opened\n"); 
			}
		}	
		else 
		{
		printf("File does not have a .PLY extension. ");    
	    }   

		  return 0;
}
			

#endif
