#include "ContactListener.h"

#include "Entities/Entity.h"

ContactListener::ContactListener()
{
    
}

ContactListener::~ContactListener()
{
    
}

void ContactListener::BeginContact(b2Contact* contact)
{
    Entity* entityA = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Entity* entityB = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
    
    entityA->handleBeginContact(entityB);
    entityB->handleBeginContact(entityA);
}

void ContactListener::EndContact(b2Contact* contact)
{
    Entity* entityA = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Entity* entityB = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
    
    entityA->handleEndContact(entityB);
    entityB->handleEndContact(entityA);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    
}
