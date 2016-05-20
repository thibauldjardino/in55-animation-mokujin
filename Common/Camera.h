#ifndef Camera_h
#define Camera_h

#include "Vectors.h"
#include "Types.h"
#include "Quaternion.h"
#include "GlFramework.h"
#include <math.h>

class Camera 
{
    public:
		void translate (float32 x, float32 y, float32 z);
		void translateX (float32 shift);
		void translateY (float32 shift);
		void translateZ (float32 shift);
	   
		void rotate (float32 angle, float32 ax, float32 ay, float32 az);
		void rotateX (float32 angle);
		void rotateY (float32 angle);
		void rotateZ (float32 angle);
	   
		const GLMatrix& getViewMatrix();
	   
		void setPosition(const Vec3 & v1);
		void setOrientation(const Quaternion & q1);
		void setAspectRatio (float32 ar);
		void setPlanes (float32 near, float32 far);
		void setFOV (float32 angle);
	   
		const GLMatrix& getProjectionMatrix();
		
    private:
		void buildViewMatrix();
		void buildProjectionMatrix();
	
		Vec3 m_position;
		Quaternion m_orientation;
		GLMatrix m_ViewMatrix;
		GLMatrix m_ProjectionMatrix;
		
		float32 aspectRatio;
		float32 nearPlane;
		float32 farPlane;
		float32 fov;
};

#endif