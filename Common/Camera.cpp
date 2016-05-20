//*****************************************************************************
//
// Class: Camera
// Author: Hamza JAFFALI
// Version: 1.0
// Last update: 2016-04-29
//
//*****************************************************************************


#include "Camera.h"

/** Default constructor.
 * Initializes the camera to canonic basis
 */
Camera::Camera() {
	
	this->m_position = new Vec3(0,0,0);
	this->m_orientation = new Quaternion(0,0,0,1);
	this->m_ViewMatrix.setIdentity();
	this->m_ProjectionMatrix.setIdentity();
	this->aspectRatio = 1; //?
	this->nearPlane = 0; //?
	this->farPlane = 1; //?
	this->fov = 0; //?
}

/**
 * 
 */
void Camera::translate (float32 x, float32 y, float32 z) {
	
	this->translateX(x);
	this->translateY(y);
	this->translateZ(z);
}

void Camera::translateX (float32 shift)  {
	
	Quaternion *axis = new Quaternion(0,1,0,0);
	Quaternion *translation = this->m_orientation*axis*shift;
	
	Vec3 transVect = new Vec3(translation.x,translation.y,translation.z);
	
	this->m_position += transVect;
}

void Camera::translateY (float32 shift)  {
	
	Quaternion axis = new Quaternion(0,0,1,0);
	Quaternion translation = this->m_orientation*axis*shift;
	
	Vec3 transVect = new Vec3(translation.x,translation.y,translation.z);
	
	this->m_position += transVect;
	
}

void Camera::translateZ (float32 shift)  {
	
	Quaternion axis = new Quaternion(0,0,0,1);
	Quaternion translation = this->m_orientation*axis*shift;
	
	Vec3 transVect = new Vec3(translation.x,translation.y,translation.z);
	
	this->m_position += transVect;
	
}

void Camera::rotate (float32 angle, float32 ax, float32 ay, float32 az) {
	
	Quaternion rotation = new Quaternion();
	rotation.setFromAxis(angle,ax,ay,az);
	
	this->m_orientation = rotation*this->m_orientation;	
}

void Camera::rotateX (float32 angle)  {
	
	this->rotate(angle,1,0,0);
}

void Camera::rotateY (float32 angle)  {
	
	this->rotate(angle,0,1,0);
}

void Camera::rotateZ (float32 angle)  {
	
	this->rotate(angle,0,0,1);
}


const GLMatrix& Camera::getViewMatrix() {
	//� verifier
	return this->m_ViewMatrix;
}

void Camera::setPosition(const Vec3 & v1) {
	
	this->m_position = new Vec3(v1.x,v1.y,v1.z);
}

void Camera::setOrientation(const Quaternion & q1) {
	
	this->m_orientation = new Quaternion(q1.w,q1.x,q1.y,q1.z);
}

void Camera::setAspectRatio (float32 ar) {
	
	this->aspectRatio = ar;
}

void Camera::setPlanes (float32 near, float32 far) {
	
	this->nearPlane = near;
	this->farPlane = far;
}
	
void Camera::setFOV (float32 angle) {
	
	this->fov = angle;
}

const GLMatrix& Camera::getProjectionMatrix() {
	//� verifier
	return this->m_ProjectionMatrix;
}

void Camera::buildViewMatrix() {
	
	Vec3 axis3 = new Vec3(this->m_orientation.x,this->m_orientation.y,this->m_orientation.z);

	Vec3 axis2 = new Vec3(axis1.y,-axis1.x,0);
	
	Vec3 axis1 = new Vec3(this->m_orientation.x,this->m_orientation.y,this->m_orientation.z);
	
	this->m_ViewMatrix.setIdentity();
	
	this->m_ViewMatrix.data[0] = axis1.x;
	this->m_ViewMatrix.data[1] = axis1.y;
	this->m_ViewMatrix.data[2] = axis1.z;
	this->m_ViewMatrix.data[3] = 0.0f;
	this->m_ViewMatrix.data[4] = axis2.x;
	this->m_ViewMatrix.data[5] = axis2.y;
	this->m_ViewMatrix.data[6] = axis2.z;
	this->m_ViewMatrix.data[7] = 0.0f;
	
	this->m_ViewMatrix.data[8] = axis3.x;
	this->m_ViewMatrix.data[9] = axis3.y;
	this->m_ViewMatrix.data[10] = axis3.z;
	this->m_ViewMatrix.data[11] = 0.0f;
	
	this->m_ViewMatrix.data[12] = -(axis1.x*m_position.x + axis2.x*m_position.y + axis3.x*m_position.z);
	this->m_ViewMatrix.data[13] = -(axis1.y*m_position.x + axis2.y*m_position.y + axis3.y*m_position.z);
	this->m_ViewMatrix.data[14] = -(axis1.z*m_position.x + axis2.z*m_position.y + axis3.z*m_position.z);
	this->m_ViewMatrix.data[15] = 1.0f;	
}

void Camera::buildProjectionMatrix() {
	
	float32 right = this->nearPlane * tan(this->fov/2.0f);
	float32 left = -right;
	float32 top = this->aspectRatio*right;
	float32 bottom = this->aspectRatio*left;
	
	this->m_ProjectionMatrix.setIdentity();
	
	this->m_ProjectionMatrix.data[0] = 2*this->nearPlane/(right-left);
	this->m_ProjectionMatrix.data[5] = 2*this->nearPlane/(top-bottom);
	this->m_ProjectionMatrix.data[8] = (right+left)/(right-left);
	this->m_ProjectionMatrix.data[9] = (top+bottom)/(top-bottom);
	this->m_ProjectionMatrix.data[10] = -(this->farPlane+this->nearPlane)/(this->farPlane-this->nearPlane);
	this->m_ProjectionMatrix.data[11] = -1.0f;
	this->m_ProjectionMatrix.data[14] = -2*(this->farPlane*this->nearPlane)/(this->farPlane-this->nearPlane);
	this->m_ProjectionMatrix.data[15] = 0.0f;
}