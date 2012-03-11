// =============================================================================
//  Vector.c
// =============================================================================
//  Copyright Relic Entertainment, Inc. All rights reserved.
//  Created June 1997 by Gary Shaw
// =============================================================================

#include "Vector.h"

#include "Debug.h"
#include "FastMath.h"

_vector_tuple::_vector_tuple() :
	x(0), y(0), z(0)
{
}

_vector_tuple::_vector_tuple(value_type xp, value_type yp, value_type zp):
	x(xp), y(yp), z(zp)
{
}

_vector_tuple::~_vector_tuple()
{
}

void _vector_tuple::Set(value_type xp, value_type yp, value_type zp)
{
	x = xp;
	y = yp;
	z = zp;
}

vector::vector() :
	_vector_tuple()
{
}

vector::~vector()
{
}

vector& vector::operator=(const hvector& h)
{
	Set(h.x, h.y, h.z);
	return *this;
}

vector vector::operator+(const vector& other) const
{
	return vector(x + other.x, y + other.y, z + other.z);
}

vector vector::operator-(const vector& other) const
{
	return vector(x - other.x, y - other.y, z - other.z);
}

vector vector::operator*(const value_type factor) const
{
	return vector(x * factor, y * factor, z * factor);
}

bool vector::operator==(const vector& other) const
{
	return x == other.x
		 && y == other.y
		 && z == other.z;
}

void vector::SetZero()
{
	Set(0.0f, 0.0f, 0.0f);
}

vector::value_type vector::Dot(const vector& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

vector& vector::Cross(const vector& first, const vector& second)
{
	return Set
	(
		(first.y * second.z) - (first.z * second.y),
		(first.z * second.x) - (first.x * second.z),
		(first.x * second.y) - (first.y * second.x)
	);
}

vector vector::Cross(const vector& other) const
{
	return vector
	(
		(y * other.z) - (z * other.y),
		(z * other.x) - (x * other.z),
		(x * other.y) - (y * other.x)
	);
}

vector& vector::Negate()
{
	Set(-x, -y, -z);
	return this;
}

vector vector::Negate() const
{
	return vector(-x, -y, -z);
}

vector::value_type vector::MagnitudeSquared() const
{
	return (x * x) + (y * y) + (z * z);
}

bool vector::IsZero() const
{
	return x == 0.0f
		 && y == 0.0f
		 && z == 0.0f;
}

hvector::hvector(value_type xp, value_type yp, value_type zp, value_type wp) :
	_vector_tuple(xp, yp, zp), w(wp)
{
}

void hvector::Set(value_type xp, value_type yp, value_type zp, value_type wp)
{
	x = xp;
	y = yp;
	z = zp;
	w = wp;
}

hvector& hvector::operator=(const vector& v)
{
	Set(x, y, z, 1.0f);
	return *this;
}

bool hvector::operator==(const hvector& other) const
{
	return x == other.x
		 && y == other.y
		 && z == other.z
		 && w == other.w;
}

hvector& hvector::Negate() override
{
	Set(-x, -y, -z, -w);
	return this;
}

hvector hvector::Negate() override const
{
	return hvector(-x, -y, -z, -w);
}

void hvector::SetZero() override
{
	Set(0.0f, 0.0f, 0.0f, 0.0f);
}

bool hvector::IsZero() override const
{
	return x == 0.0f
		 && y == 0.0f
		 && z == 0.0f
		 && w == 0.0f;
}

hvector::value_type hvector::MagnitudeSquared() override const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

hvector::value_type hvector::Dot(const hvector& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}


/*=============================================================================
    Functions:
=============================================================================*/

/*-----------------------------------------------------------------------------
    Name        : vecNormalize
    Description : normalizes a vector (makes it a unit vector)
    Inputs      : vector
    Outputs     : vector is normalized
    Return      :
----------------------------------------------------------------------------*/
void vecNormalize(vector& a)
{
    real32 mag = fsqrt(vecMagnitudeSquared(a));
    real32 oneOverMag;

#ifdef OPTIMIZE_VERBOSE
   // vecNormalizeCounter++;
#endif
    if (mag == 0.0f)
        return;

    oneOverMag = 1.0f / mag;

    a.x *= oneOverMag;
    a.y *= oneOverMag;
    a.z *= oneOverMag;
}

/*-----------------------------------------------------------------------------
    Name        : vecHomogenize
    Description : homogenizes an hvector (to the w == 1 plane)
    Inputs      : dst - destination vector
                  src - source hvector
    Outputs     : dst is homogenized from src
    Return      :
----------------------------------------------------------------------------*/
void vecHomogenize(vector& dst, const hvector& src)
{
    real32 oneOverW;

    vecGrabVecFromHVec(dst, src);
    if (src.w == 0.0f || src.w == 1.0f)
    {
        return;
    }

    oneOverW = 1.0f / src.w;
    dst.x *= oneOverW;
    dst.y *= oneOverW;
    dst.z *= oneOverW;
}

/*-----------------------------------------------------------------------------
    Name        : vecCopyAndNormalize
    Description : copies a source vector to destination vector, and then
                  normalizes the destination vector
    Inputs      : src, dst
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void vecCopyAndNormalize(const vector& src, vector& dst)
{
    real32 mag = fsqrt(vecMagnitudeSquared(src));
    real32 oneOverMag = 1.0f / mag;

    dst.x = src.x * oneOverMag;
    dst.y = src.y * oneOverMag;
    dst.z = src.z * oneOverMag;
}

/*-----------------------------------------------------------------------------
    Name        : vecNormalizeToLength
    Description : Normalizes vector to given length.
    Inputs      : vector, length
    Outputs     : vector will now have length length.
    Return      :
----------------------------------------------------------------------------*/
void vecNormalizeToLength(vector& a, real32 length)
{
    real32 mag = fsqrt(vecMagnitudeSquared(a));
    real32 ratio = length / mag;

    a.x *= ratio;
    a.y *= ratio;
    a.z *= ratio;
}

/*-----------------------------------------------------------------------------
    Name        : vecCapVectorSloppy
    Description : limits a vector's magnitude from growing beyond a maximum
                  magnitude by chopping x,y,z separately.
    Inputs      : vectorToCap, maxMagnitude
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void vecCapVectorSloppy(vector& vectorToCap, real32 maxMagnitude)
{
    real32 negMaxMagnitude = -maxMagnitude;

    if (vectorToCap.x > maxMagnitude)
    	vectorToCap.x = maxMagnitude;
    else if (vectorToCap.x < negMaxMagnitude)
        vectorToCap.x = negMaxMagnitude;

    if (vectorToCap.y > maxMagnitude)
        vectorToCap.y = maxMagnitude;
    else if (vectorToCap.y < negMaxMagnitude)
        vectorToCap.y = negMaxMagnitude;

    if (vectorToCap.z > maxMagnitude)
        vectorToCap.z = maxMagnitude;
    else if (vectorToCap.z < negMaxMagnitude)
        vectorToCap.z = negMaxMagnitude;
}

/*-----------------------------------------------------------------------------
    Name        : vecCapVector
    Description : limits a vector's magnitude from growing beyond a maximum
                  magnitude
    Inputs      : vectorToCap, maxMagnitude
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void vecCapVector(vector& vectorToCap, real32 maxMagnitude)
{
    real32 actualMag = fsqrt(vecMagnitudeSquared(vectorToCap));
    real32 ratio;

    if (actualMag <= maxMagnitude)
    	return;

	ratio = maxMagnitude / actualMag;
	vectorToCap.x *= ratio;
	vectorToCap.y *= ratio;
	vectorToCap.z *= ratio;
}

/*-----------------------------------------------------------------------------
    Name        : vecCapVectorWithMag
    Description : limits a vector's magnitude from growing beyond a maximum
                  magnitude
    Inputs      : vectorToCap, maxMagnitude, actualMag
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void vecCapVectorWithMag(vector& vectorToCap, real32 maxMagnitude, real32 actualMag)
{
    if (actualMag <= maxMagnitude)
    	return;

    auto ratio = maxMagnitude / actualMag;
	vectorToCap.x *= ratio;
	vectorToCap.y *= ratio;
	vectorToCap.z *= ratio;
}

/*-----------------------------------------------------------------------------
    Name        : vecCapMinVector
    Description : limits a vector's minimum magnitude from growing below a maximum
                  magnitude
    Inputs      : vectorToCap, minMagnitude
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void vecCapMinVector(vector& vectorToCap, real32 minMagnitude)
{
    real32 actualMag = fsqrt(vecMagnitudeSquared(vectorToCap));

    if (actualMag >= minMagnitude)
    	return;

	auto ratio = minMagnitude / actualMag;
	vectorToCap.x *= ratio;
	vectorToCap.y *= ratio;
	vectorToCap.z *= ratio;
}

/*-----------------------------------------------------------------------------
    Name        : vecCapMinMaxVector
    Description : limits both the vector's minimum and maximum magnitude
    Inputs      : vectorToCap, minMagnitude, maxMagnitude
    Outputs     :
    Return      :
----------------------------------------------------------------------------*/
void vecCapMinMaxVector(vector& vectorToCap, real32 minMagnitude, real32 maxMagnitude)
{
    real32 actualMag = fsqrt(vecMagnitudeSquared(vectorToCap));
    real32 ratio;

    if (actualMag < minMagnitude)
    {
        ratio = minMagnitude / actualMag;
        vectorToCap.x *= ratio;
        vectorToCap.y *= ratio;
        vectorToCap.z *= ratio;
    }

    if (actualMag > maxMagnitude)
    {
        ratio = maxMagnitude / actualMag;
        vectorToCap.x *= ratio;
        vectorToCap.y *= ratio;
        vectorToCap.z *= ratio;
    }
}

/*-----------------------------------------------------------------------------
    Name        : getVectDistSloppy
    Description : given a distance vector, gives a sloppy approximation of the distance
    Inputs      : diff
    Outputs     :
    Return      : sloppy approximation of the distance
----------------------------------------------------------------------------*/
real32 getVectDistSloppy(const vector& cdiff)
{
	vector diff(cdiff);
    diff.x = ::abs(diff.x);
    diff.y = ::abs(diff.y);
    diff.z = ::abs(diff.z);

    if (diff.x > diff.y)
    {
        if (diff.x > diff.z)
            return diff.x;
        else
            return diff.z;
    }
    else
    {
        if (diff.y > diff.z)
            return diff.y;
        else
            return diff.z;
    }
}

/*-----------------------------------------------------------------------------
    Name        : vecLineIntersectWithXYPlane
    Description : finds the point of intersection between a line and the
                  XY plane at z=zp.  The line is defined with the two points
                  linepoint1 and linepoint2.
    Inputs      : linepoint1, linepoint2, zp
    Outputs     : result, point of intersection
    Return      :
----------------------------------------------------------------------------*/
void vecLineIntersectWithXYPlane(vector& result, const vector& linepoint1, const vector& linepoint2, real32 zp)
{
    real32 k;

    k = (zp - linepoint1.z) / (linepoint2.z - linepoint1.z);

    result.x = (linepoint2.x - linepoint1.x)*k + linepoint1.x;
    result.y = (linepoint2.y - linepoint1.y)*k + linepoint1.y;
    result.z = zp;
}

/*-----------------------------------------------------------------------------
    Name        : vecLineIntersectWithYZPlane
    Description : finds the point of intersection between a line and the
                  YZ plane at x=xp.  The line is defined with the two points
                  linepoint1 and linepoint2.
    Inputs      : linepoint1, linepoint2, xp
    Outputs     : result, point of intersection
    Return      :
----------------------------------------------------------------------------*/
void vecLineIntersectWithYZPlane(vector& result, const vector& linepoint1, const vector& linepoint2, real32 xp)
{
    real32 k;

    k = (xp - linepoint1.x) / (linepoint2.x - linepoint1.x);

    result.y = (linepoint2.y - linepoint1.y)*k + linepoint1.y;
    result.z = (linepoint2.z - linepoint1.z)*k + linepoint1.z;
    result.x = xp;
}

/*-----------------------------------------------------------------------------
    Name        : vecLineIntersectWithXZPlane
    Description : finds the point of intersection between a line and the
                  XZ plane at y=yp.  The line is defined with the two points
                  linepoint1 and linepoint2.
    Inputs      : linepoint1, linepoint2, yp
    Outputs     : result, point of intersection
    Return      :
----------------------------------------------------------------------------*/
void vecLineIntersectWithXZPlane(vector& result, const vector& linepoint1, const vector& linepoint2, real32 yp)
{
    real32 k;

    k = (yp - linepoint1.y) / (linepoint2.y - linepoint1.y);

    result.x = (linepoint2.x - linepoint1.x)*k + linepoint1.x;
    result.z = (linepoint2.z - linepoint1.z)*k + linepoint1.z;
    result.y = yp;
}

/*-----------------------------------------------------------------------------
    Name        : vecLineIntersectWithPlane
    Description : Compute the intersection of an arbitrary plane and an
                    arbitrary ray.
    Inputs      : Vplane - point on plane
                  Vnormal - normal to plane
                  Vline - point on line
                  Vdirection - direction of line
    Outputs     : dest - intersection point
    Return      : will generate error if there is no intersection (line is
                    paralell to plane)
----------------------------------------------------------------------------*/
void vecLineIntersectWithPlane(vector& dest, const vector& Vplane, const vector& Vnormal, const vector& Vline, const vector& Vdirection)
{
    real32 tScalar, value;
    vector temp;

    value = vecDotProduct(Vdirection, Vnormal);
    dbgAssertOrIgnore(value != 0.0f);

    vecSub(temp, Vline, Vplane);

    //t = _-(Rl-Rp).N_
    //         V.N
    tScalar = -vecDotProduct(temp, Vnormal) / value;

    //R = Rl + tV
    dest.x = Vline.x + tScalar * Vdirection.x;
    dest.y = Vline.y + tScalar * Vdirection.y;
    dest.z = Vline.z + tScalar * Vdirection.z;
}

/*-----------------------------------------------------------------------------
    Name        : vecVectorsBlend
    Description : Linearly blend between two vectors.
    Inputs      : start, end - endpoints of the interpolation
                  factor - amount of end to use
    Outputs     : result - where the interpolated result is stored.
    Return      :
----------------------------------------------------------------------------*/
void vecVectorsBlend(vector& result, const vector& start, const vector& end, real32 factor)
{
    real32 oneMinusFactor = 1.0f - factor;
    result.x = start.x * oneMinusFactor + end.x * factor;
    result.y = start.y * oneMinusFactor + end.y * factor;
    result.z = start.z * oneMinusFactor + end.z * factor;
}

void vecSet(vector& v, vector::value_type xp, vector::value_type yp,vector::value_type zp)
{
	v.Set(xp, yp, zp);
}

void vecGrabVecFromHVec(vector& v, const hvector& h)
{
	v = h;
}

void vecMakeHVecFromVec(hvector& h, const vector& v)
{
	h = v;
}

void vecZeroVector(vector& a)
{
    a.SetZero();
}

void vecAdd(vector& a, const vector& b, const vector& c)
{
	a = b + c;
}

void vecAddTo(vector& a, const vector& b)
{
	a += b;
}

void vecSub(vector& a, const vector& b, const vector& c)
{
	a = b - c;
}

void vecSubFrom(vector& a, const vector& b)
{
	a -= b;
}

vector::value_type vecDotProduct(const vector& a, const vector& b)
{
	return a.Dot(b);
}

void vecCrossProduct(vector& result, const vector& a, const vector& b)
{
	result.Cross(a, b);
}

void vecAddToScalarMultiply(vector& dstvec, const vector& vec, vector::value_type k)
{
	dstvec += vec * k;
}

void vecSubFromScalarMultiply(vector& dstvec, const vector& vec, vector::value_type k)
{
	dstvec -= vec * k;
}

void vecScalarMultiply(vector& dstvec, const vector& vec, vector::value_type k)
{
	dstvec = vec * k;
}

void vecMultiplyByScalar(vector& vec, vector::value_type k)
{
	vec *= k;
}

void vecScalarDivide(vector& dstvec, const vector& vec, vector::value_type k, vector& tmp)
{
    tmp = 1.0f / k;
    dstvec = vec * tmp;
}

void vecScalarDivide(vector& dstvec, const vector& vec, vector::value_type k)
{
	vector tmp;
	vecScalarDivide(dstvec, vec, k, tmp);
}

void vecDivideByScalar(vector& vec, vector::value_type k, vector& tmp)
{
    tmp = 1.0f / k;
    vec *= tmp;
}

void vecDivideByScalar(vector& vec, vector::value_type k)
{
	vector tmp;
	vecDivideByScalar(vec, k, tmp);
}

void vecNegate(vector& vec)
{
	vec.Negate();
}

void vecCopyAndNegate(vector& dstvec, const vector& vec)
{
	dstvec = vec.Negate();
}

vector::value_type vecMagnitudeSquared(const vector& a)
{
	return a.MagnitudeSquared();
}

bool vecAreEqual(const vector& a, const vector& b)
{
	return a == b;
}

bool vecIsZero(const vector& a)
{
	return a.IsZero();
}

