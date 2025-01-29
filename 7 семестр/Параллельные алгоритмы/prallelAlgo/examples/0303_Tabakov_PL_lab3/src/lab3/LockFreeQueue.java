package lab3;

import java.util.concurrent.atomic.AtomicReference;

public class LockFreeQueue<T> implements CustomQueue<T> {
    private static class Node<T> {
        private final AtomicReference<Node<T>> next = new AtomicReference<>();
        private T data;

        Node(T data) {
            this.data = data;
        }
    }

    private final AtomicReference<Node<T>> head;
    private final AtomicReference<Node<T>> tail;

    public LockFreeQueue() {
        Node<T> dummyNode = new Node<>(null);
        head = new AtomicReference<>(dummyNode);
        tail = new AtomicReference<>(dummyNode);
    }

    public void add(T element) {
        Node<T> new_node = new Node<>(element);
        while (true) {
            Node<T> last = tail.get();
            Node<T> next = last.next.get();
            if (last == tail.get()) {
                if (next == null) {
                    if (last.next.compareAndSet(next, new_node)) {
                        tail.compareAndSet(last, new_node);
                        return;
                    }
                } else {
                    tail.compareAndSet(last, next);
                }
            }
        }
    }

    public T take() {
        while (true) {
            Node<T> first = head.get();
            Node<T> last = tail.get();
            Node<T> next = first.next.get();
            if (first == last) {
                if (next == null) {
                    return null;
                }
                tail.compareAndSet(last, next);
            } else {
                if (head.compareAndSet(first, next)) {
                    return next.data;
                }
            }
        }
    }
}
