#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED
 
#include <cmath>
#include <SFML/System.hpp>
#include <vector>
 
namespace math
{
/// Returns a random number between start and end.
template <class T>
T rand(T start, T end)
{
    return sf::Randomizer::Random(start, end);
}
 
/// Linearly interpolates two values.
template <class T>
T lerp(T start, T end, T val)
{
    return start + (end - start) * val;
}
 
/// Returns a value clamped between min and max.
template <class T>
T clamp(T value, T min, T max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
 
    return value;
}
 
/// Convert degrees to radians.
template <class T>
T radians(T degrees)
{
    return degrees * (M_PI / 180);
}
 
/// Convert radians to degrees.
template <class T>
T degrees(T radians)
{
    return radians * (180 / M_PI);
}
 
/// Linearly interpolates two vectors.
template <class T>
sf::Vector2<T> lerp(sf::Vector2<T> start, sf::Vector2<T> end, float val)
{
    float x = start.x + (end.x - start.x) * val;
    float y = start.y + (end.y - start.y) * val;
 
    return sf::Vector2<T>(x, y);
}
 
/// Returns the length of a vector.
template <class T>
T length(sf::Vector2<T> v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
 
/// Returns the squared length of a vector, quick because it doesn't use sqrt.
template <class T>
T lengthSquared(sf::Vector2<T> v)
{
    return v.x * v.x + v.y * v.y;
}
 
/// Returns the absolute distance between two vectors.
template <class T>
float distance(const sf::Vector2<T>& vec1, const sf::Vector2<T>& vec2)
{
    T xDist = vec2.x - vec1.x;
    T yDist = vec2.y - vec1.y;
 
    return sqrt(xDist * xDist + yDist * yDist);
}
 
/// Returns the squared distance between two vectors, quick because it doesn't use sqrt.
template <class T>
T distanceSquared(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
{
    T diffX = v2.x - v1.x;
    T diffY = v2.y - v1.y;
 
    return diffX * diffX + diffY * diffY;
}
 
/// Returns the cross product of a vector, or the vector perpendicular to it.
template <class T>
sf::Vector2<T> cross(const sf::Vector2<T>& vec)
{
    return sf::Vector2<T>(vec.y, -vec.x);
}
 
/// Normalize a vector, that is, make it's length equal 1.
template <class T>
sf::Vector2<T> normalize(const sf::Vector2<T>& vec)
{
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
 
    return sf::Vector2<T>(vec.x / length, vec.y / length);
}
 
template <class T>
T catmullRom(T val1, T val2, T val3, T val4, float amount)
{
    float t2 = amount * amount;
    float t3 = t2 * amount;
 
    T out = 0.5f * ((2.0f * val2) + (-val1 + val3) * amount +
                    (2.0f * val1 - 5.0f * val2 + 4.0f * val3 - val4) * t2 +
                    (-val1 + 3.0f * val2 - 3.0f * val3 + val4) * t3);
 
    return out;
}
 
template <class T>
sf::Vector2f catmullRom(const sf::Vector2f& val1, const sf::Vector2f& val2, const sf::Vector2f& val3, const sf::Vector2f& val4, float amount)
{
    sf::Vector2f result;
 
    result.x = catmullRom(val1.x, val2.x, val3.x, val4.x, amount);
    result.y = catmullRom(val1.y, val2.y, val3.y, val4.y, amount);
 
    return result;
}
 
template <class T>
std::vector<sf::Vector2<T> > interpolateCatmullRom(const sf::Vector2<T>& val1, const sf::Vector2<T>& val2, const sf::Vector2<T>& val3, const sf::Vector2<T>& val4, int detail)
{
    std::vector<sf::Vector2<T> > points;
 
    for (int i = 0; i < detail; i++)
    {
        sf::Vector2<T> newPoint = math::catmullRom(val1, val2, val3, val4, (float)i / (float)detail);
        points.push_back(newPoint);
    }
 
    return points;
}
}
 
#endif // MATH_H_INCLUDED
 
