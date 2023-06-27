#pragma once
#include <string>

namespace LxCFD
{
    struct Vector3d
    {
        Vector3d();
        Vector3d(double x, double y, double z);

        double X = 0;
        double Y = 0;
        double Z = 0;

        void Negate();
        double CalLengthSquared();
        double CalLength();
        std::string ToString();
        bool Is0() const;
        static bool TryParse(Vector3d &out_result, std::string inputString);
        Vector3d &operator+=(const Vector3d &b);
        Vector3d &operator-=(const Vector3d &b);
        Vector3d &operator*=(const double &b);
        Vector3d operator+(const Vector3d &b) const;
        Vector3d operator-(const Vector3d &b) const;
        Vector3d operator-() const;
        Vector3d operator*(double d) const;
        friend Vector3d operator*(const double d, const Vector3d &v);
        static double DotProduct(const Vector3d &a, const Vector3d &b);
        static Vector3d CrossProduct(const Vector3d &a, const Vector3d &b);
        static Vector3d XXYYZZProduct(const Vector3d &a, const Vector3d &b);
        static Vector3d PointRotate(const Vector3d &sourcePoint, const Vector3d &axis_length1, const Vector3d &pAxis, const double Radian);
        static Vector3d PointToPlane(Vector3d pointOut, Vector3d vectorOfPlane, Vector3d pointInPlane);
        static Vector3d VectorToPlane(Vector3d Vector, Vector3d vectorOfPlane); //矢量在平面上的投影
    };
}
// void AddToSelf(Vector3d v);
// void MinusToSelf(Vector3d v);
// void MultiplyToSelf(double d);