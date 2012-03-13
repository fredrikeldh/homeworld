// =============================================================================
//  Matrix.h
// =============================================================================
//  Copyright Relic Entertainment, Inc. All rights reserved.
//  Created June 1997 by Gary Shaw
// =============================================================================

#ifndef ___MATRIX_H
#define ___MATRIX_H

#include "Types.h"
#include "Vector.h"

// INTERFACE -------------------------------------------------------------------

template <typename PT>
struct _Base2ColumnMatrix
{
	virtual ~_Base2ColumnMatrix() {};
	typedef PT column;

	virtual column GetColumn1() const = 0;
	virtual void  SetColumn1(const column& col) = 0;

	virtual column GetColumn2() const = 0;
	virtual void  SetColumn2(const column& col) = 0;

    virtual column::value_type MultiplyRow1   (const column& col) const = 0;
    virtual column::value_type MultiplyRow2   (const column& col) const = 0;

    virtual column::value_type MultiplyColumn1(const column& col) const = 0;
    virtual column::value_type MultiplyColumn2(const column& col) const = 0;

	virtual void Transpose() = 0;
};

template <typename PT>
struct _Base3ColumnMatrix : public _Base2ColumnMatrix<PT>
{
	virtual ~_Base3ColumnMatrix() {};
	virtual column GetColumn3() const = 0;
	virtual void  SetColumn3(const column& col) = 0;

    virtual column::value_type MultiplyRow3   (const column& col) const = 0;
    virtual column::value_type MultiplyColumn3(const column& col) const = 0;
};

template <typename PT>
struct _Base4ColumnMatrix : public _Base3ColumnMatrix<PT>
{
	virtual ~_Base4ColumnMatrix() {};
	virtual column GetColumn4() const = 0;
	virtual void  SetColumn4(const column& col) = 0;

	virtual column::value_type MultiplyRow4   (const column& col) const = 0;
    virtual column::value_type MultiplyColumn4(const column& col) const = 0;
};

struct matrix : public _Base3ColumnMatrix<vector>
{
/*-----------------------------------------------------------------------------
    Conceptually, and mathematically, you should think of the matrix as follows:

    |m11 m12 m13|
    |m21 m22 m23|
    |m31 m32 m33|

    In memory, it is stored as follows to be compatible with GameGL
-----------------------------------------------------------------------------*/
    real32 m11,m21,m31, m12,m22,m32, m13,m23,m33;

    column GetColumn1() override const;
    column GetColumn2() override const;
    column GetColumn3() override const;

    void SetColumn1(const column& vec) override;
    void SetColumn2(const column& vec) override;
    void SetColumn3(const column& vec) override;

    column::value_type Multiply(column::value_type x1, column::value_type x2,
                                 column::value_type x3,
                                 const column& col) const;

    column::value_type MultiplyRow1(const column& col) override const;
    column::value_type MultiplyRow2(const column& col) override const;
    column::value_type MultiplyRow3(const column& col) override const;

    column::value_type MultiplyColumn1(const column& col) override const;
    column::value_type MultiplyColumn2(const column& col) override const;
    column::value_type MultiplyColumn3(const column& col) override const;

    void Transpose()
    {
        std::swap(m21, m12);
        std::swap(m31, m13);
        std::swap(m32, m23);
    }
};

struct hmatrix : public _Base4ColumnMatrix<hvector>
{
/*-----------------------------------------------------------------------------
    Conceptually, and mathematically, you should think of the matrix as follows:

    |m11 m12 m13 m14|
    |m21 m22 m23 m24|
    |m31 m32 m33 m34|
    |m41 m42 m43 m44|

    In memory, it is stored as follows to be compatible with GameGL
-----------------------------------------------------------------------------*/
    real32 m11,m21,m31,m41, m12,m22,m32,m42, m13,m23,m33,m43, m14,m24,m34,m44;

    column GetColumn1() override const;
    column GetColumn2() override const;
    column GetColumn3() override const;
    column GetColumn4() override const;

    void SetColumn1(column::value_type f1, column::value_type f2,
                      column::value_type f3, column::value_type f4);

    void SetColumn1(const column& hvec) override;

    void SetColumn2(column::value_type f1, column::value_type f2,
                      column::value_type f3, column::value_type f4);

    void SetColumn2(const column& hvec) override;

    void SetColumn3(column::value_type f1, column::value_type f2,
                      column::value_type f3, column::value_type f4);

    void SetColumn3(const column& hvec) override;

    void SetColumn4(column::value_type f1, column::value_type f2,
                      column::value_type f3, column::value_type f4);

    void SetColumn4(const column& hvec) override;

    column::value_type Multiply(column::value_type x1, column::value_type x2,
                                   column::value_type x3, column::value_type x4,
                                   const column& col) const;

    column::value_type MultiplyRow1(const column& col) override const;
    column::value_type MultiplyRow2(const column& col) override const;
    column::value_type MultiplyRow3(const column& col) override const;
    column::value_type MultiplyRow4(const column& col) override const;

    column::value_type MultiplyColumn1(const column& col) override const;
    column::value_type MultiplyColumn2(const column& col) override const;
    column::value_type MultiplyColumn3(const column& col) override const;
    column::value_type MultiplyColumn4(const column& col) override const;

    void Set(const column& col1, const column& col2,
              const column& col3, const column& col4);

    void Set(const matrix& matrix, const vector& col,
              column::value_type f41 = 0.0f, column::value_type f42 = 0.0f,
              column::value_type f43 = 0.0f, column::value_type f44 = 1.0f);

    void Set(const matrix& matrix, column::value_type f41 = 0.0f, column::value_type f42 = 0.0f,
              column::value_type f43 = 0.0f);

    void Set(const matrix& matrix, const column& col,
              column::value_type f41 = 0.0f, column::value_type f42 = 0.0f,
              column::value_type f43 = 0.0f);

    column::value_type MultiplyRow1(const column& col) override const;
    column::value_type MultiplyRow2(const column& col) override const;
    column::value_type MultiplyRow3(const column& col) override const;
    column::value_type MultiplyRow4(const column& col) override const;

    void Transpose()
    {
        std::swap(m12, m21);
        std::swap(m13, m31);
        std::swap(m14, m41);
        std::swap(m23, m32);
        std::swap(m24, m42);
        std::swap(m34, m43);
    }

    matrix GetMatrix() const
    {
    	return matrix
    	(
    		m11,
    		m21,
    		m31,

    		m12,
    		m22,
    		m32,

    		m13,
    		m23,
    		m33
    	);
    }
};

vector  operator*(const  matrix& matrix, const  vector& vector);
vector  operator*(const  vector& vector, const  matrix& matrix);
hvector operator*(const hmatrix& matrix, const hvector& vector);
hvector operator*(const hvector& vector, const hmatrix& matrix);


// -----------------------------------------------------------------------------
//  Homogenous matrix macros:

void hmatGetHVectFromHMatrixCol1(hvector& hvec, const hmatrix& hmat);
void hmatGetHVectFromHMatrixCol2(hvector& hvec, const hmatrix& hmat);
void hmatGetHVectFromHMatrixCol3(hvector& hvec, const hmatrix& hmat);
void hmatGetHVectFromHMatrixCol4(hvector& hvec, const hmatrix& hmat);

// -----------------------------------------------------------------------------

void hmatPutHVectIntoHMatrixCol1(const hvector& hvec, hmatrix& hmat);
void hmatPutHVectIntoHMatrixCol2(const hvector& hvec, hmatrix& hmat);
void hmatPutHVectIntoHMatrixCol3(const hvector& hvec, hmatrix& hmat);
void hmatPutHVectIntoHMatrixCol4(const hvector& hvec, hmatrix& hmat);

// -----------------------------------------------------------------------------

void hmatGetVectFromHMatrixCol1(vector& vec, const hmatrix& hmat);
void hmatGetVectFromHMatrixCol2(vector& vec, const hmatrix& hmat);
void hmatGetVectFromHMatrixCol3(vector& vec, const hmatrix& hmat);
void hmatGetVectFromHMatrixCol4(vector& vec, const hmatrix& hmat);
// -----------------------------------------------------------------------------

void hmatPutVectIntoHMatrixCol1(const vector& vec, hmatrix& hmat);
void hmatPutVectIntoHMatrixCol2(const vector& vec, hmatrix& hmat);
void hmatPutVectIntoHMatrixCol3(const vector& vec, hmatrix& hmat);
void hmatPutVectIntoHMatrixCol4(const vector& vec, hmatrix& hmat);

// -----------------------------------------------------------------------------
//  3 X 3 matrix macros:

void matGetVectFromMatrixCol1(vector& vec, const matrix& mat);
void matGetVectFromMatrixCol2(vector& vec, const matrix& mat);
void matGetVectFromMatrixCol3(vector& vec, const matrix& mat);

// -----------------------------------------------------------------------------

void matPutVectIntoMatrixCol1(const vector& vec, matrix& mat);
void matPutVectIntoMatrixCol2(const vector& vec, matrix& mat);
void matPutVectIntoMatrixCol3(const vector& vec, matrix& mat);

// -----------------------------------------------------------------------------


extern const hmatrix IdentityHMatrix;
extern const matrix  IdentityMatrix;


void hmatMakeHMatFromMat(hmatrix& result, const matrix& mat);
void hmatMakeHMatFromMatAndVec(hmatrix& result, const matrix& mat, const vector& pos);
void hmatCreateHMatFromHVecs(hmatrix& result, const hvector& col1, const hvector& col2, const hvector& col3, const hvector& col4);
void hmatMultiplyHMatByHMat(hmatrix *result, hmatrix *first, hmatrix *second);
void MultiplyMatrix4fByMatrix4f(real32* c, const real32* a, const real32* b);
void hmatMultiplyHMatByHVec(hvector& result, const hmatrix& matrix, const hvector&vector);
void hmatMultiplyHVecByHMat(hvector& result, const hvector& vector, const hmatrix& matrix);
void hmatTranspose(hmatrix& matrix);
void hmatCopyAndTranspose(const hmatrix& src, hmatrix&dsttrans);
void hmatMakeRotAboutZ(hmatrix& matrix, real32 costheta, real32 sintheta);
void hmatMakeRotAboutX(hmatrix& matrix, real32 costheta, real32 sintheta);
void hmatMakeRotAboutY(hmatrix& matrix, real32 costheta, real32 sintheta);
void hmatPrintHMatrix(hmatrix& a);

void matGetMatFromHMat(matrix& result, const hmatrix& hmat);
void matCreateCoordSysFromHeading(matrix& result, const vector& heading);
void matCreateMatFromVecs(matrix& result, const vector& col1, const vector& col2, const vector& col3);
void matMultiplyMatByMat(matrix *result, matrix *first, matrix *second);
void matMultiplyMatByVec(vector& result, const matrix& matrix, const vector& vector);
void matMultiplyVecByMat(vector& result, const vector& vector, const matrix& matrix);
void matTranspose(matrix& matrix);
void matCopyAndTranspose(matrix& src, matrix& dsttrans);
void matMakeRotAboutZ(matrix& matrix, real32 costheta, real32 sintheta);
void matMakeRotAboutX(matrix& matrix, real32 costheta, real32 sintheta);
void matMakeRotAboutY(matrix& matrix, real32 costheta, real32 sintheta);
void matPrintmatrix(matrix& a);
void matCopyAndScale(matrix& out, const matrix& in, real32 scale);

#endif
