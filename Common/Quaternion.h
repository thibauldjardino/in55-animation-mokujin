#ifndef Quaternion_h
#define Quaternion_h

#include "Vectors.h"
#include "Types.h"
#include <math.h>

class Quaternion 
{
    public:
        Quaternion();
		Quaternion(const Quaternion & q);
		Quaternion(float32 w, float32 x, float32 y, float32 z);
		
		Quaternion operator* (const Quaternion & q);
		Vec3 operator* (const Vec3 & v);
		Quaternion operator* (float32 f);
		Quaternion& operator*= (const Quaternion & q);
		Quaternion operator+ (const Quaternion & q);
		
		float32 dot (const Quaternion & q);
		
		void set (float32 w, float32 x, float32 y, float32 z);
		
		void setFromAxis (float32 angle, float32 ax, float32 ay, float32 az);
		
		Quaternion conjuguate ();
		
		Quaternion slerp (const Quaternion & q1, const Quaternion & q2, float32 t);
		
		void normalize ();
		
		void setRotationMatrix (float32* mat);

    private:
	
        float32 w;
        float32 x;
        float32 y;
        float32 z;
};

#endif