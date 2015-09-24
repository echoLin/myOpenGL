
class Vector
{
public:
	double x;
	double y;
	double z;

	Vector(){}

	Vector(double r, double s, double t){
		x = r;
		y = s;
		z = t;
	}

	Vector(double b[]){
		x = b[0];
		y = b[1];
		z = b[2];
	}

	Vector& set(double r, double s, double t){
		x = r;
		y = s;
		z = t;
		return *this;
	}

	double& operator [](long k){
		return ((&x)[k]);
	}

	const double& operator [](long k) const{
		return ((&x)[k]);
	}

	Vector& operator =(const Vector& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector& operator +=(const Vector& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector& operator -=(const Vector& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector& operator *=(double t){
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	Vector& operator /=(double t){
		double f = 1.0f/t;
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Vector& operator %=(const Vector& v){
		double r,s;
		r = y*v.z - z*v.y;
		s = z*v.x - x*v.z;
		z = x*v.y - y*v.x;
		x = r;
		y = s;
		return *this;
	}

	Vector& operator &=(const Vector& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector operator -(void) const{
		return (Vector(-x,-y,-z));
	}

	Vector operator +(const Vector& v)const{
		return (Vector(x+v.x, y+v.y, z+v.z));
	}

	Vector operator -(const Vector& v)const{
		return (Vector(x-v.x,y-v.y,z-v.z));
	}

	Vector operator *(double t)const{
		return (Vector(x*t, y*t, z*t));
	}

	Vector operator/(double t)const{
		double f = 1.0f/t;
		return (Vector(x*f, y*f, z*f));
	}

	double operator *(const Vector& v)const{
		return x*v.x + y*v.y + z*v.z;
	}

	Vector operator %(const Vector& v)const{
		return (Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x));
	}

	Vector operator &(const Vector& v)const{
		return (Vector(x*v.x, y*v.y, z*v.z));
	}

	bool operator ==(const Vector& v)const{
		return ((x==v.x)&&(y == v.y)&&(z==v.z));
	}

	bool operator !=(const Vector& v)const{
		return ((x!=v.x)||(y!=v.y)||(z!=v.z));
	}

	Vector& Normalize(void){
		return (*this /= sqrtf(x*x + y*y + z*z));
	}

};

inline Vector operator *(double t, const Vector & v){
	return (Vector(t*v.x, t* v.y, t*v.z));
}

inline double Dot(const Vector& v1, const Vector& v2){
	return (v1*v2);
}

inline Vector Cross(const Vector& v1, const Vector& v2){
	return v1%v2;
}

inline double Magnitude(const Vector& v){
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

inline double InverseMag(const Vector& v){
	return 1.0f/sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

inline double SquaredMag(const Vector& v){
	return (v.x*v.x + v.y*v.y + v.z*v.z);
}

// v1 x v2
inline Vector Mult(const Vector& v1, const Vector& v2){
	return (Vector(v1.y*v2.z-v2.y*v1.z, v1.z*v2.x-v2.z*v1.x, v1.x*v2.y-v2.x*v1.y));
}
