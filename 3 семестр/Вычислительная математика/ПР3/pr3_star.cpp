#include <iostream>
#include <cmath>

double F(double x, double c)
{
    return c * cos(x);
}

double F_shtrih(double x, double c)
{
    return -c * sin(x);
}

double truncRound(double x, double epsilon)
{
    return trunc(x / epsilon) * epsilon;
}

double BISECT(double Left, double Right, double Eps, int &N, double c)
{
    double E = fabs(Eps) * 2.0;
    double FLeft = F(Left, c);
    double FRight = F(Right, c);
    double X = (Left + Right) / 2.0;
    double Y;
    if (FLeft * FRight > 0.0)
    {
        puts("neverno zadan interval\n");
        exit(1);
    }
    if (Eps <= 0.0)
    {
        puts("neverno zadana tochnost\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0)
        return Left;
    if (FRight == 0.0)
        return Right;
    while ((Right - Left) >= E)
    {
        X = 0.5 * (Right + Left);
        Y = F(X, c);
        if (Y == 0.0)
            return (X);
        if (Y * FLeft < 0.0)
            Right = X;
        else
        {
            Left = X;
            FLeft = Y;
        }
        N++;
        std::cout << "X_" << N << " = " << truncRound(X, Eps) << " " << F(truncRound(X, Eps), c) << '\n';
    };
    return (X);
}

double BISECT_2(double Left, double Right, double Eps, int &N, double c)
{
    double E = fabs(Eps) * 2.0;
    double FLeft = F(Left, c);
    double FRight = F(Right, c);
    double X = (Left + Right) / 2.0;
    double Y;
    if (FLeft * FRight > 0.0)
    {
        puts("neverno zadan interval\n");
        exit(1);
    }
    if (Eps <= 0.0)
    {
        puts("neverno zadana tochnost\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0)
        return Left;
    if (FRight == 0.0)
        return Right;
    while (N < 30)
    {
        X = 0.5 * (Right + Left);
        Y = F(X, c);
        if (Y == 0.0)
            return (X);
        if (Y * FLeft < 0.0)
            Right = X;
        else
        {
            Left = X;
            FLeft = Y;
        }
        N++;
        std::cout << "X_" << N << " = " << X << " " << F(X, c) << '\n';
    };
    return (X);
}

double Round(double X, double Delta)
{
    if (Delta <= 1E-9)
    {
        puts("Неверно задана точность округления\n");
        exit(1);
    }
    if (X > 0.0)
        return (Delta * (long((X / Delta) + 0.5)));
    else
        return (Delta * (long((X / Delta) - 0.5)));
}

double HORDA(double Left, double Right, double Eps, int &N, double c)
{
    double FLeft = F(Left, c);
    double FRight = F(Right, c);
    double X, Y;
    if (FLeft * FRight > 0.0)
    {
        puts("Неверное задание интервала\n");
        exit(1);
    }
    if (Eps <= 0.0)
    {
        puts("Неверное задание точности\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0)
    {
        return Left;
    }
    if (FRight == 0.0)
    {
        return Right;
    }
    do
    {
        X = Left - (Right - Left) * FLeft / (FRight - FLeft);
        Y = F(X, c);
        if (Y == 0.0)
        {
            return X;
        }
        if (Y * FLeft < 0.0)
        {
            Right = X;
            FRight = Y;
        }
        else
        {
            Left = X;
            FLeft = Y;
        }
        N++;
        // std::cout << "X_" << N << " = " << X << " " << F(X, c) << '\n';
        std::cout << "X_" << N << " = " << truncRound(X, Eps) << " " << F(truncRound(X, Eps), c) << '\n';
    } while (fabs(Y) >= Eps);
    return X;
}

double HORDA_2(double Left, double Right, double Eps, int &N, double c)
{
    double FLeft = F(Left, c);
    double FRight = F(Right, c);
    double X, Y;
    if (FLeft * FRight > 0.0)
    {
        puts("Неверное задание интервала\n");
        exit(1);
    }
    if (Eps <= 0.0)
    {
        puts("Неверное задание точности\n");
        exit(1);
    }
    N = 0;
    if (FLeft == 0.0)
    {
        return Left;
    }
    if (FRight == 0.0)
    {
        return Right;
    }
    do
    {
        X = Left - (Right - Left) * FLeft / (FRight - FLeft);
        Y = F(X, c);
        if (Y == 0.0)
        {
            return X;
        }
        if (Y * FLeft < 0.0)
        {
            Right = X;
            FRight = Y;
        }
        else
        {
            Left = X;
            FLeft = Y;
        }
        N++;
        std::cout << "X_" << N << " = " << X << " " << F(X, c) << '\n';
    } while (N < 30);
    return X;
}

int main()
{
    double c;
    double Epsilon;
    double Delta;
    int N;

    std::cout << "C            = ";
    std::cin >> c;
    std::cout << "Epsilon      = ";
    std::cin >> Epsilon;
    std::cout << "Delta        = ";
    std::cin >> Delta;

    double X = HORDA(1.5, 2, Epsilon, N, c);
    std::cout << "X            = " << X << '\n';
    std::cout << "F(x)         = " << Round(F(X, c), Delta) << '\n';
    std::cout << "N            = " << N << '\n';
    std::cout << "Nu_Delta     = " << fabs(1 / F_shtrih(X, c)) << '\n';
    std::cout << "Nu_Delta_max = " << Epsilon / Delta << '\n';

    return 0;
}
