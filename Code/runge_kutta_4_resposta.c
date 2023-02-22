#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double sigma = 10.0, b = 8./3, r = 28.0;

int rk4(double *, double *, double, int, double *, int (* camp)(double *, double *, double, int , double *));
int lorenz(double *, double *, double, int, double *);

int main(void){
        int i, n, iflat, num_rk;
        double t, h, t_fin, m, *y, *f, senyal;
        FILE *privat, *sortida, *entrada, *din, *error;
	
	/* --------------------------------------------------------------------------------------------------- */
	/* Dos fitxers: 1.- rk4_re.res envia per fitxer x_r(t). 2.- din_re.res envia t, x_r(t), y_r(t), z_r(t) */
	/* --------------------------------------------------------------------------------------------------- */
	
	error = fopen("error_re.res", "w");
	sortida = fopen("rk4_re.res", "w");
        entrada = fopen("rk4_tr.res", "r");
	din = fopen("din_re.res", "w");	
	privat = fopen("rk4_privat.res", "r");
	
	if(privat == NULL){
		printf("Mal fitxer \n");
		exit(1);
	}
	
	if(error == NULL){
		printf("mal fitxer \n");
		exit(1);
	}

	if(sortida == NULL){
		printf("No memoria \n");
		exit(1);
	}
	
	if(entrada == NULL){
		printf("Mal fitxer \n");
		exit(1);
	}

	if(din == NULL){
		printf("Mal fitxer \n");
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

	fscanf(privat, "%le %le %le", &t, &t_fin, &h);
		
	printf("Condicions inicials x0, \t y0, \t z0 = \n");
        for (i = 0; i<n; i++)
                scanf("%le", &y[i]);

        num_rk = 0;

        do{
		fscanf(entrada, "%le ", &senyal);	
		
		m = senyal - y[0];	
			
		fprintf(sortida, "%+25.10le %+25.10le %+25.10le \n", t, y[0], m);
	
		fprintf(error, "%+25.10le \n", m);
	
                iflat = rk4(&t, y, senyal, n, &h, lorenz);
                if(iflat != 1){
                        printf("No puc integrar \n");
                        exit(1);
                }
		
                num_rk++;
        }while(t < t_fin);
	
        free(y);
        free(f);
        fclose(sortida);
	fclose(entrada);
	fclose(error);	

return(0);
}

int lorenz(double *t, double *y, double senyal, int n, double *f){
	f[0] = sigma*y[1] - sigma*y[0];
        f[1] = senyal*r - senyal*y[2] - y[1];
        f[2] = senyal*y[1] - b*y[2];

return(1);
}
