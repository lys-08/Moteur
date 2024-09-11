#include "matrix.h"



/**
 * @brief Default and evaluated constructor
 *
 * @param m_00 first line, first column
 * @param m_01 first line, second column
 * @param m_02 ...
 * @param m_03
 * @param m_10
 * @param m_11
 * @param m_12
 * @param m_13
 * @param m_20
 * @param m_21
 * @param m_22
 * @param m_23
 * @param m_30
 * @param m_31
 * @param m_32
 * @param m_33
*/
Matrix::Matrix(float m_00, float m_01, float m_02, float m_03,
    float m_10, float m_11, float m_12, float m_13,
    float m_20, float m_21, float m_22, float m_23,
    float m_30, float m_31, float m_32, float m_33)
{
    mat_[0][0] = m_00;
    mat_[0][1] = m_01;
    mat_[0][2] = m_02;
    mat_[0][3] = m_03;

    mat_[1][0] = m_10;
    mat_[1][1] = m_11;
    mat_[1][2] = m_12;
    mat_[1][3] = m_13;

    mat_[2][0] = m_20;
    mat_[2][1] = m_21;
    mat_[2][2] = m_22;
    mat_[2][3] = m_23;

    mat_[3][0] = m_30;
    mat_[3][1] = m_31;
    mat_[3][2] = m_32;
    mat_[3][3] = m_33;
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float& Matrix::operator[](std::pair<int, int> index)
{
    if (index.first < 0 || index.first > 3 || index.second < 0 || index.second > 3)
    {
        throw std::out_of_range("indice(s) out of range");
    }

    return mat_[index.first][index.second];
}

const float& Matrix::operator[](std::pair<int, int> index) const
{
    if (index.first < 0 || index.first > 3 || index.second < 0 || index.second > 3)
    {
        throw std::out_of_range("indice(s) out of range");
    }

    return mat_[index.first][index.second];
}



// ============================================================================
// Operator overloading =======================================================
// ============================================================================

Matrix Matrix::operator*=(const Matrix& m)
{
    Matrix resu;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resu[{i, j}] = mat_[i][0] * m[{0, j}]
                + mat_[i][1] * m[{1, j}]
                + mat_[i][2] * m[{2, j}]
                + mat_[i][3] * m[{3, j}];
        }
    }

    return resu;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * TODO
*/
Matrix Matrix::inv()
{
    Matrix resu;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            resu[{i, j}] = mat_[j][i];
        }
        resu[{i, 3}] = 0;
    }

    resu[{3, 0}] = -(mat_[3][0] * resu[{0, 0}] + mat_[3][1] * resu[{1, 0}] + mat_[3][2] * resu[{2, 0}]);
    resu[{3, 1}] = -(mat_[3][0] * resu[{0, 1}] + mat_[3][1] * resu[{1, 1}] + mat_[3][2] * resu[{2, 1}]);
    resu[{3, 2}] = -(mat_[3][0] * resu[{0, 2}] + mat_[3][1] * resu[{1, 2}] + mat_[3][2] * resu[{2, 2}]);
    resu[{3, 3}] = 1.0f;

    return resu;
}


/**
 * TODO
*/
void Matrix::initMatProj(int w, int h)
{
    float zNear = 0.1f;
    float zFar = 1000.0f;
    float theta = 90.0f;
    float wRatio = (float)h / (float)w; //Ratio de la fenêtre
    float thetaRad = 1.0f / tanf((theta / 2.0f) / 180.0f * 3.14); //en radian // TODO PI

    mat_[0][0] = wRatio * thetaRad;
    mat_[1][1] = thetaRad;
    mat_[2][2] = zFar / (zFar - zNear);
    mat_[3][2] = (-zFar * zNear) / (zFar - zNear);
    mat_[2][3] = 1.0f;
}


/**
 * TODO
*/
void Matrix::initMatRotX(float theta)
{
    mat_[0][0] = 1.0f;
    mat_[1][1] = cosf(theta);
    mat_[1][2] = sinf(theta);
    mat_[2][1] = -sinf(theta);
    mat_[2][2] = cosf(theta);
    mat_[3][3] = 1.0f;
}


/**
 * TODO
*/
void Matrix::initMatRotY(float theta)
{
    mat_[0][0] = cosf(theta);
    mat_[0][2] = -sinf(theta);
    mat_[1][1] = 1.0f;
    mat_[2][0] = sinf(theta);
    mat_[2][2] = cosf(theta);
    mat_[3][3] = 1.0f;
}


/**
 * TODO
*/
void Matrix::initMatRotZ(float theta)
{
    mat_[0][0] = cosf(theta);
    mat_[0][1] = sinf(theta);
    mat_[1][0] = -sinf(theta);
    mat_[1][1] = cosf(theta);
    mat_[2][2] = 1.0f;
    mat_[3][3] = 1.0f;
}



// ============================================================================
// External operators =========================================================
// ============================================================================

/**
 * TODO
*/
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix resu = m1;
    return resu *= m2;
}


/**
 * TODO
*/
Vector3d vectorXmatrix(const Vector3d& vect, const Matrix& mat)
{
    Vector3d resu;

    float x = vect.getX() * mat[{0, 0}] + vect.getY() * mat[{1, 0}] + vect.getZ() * mat[{2, 0}] + vect.getW() * mat[{3, 0}];
    float y = vect.getX() * mat[{0, 1}] + vect.getY() * mat[{1, 1}] + vect.getZ() * mat[{2, 1}] + vect.getW() * mat[{3, 1}];
    float z = vect.getX() * mat[{0, 2}] + vect.getY() * mat[{1, 2}] + vect.getZ() * mat[{2, 2}] + vect.getW() * mat[{3, 2}];

    float w = vect.getX() * mat[{0, 3}] + vect.getY() * mat[{1, 3}] + vect.getZ() * mat[{2, 3}] + vect.getW() * mat[{3, 3}];

    if (w != 0.0f)
    {
        x /= w;
        y /= w;
        z /= w;
        w /= w;
    }

    resu.setX(x);
    resu.setY(y);
    resu.setZ(z);
    resu.setW(w);

    return resu;
}