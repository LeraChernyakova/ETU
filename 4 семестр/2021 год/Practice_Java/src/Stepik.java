import java.math.BigInteger;

public class Stepik {

    public static int leapYearCount(int year) {
        int i = 0;
        while (year != 0){
            if ((year%4==0 && year%100!=0) || (year%400==0)) {
                i++;
            }
            year--;
        }
        return i;
    }
    public static boolean doubleExpression(double a, double b, double c) {
        return Math.abs((a+b)-c) < 0.00001;
    }
    public static char charExpression(int a) {
        return (char) ('\\' + a);
    }
    public static boolean isPalindrome(String text) {
        String replaced = text.toLowerCase().replaceAll("[^a-zA-Z0-9]", "");
        String reversed = new StringBuffer(replaced).reverse().toString();
        return reversed.equals(replaced);
    }
    public static BigInteger factorial(int value){
        BigInteger res = BigInteger.ONE;
        if (value == 0) return res;
        for (int i = 1; i <=value; ++i){
            res = res.multiply(BigInteger.valueOf(i));
        }
        return res;
    }
    public static double integrate(DoubleUnary0perator f, double a, double b) {
        double step = 0.000001;
        double result = 0;
        while (a < b) {
            result += f.applyAsDouble(a) * step;
            a += step;
        }
        return result;
    }
    public static void main(String[] args) {
        System.out.println(charExpression(32));
    }
    public static double sqrt(double x) throws java.lang.IllegalArgumentException {
        if (x < 0)
            throw new IllegalArgumentException("Expected non-negative number, gor " + x);
        else
            return Math.sqrt(x); // your implementation here
    }
    public static String getCallerClassAndMethodName(){
        if (Thread.currentThread().getStackTrace().length > 3){
            return Thread.currentThread().getStackTrace()[3].getClassName() + '#' + Thread.currentThread().getStackTrace()[3].getMethodName();
        }
        return null;
    }
}

