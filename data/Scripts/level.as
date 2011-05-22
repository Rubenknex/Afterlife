int frameCounter = 0;
float timer = 0.0f;

void initialize()
{
    playMusic("data/Sounds/Ambience/ambience_1.ogg");

    setAmbientColor(90, 90, 90);

    addPointLight("lantern", Vec2(500.0f, 500.0f), 1.0f, 75.0f, 255, 230, 150, 16);
    addSpotLight("spot", Vec2(200.0f, 600.0f), 1.0f, 300.0f, 255, 230, 150, 0.0f, 15.0f);
    setLightState("spot", false);
}

void update(float dt)
{
    frameCounter += 1;
    timer += dt;

    setLightIntensity("lantern", rand(0.7f, 0.9f));
    setLightPosition("lantern", Vec2(500.0f + sin(timer) * 100.0f, 500.0f + cos(timer) * 100.0f));

    setLightAngle("spot", timer * 20.0f);

    if (isKeyDown("space"))
        setLightState("spot", true);
    else
        setLightState("spot", false);

    //if (getPlayerPosition().x > 500.0f)
        //stopMusic("data/Sounds/Ambience/ambience_1.ogg");

    if (getZombieCount() < 5)
    {
        addZombie(rand(100.0f, 300.0f), rand(100.0f, 300.0f));
    }

    if (frameCounter > 60)
    {
        //fireParticleSystem("blood_explode", getPlayerPosition());
        //playSound("data/Sounds/Weapons/grenade.wav", 100.0f, 1.0f);

        frameCounter = 0;
    }
}
