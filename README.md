# euler_integration_sample
demonstration of euler integration (source [article](https://gafferongames.com/post/integration_basics/))

## Explicit Euler

If the acceleration is constant (F/m in the following example, both are constant) explicit euler is close enough to calculate velocity and position, with a delta time small enough.

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

## Semi-Implicit Euler 

For a spring damper system acceleration changes over each step and above method does not work. For a changing acceleration semi-implicit euler integration is used for close enough results.   

Most commercial game physics engines use this integrator.

Switching from explicit to semi-implicit euler is as simple as changing:

~~~~ C
    position += velocity * dt;
    velocity += acceleration * dt;
~~~~

to:

~~~~ C
    velocity += acceleration * dt;
    position += velocity * dt;
~~~~
