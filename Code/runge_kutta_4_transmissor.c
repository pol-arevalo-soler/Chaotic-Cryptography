#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double sigma = 10.0, b = 8./3, r = 28.0;

int rk4(double *, double *, int , double *, int (* camp)(double *, double *, int , double *));
int lorenz(double *, double *, int , double *);

int main(void){
        int i, n, iflat, num_rk;
        double t, h, t_fin, m, s, *y, *f;
        FILE *sortida, *din, *error, *privat;

        sortida = fopen("rk4_tr.res", "w");
	din = fopen("din_tr.res", "w");
	error = fopen("error_tr.res", "w");
	privat = fopen("rk4_privat.res", "w");	

	if(privat == NULL){
		printf("Mal fitxer privat \n");
		exit(1);
	}

	if(error == NULL){
		printf("Mal fitxer sortida \n");
		exit(1);
	}
	if(sortida == NULL){
		printf("Mal fitxer sortida \n");
		exit(1);
	}
	if(din == NULL){
		printf("Mal fitxer din \n");	
		exit(1);
	}

        n = 3;

        y = (double *) malloc(n*sizeof(double));
        if(y == NULL){
                printf("no tenim prou memoria main, vector y");
                exit(1);
        }

        f = (double *) malloc(n*sizeof(double));
        if(f == NULL){
                printf("no tenim prou memoria main, vector f");
                exit(1);
        }

        /* --------------------------------------------------------------- */
	/* Llegeixo temps incial, condicions inicials, pas h i temps final */
        /* --------------------------------------------------------------- */

        printf("Temps inicial t0 = \n");
        scanf("%le", &t);

	printf("Temps final t_fin = \n");
	scanf("%le", &t_fin);
	
	printf("Pas h = \n");
	scanf("%le", &h);
	        
	printf("Condicions inicials x0, \t y0, \t z0 = \n");
        for (i = 0; i < n; i++)
                scanf("%le", &y[i]);
        
	fprintf(privat, "%+25.10le %+25.10le %+25.10le \n", t, t_fin, h);
	
        num_rk = 0;

        do{
		m = sin(10*t);
		s = m + y[0];
		fprintf(sortida, "%+25.10le \n", s);

                fprintf(din, "%+25.10le %+25.10le %+25.10le %+25.10le \n", t, y[0], m, s);

                fprintf(error, "%+25.10le \n", m);

                iflat = rk4(&t, y, n, &h, lorenz);
                if(iflat != 1){
                        printf("No puc integrar \n");
                	exit(1);
                }

                num_rk++;
        }while(t < t_fin);

        free(y);
        free(f);
        fclose(sortida);
	fclose(privat);
	fclose(error);
	fclose(din);

return(0);
}

int lorenz(double *t, double *y, int n, double *f){
        f[0] = sigma*y[1] - sigma*y[0];
        f[1] = y[0]*r - y[0]*y[2] - y[1];
        f[2] = y[0]*y[1] - b*y[2];

return(1);
}
