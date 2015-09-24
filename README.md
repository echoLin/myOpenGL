# myOpenGL
This is a library like opengl. It only implements some functions.

Project directory ：

  Bmp.h----------------------class for reading and saving bmp files
  
      void LoadBmp(const char* file)-------------------------read bmp files
      
      void SaveBmp(const char* file)-------------------------save bmp files
      
      void setClearColor(Color color)------------------------set background color
      
      void setZBuffer(double z)------------------------------initialize the value of deep buffer
      
      void writeColorBuffer(Color c, int x, int y, int z)----write pixel's color
      
  Light.h--------------------class for lights
  
  Matrix.h-------------------class for 4x4 matrixs
  
  Plane.h--------------------class for planes
  
  PlyLoader.h----------------class for loading ply files
  
  Point.h--------------------class for points
  
  Vector.h-------------------class for vectors
  
  ViewPort.h-----------------class for 1x4 viewports
  
  myOpenGL.h-----------------class for opengl
  
      void MatrixMode(int mode)-----------------------------------setting what matrix point to CTM
      void LoadIdentity()-----------------------------------------initialize CTM matrix
      void ClearColor(BYTE r, BYTE g, BYTE b)---------------------set background color
      void PenColor((BYTE r, BYTE g, BYTE b)----------------------set pencil color
      void ViewPort(int x, int y, int w, int h)-------------------set viewport
      void Translate(double x, double y, double z)----------------translate
      void RotateX(double angle)----------------------------------rotate angle around x
      void RotateY(double angle)----------------------------------rotate angle around y
      void RotateZ(double angle)----------------------------------rotate angle around z
      void Scale(double nx, double ny, double nz)-----------------scale
      void LookAt(doubel ex, double ey, double ez, double dx double dy, double dz, double ux, double uy, double uz)----translate viewpoint
      void Frustum(double left,double right,double bottom,double top,double near,double far)--------Perspective projection
      void Perspective(double fovy, double aspect, double zNear, double zFar)---------------Perspective projection
      void Ortho(double left,double right,double bottom,double top,double near,double far)------Orthogonal projection
      Color PhongColor(Point p)---------------------calculate the phong color
      Point Project(Point v) ------------------ calculate the location in canvas
  
  main.cpp-------------------test file
