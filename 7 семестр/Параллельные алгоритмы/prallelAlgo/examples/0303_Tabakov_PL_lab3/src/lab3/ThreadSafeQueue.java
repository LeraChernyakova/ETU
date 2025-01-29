package lab3;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadSafeQueue<T> implements CustomQueue<T> {

    private final Queue<T> queue = new LinkedList<>();

    private final Lock lock = new ReentrantLock();

    private final Condition condition = lock.newCondition();

    public void add(T element) {
        lock.lock();
        try {
            queue.add(element);
            condition.signal();
        } finally {
            lock.unlock();
        }
    }

    public T take() {
        lock.lock();
        try {
            while (queue.isEmpty()) {
                try {
                    condition.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            return queue.poll();
        } finally {
            lock.unlock();
        }
    }
}

