package lab2;

public interface CustomQueue<T> {

    void add(T element);

    T take() throws InterruptedException;
}
