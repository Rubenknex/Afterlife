void initialize()
{
    //playMusic("data/Sounds/Ambience/ambience_1.ogg");

    loadParticleSystem("data/ParticleSystems/blood.json");
    loadParticleSystem("data/ParticleSystems/dust.json");

    addPlayer("player", Vec2(200.0, 200.0));

    addZombie("zombie_1", Vec2(100.0, 100.0));
    addZombie("zombie_2", Vec2(300.0, 100.0));
    addZombie("zombie_3", Vec2(200.0, 400.0));
}

float timer = 0.0f;

void update(float dt)
{
    timer += dt;

    setLightIntensity("ambient_point_1", rand(0.6f, 0.9f));

    float spotAngle = getLightAngle("ambient_spot_1");
    setLightAngle("ambient_spot_1", spotAngle + 0.4f);

    setLightIntensity("ambient_spot_1", 0.5f + sin(timer * 2.0f) / 2.0f);
}
