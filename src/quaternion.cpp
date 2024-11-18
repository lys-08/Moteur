/**
* \file quaternion.cpp
* This file contains the implementation of all methods and attributes of the Quaternion class
*/

#include "quaternion.h"





/**
 * @brief Default and evaluated constructor
 */
Quaternion::Quaternion(float w, float i, float j, float k)
{
    w_ = w;
    i_ = i;
    j_ = j;
    k_ = k;
}

/**
 * @brief Copy constructor
 */
Quaternion::Quaternion(const Quaternion& other)
{
    w_ = other.w_;
    i_ = other.i_;
    j_ = other.j_;
    k_ = other.k_;
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float Quaternion::getW() const
{
    return w_;
}

float Quaternion::getI() const
{
    return i_;
}

float Quaternion::getJ() const
{
    return j_;
}

float Quaternion::getK() const
{
    return k_;
}

void Quaternion::setW(float w)
{
    w_ = w;
}

void Quaternion::setI(float i)
{
    i_ = i;
}

void Quaternion::setJ(float j)
{
    j_ = j;
}

void Quaternion::setK(float k)
{
    k_ = k;
}



// ============================================================================
// Operator overloading =======================================================
// ============================================================================

Quaternion Quaternion::operator+=(const Quaternion& other)
{
    w_ += other.w_;
    i_ += other.i_;
    j_ += other.j_;
    k_ += other.k_;

    return *this;
}

Quaternion Quaternion::operator*=(const Quaternion& other)
{
    Quaternion resu;

    resu.w_ = w_ * other.w_ - i_ * other.i_ - j_ * other.j_ - k_ * other.k_;
    resu.i_ = w_ * other.i_ + i_ * other.w_ + j_ * other.k_ - k_ * other.j_;
    resu.j_ = w_ * other.j_ - i_ * other.k_ + j_ * other.w_ + k_ * other.i_;
    resu.k_ = w_ * other.k_ + i_ * other.j_ - j_ * other.i_ + k_ * other.w_;

    *this = resu;
    return *this;
}

Quaternion Quaternion::operator*=(float f)
{
    w_ *= f;
    i_ *= f;
    j_ *= f;
    k_ *= f;

    return *this;
}

Quaternion Quaternion::operator/=(float f)
{
    if (f == 0.0)
    {
        throw std::invalid_argument("Division by zero");
    }

    w_ /= f;
    i_ /= f;
    j_ /= f;
    k_ /= f;

    return *this;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Return the quaternion identity
 *
 * @return the quaternion identity
*/
Quaternion Quaternion::identity()
{
    return Quaternion(1, 0, 0, 0);
}

/**
 * @brief Return the norm of the current quaternion
 *
 * @return norm of the quaternion
*/
float Quaternion::norm()
{
    return sqrt(w_ * w_ + i_ * i_ + j_ * j_ + k_ * k_);
}

/**
 * @brief Return the conjugate quaternion
 *
 * @return the conjugate identity
*/
Quaternion Quaternion::conjugate()
{
    return Quaternion(w_, - i_, - j_, - k_);
}

/**
 * @brief Return the inverse quaternion
 *
 * @return the inverse identity
*/
Quaternion Quaternion::inv()
{
    float norm = this->norm();

    if (norm == 0.0)
    {
        throw std::invalid_argument("Division by zero");
    }

    return this->conjugate() /= norm;
}

/**
 * @brief Performs the dot product between the current quaternion and the quaternion passed as parameter
 *
 * @param other the other quaternion
 * @return the dot product
*/
float Quaternion::dotProduct(const Quaternion& other) const
{
    return w_ * other.w_ + i_ * other.i_ + j_ * other.j_ + k_ * other.k_;
}

void Quaternion::normalise()
{
    

    float magnitude = std::sqrt(w_ * w_ + i_ * i_ + j_ * j_ + k_ * k_);

    // Vérification pour éviter la division par zéro
    if (magnitude > 0.0f)
    {
        w_ /= magnitude;
        i_ /= magnitude;
        j_ /= magnitude;
        k_ /= magnitude;
    }
    else
    {
        *this = identity();
    }
}

// TODO
/**
 * @brief Determine the fraction t of displacement
 *
 * @param t the exponent
 * @return the result quaternion
*/
//Quaternion Quaternion::exponentiation(int t)
//{
//    float alpha = acos(w_);
//    if (alpha == 0.0)
//    {
//        throw std::invalid_argument("Division by zero"); // sin(0) = 0
//    }
//
//    float w = cos(t * alpha) * sin(t * alpha) / sin(alpha);
//
//    return Quaternion(w, i_, j_, k_);
//}

Quaternion Quaternion::exponentiation(int t)
{
    float alpha = acos(w_);
    float sin_alpha = sin(alpha);

    // Gestion du cas spécial où le quaternion est proche d'une rotation nulle
    if (sin_alpha == 0.0f)
    {
        // Si alpha est proche de zéro, on retourne l'exponentiation de la partie scalaire
        return Quaternion(cos(t * alpha), 0.0f, 0.0f, 0.0f);
    }

    // Calcul des nouveaux coefficients
    float new_w = cos(t * alpha);
    float scale = sin(t * alpha) / sin_alpha;  // Échelle pour les composants vectoriels

    float new_i = i_ * scale;
    float new_j = j_ * scale;
    float new_k = k_ * scale;

    return Quaternion(new_w, new_i, new_j, new_k);
}


/**
 * @brief Determine the angular movement between two quaternion
 *
 * @param other the other quaternion
 * @return the angular movement between the current quaternion and the one passed as parameter
*/
Quaternion Quaternion::angularMovement(const Quaternion& other)
{
    return other * this->conjugate();
}

/**
 * @brief Convert the quaternion to a matrix3
 *
 * @return the result matrix
*/
Matrix3 Quaternion::toMatrix()
{
    return Matrix3(
        // first line
        1 - 2 * (j_ * j_ + k_ * k_),
        2 * (i_ * j_ + k_ * w_),
        2 * (i_ * k_ - j_ * w_),
        // second line
        2 * (i_ * j_ - k_ * w_),
        1 - 2 * (i_ * i_ + k_ * k_),
        2 * (j_ * k_ + i_ * w_),
        // third line
        2 * (i_ * k_ + j_ * w_),
        2 * (j_ * k_ - i_ * w_),
        1 - 2 * (i_ * i_ + j_ * j_)
    );
}



// ============================================================================
// External operators =========================================================
// ============================================================================

Quaternion operator+(const Quaternion& v1, const Quaternion& v2)
{
    Quaternion resu = Quaternion(v1);
    return resu += v2;
}

Quaternion operator*(const Quaternion& v1, const Quaternion& v2)
{
    Quaternion resu = Quaternion(v1);
    return resu *= v2;
}

Quaternion operator*(const Quaternion& v, float f)
{
    Quaternion resu = Quaternion(v);
    return resu *= f;
}

Quaternion operator*(float f, const Quaternion& v)
{
    Quaternion resu = Quaternion(v);
    return resu * f;
}

Quaternion operator/(const Quaternion& v, float f)
{
    Quaternion resu = Quaternion(v);
    return resu /= f;
}