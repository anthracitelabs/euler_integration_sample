# euler_integration_sample
demonstration of euler integration (source gaffer on games)

## Explicit Euler

~~~~ C
	double t = 0.0;
    float dt = 1.0f;

    float velocity = 0.0f;
    float position = 0.0f;
    float force = 10.0f;
    float mass = 1.0f;

    while ( t <= 10.0 )
    {
        position = position + velocity * dt;
        velocity = velocity + ( force / mass ) * dt;
        t += dt;
    }
~~~~
