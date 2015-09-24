
class Point : public Vector
{
public:
	double k;
	static double ka;//环境光的反射率
	static double kd;//漫反射反射率
	static double ks;//镜面反射反射率
	Point(){}
	Point(double r, double s, double t):Vector(r,s,t){
		k = 1;
	}

	Point(double p[3]):Vector(p[0],p[1],p[2]){
		k = p[3];
	}

	void setMaterial(double a, double d, double s){
		ka = a;
		ks = s;
		kd = d;
	}

	double getKA(){
		return ka;
	}
	double getKD(){
		return kd;
	}
	double getKS(){
		return ks;
	}


	Point& operator =(const Vector& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Point& operator *=(double t){
		x *= t;
		y *= t;
		z *= t;
		k = 1;
		return *this;
	}

	Point& operator /=(double t){
		double f = 1.0f/t;
		x *= f;
		y *= f;
		z *= f;
		k = 1;
		return *this;
	}

	Point& operator &=(const Vector& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		k = 1;
		return *this;
	}

	Point operator -(void) const{
		return (Point(-x,-y,-z));
	}

	Point operator +(const Vector& v)const{
		return (Point(x+v.x, y+v.y, z+v.z));
	}

	Vector operator -(const Point& p)const{
		return (Vector(x-p.x,y-p.y,z-p.z));
	}

	Point operator *(double t)const{
		return (Point(x*t, y*t, z*t));
	}

	Point operator/(double t)const{
		double f = 1.0f/t;
		return (Point(x*f, y*f, z*f));
	}

	Point operator &(const Vector& v)const{
		return (Point(x*v.x, y*v.y, z*v.z));
	}

	void printPoint(){
		printf("Point: %f, %f, %f\n",x, y, z);
	}

	double distanceTo(const Vector& v)const{
		 return sqrtf((v - *this)*(v - *this));
	}
};

inline Point operator *(double t, const Point& p){
	return Point(t*p.x , t*p.y, t*p.z);
}

double Point::ka = 0;
double Point::kd = 0;
double Point::ks = 0;
