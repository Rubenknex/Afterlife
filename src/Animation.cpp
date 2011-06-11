#include "Animation.h"

Animation::Animation(int frameW, int frameH, int numX, int numY, int frameCount, float frameTime)
{
    mFrameCount = frameCount;

    for (int y = 0; y < numY; y++)
    {
        for (int x = 0; x < numX; x++)
        {
            if (mFrames.size() < frameCount)
                mFrames.push_back(sf::IntRect(x * frameW, y * frameH, frameW, frameH));
        }
    }

    mTimer = 0.0f;
    mFrameTime = frameTime;

    mPlaying = false;
    mMode = Single;
}

Animation::~Animation()
{

}

void Animation::update(float dt)
{
    if (mPlaying)
    {
        mTimer += dt;

        // If we have passed all the frames, either stop playing or set the timer to 0
        // according tot he current mode.
        if (mTimer > mFrameCount * mFrameTime)
        {
            if (mMode == Single)
                mPlaying = false;

            mTimer = 0.0f;
        }
    }
}

void Animation::pause()
{
    mPlaying = false;
}

void Animation::reset()
{
    mPlaying = false;
    mTimer = 0.0f;
}

void Animation::start(AnimationMode mode)
{
    if (!mPlaying)
    {
        mMode = mode;
        mPlaying = true;
    }
}

const sf::IntRect& Animation::getRect()
{
    int currentFrame = mTimer / mFrameTime;

    return mFrames[currentFrame];
}
