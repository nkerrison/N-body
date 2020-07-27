#include <stdio.h>
#include <math.h>

int main()
{
  int t;
  double x[1000], v[1000], h=0.01;

  FILE *fp;
  fp = fopen("data.csv", "w");

  // fprintf(fp, "position, velocity\n");

  for(t = 0; t < 1000; t++)
  {
    x[t] = sin(t) + cos(t) * h;
    v[t] = cos(t) - sin(t) * h;

    fprintf(fp, "%f, %f\n", x[t], v[t]);
  }

  fclose (fp);

  return 0;
}
