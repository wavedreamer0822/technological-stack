#include "Vector3d.h"
#include <sstream>
#include <cmath>
#include "LxTool.h"
#include "LxString.h"
namespace LxCFD
{
    Vector3d::Vector3d() {}
    Vector3d::Vector3d(double x, double y, double z) : X(x), Y(y), Z(z) {}
    void Vector3d::Negate()
    {
        X = -X;
        Y = -Y;
        Z = -Z;
    }
    double Vector3d::CalLengthSquared()
    {
        return X * X + Y * Y + Z * Z; // pow(X, 2) + pow(Y, 2) + pow(Z, 2);
    }
    double Vector3d::CalLength()
    {
        return sqrt(CalLengthSquared());
    }
    std::string Vector3d::ToString()
    {
        std::stringstream ss;
        ss << X << "," << Y << "," << Z;
        return ss.str();
    }
    bool Vector3d::Is0() const
    {
        return X == 0 && Y == 0 && Z == 0;
    }
    bool Vector3d::TryParse(Vector3d &out_result, std::string inputString)
    {
        std::vector<std::string> splitedStr;
        LxString::Split(splitedStr, inputString, ",，");
        if (splitedStr.size() != 3)
            return false;
        if (LxString::StringToDouble(out_result.X, LxString::Trim(splitedStr[0])) && LxString::StringToDouble(out_result.Y, LxString::Trim(splitedStr[1])) && LxString::StringToDouble(out_result.Z, LxString::Trim(splitedStr[2])))
            return true;
        else
            return false;
    }
    Vector3d &Vector3d::operator+=(const Vector3d &b)
    {
        X += b.X;
        Y += b.Y;
        Z += b.Z;
        return *this;
    }
    Vector3d &Vector3d::operator-=(const Vector3d &b)
    {
        X -= b.X;
        Y -= b.Y;
        Z -= b.Z;
        return *this;
    }
    Vector3d &Vector3d::operator*=(const double &d)
    {
        X *= d;
        Y *= d;
        Z *= d;
        return *this;
    }
    Vector3d Vector3d::operator+(const Vector3d &b) const
    {
        return Vector3d(X + b.X, Y + b.Y, Z + b.Z);
    }
    Vector3d Vector3d::operator-(const Vector3d &b) const
    {
        return Vector3d(X - b.X, Y - b.Y, Z - b.Z);
    }
    Vector3d Vector3d::operator-() const
    {
        return Vector3d(-X, -Y, -Z);
    }
    Vector3d Vector3d::operator*(double d) const
    {
        return Vector3d(X * d, Y * d, Z * d);
    }
    Vector3d operator*(const double d, const Vector3d &v)
    {
        return v * d;
        //return Vector3d(v.X * d, v.Y * d, v.Z * d);
    }
    double Vector3d::DotProduct(const Vector3d &a, const Vector3d &b)
    {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
    }
    Vector3d Vector3d::CrossProduct(const Vector3d &a, const Vector3d &b)
    {
        return Vector3d(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
    }
    Vector3d Vector3d::XXYYZZProduct(const Vector3d &a, const Vector3d &b)
    {
        return Vector3d(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
    }
    Vector3d Vector3d::PointRotate(const Vector3d &sourcePoint, const Vector3d &axis_length1, const Vector3d &pAxis, const double Radian) //后续改为vector3d类型,不能删
    {                                                                                                                                     //右手坐标系下，vector朝向你，逆时针旋转
        double c = cos(Radian);
        double c1 = 1 - c;
        double s = sin(Radian);
        double axy = axis_length1.X * axis_length1.Y;
        double ayz = axis_length1.Y * axis_length1.Z;
        double axz = axis_length1.X * axis_length1.Z;
        return Vector3d(
            (axis_length1.X * axis_length1.X * c1 + c) * (sourcePoint.X - pAxis.X) + (axy * c1 - axis_length1.Z * s) * (sourcePoint.Y - pAxis.Y) + (axz * c1 + axis_length1.Y * s) * (sourcePoint.Z - pAxis.Z) + pAxis.X,
            (axy * c1 + axis_length1.Z * s) * (sourcePoint.X - pAxis.X) + (axis_length1.Y * axis_length1.Y * c1 + c) * (sourcePoint.Y - pAxis.Y) + (ayz * c1 - axis_length1.X * s) * (sourcePoint.Z - pAxis.Z) + pAxis.Y,
            (axz * c1 - axis_length1.Y * s) * (sourcePoint.X - pAxis.X) + (ayz * c1 + axis_length1.X * s) * (sourcePoint.Y - pAxis.Y) + (axis_length1.Z * axis_length1.Z * c1 + c) * (sourcePoint.Z - pAxis.Z) + pAxis.Z);
    }

    Vector3d Vector3d::PointToPlane(Vector3d pointOut, Vector3d vectorOfPlane, Vector3d pointInPlane)
    {
        double t = (vectorOfPlane.X * (pointOut.X - pointInPlane.X) + vectorOfPlane.Y * (pointOut.Y - pointInPlane.Y) + vectorOfPlane.Z * (pointOut.Z - pointInPlane.Z)) / (vectorOfPlane.CalLengthSquared());
        return Vector3d(pointOut.X - vectorOfPlane.X * t,
                        pointOut.Y - vectorOfPlane.Y * t, pointOut.Z - vectorOfPlane.Z * t);
    }

    Vector3d Vector3d::VectorToPlane(Vector3d Vector, Vector3d vectorOfPlane) //矢量在平面上的投影
    {
        //Vector.MinusToSelf(DotProduct(Vector, vectorOfPlane) / vectorOfPlane.CalLengthSquared() * vectorOfPlane);
        //return Vector;
        return Vector - DotProduct(Vector, vectorOfPlane) / vectorOfPlane.CalLengthSquared() * vectorOfPlane;
    }
}
    // void Vector3d::AddToSelf(Vector3d v)
    // {
    //     X += v.X;
    //     Y += v.Y;
    //     Z += v.Z;
    // }
    // void Vector3d::MinusToSelf(Vector3d v)
    // {
    //     X -= v.X;
    //     Y -= v.Y;
    //     Z -= v.Z;
    // }
    // void Vector3d::MultiplyToSelf(double d)
    // {
    //     X *= d;
    //     Y *= d;
    //     Z *= d;
    // }