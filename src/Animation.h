#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

/// Animation provides frames for animation sprite sheets.
class Animation
{
public:
    enum AnimationMode
    {
        Loop,
        LoopReverse,
        Single,
        SingleReverse,
    };

public:
    Animation(int frameW, int frameH, int numX, int numY, int frameCount, float frameTime);
    ~Animation();

    void update(float dt);

    void pause();
    void reset();
    void start(AnimationMode mode);

    const sf::IntRect& getRect();

private:
    int mFrameCount;
    std::vector<sf::IntRect> mFrames;
    float mTimer;
    float mFrameTime;
    bool mPlaying;
    AnimationMode mMode;
};

#endif // ANIMATION_H_INCLUDED
