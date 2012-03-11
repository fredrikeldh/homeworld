// =============================================================================
//  Vector.h
// =============================================================================
//  Copyright Relic Entertainment, Inc. All rights reserved.
//  Created June 1997 by Gary Shaw
// =============================================================================

#ifndef ___VECTOR_H
#define ___VECTOR_H

#include "Types.h"

// INTERFACE -------------------------------------------------------------------

struct _vector_tuple
{
	typedef real32 value_type;
	value_type x,y,z;

	_vector_tuple();
	_vector_tuple(value_type xp, value_type yp, value_type zp);
	virtual ~_vector_tuple();

	void Set(value_type xp, value_type yp, value_type zp);

	virtual void SetZero() = 0;
	virtual bool IsZero() const = 0;

	virtual value_type MagnitudeSquared() const = 0;
};

struct hvector;

struct vector : public _vector_tuple
{
	vector();

	virtual ~vector();

	vector& operator= (const hvector& h);
	vector  operator+ (const vector& other) const;
	vector  operator- (const vector& other) const;
	vector  operator* (const value_type factor) const;
	bool   operator==(const vector& other) const;

	value_type Dot(const vector& other) const;

	vector& Cross(const vector& first, const vector& second);
	vector  Cross(const vector& other) const;

	vector& Negate();
	vector  Negate() const;

	value_type MagnitudeSquared() override const;

	void SetZero() override;
	bool IsZero() override const;
};

struct hvector : public _vector_tuple
{
	value_type w;

	hvector(value_type xp, value_type yp, value_type zp, value_type wp);

	void Set(value_type xp, value_type yp, value_type zp, value_type wp);

	hvector& operator= (const vector& v);
	bool    operator==(const hvector& other) const;

	hvector& Negate() override;
	hvector  Negate() override const;

	void SetZero() override;
	bool IsZero() override const;

	value_type MagnitudeSquared() override const;

	value_type Dot(const hvector& other) const;
};

void vecSet(vector& v, vector::value_type xp, vector::value_type yp,vector::value_type zp);

void vecGrabVecFromHVec(vector& v, const hvector& h);

void vecMakeHVecFromVec(hvector& h, const vector& v);

void vecZeroVector(vector& a);

void vecAdd(vector& a, const vector& b, const vector& c);

void vecAddTo(vector& a, const vector& b);

void vecSub(vector& a, const vector& b, const vector& c);

void vecSubFrom(vector& a, const vector& b);

vector::value_type vecDotProduct(const vector& a, const vector& b);

void vecCrossProduct(vector& result, const vector& a, const vector& b);

void vecAddToScalarMultiply(vector& dstvec, const vector& vec, vector::value_type k);

void vecSubFromScalarMultiply(vector& dstvec, const vector& vec, vector::value_type k);

void vecScalarMultiply(vector& dstvec, const vector& vec, vector::value_type k);

void vecMultiplyByScalar(vector& vec, vector::value_type k);

void vecScalarDivide(vector& dstvec, const vector& vec, vector::value_type k, vector& tmp);

void vecScalarDivide(vector& dstvec, const vector& vec, vector::value_type k);

void vecDivideByScalar(vector& vec, vector::value_type k, vector& tmp);

void vecDivideByScalar(vector& vec, vector::value_type k);

void vecNegate(vector& vec);

void vecCopyAndNegate(vector& dstvec, const vector& vec);

vector::value_type vecMagnitudeSquared(const vector& a);

bool vecAreEqual(const vector& a, const vector& b);

bool vecIsZero(const vector& a);

#define VECTOR_ORIGIN  {0.0, 0.0, 0.0}

void vecNormalize(vector& a);
void vecHomogenize(vector& dst, const hvector& src);
void vecCopyAndNormalize(vector& src, const vector& dst);
void vecNormalizeToLength(vector& a, real32 length);
void vecCapVectorSloppy(vector& vectorToCap, real32 maxMagnitude);
void vecCapVector(vector& vectorToCap, real32 maxMagnitude);
void vecCapVectorWithMag(vector& vectorToCap, real32 maxMagnitude, real32 actualMag);
void vecCapMinVector(vector& vectorToCap, real32 minMagnitude);
void vecCapMinMaxVector(vector& vectorToCap, real32 minMagnitude, real32 maxMagnitude);
real32 getVectDistSloppy(const vector& diff);
void vecLineIntersectWithXYPlane(vector& result, const vector& linepoint1, const vector& linepoint2, real32 zp);
void vecLineIntersectWithYZPlane(vector& result, const vector& linepoint1, const vector& linepoint2, real32 xp);
void vecLineIntersectWithXZPlane(vector& result, const vector& linepoint1, const vector& linepoint2, real32 yp);
void vecLineIntersectWithPlane(vector& dest, const vector& Vplane, const vector& Vnormal, const vector& Vline, const vector& Vdirection);
void vecVectorsBlend(vector& result, const vector& start, const vector& end, real32 factor);

#endif
