#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int rk4(double *t, double *y, double senyal, int n, double *h, int (* camp)(double *t, double *y,  double senyal, int n, double *g)){
        int iflat, i;
        double t1;
        double senyal_1, *f, *k1, *k2, *k3, *k4, *y1;
	
        /* --------------- */
        /* Guardem memoria */
        /* --------------- */
        f = (double *)malloc(n*sizeof(double));
        if(f == NULL){
                printf("no tenim prou memoria rk4, vector f");
                exit(1);
        }

        k1 = (double *)malloc(n*sizeof(double));
        if(k1 == NULL){
                printf("no tenim prou memoria rk4, vector k1");
                exit(1);
        }

        k2 = (double *)malloc(n*sizeof(double));
        if(k2 == NULL){
                printf("no tenim prou memoria rk4, vector k2");
                exit(1);
        }

        k3 = (double *)malloc(n*sizeof(double));
        if(k3 == NULL){
                printf("no tenim prou memoria rk4, vector k3");
                exit(1);
        }

        k4 = (double *)malloc(n*sizeof(double));
        if(k4 == NULL){
                printf("no tenim prou memoria rk4, vector k4");
                exit(1);
        }

        y1 = (double *)malloc(n*sizeof(double));
        if(y1 == NULL){
                printf("no tenim prou memoria rk4, vector y1");
                exit(1);
        }

        /* ----------- */
        /* Calculem k1 */
        /* ----------- */
        t1 = *t;
        iflat = camp(&t1, y, senyal, n, f);
        if(iflat == 0) return 0;
        for(i = 0; i < n; i++)
                k1[i] = *h*f[i];

	
        /* ----------- */
        /* Calculem k2 */
        /* ----------- */
        t1 = *t + 0.5*(*h);
        for(i = 0; i < n; i++)
		y1[i] = y[i] + 0.5*k1[i];

	senyal_1 = senyal + 0.5*k1[0];
	
        iflat = camp(&t1, y1, senyal_1, n, f);
        if(iflat == 0) return 0;
        for(i = 0; i < n; i++)
                k2[i] = *h*f[i];
		
	
        /* ----------- */
        /* Calculem k3 */
        /* ----------- */
	for(i = 0; i < n; i++)
        	y1[i] = y[i] + 0.5*k2[i];
		
	senyal_1 = senyal + 0.5*k2[0];
	
	iflat = camp(&t1, y1, senyal_1, n, f);
        if(iflat == 0) return 0;
        for(i = 0; i < n; i++)
                k3[i] = *h*f[i];

        /* ----------- */
        /* Calculem k4 */
        /* ----------- */
        *t = *t + *h;
	for(i = 0; i < n; i++)
        	y1[i] = y[i] + k3[i];
	
	senyal_1 = senyal + k3[0];

        iflat = camp(t, y1, senyal_1, n, f);
        if(iflat == 0) return 0;
        for (i = 0; i < n; i++)
                k4[i] = *h*f[i];
	
        /* ----------------------- */
        /* Calculem resultat final */
        /* ----------------------- */
        
	for (i = 0; i < n; i++)
                y[i] = y[i] + (k1[i]+2.0*k2[i]+2.0*k3[i]+k4[i])/6.0;

return(1);
}
