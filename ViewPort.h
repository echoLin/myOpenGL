
class ViewPort{
public:
	int view[4];

	ViewPort(){
		 view[0] = 0;
		 view[1] = 0;
		 view[2] = 640;
		 view[3] = 480;
	}

	ViewPort(int x, int y, int m, int n){
		view[0] = x;
		view[1] = y;
		view[2] = m;
		view[3] = n;
	}

	void init(){
		 view[0] = 0;
		 view[1] = 0;
		 view[2] = 640;
		 view[3] = 480;
	}

	void set(int x, int y, int m, int n){
		view[0] = x;
		view[1] = y;
		view[2] = m;
		view[3] = n;
	}

	Point operator *(const Point& p) const{
		double b[3] = {view[0] + (1 + p.x) * view[2] / 2,
			view[1] + (1 + p.y) * view[3] / 2,
			(1 + p.z) / 2};
		return Point(b);
	}
};
