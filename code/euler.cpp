#include <stdio.h>

int main()
{
	printf("euler integration\n");

	/*
	 ***** Explicit Euler *****
	 * 
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
	 */
	
	/*
	 * Implicit Euler
	 * Mass: 1 kilogram
	 * Initial position: 1000 meters from origin
	 * Hooke’s law spring coefficient: k = 15
	 * Hooke’s law damping coefficient: b = 0.1
	 */
	
	
	 // ---- Simulation Parameters ----
    double mass = 1.0;          // Mass (m) in kg
    double k = 15.0;            // Spring stiffness constant (k) in N/m
    double c = 0.1;             // Damping coefficient (c) in N*s/m
    
    // ---- Initial Conditions ----
    double x = 1000.0;             // Displacement from equilibrium (meters)
    double v = 0.0;             // Velocity (meters/second)
    
    // ---- Time Configuration ----
    double t = 0.0;             // Start time (seconds)
    double dt = 0.01;           // Time step size (seconds)
    double t_max = 5.0;         // Total simulation time (seconds)

    // ---- Simulation Loop ----
    while (t <= t_max) {
        // 1. Calculate physical forces acting on the mass
        double spring_force = -k * x;
        double damping_force = -c * v;
        double total_force = spring_force + damping_force;

        // 2. Calculate acceleration (Newton's Second Law: F = ma)
        double acceleration = total_force / mass;

        // 3. Semi-Implicit Euler Integration (Update velocity first, then position)
        v += acceleration * dt;
        x += v * dt;

        // 4. Advance time
        t += dt;
    }
	
	
return 0; 
}
