#include <stdio.h>

int main()
{
	printf("euler integration\n");

	/*
	 * Mass: 1 kilogram
	 * Initial position: 1000 meters from origin
	 * Hooke’s law spring coefficient: k = 15
	 * Hooke’s law damping coefficient: b = 0.1
	 */
	
	double t = 0.0;
    float dt = 1.0f / 100.0f;

    float velocity = 0.0f;
    float position = 0.0f;
    float force = 10.0f;
    float mass = 1.0f;

    while ( t <= 10.0 )
    {
		printf("t = %f\tposition = %f\tvelocity = %f\n", t, position, velocity);

        position = position + velocity * dt;
        velocity = velocity + ( force / mass ) * dt;
        t += dt;
    }
	
return 0; 
}
