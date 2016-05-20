//*****************************************************************************
//
// Class: Quaternion
// Author: Hamza JAFFALI
// Version: 1.0
// Last update: 2016-04-29
//
//*****************************************************************************


#include "Quaternion.h"

/** Default constructor.
 * Initializes the quaternion to zero
 */
Quaternion::Quaternion() {
	
	this->w = 0.0f;
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

/** Copy constructor.
 * Initializes the quaternion with attributes of the quaternion
 * in parameter
 * Parameter : q, the quaternion to be copied
 */
Quaternion::Quaternion(const Quaternion & q); {
	
	this->w = q.w;
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
	
	//this->normalize();
}

/**
 * 
 */
Quaternion::Quaternion(float32 w2, float32 x2, float32 y2, float32 z2) {
	
	this->w = w2;
    this->x = x2;
    this->y = y2;
    this->z = z2;
}

/**
 * 
 */
Quaternion Quaternion::operator* (const Quaternion & q) {
	
	new_w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
	
	new_x = this->w * q.x + q.w * this->x + this->y * q.z - this->z * q.y;
	
	new_y = this->w * q.y + q.w * this->y + q.x * this->z - q.z * this->x;
	
	new_z = this->w * q.z + q.w * this->z + this->x * q.y - this->y * q.x;

	Quaternion result = new Quaternion(new_w, new_x, new_y, new_z);
	
	// Problème à résoudre ici, si on normalize, quand on fait qr.qp.qr-1 ça normalise le quaternion intermédiaire
	//result->normalize();
	
	return result;
}

/**
 * 
 */
Vec3 Quaternion::operator* (const Vec3 & v) {

	Quaternion point = new Quaternion(0.0f, v.x, v.y, v.z);
	
	Quaternion rotation = new Quaternion(this);
	rotation->normalize
	Quaternion rotation_conjuguate = rotation->conjuguate();
	Quaternion rotated = rotation * point * rotation_conjuguate;
	
	return new Vec3(rotated.x, rotated.y, rotated.z);
}

/**
 * 
 */
Quaternion Quaternion::operator* (float32 f) {
	
	return new Quaternion(this->w*f, this->x*f, this->y*f, this->z*f);
}

/**
 * 
 */
Quaternion& Quaternion::operator*= (const Quaternion & q) {
	
	Quaternion result = this*q;
	result->normalize();
	
	this->set(result.w, result.x, result.y, result.z);
	
	return (*this);
}

/**
 * 
 */
Quaternion Quaternion::operator+ (const Quaternion & q) {
	
	new_w = this->w + q->w;
	
	new_x = this->x + q->x;
	
	new_y = this->y + q->y;
	
	new_z = this->z + q->z;

	Quaternion result = new Quaternion(new_w, new_x, new_y, new_z);
	
	return result;
}

/**
 * 
 */
float32 Quaternion::dot (const Quaternion & q) {
	
	return this->w * q->w + this->x * q->x + this->y * q->y + this->z * q->z;
}

/**
 * 
 */
void Quaternion::set (float32 w, float32 x, float32 y, float32 z) {
	
	this->w = q->w;
    this->x = q->x;
    this->y = q->y;
    this->z = q->z;	
}

/**
 * 
 */
void Quaternion::setFromAxis (float32 angle, float32 ax, float32 ay, float32 az) {
	
	Vec3 axis = new Vec3(ax,ay,az);
	axis->normalize();
	
	this->w = cos(angle/2.0f);
    this->x = sin(angle/2.0f)*axis->x;
    this->y = sin(angle/2.0f)*axis->y;
    this->z = sin(angle/2.0f)*axis->z;	
}

/**
 * 
 */
Quaternion Quaternion::conjuguate () {
	
	return new Quaternion(this->w, -this->x, -this->y, -this->z);
}

/**
 * 
 */
Quaternion slerp (const Quaternion & q1, const Quaternion & q2, float32 t) {
	
	q1.normalize();
	q2.normalize();
	
	Quaternion interpolation;
	
	float32 dotProduct = dot(q1,q2);
	float32 theta = acos(dotProduct);
	float32 sinTheta = sqrt(1- dotProduct*dotProduct);
	
	interpolation = q1*(sin(theta*(1-t))/sinTheta) + q2*(sin(theta*t)/sinTheta);
	
	return interpolation;
}

/**
 * 
 */
void Quaternion::normalize () {
	
	float32 norm = sqrt(this->w*this->w + this->x*this->x + this->y*this->y + this->z*this->z);
	
	if(norm !=0.0f) {
		
		norm=1/norm;
		this->w*=norm;
		this->x*=norm;
		this->y*=norm;
		this->z*=norm;	
	}
	
}

/**
 * We suppose that mat is 4x4 dimension
 */
void Quaternion::setRotationMatrix (float32* mat) {
	
	float32 trace = mat[0] + mat[5] + mat[10];
	float32 new_w;
	float32 new_x;
	float32 new_y;
	float32 new_z;
	
	
	if(trace>0) {
		new_w = sqrt(trace +1)/2.0f;
		new_x = (mat[6] - mat[9])/(4*new_w);
		new_y = (mat[8] - mat[2])/(4*new_w);
		new_z = (mat[1] - mat[4])/(4*new_w);
	} else {
		max = fmaxf(fmaxf(mat[0],mat[5]),mat[10]);
		
		if(max==mat[0]) {
			new_x = sqrt(mat[0] - mat[5] - mat[10] +1)/2.0f;
			new_w = (mat[9] - mat[6])/(4*new_x);
			new_y = (mat[4] + mat[1])/(4*new_x);
			new_z = (mat[8] + mat[2])/(4*new_x);
		} else if (max==mat[5]) {
			new_y = sqrt(mat[5] - mat[0] - mat[10] +1)/2.0f;
			new_w = (mat[2] - mat[8])/(4*new_y);
			new_x = (mat[4] + mat[1])/(4*new_y);
			new_z = (mat[6] + mat[9])/(4*new_y);
		} else {
			new_z = sqrt(mat[10] - mat[0] - mat[5] +1)/2.0f;
			new_w = (mat[4] - mat[1])/(4*new_z);
			new_x = (mat[8] + mat[2])/(4*new_z);
			new_y = (mat[9] + mat[6])/(4*new_z);
		}	
	}
	
	this.set(new_w,new_x,new_y,new_z);
}