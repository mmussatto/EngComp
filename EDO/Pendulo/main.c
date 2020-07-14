#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define gravit 9.8

float f1(float t, float Vx)
{//derivada de x
   return(Vx);	     
}

float f2(float t, float Vy)
{//derivada de y
    return(Vy);
}

float f3(float t, float x, float T)
{//derivada de Vx
    return(-( T * x ));
}

float f4(float t, float y, float T)
{//derivada de Vy
    return(-( T * y ) - gravit);
}

float f5(float t, float Vy)
{//derivada de T
    return (-3 * gravit * Vy);
}


int main()
{

    FILE *file;

    int i, j, n;
    float x, y, Vx, Vy, T, t; 
    float x_euler, y_euler, Vx_euler, Vy_euler, T_euler; //preditor
    float x0, y0, V_x0, V_y0, T0, h, tfim; //condicoes iniciais
    float k1, k2, k3, k4, k5; //derivadas

    file = fopen("saida.txt", "w");
    if(file == NULL)
    {
        printf("\nProblemas na abertura do arquivo\n");
        return 0;
    }

    
    //condicoes inicias
    x0 = 1.0; 
    y0 = 0.0;
    V_x0 = 0;
    V_y0 = 0;
    T0 = 0;
    t = 0;

    //passo
    h = 0.001; 

    //limite
    tfim = 3.0;

    //numero de interções
    n = (int)((tfim - 0)/h);
    
    x = x0;
    y = y0;
    Vx = V_x0;
    Vy = V_y0;
    T = T0;
    
    fprintf(file, "t \t x\ty\tVx\tVy\tT    \n");
    fprintf(file, "%f\t%f\t%f\t%f\t%f\t%f \n", t, x, y, Vx, Vy, T );

    for (i = 0; i < n; i++) 
    {
        k1 = f1(t, Vx);
        k2 = f2(t, Vy);
        k3 = f3(t, x, T);
        k4 = f4(t, y, T);
        k5 = f5(t, Vy);

        //preditor
        x_euler = x + h * k1;
        y_euler = y + h * k2;
        Vx_euler = Vx + h * k3;
        Vy_euler = Vy + h * k4;
        T_euler = T + h * k5;

        //corretor
        x = x + h/2 * (k1 + f1(t, Vx_euler));
        y = y + h/2 * (k2+ f2(t,Vy_euler));
        Vx = Vx + h/2 * (k3 + f3(t, x_euler, T_euler));
        Vy = Vy + h/2 * (k4 + f4(t, y_euler, T_euler));
        T = T + h/2 * (k5 + f5(t, Vy_euler));
        
        //passo
        t = t + h;

        fprintf(file, "%f\t%f\t%f\t%f\t%f\t%f \n", t, x, y, Vx, Vy, T );
    }

    fclose(file);

    return 0;
}
