//SMART TUNNEL AIRFLOW STABILIZATION SYSTEM (PID LOOP)
//CODE BY: Amith Mathew Titus & Anugraha M.
//DATE: 14/12/2024 -> 15/12/2024
//LICENSE: MIT License

#include "pid.h"
#define TIME_DELAY 100

static float Kp = 1; // Proportional gain
static float Ki = 0.5; // Integral gain
static float Kd = 0.01; // Derivative gain

static float integral = 0;     // Integral term
static float prev_error = 0;   // Previous error

float pid_control(float setpoint, float measured_value) {
    float error = setpoint - measured_value; // Calculate error
    integral += error * (TIME_DELAY / 1000.0); // Update integral (scaled by time)

    // Anti-windup: Clamp integral term
    if (integral > 255 / Ki) integral = 255 / Ki;
    if (integral < 0) integral = 0;

    float derivative = error - prev_error;  // Calculate derivative
    prev_error = error;                     // Update previous error
    return (Kp * error) + (Ki * integral) + (Kd * derivative); // Calculate PID output
}
