void initialize()
{
    playMusic("data/Sounds/Ambience/ambience_1.ogg");
    
    setAmbientColor(60, 60, 60);
    
    addWeaponPickup("data/Weapons/ak47.xml", Vec2(500.0f, 500.0f));
    addWeaponPickup("data/Weapons/uzi.xml", Vec2(600.0f, 500.0f));
    addWeaponPickup("data/Weapons/famas.xml", Vec2(500.0f, 600.0f));
}

float timer = 0.0f;
float lightSwitchTimer = 0.0f;

void update(float dt)
{
    timer += dt;
    
    lightSwitchTimer -= dt;
    
    if (lightSwitchTimer < 0.0f)
    {
        setLightIntensity("lantern2", rand(0.1f, 0.5f));

        lightSwitchTimer = rand(0.1f, 0.3f);
    }
    
    setLightIntensity("lantern", rand(0.5f,0.7f));   
    
    if (getZombieCount() < 5)
    {
        addZombie(rand(100.0f, 1000.0f), rand(100.0f, 1000.0f));
    }
}
