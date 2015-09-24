
class Plane{//平面方程：a(X-x)+b(Y-y)+c(Z-z)+d=0
public:
	//(a,b,c)为平面法向量
	double a;
	double b;
	double c;
	double d;
	//(x,y,z)为平面上的一个点
	double x;
	double y;
	double z;

	int flag;//法向量为正，flag = 1; 法向量为负，flag = -1

	Plane(){};

	Plane(double x, double y, double z ,double m, int f){
		a = x;
		b = y;
		c = z;
		d = m;
		flag = f;
	}

	//（x1,y1,z1）在平面上 （x2,y2,z2）不在平面上 （x2-x1,y2-y1,z2-z1）垂直于平面
	Plane(double x1, double y1, double z1,
		double x2, double y2, double z2){
			//点和法向量
			a = x2-x1;
			b = y2-y1;
			c = z2-z1;
			d = -(a*x1 + b*y1 + c*z1);
			if(a<0 || b<0 || c<0)
				flag = -1;
			else flag = 1;
	}

	//计算点是否在平面内，根据flag的值判断是在裁剪体内还是在裁剪体外 并返回判断结果
	int operator * (const Point& v)const{
		int result = a*v.x + b*v.y + c*v.z + d;
		// 0 在平面上 1 在裁剪体内 -1 在裁剪体外
		if(flag == 1){
			if(result==0)
				return 0;
			else if(result>0)
				return 1;
			else 
				return -1;
		}else if(flag == -1){
			if(result == 0)
				return 0;
			else if(result >0)
				return -1;
			else 
				return 1;
		}
	}

	//根据两个点算出这两个点连成的直线与平面的交点
	Vector getCrossPoint(const Point& v, const Point& u){
		Vector nL = u - v;
		Vector nP(a,b,c);
		Vector vP(x,y,z);
		double t = ((vP-v)*nP)/(nP*nL);
		return (Vector(v[0]+(nL[0]*t), v[1]+(nL[1]*t), v[2]+(nL[3]*t)));
	}
};
