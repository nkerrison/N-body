#include <stdio.h>
#include <math.h>

// vector data type idea from rosettacode.org/wiki/N-body_problem

typedef struct
{
	double x, y, z;
}vector;

vector scale(double a, vector r)
{
  vector s = {a*r.x, a*r.y, a*r.z};
  return s;
}

vector add(vector r1, vector r2)
{
  vector s = {r1.x+r2.x, r1.y+r2.y, r1.z+r2.z};
  return s;
}

vector subtract(vector r1, vector r2)
{
  vector s = {r1.x-r2.x, r1.y-r2.y, r1.z-r2.z};
  return s;
}

double norm(vector r)
{
  return sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
}

vector acceleration(vector r1, vector r2, int m1)
{
  int G = 1;
  vector r, accel;
  double normr, normrCubed;
  r = subtract(r2, r1);
  normr = norm(r);
  accel = scale(G * m1/pow(normr, 3), r);
  return accel;
}

int main()
{
  // variables and arrays
  int t;
  int m_SirA = 10, m_SirB = 1;
  double h = 0.01;
  vector r_SirA[1000], v_SirA[1000];
  vector r_SirB[1000], v_SirB[1000];

  // initial positions and velocities
  r_SirA[0] = {1.0, 0.0, 0.0};
  r_SirB[0] = {-1.0, 0.0, 0.0};
  v_SirA[0] = {0.0, 0.05, 0.0};
  v_SirB[0] = {0.0, -0.5, 0.0};

  // create file for writing
  FILE *fp;
  fp = fopen("Euler_data.csv", "w");

  // Euler method
  for(t = 0; t < 1000; t++)
  {
    v_SirA[t+1] = add(v_SirA[t], scale(h, acceleration(v_SirB[t], v_SirA[t], m_SirB)));
    r_SirA[t+1] = add(r_SirA[t], scale(h, v_SirA[t]));
    v_SirB[t+1] = add(v_SirB[t], scale(h, acceleration(v_SirA[t], v_SirB[t], m_SirA)));
    r_SirB[t+1] = add(r_SirB[t], scale(h, v_SirB[t]));

    fprintf(fp, "%lf, %lf, %lf, %lf\n", v_SirA[t+1], r_SirA[t+1], v_SirB[t+1], r_SirB[t+1]);
  }

  fclose (fp);

  return 0;
}
