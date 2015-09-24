#include<stdio.h>
#include<math.h>
#include"Vector.h"
#include"Point.h"
#include"Plane.h"
#include"Matrix.h"
#include"ViewPort.h"
#include"Bmp.h"
#include"Light.h"
#include"myOpenGL.h"
#include"PlyLoader.h"

myOpenGL mygl;

void drawPly();
void drawLine();

void main(){
	drawPly();
	//drawLine();
}

void drawPly(){
	CPLYLoader ply;
	//读取Ply数据
	ply.LoadModel("lizhenxiout-repaired.ply");

	mygl.ClearColor(255,255,255);
	mygl.PenColor(255,0,0);

	mygl.ViewPort(0,0,640,480);
	mygl.MatrixMode(MY_PROJECTION);
	mygl.LoadIdentity();
	mygl.Ortho(-1000,1000,-1000,1000,-1000,1000);

	mygl.MatrixMode(MY_MODELVIEW);
	mygl.LoadIdentity();
	//mygl.RotateY(70);
	//mygl.Translate(500,0,500);
	//mygl.Scale(0.5,0.5,0.5);
	
	//设置材质
	Point::ka = 0.15;
	Point::ks = 0.8;
	Point::kd = 0.15;
	//设置光照
	Vector eye(1,1,0);
	Vector lightPos(1,1,1);
	//color(blue,green,red);
	Color lightColor = {0,255,0};
	//mygl.setLight(eye,lightPos,lightColor,10,10,1);
	
	for(int i=0; i<ply.m_totalConnectedPoints*3; i+=3){
		Point p(ply.mp_vertexXYZ[i],ply.mp_vertexXYZ[i+1],ply.mp_vertexXYZ[i+2]);
		mygl.DrawPexil(p);
	}
	mygl.bmp.SaveBmp("plyBmp.bmp");
}

void drawLine(){
	//red,green,blue
	mygl.ClearColor(0,0,0);

	mygl.MatrixMode(MY_PROJECTION);
	mygl.LoadIdentity();
	mygl.Ortho(-500,500,-500,500,-500,500);

	mygl.MatrixMode(MY_MODELVIEW);
	mygl.LoadIdentity();

	mygl.ViewPort(0,0,640,480);

	//color(blue,green,red);
	Color color1 = {255,0,0};
	Color color2 = {0.0,255};
	Point p1(-100,300,-100);
	Point p2(300,300,300);

	mygl.DrawLine(p1, p2, color1, color2);
	mygl.bmp.SaveBmp("line.bmp");

}
