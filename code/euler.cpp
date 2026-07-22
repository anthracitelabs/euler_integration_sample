#include <windows.h>
#include <stdint.h>
#include <stdio.h>


uint64_t globalPerfCounterFrequency;

inline float Win32GetSecondsElapsed(uint64_t start, uint64_t End)
{
	float result = 0;
	result = (float)(End - start) / (float)globalPerfCounterFrequency;
	return result;
}

inline uint64_t Win32GetPerfCounter()
{
	LARGE_INTEGER result;
	QueryPerformanceCounter(&result);
	return result.QuadPart;
}

int main()
{
	printf("Euler integration - Semi-Implicit Euler\n");

	/*
	 * Implicit Euler
	 * Mass: 1 kilogram
	 * Initial position: 1000 meters from origin
	 * Hooke’s law spring coefficient: k = 15
	 * Hooke’s law damping coefficient: b = 0.05
	 */

	// ---- Simulation Parameters ----
	double mass = 1.0;          // Mass (m) in kg
	double k = 15.0;            // Spring stiffness constant (k) in N/m
	double c = 0.05;             // Damping coefficient (c) in N*s/m

	// ---- Initial Conditions ----
	double x = 1000.0;             // Displacement from equilibrium (meters)
	double v = 0.0;             // Velocity (meters/second)

	// ---- Time Configuration ----
	double t = 0.0;             // Start time (seconds)
	double dt = 0.01;           // Time step size (seconds)
	double t_max = 1000.0;         // Total simulation time (seconds)

	bool sleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);

	float targetSecondsPerFrame = 1.0f / 100.0f;

	LARGE_INTEGER counterPerSecond;
	QueryPerformanceFrequency(&counterPerSecond);
	globalPerfCounterFrequency = counterPerSecond.QuadPart;

	uint64_t lastCounter = Win32GetPerfCounter();

	printf("\n\n\n");

	char str[150];
	// ---- Simulation Loop ----
	while (t <= t_max) {

		int full_spring = 1000 + x;
		int normalized = (full_spring / 2000.0) * 100;
		for (int i = 0; i < 100; i++) 
		{
			if(i == 99)
				str[99] = '\0';
			else if(i >= normalized)
				str[i] = ' ';
			else
				str[i] = '~';
		}
		printf("\r%s", str);
		//printf("t = %f\tx = %f\tv = %f\n", t, x, v);

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

		// Lock the frame rate
		float secondsElapsed = Win32GetSecondsElapsed(lastCounter, Win32GetPerfCounter());
		if(secondsElapsed < targetSecondsPerFrame) {
			if(sleepIsGranular) {
				DWORD sleepMS = (DWORD)(1000 * (targetSecondsPerFrame - secondsElapsed));
				if(sleepMS > 5.0) 
				{
					Sleep(sleepMS - 4.0);
				}
			}

			// spin lock for remaining time
			while(secondsElapsed < targetSecondsPerFrame) 
			{
				secondsElapsed = Win32GetSecondsElapsed(lastCounter, Win32GetPerfCounter());
			}
		} 
		else 
		{
			// We missed a frame
		}

		lastCounter = Win32GetPerfCounter();
	}

	timeEndPeriod(1);

	return 0; 
}
