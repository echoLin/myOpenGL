#define PI 3.141592653
#define MY_PROJECTION 1
#define MY_MODELVIEW 2
#define Width 640
#define Height 480

class myOpenGL{
public:
	Bmp bmp;
	Matrix* CTM;
	Matrix ModelView;
	Matrix Projection;
	ViewPort View;
	Color clearColor;
	Color penColor;
	Light light;
	Plane plane[6];//left right top bottom front back

	//基本函数
	myOpenGL();
	void MatrixMode(int mode);
	void LoadIdentity();
	void ClearColor(BYTE r, BYTE g, BYTE b);
	void PenColor(BYTE r, BYTE g, BYTE b);

	//视图矩阵变换
	void Translate(double x, double y, double z);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	void Rotate(double angle, double nx, double ny, double nz);
	void Scale(double nx, double ny, double nz);
	void LookAt(double ex, double ey, double ez, double dx, double dy, double dz, double ux, double uy, double uz);
	
	//投影矩阵变换
	void Frustum(double left,double right,double bottom,double top,double near,double far);
	void Perspective(double fovy, double aspect, double zNear, double zFar);
	void Ortho(double left,double right,double bottom,double top,double near,double far);
	
	//视口
	void ViewPort(int x,int y,int w,int h);

	//裁剪
	int Clip();

	//设置光源，计算点的坐标和phong颜色
	void setLight(Vector eye, Vector ligt, Color c, double la, double ls, double ld);
	Point Project(Point v);
	Color PhongColor(Point p);

	//绘图函数
	void DrawPexil(Point p);
	void DrawLine(Point p1, Point p2, Color color1, Color color2);
};


/**
*	基本函数
*    @author echoLin
*/
myOpenGL::myOpenGL(){
	MatrixMode(MY_PROJECTION);
	LoadIdentity();
	MatrixMode(MY_MODELVIEW);
	LoadIdentity();
	View.init();
}

void myOpenGL::MatrixMode(int mode){
	switch(mode){
	case MY_PROJECTION:
		CTM = &Projection;
		break;
	case MY_MODELVIEW:
		CTM = &ModelView;
		break;
	}
}

void myOpenGL::LoadIdentity(){
	CTM->init();
}

void myOpenGL::ClearColor(BYTE r, BYTE g, BYTE b){
	clearColor.rgbRed = r;
	clearColor.rgbGreen = g;
	clearColor.rgbBlue = b;
	bmp.setClearColor(clearColor);
}

void myOpenGL::PenColor(BYTE r, BYTE g, BYTE b){
	penColor.rgbRed = r;
	penColor.rgbGreen = g;
	penColor.rgbBlue = b;
}

/**
*	视图矩阵变换
*	@author echoLin
*/
void myOpenGL::Translate(double x, double y, double z){
	double t[4][4];
	memset(t,0,sizeof(t));
	for(int i = 0; i<4; i++)
		t[i][i] = 1;
	t[0][3] += x;//m12
	t[1][3] += y;//m14
	t[2][3] += z;//m15
	Matrix T(t);
	*CTM = (*CTM) * T;
}

void myOpenGL::RotateX(double angle){
	angle = PI*angle/180.0f;
	double r[4][4];
	memset(r,0,sizeof(r));
	r[0][0] = 1;
	r[3][3] = 1;
	r[1][1] = cos(angle);
	r[1][2] = -sin(angle);
	r[2][1] = sin(angle);
	r[2][2] = cos(angle);
	Matrix R(r);
	*CTM = (*CTM) * R;
}

void myOpenGL::RotateY(double angle){
	angle = PI*angle/180.0f;
	double r[4][4];
	memset(r,0,sizeof(r));
	r[1][1] = 1;
	r[3][3] = 1;
	r[0][0] = cos(angle);
	r[0][2] = sin(angle);
	r[2][0] = -sin(angle);
	r[2][2] = cos(angle);
	Matrix R(r);
	*CTM = (*CTM) * R;
}

void myOpenGL::RotateZ(double angle){
	angle = PI*angle/180.0f;
	double r[4][4];
	memset(r,0,sizeof(r));
	r[2][2] = 1;
	r[3][3] = 1;
	r[0][0] = cos(angle);
	r[0][1] = -sin(angle);
	r[1][0] = sin(angle);
	r[1][1] = cos(angle);
	Matrix R(r);
	*CTM = (*CTM) * R;
}

void myOpenGL::Rotate(double angle, double nx, double ny, double nz){
	angle = PI*angle/180.0f;
	Vector v(nx,ny,nz);
	Vector n = v.Normalize();
	double d = sqrt(n.y*n.y + n.z*n.z);
	double deltaAngleX = acos(n.z /d )*180.0f/PI;
	double deltaAngleY = -acos(d) * 180.0f/PI;

	RotateX(-deltaAngleX);
	RotateY(-deltaAngleY);
	RotateZ(angle);
	RotateY(deltaAngleY);
	RotateX(deltaAngleX);
}

void myOpenGL::Scale(double nx, double ny, double nz){
	double s[4][4];
	memset(s,0,sizeof(s));
	s[0][0] = 1;
	s[1][1] = 1;
	s[2][2] = 1;
	s[3][3] = 1;
	s[0][0] *= nx;
	s[1][1] *= ny;
	s[2][2] *= nz;

	Matrix S(s);
	*CTM = (*CTM) * S;
}

void myOpenGL::LookAt(double ex, double ey, double ez, double dx, double dy, double dz, double ux, double uy, double uz){
	double b[3]={ux,uy,uz};
	Vector vu(b);
	vu = vu.Normalize();

	b[0] = dx - ex;
	b[1] = dy - ey;
	b[2] = dz - ez;
	Vector n(b);
	n = n.Normalize();

	Vector v;
	v = vu - n*(vu*n)/(n*n);
	v = v.Normalize();
	
	//u = v x n
	Vector u = Mult(u,v);
	u = u.Normalize();

	n = -n;
	u = -u;

	double m[4][4];
	memset(m,0,sizeof(m));
	for(int i = 0; i<3; i++){
		m[0][i] = u[i];
		m[1][i] = v[i];
		m[2][i] = n[i];
		m[3][i] = 0;
	}
	m[0][3] = -ex*u[0] - ey*u[1] - ez*u[2];
	m[1][3] = -ex*v[0] - ey*v[1] - ez*v[2];
	m[2][3] = -ex*n[0] - ey*n[1] - ez*n[2];
	m[3][3] = 1;

	Matrix M(m);
	*CTM = (*CTM) * M;

	//设置light的eyePosition
	light.setEyePosition(ex, ey, ez);
}
	
/**
*	投影矩阵变换
*	@author echoLin
*/
void myOpenGL::Frustum(double left,double right,double bottom,double top,double near,double far){
	double m[4][4];
	memset(m,0,sizeof(m));

	m[0][0] = 2*near / (right - left);
	m[0][2] = (right + left) / (right - left);
	m[1][1] = 2*near / (top - bottom);
	m[1][2] = (top + bottom)/(top-bottom);
	m[2][2] = -(far+near)/(far-near);
	m[2][3] = -2*near * far / (far - near);
	m[3][2] = -1;

	Matrix M(m);
	*CTM = (*CTM) * M;
}

void myOpenGL::Perspective(double fovy, double aspect, double zNear, double zFar){
	double dbFov = fovy * PI / 180.0f;
	double dbTan = tan(dbFov / 2);
	Frustum(-zNear*dbTan*aspect,
		zNear*dbTan*aspect,
		-zNear*dbTan,
		zNear*dbTan,
		zNear,
		zFar);
}

void myOpenGL::Ortho(double left,double right,double bottom,double top,double near,double far){
	double m[4][4];
	memset(m,0,sizeof(m));
	m[0][0] = 2.0f/(right-left);
	m[0][3] = -(right+left)/(right-left);
	m[1][1] = 2/(top-bottom);
	m[1][3] = -(top+bottom)/(top-bottom);
	m[2][2] = -2/(far-near);
	m[2][3] = -(far+near)/(far-near);
	m[3][3] = 1;

	Matrix M(m);
	//M.printMatrix();
	//((*CTM) * M).printMatrix();
	*CTM = (*CTM) * M;
	//CTM->printMatrix();

	plane[0] = Plane(left,bottom,-near,right,bottom,-near);
	plane[1] = Plane(right,bottom,-near,left,bottom,-near);
	plane[2] = Plane(left,top,-near,left,bottom,-near);
	plane[3] = Plane(left,bottom,-near,left,top,-near);
	plane[4] = Plane(left,bottom,-near,left,bottom,-far);
	plane[5] = Plane(left,bottom,-far,left,bottom,-near);

	Point p(0,0,far);
	p = Project(p);
	bmp.setZBuffer(p.z);
}
	
/**
*	视口
*	@author echoLin
*/
void myOpenGL::ViewPort(int x,int y,int w,int h){
	View.set(x,y,w,h);
}


/**
*	设置光源，计算点的坐标和phong颜色
*	@author echoLin
*/
void myOpenGL::setLight(Vector eye, Vector ligt, Color c, double ld, double ls, double la){
	light.setEyePosition(eye);
	light.setLightPosition(ligt);
	light.setLightColor(c);
	light.la = la;
	light.ld = ld;
	light.ls = ls;
}

Point myOpenGL::Project(Point v){
	Point out;
	out = ModelView * v;
	out = Projection * out;
	if(out[3] == 0)
		return NULL;

	for(int i = 0; i<3; i++)
		out[i] /= out[3];

	out = View * out;
	return out;
}

Color myOpenGL::PhongColor(Point p){
	//p 点的坐标；n 点p的法向；light 光源（包括 视点位置，光源位置，光源颜色及其相关光源强度）
	Color color;
	Vector n = p;
	Vector l = Vector(-light.lightPosition.x+p.x,-light.lightPosition.y+p.y,-light.lightPosition.z+p.z);
	l.Normalize();
	n.Normalize();
	light.eyePosition.Normalize();
	float ln = l[0]*n[0] + l[1]*n[1] + l[2]*n[2];
	float r[3] = {2*ln*n[0]-1, 2*ln*n[1]-1, 2*ln*n[2]-1};
	float rv = r[0]*light.eyePosition.x + r[1]*light.eyePosition.y + r[2]*light.eyePosition.z;
	//rv = (float)pow(rv,light.sa);
	if(ln<0.0)
		ln = 0.0;
	if(rv<0.0)
		rv = 0.0;

	color.rgbRed = (p.getKD() * light.ld * ln + p.getKS() * light.ls * rv + p.getKA() * light.la) * light.lightColor.rgbRed;
	color.rgbGreen = (p.getKD() * light.ld * ln + p.getKS() * light.ls * rv + p.getKA() * light.la) * light.lightColor.rgbGreen;
	color.rgbBlue = (p.getKD() * light.ld * ln + p.getKS() * light.ls * rv + p.getKA() * light.la) * light.lightColor.rgbBlue;
	
	color.rgbRed = (color.rgbRed + penColor.rgbRed)>255 ? (color.rgbRed + penColor.rgbRed)%255 : (color.rgbRed + penColor.rgbRed);
	color.rgbGreen = (color.rgbGreen + penColor.rgbGreen)>255 ? (color.rgbGreen + penColor.rgbGreen)%255 : (color.rgbGreen + penColor.rgbGreen);
	color.rgbBlue = (color.rgbBlue + penColor.rgbBlue)>255 ? (color.rgbBlue + penColor.rgbBlue)%255 : (color.rgbBlue + penColor.rgbBlue);
	
	return color;
}


/**
*	裁剪
*	@author echoLin
*/
int myOpenGL::Clip(){
/*
	SVector *p = vList;
	SVector *q = vList;
	for(int i = 0; i<6; i++)//遍历平面
		while(p->next!=NULL){//遍历顶点
			int f = plane[i] * p->v;
			if(f == -1){//p在裁剪体外
				int ff = plane[i] * p->next->v;
				if(ff==0 ||ff==-1){//p->next->v也不在裁剪体内或者刚好在平面内，则删去p而不用求交点
					if(p==vList){
						p=p->next;
						vList = p;
						q = p;
					}else{
						q->next = p->next;
						free(p);
						p = q->next;
					}
				}else{//ff == 1 : 求平面与直线的交点并将该点记录到vList上
					Vector v = plane[i].getCrossPoint(p->v,p->next->v);
					SVector *sv;
					sv->v = v;
					sv->next = p->next;
					free(p);
					q->next = sv;
					q = sv;
					p = sv->next;
				}
			}else{//f == 1 || f == 0 : p在裁剪体内
				q = p;
				p = p->next;
			}
		}
		*/
	return 0;
}

/**
*	绘图函数
*	@author echoLin
*/
void myOpenGL::DrawPexil(Point p){
	//p.printPoint();
	Point pPro = Project(p);
	//pPro.printPoint();
	Color color = PhongColor(p);
	//printf("color: %d, %d, %d\n",color.rgbRed, color.rgbGreen, color.rgbBlue);
	bmp.writeColorBuffer(color,pPro.x, pPro.y, pPro.z);
}
void myOpenGL::DrawLine(Point p1, Point p2, Color color1, Color color2){
	double d = p1.distanceTo(p2);
	double dRed = (double)(color2.rgbRed - color1.rgbRed)/d;
	double dGreen = (double)(color2.rgbGreen - color1.rgbGreen)/d;
	double dBlue = (double)(color2.rgbBlue - color1.rgbBlue)/d;

	printf("dColor: %f %f %f\n",dRed, dGreen, dBlue);
		
	double dx = 1;
	double dy = 1;
	double dz = 1;
	int i=0;
	//判断应该以x递增还是以y递增
	if(abs(p1.x - p2.x) >= abs(p1.y - p2.y)){//x 轴上的间距比较大 以x 递增
		//确定x轴的增量
		if(p2.x - p1.x < 0)
			dx = -1;
		//确定y轴的增量
		dy = (double)(p2.y - p1.y)/(double)abs(p2.x - p1.x);
		dz = (double)(p2.z - p1.z)/(double)abs(p2.x - p1.x);

		//开始绘点
		Point p(p1);
		while(abs(p.x)!=abs(p2.x)){
			penColor.rgbRed = color1.rgbRed + dRed*i;
			penColor.rgbGreen = color1.rgbGreen + dGreen*i;
			penColor.rgbBlue = color1.rgbBlue + dBlue*i;
			//printf("penColor: %d %d %d\n",penColor.rgbRed, penColor.rgbGreen, penColor.rgbBlue);
			
			DrawPexil(p);

			p.x += dx;
			p.y += dy;
			p.z += dz;
			i++;
		}
	}else{// 以y递增
		if(p2.y - p1.y < 0)
			dy = -1;
		//确定y轴的增量
		dx = (double)(p2.x - p1.x)/(double)abs(p2.y - p1.y);
		dz = (double)(p2.z - p1.z)/(double)abs(p2.y - p1.y);

		//开始绘点
		Point p(p1);
		while(abs(p.y)!=abs(p2.y)){
			penColor.rgbRed = color1.rgbRed + dRed*i;
			penColor.rgbGreen = color1.rgbGreen + dGreen*i;
			penColor.rgbBlue = color1.rgbBlue + dBlue*i;
			//printf("penColor: %d %d %d\n",penColor.rgbRed, penColor.rgbGreen, penColor.rgbBlue);
			
			DrawPexil(p);

			p.x += dx;
			p.y += dy;
			p.z += dz;
			i++;
		}
	}

}
