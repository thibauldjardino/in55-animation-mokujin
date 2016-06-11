//*****************************************************************************
//
// Class: Camera
// Author: Hamza JAFFALI
// Version: 1.0
// Last update: 2016-04-29
//
//*****************************************************************************


#include "Camera.h"


/** Constructor.
 * Initializes the camera with position in parameter
 */
Camera::Camera(float32 posX, float32 posY, float32 posZ, float32 lookX, float32 lookY, float32 lookZ ) {
	
    this->m_position = new Vec3(posX,posY,posZ);

    if(posX*posY*posZ==0)
        this->m_forwardOrientation = new Quaternion(0,-15,-15,-15);
    else
        this->m_forwardOrientation = new Quaternion(0,lookX-posX,lookY-posY,lookZ-posZ);
    this->m_upOrientation = new Quaternion(0,lookY-posY,posX-lookX,0);
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
	
    Vec3 *axis3 = new Vec3(this->m_forwardOrientation->x,this->m_forwardOrientation->y,this->m_forwardOrientation->z);

    Vec3 *axis2 = new Vec3(this->m_upOrientation->x,this->m_upOrientation->y,this->m_upOrientation->z);

    Vec3 axis1 = axis2->crossProduct(*axis3);
    axis1.normalize();

    Vec3 translation = axis1*shift;

    (*this->m_position) += translation;
}

void Camera::translateY (float32 shift)  {
	
    Vec3 *axis2 = new Vec3(this->m_upOrientation->x,this->m_upOrientation->y,this->m_upOrientation->z);
    axis2->normalize();

    Vec3 translation = (*axis2)*shift;

    (*this->m_position) += translation;
	
}

void Camera::translateZ (float32 shift)  {
	
    Vec3 *axis3 = new Vec3(this->m_forwardOrientation->x,this->m_forwardOrientation->y,this->m_forwardOrientation->z);
    axis3->normalize();

    Vec3 translation = (*axis3)*shift;

    (*this->m_position) += translation;
}

void Camera::rotate (float32 angle, float32 ax, float32 ay, float32 az) {
	
    Quaternion *rotation = new Quaternion();
    rotation->setFromAxis(angle,ax,ay,az);

    Vec3 *new_forwardOrientation = new Vec3(this->m_forwardOrientation->x,this->m_forwardOrientation->y,this->m_forwardOrientation->z);
    *new_forwardOrientation = (*rotation)*(*new_forwardOrientation);

    Vec3 *new_upOrientation = new Vec3(this->m_upOrientation->x,this->m_upOrientation->y,this->m_upOrientation->z);
    *new_upOrientation = (*rotation)*(*new_upOrientation);

    this->m_forwardOrientation->set(0,new_forwardOrientation->x,new_forwardOrientation->y,new_forwardOrientation->z);
    this->m_upOrientation->set(0,new_upOrientation->x,new_upOrientation->y,new_upOrientation->z);
}

void Camera::rotateX (float32 angle)  {
	
    Vec3 *axisZ = new Vec3(this->m_forwardOrientation->x,this->m_forwardOrientation->y,this->m_forwardOrientation->z);

    Vec3 *axisY = new Vec3(this->m_upOrientation->x,this->m_upOrientation->y,this->m_upOrientation->z);

    Vec3 axisX = axisY->crossProduct(*axisZ);

    this->rotate(angle,axisX.x,axisX.y,axisX.z);
}

void Camera::rotateY (float32 angle)  {
	
    this->rotate(angle,this->m_upOrientation->x,this->m_upOrientation->y,this->m_upOrientation->z);
}

void Camera::rotateZ (float32 angle)  {
	
    this->rotate(angle,this->m_forwardOrientation->x,this->m_forwardOrientation->y,this->m_forwardOrientation->z);
}


const GLMatrix& Camera::getViewMatrix() {
	//à verifier
	return this->m_ViewMatrix;
}

void Camera::setPosition(const Vec3 & v1) {
	
	this->m_position = new Vec3(v1.x,v1.y,v1.z);
}

void Camera::setOrientation(const Quaternion & q1) {
	
    this->m_forwardOrientation = new Quaternion(q1.w,q1.x,q1.y,q1.z);
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
	//à verifier
	return this->m_ProjectionMatrix;
}

void Camera::buildViewMatrix() {
	
    Vec3 *axis3 = new Vec3(this->m_forwardOrientation->x,this->m_forwardOrientation->y,this->m_forwardOrientation->z);

    Vec3 *axis2 = new Vec3(this->m_upOrientation->x,this->m_upOrientation->y,this->m_upOrientation->z);
	
    Vec3 axis1 = axis2->crossProduct(*axis3);

	this->m_ViewMatrix.setIdentity();
	
    this->m_ViewMatrix.data[0] = axis1.x;
    this->m_ViewMatrix.data[1] = axis1.y;
    this->m_ViewMatrix.data[2] = axis1.z;
	this->m_ViewMatrix.data[3] = 0.0f;
    this->m_ViewMatrix.data[4] = axis2->x;
    this->m_ViewMatrix.data[5] = axis2->y;
    this->m_ViewMatrix.data[6] = axis2->z;
	this->m_ViewMatrix.data[7] = 0.0f;
	
    this->m_ViewMatrix.data[8] = axis3->x;
    this->m_ViewMatrix.data[9] = axis3->y;
    this->m_ViewMatrix.data[10] = axis3->z;
	this->m_ViewMatrix.data[11] = 0.0f;
	
    this->m_ViewMatrix.data[12] = -(axis1.x*m_position->x + axis2->x*m_position->y + axis3->x*m_position->z);
    this->m_ViewMatrix.data[13] = -(axis1.y*m_position->x + axis2->y*m_position->y + axis3->y*m_position->z);
    this->m_ViewMatrix.data[14] = -(axis1.z*m_position->x + axis2->z*m_position->y + axis3->z*m_position->z);
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
