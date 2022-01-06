#include "my_solver.h"


void program3_4() {
    int i, ia, j, n;
    int* l;
    float* a;
    float* b;
    float* s;
    float* x;
    float* back_up_a;
    float* back_up_b;

    /********************************/

    /// 텍스트 파일 바꾸시면 됩니다!!
    FILE* fp_r = fopen("Hilbert_32.txt", "r");
    ///
    
    FILE* fp_w = fopen("solution_3-4.txt", "w");
    fscanf(fp_r, "%d", &n);

    a = (float*)malloc(sizeof(float) * (n * n));
    b = (float*)malloc(sizeof(float) * n);
    x = (float*)malloc(sizeof(float) * n);
    s = (float*)malloc(sizeof(float) * n);

    l = (int*)malloc(sizeof(int) * n);

    back_up_a = (float*)malloc(sizeof(float) * (n*n));
    back_up_b = (float*)malloc(sizeof(float) * n);


    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            fscanf(fp_r, "%f", &a[i + j * n]);
        }
    }

    for (int i = 0; i < n; i++)
        fscanf(fp_r, "%f", &b[i]);

    ia = n;

    printf("---------------------------------------------------\n");
    printf("<<<   matrix A   >>>\n\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%6lf  ", a[i + j * n]);
            back_up_a[i + j * n]= a[i + j * n];
        }
        printf("\n");
    }

    printf("---------------------------------------------------\n");

    printf("\n\n---------------------------------------------------\n");
    printf("<<<   matrix B   >>>\n\n");
    for (i = 0; i < n; i++) {
        printf("%6lf  ", b[i]);
        back_up_b[i] = b[i];
    }
    gespp_(&n, a, &ia, l, s);

    printf("\n---------------------------------------------------\n");

    printf("\n\n---------------------------------------------------\n");
    printf("<<<   Result of gespp_   >>>\n\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%6lf  ", a[i + j * n]);
        }
        printf("\n");
    }

    printf("---------------------------------------------------\n");

    solve_(&n, a, &ia, l, b, x);

    printf("\n\n---------------------------------------------------\n");
 
    printf("<<<  Result of solve_   >>>\n\n");

    float* func = (float*)malloc(sizeof(float) * n);

    double AX_B = 0.0;
    double B = 0.0;


    for (i = 0; i < n; i++) {
        double sum = 0.0;
        for (j = 0; j < n; j++) {
            sum += back_up_a[i + j * n] * x[j];

        }

        sum -= back_up_b[i];
        sum = pow(sum, 2);

        AX_B += sum;
        B += pow(back_up_b[i], 2);

        func[i] = fabs(sum);
    }


    for (i = 0; i < n; i++) {
        printf("x[%d] : %.5e\t\t\tFunc : %.5e\n", i, x[i], func[i]);
        //fprintf(fp_w,"x[%d] : %.5lf\t\tFunc : %.5lf \n", i, x[i], func[i]);
        fprintf(fp_w, "x[%d] : %.5e\n", i, x[i]);
    }

    printf("\n\n<<<   ||Ax-b|| / || b ||   >>>\n");
    printf("%.5e\n", sqrt(AX_B) / sqrt(B));

    fprintf(fp_w,"\n\n<<<   ||Ax-b|| / || b ||   >>>\n");
    fprintf(fp_w, "%.5e\n", sqrt(AX_B) / sqrt(B));
   

    printf("---------------------------------------------------\n");

    fclose(fp_r); fclose(fp_w);

    free(a); free(b); free(s); free(x); free(func);
    free(back_up_a); free(back_up_b);
    /********************************/
}