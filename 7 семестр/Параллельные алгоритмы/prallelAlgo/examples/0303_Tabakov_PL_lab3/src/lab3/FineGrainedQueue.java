package lab3;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class FineGrainedQueue<T> implements CustomQueue<T> {
    private class Node {
        private T value;
        private Node next;

        public Node(T value) {
            this.value = value;
            this.next = null;
        }
    }

    private final Lock headLock = new ReentrantLock();
    private Node head;
    private final Lock tailLock = new ReentrantLock();
    private Node tail;
    private final Condition condition = tailLock.newCondition();

    private Node getTail() {
        tailLock.lock();
        try {
            return tail;
        } finally {
            tailLock.unlock();
        }
    }

    private Node popHead() {
        headLock.lock();
        try {
            Node oldHead = head;
            head = head.next;
            return oldHead;
        } finally {
            headLock.unlock();
        }
    }

    private void waitForData() throws InterruptedException {
        headLock.lock();
        try {
            while (head == getTail()) {
                condition.await();
            }
        } finally {
            headLock.unlock();
        }
    }

    private Node waitPopHead() throws InterruptedException {
        headLock.lock();
        try {
            waitForData();
            return popHead();
        } finally {
            headLock.unlock();
        }
    }

    public FineGrainedQueue() {
        head = new Node(null);
        tail = head;
    }

    public void add(T element) {
        Node newTail = new Node(element);
        tailLock.lock();
        try {
            tail.value = element;
            tail.next = newTail;
            tail = newTail;
            condition.signal();
        } finally {
            tailLock.unlock();
        }
    }

    public T take() throws InterruptedException {
        Node oldHead = waitPopHead();
        return oldHead.value;
    }
}
