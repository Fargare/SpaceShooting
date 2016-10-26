#ifndef _VECTOR
#define _VECTOR
#include <windows.h>
#include <math.h>
#include <GL/GL.h>

//ベクトルクラス
//座標同士の四則演算だけでなく、内積や外積、距離なども関数としている
//今回はこの要素にHPや向き、速さなどを追加し、利用した

//------------------------------------------------------------------------//
// Misc. Constants
//------------------------------------------------------------------------//

GLfloat	const	pi	= 3.14159265f;
GLfloat	const	g	= -32.174f;		// acceleration due to gravity, ft/s^2
GLfloat	const	rho = 0.0023769f;	// desity of air at sea level, slugs/ft^3
GLfloat	const	tol = 0.000000000000001f;		// GLfloat type tolerance 


//------------------------------------------------------------------------//
// Misc. Functions
//------------------------------------------------------------------------//
inline	GLfloat	DegreesToRadians(GLfloat deg);
inline	GLfloat	RadiansToDegrees(GLfloat rad);

inline	GLfloat	DegreesToRadians(GLfloat deg)
{
	return deg * pi / 180.0f;
}

inline	GLfloat	RadiansToDegrees(GLfloat rad)
{	
	return rad * 180.0f / pi;
}

//------------------------------------------------------------------------//
// Vector Class and vector functions
//------------------------------------------------------------------------//
class Vector {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat theta;
	GLfloat V;
	bool exist;
	GLint counter;


	Vector(void);
	Vector(GLfloat xi, GLfloat yi, GLfloat zi);

	GLfloat Magnitude(void);
	void  Normalize(void);
	void  Reverse(void);

	Vector& operator+=(Vector u);	// vector addition
	Vector& operator-=(Vector u);	// vector subtraction
	Vector& operator*=(GLfloat s);	// scalar multiply
	Vector& operator/=(GLfloat s);	// scalar divide

	Vector operator-(void);

};

inline	Vector operator+(Vector u, Vector v);
inline	Vector operator-(Vector u, Vector v);
inline	Vector operator^(Vector u, Vector v);
inline	GLfloat operator*(Vector u, Vector v);
inline	Vector operator*(GLfloat s, Vector u);
inline	Vector operator*(Vector u, GLfloat s);
inline	Vector operator/(Vector u, GLfloat s);
inline	GLfloat TripleScalarProduct(Vector u, Vector v, Vector w);

inline Vector::Vector(void)
{
	x = 0;
	y = 0;
	z = 0;
	theta=0;
	V=0.05;
	counter=0;
	exist=false;
}

inline Vector::Vector(GLfloat xi, GLfloat yi, GLfloat zi)
{
	x = xi;
	y = yi;
	z = zi;
	theta=0;
	V=0.05;
	counter=0;
	exist=false;
}

inline	GLfloat Vector::Magnitude(void)
{
	return (GLfloat) sqrt(x*x + y*y + z*z);
}

inline	void  Vector::Normalize(void)
{
	GLfloat m = (GLfloat) sqrt(x*x + y*y + z*z);
	if(m <= tol) m = 1;
	x /= m;
	y /= m;
	z /= m;	

	if (fabs(x) < tol) x = 0.0f;
	if (fabs(y) < tol) y = 0.0f;
	if (fabs(z) < tol) z = 0.0f;
}

inline	void  Vector::Reverse(void)
{
	x = -x;
	y = -y;
	z = -z;
}

inline Vector& Vector::operator+=(Vector u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

inline	Vector& Vector::operator-=(Vector u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

inline	Vector& Vector::operator*=(GLfloat s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

inline	Vector& Vector::operator/=(GLfloat s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

inline	Vector Vector::operator-(void)
{
	return Vector(-x, -y, -z);
}


inline	Vector operator+(Vector u, Vector v)
{
	return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline	Vector operator-(Vector u, Vector v)
{
	return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

// Vector cross product (u cross v)
inline	Vector operator^(Vector u, Vector v)
{
	return Vector(	u.y*v.z - u.z*v.y,
		-u.x*v.z + u.z*v.x,
		u.x*v.y - u.y*v.x );
}

// Vector dot product
inline	GLfloat operator*(Vector u, Vector v)
{
	return (u.x*v.x + u.y*v.y + u.z*v.z);
}

inline	Vector operator*(GLfloat s, Vector u)
{
	return Vector(u.x*s, u.y*s, u.z*s);
}

inline	Vector operator*(Vector u, GLfloat s)
{
	return Vector(u.x*s, u.y*s, u.z*s);
}

inline	Vector operator/(Vector u, GLfloat s)
{
	return Vector(u.x/s, u.y/s, u.z/s);
}

// triple scalar product (u dot (v cross w))
inline	GLfloat TripleScalarProduct(Vector u, Vector v, Vector w)
{
	return GLfloat(	(u.x * (v.y*w.z - v.z*w.y)) +
		(u.y * (-v.x*w.z + v.z*w.x)) +
		(u.z * (v.x*w.y - v.y*w.x)) );
	//return u*(v^w);

}

#endif