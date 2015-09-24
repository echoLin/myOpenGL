class Light{
public:
	Vector eyePosition;
	Vector lightPosition;
	Color lightColor;
	double ld;//漫反射强度
	double ls;//镜面光强度
	double la;//环境光强度
	double sa;//镜面反射的高光系数

	Light(){
		ld = 0;
		ls = 0;
		la = 0;
		sa = 0;
	}

	void setLightColor(Color c){
		lightColor.rgbRed = c.rgbRed;
		lightColor.rgbGreen = c.rgbGreen;
		lightColor.rgbBlue = c.rgbBlue;
	}

	void setEyePosition(double ex, double ey, double ez){
		eyePosition = Vector(ex,ey,ez);
	}

	void setEyePosition(Vector eye){
		eyePosition = eye;
	}

	void setLightPosition(double lx, double ly, double lz){
		lightPosition = Vector(lx, ly, lz);
	}
	
	void setLightPosition(Vector l){
		lightPosition = l;
	}

	void setLD(double d){
		ld = d;
	}

	void setLS(double s){
		ls = s;
	}

	void setLA(double a){
		la = a;
	}

	void setSA(double Sa){
		sa = Sa;
	}

	void setL(double d, double s, double a){
		ld = d;
		ls = s;
		la = a;
	}
};
