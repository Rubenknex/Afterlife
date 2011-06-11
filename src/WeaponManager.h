#ifndef WEAPONMANAGER_H_INCLUDED
#define WEAPONMANAGER_H_INCLUDED
 
#include <map>
 
#include "Weapon.h"
 
class WeaponManager
{
public:
    WeaponManager();
    ~WeaponManager();
 
    void load(shared_ptr<ProjectileManager> pm, const std::string& filename);
 
 
private:
 
};
 
#endif // WEAPONMANAGER_H_INCLUDED
 
