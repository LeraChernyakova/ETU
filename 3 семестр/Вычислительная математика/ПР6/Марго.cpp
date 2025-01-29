#include <iostream>

#include <cmath>

#define SIZE 4
double* Gauss(double** matr,double* b){
    double *x, max;
    int k, index;
    double eps = 0.00001;
    x = new double[SIZE];
    k = 0;
    while (k < SIZE)
    {
        max = abs(matr[k][k]);
        index = k;
        for (int i = k + 1; i < SIZE; i++)
        {
            if (abs(matr[i][k]) > max)
            {
                max = abs(matr[i][k]);
                index = i;
            }
        }


        if (max < eps)
        {

            std::cout << "Решение получить невозможно из-за нулевого столбца ";
            std::cout << index << " матрицы A\n";
            return 0;
        }

        for (int j = 0; j < SIZE; j++)
        {
            double temp = matr[k][j];
            matr[k][j] = matr[index][j];
            matr[index][j] = temp;
        }
        double temp = b[k];
        b[k] = b[index];
        b[index] = temp;

        for (int i = k; i < SIZE; i++)
        {
            double temp = matr[i][k];
            if (abs(temp) < eps)
                continue;


            for (int j = 0; j < SIZE; j++)
                matr[i][j] = matr[i][j] / temp;
            b[i] = b[i] / temp;

            if (i == k)
                continue;

            for (int j = 0; j < SIZE; j++)
                matr[i][j] = matr[i][j] - matr[k][j];
            b[i] = b[i] - b[k];
        }
        k++;
    }

    for (k = SIZE - 1; k >= 0; k--)
    {
        x[k] = b[k];
        for (int i = 0; i < k; i++)
            b[i] = b[i] - matr[i][k] * x[k];
    }

    return x;
}

int search(double** a, int m, int n, double what,
           bool match, unsigned int& uI, unsigned int& uJ, unsigned int starti, unsigned int startj) {
    if ((!m) || (!n)) return 0;
    if ((starti >= n) || (startj >= m)) return 0;
    for (unsigned int i = starti; i < n; i++)
        for (unsigned int j = startj; j < m; j++) {
            if (match == true) {
                if (a[i][i] == what) {
                    uI = i; uJ = j; return 1;
                }
            }
            else if (a[i][j] != what) {
                uI = i; uJ = j; return 1;
            }
        }
    return 0;
}

void swaprows(double** a, int n, int m, unsigned int x1, unsigned int x2) {
    if ((!n) || (!m)) return;
    if ((x1 >= n) || (x2 >= n) || (x1 == x2)) return;
    double tmp;
    for (unsigned int x = 0; x < m; x++) {
        tmp = a[x1][x];
        a[x1][x] = a[x2][x];
        a[x2][x] = tmp;
    }
    return;
};

void swapcolumns(double** a, int n, int m, unsigned int x1, unsigned int x2) {

    if ((!n) || (!m)) return;
    if ((x1 >= m) || (x2 >= m) || (x1 == x2)) return;
    double tmp;
    for (unsigned int x = 0; x < n; x++) {
        tmp = a[x][x1];
        a[x][x1] = a[x][x2];
        a[x][x2] = tmp;
    }
    return;
};

double determinant(double** a, unsigned int n) {
    unsigned int m = n;
    if (m == 0) return 0;
    if (m == 1) return a[0][0];
    if (m == 2) return (a[0][0] * a[1][1] - a[1][0] * a[0][1]);
    bool sign = false;
    double det = 1;
    double tmp;
    unsigned int x, y;
    for (unsigned int i = 0; i < n; i++) {
        if (a[i][i] == 0) {
            if (!search(a, m, n, 0, false, y, x, i, i)) return 0;
            if (i != y) {
                swaprows(a, m, n, i, y);
                sign = !sign;
            }
            if (i != x) {
                swapcolumns(a, m, n, i, x);
                sign = !sign;
            }

        }
        det *= a[i][i];
        tmp = a[i][i];
        for (x = i; x < m; x++) {
            a[i][x] = a[i][x] / tmp;
        }

        for (y = i + 1; y < n; y++) {
            tmp = a[y][i];
            for (x = i; x < m; x++)
                a[y][x] -= (a[i][x] * tmp);
        }
    }
    if (sign) return det * (-1);
    return det;
};

double minor(double **matr,int fi,int fj){
    double m=0.0;
    double **t_matr =  new double*[SIZE];
    for(int i=0;i<SIZE;i++){
        t_matr[i] = new double[SIZE];

    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            t_matr[j][i]=matr[i][j];
        }
    }
    double **A =  new double*[SIZE-1];
    for(int i=0;i<SIZE-1;i++){
        A[i] = new double[SIZE-1];

    }
    fi-=1,fj-=1;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(i!=fi && j!=fj){
                if(i>fi) {
                    if (j > fj)
                        A[i - 1][j - 1] = t_matr[i][j];
                    else
                        A[i - 1][j] = t_matr[i][j];
                }else{
                    if (j > fj)
                        A[i][j - 1] = t_matr[i][j];
                    else
                        A[i][j] = t_matr[i][j];
                }
            }
        }
    }

    m = (A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1]
            -A[0][2]*A[1][1]*A[2][0] - A[0][1]*A[1][0]*A[2][2] - A[0][0]*A[1][2]*A[2][1] );


    for(int i=0;i<SIZE;i++){
        delete t_matr[i];
    }
    delete[] t_matr;

    for(int i=0;i<SIZE-1;i++){
        delete A[i];
    }
    delete[] A;
    if((fi+fj)%2==0)
        return m;

    return (-1.0)*m;
}
void ReverseMatr(double** matr,double det){
    double **A =  new double*[SIZE];
    for(int i=0;i<SIZE;i++){
        A[i] = new double[SIZE];

    }


    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            //std::cout<<minor(matr,i+1,j+1)<<" ";
            A[i][j]=minor(matr,i+1,j+1)/det;
        }
       // std::cout<<"\n";
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            matr[i][j]=A[i][j];
        }
    }


    for(int i=0;i<SIZE;i++){
        delete A[i];
    }
    delete[] A;
}
double* ReverseMethod(double** rev_matr,double* b,double det){
    double* x= new double[SIZE];

    ReverseMatr(rev_matr,det);

    for(int i=0;i<SIZE;i++) {
        double tmp=0;
        for (int j = 0; j < SIZE; j++) {
            tmp+=rev_matr[i][j]*b[j];
        }
        x[i]=tmp;
    }
    return x;
}

int main() {

    double* x;
    double m[][4] =   {{4+std::rand()%100/1000.0,-6+std::rand()%100/1000.0,3+std::rand()%100/1000.0,3+std::rand()%100/1000.0},//16
                       {4+std::rand()%100/1000.0,-4+std::rand()%100/1000.0,3+std::rand()%100/1000.0,2+std::rand()%100/1000.0},//13
                       {5+std::rand()%100/1000.0,1+std::rand()%100/1000.0,-2+std::rand()%100/1000.0,-5+std::rand()%100/1000.0},//13
                       {10+std::rand()%100/1000.0,7+std::rand()%100/1000.0,5+std::rand()%100/1000.0,4+std::rand()%100/1000.0}};//26

    double mm[][4] =   {{4,-6,3,3},//16
                       {4,-4,3,2},//13
                       {5,1,-2,-5},//13
                       {10,7,5,4}};//26

    double bad[][4] =   {{4,1.0/2,3,1.0/4},
                        {4,1.0/3,3,1.0/5},
                        {5,1.0/4,-2,1.0/6},
                        {10,1.0/5,5,1.0/7}};

    double rev_m[][4]={{49.0/145.0,-54.0/145.0,3.0/29.0,9.0/145.0},//0.875862
                       {-52.0/435.0,7.0/435.0,-2.0/87.0,23.0/435.0},//0.2114941
                       {-162.0/145.0,217.0/145.0,-4.0/29.0,-12.0/145.0},//2.8344796
                       {331.0/435.0,-421.0/435.0,-4.0/87.0,46.0/435.0}}; //1.88046


    double **matr =  new double*[SIZE];
    for(int i=0;i<SIZE;i++){
        matr[i] = new double[SIZE];
    }

    double **dmatr =  new double*[SIZE];
    for(int i=0;i<SIZE;i++){
        dmatr[i] = new double[SIZE];
    }
    double **rev_matr =  new double*[SIZE];
    for(int i=0;i<SIZE;i++){
        rev_matr[i] = new double[SIZE];
    }


    std::srand(std::time(nullptr));
//    double x1=std::rand()%100/1000.0,x2=std::rand()%100/1000.0,x3=std::rand()%100/1000.0,x4=std::rand()%100/1000.0;
//    double b[]={-4+x1,0+x2,11+x3,3+x4};
    double b[]={-4,0,11,3};
//    std::cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<"\n";
//    std::cout<<"dB "<<(fabs(-4.0+b[0])+fabs(0.0-b[1])+fabs(11.0-b[2])+fabs(3.0-b[3]))/(18.0)<<"\n";
    double bb[4];
    for(int i=0;i<SIZE;i++)
        bb[i]=b[i];
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            matr[i][j] =bad[i][j];
            dmatr[i][j] =bad[i][j];
            rev_matr[i][j]=bad[i][j];
            std::cout<<matr[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
    //

    x = Gauss(matr, b);
    std::cout<<"GAUSS:\n";
    for(int i=0;i<SIZE;i++){
        std::cout<<"X"<<i+1<<": "<<x[i]<<"\n";
    }


    double det = determinant(dmatr,SIZE);
     std::cout<<det<<'\n';

    std::cout<<"\nREVERSE:\n";
    x = ReverseMethod(rev_matr, bb, det);
    for(int i=0;i<SIZE;i++){
        std::cout<<"X"<<i+1<<": "<<x[i]<<"\n";
    }
    double norm=0.0;
    for(int i=0;i<SIZE;i++)
    {
        double temp=0.0;
        for(int j=0;j<SIZE;j++)
            temp+=(double)fabs(mm[i][j]-bad[i][j]);
        //temp+=(double)fabs(matr[i][j]);
        if(temp>norm)
            norm=temp;
    }
    double norm2=0.0;
    //ReverseMatr(mm,det);
    for(int i=0;i<SIZE;i++)
    {
        double temp=0.0;
        for(int j=0;j<SIZE;j++)
            temp+=(double)fabs(mm[i][j]);
            //temp+=(double)fabs(rev_matr[i][j]);
        if(temp>norm2)
            norm2=temp;

    }
//X0: -0.0275862
//X1: 0.383908
//X2: 2.70345
//X3: -3.23218

//    X1: -0.0235586
//    X2: 0.377857
//    X3: 2.73774
//    X4: -3.25829

    std::cout<<"dA: "<<norm/norm2<<"\n";
//    std::cout<<"norma: "<<norm*norm2<<"\n";
    std::cout<<"dX"<<(fabs(-0.0275862-x[0])+fabs(0.377857-x[1])+fabs(2.73774-x[2])+fabs(-3.25829-x[3]))/(0.0275862+0.377857+2.73774+3.25829)<<"\n";

    for(int i=0;i<SIZE;i++){
        delete matr[i];
        delete rev_matr[i];
        delete dmatr[i];
    }
    delete[] matr;
    delete [] rev_matr;
    delete [] dmatr;


    return 0;
}
