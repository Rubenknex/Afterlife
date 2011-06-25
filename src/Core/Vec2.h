#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2
{
public:
    Vec2();
    Vec2(float xy);
    Vec2(float x, float y);
    
    
    
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator*=(float rhs);
    Vec2& operator/=(float rhs);
    
    const Vec2 operator-(const Vec2& rhs) const;
    const Vec2 operator+(const Vec2& rhs) const;
    const Vec2 operator*(float rhs) const;
    const Vec2 operator/(float rhs) const;
    
    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;

public:
    float x;
    float y;
};

#endif // VEC2_H_INCLUDED
