#include<fstream>
class Matrix{
public:
double m[4][4];

	Matrix(){
		for(int i = 0; i<4; i++)
			for(int j = 0; j<4; j++)
				if(i==j)
					m[i][j] = 1;
				else m[i][j] = 0;
	}

	Matrix(double t[4][4]){
		memcpy(m,t,sizeof(m));
	}

	Matrix(const Matrix &T){
		memcpy(m,T.m,sizeof(m));
	}

	void init(){
		for(int i = 0; i<4; i++)
			for(int j = 0; j<4; j++)
				if(i==j)
					m[i][j] = 1;
				else m[i][j] = 0;
	}

	Matrix operator *(const Matrix &T) const{
		double temp[4][4];
		memset(temp,0,sizeof(temp));
		
		int i,j,k;
		for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
		for(k = 0; k < 4; k++)
			temp[i][j] += m[i][k] * T.m[k][j];
		
		return Matrix(temp);
	}

	void operator =(const Matrix &T){
		for(int i = 0; i<4; i++)
			for(int j = 0; j<4; j++)
				m[i][j] = T.m[i][j];
	}

	Point operator *(const Point &in) const{
		double out[4];
		out[0] = m[0][0]*in.x +m[0][1]*in.y +m[0][2]*in.z +m[0][3]*in.k;
		out[1] = m[1][0]*in.x +m[1][1]*in.y +m[1][2]*in.z +m[1][3]*in.k;
		out[2] = m[2][0]*in.x +m[2][1]*in.y +m[2][2]*in.z +m[2][3]*in.k;
		out[3] = m[3][0]*in.x +m[3][1]*in.y +m[3][2]*in.z +m[3][3]*in.k;
		return (Point(out));
	}

	void printMatrix(){
		for(int i = 0; i<4; i++)
			printf("%5.10f %5.10f %5.10f %5.10f\n",m[i][0],m[i][1],m[i][2],m[i][3]);
		printf("\n");
	}
};
