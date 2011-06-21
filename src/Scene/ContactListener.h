#ifndef CONTACTLISTENER_H_INCLUDED
#define CONTACTLISTENER_H_INCLUDED

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    ~ContactListener();

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // CONTACTLISTENER_H_INCLUDED
