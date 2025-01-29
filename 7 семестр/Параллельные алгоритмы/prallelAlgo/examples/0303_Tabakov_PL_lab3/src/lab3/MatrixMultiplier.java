package lab3;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class MatrixMultiplier {

    private static final int MATRIX_SIZE = 100; // Replace with your desired matrix size
    private static final int PRODUCERS_NUM = 6; // Number of producer threads
    private static final int CONSUMERS_NUM = 5; // Number of consumer threads

    static volatile boolean finished = false;
    static AtomicInteger generated = new AtomicInteger(0);
    static AtomicInteger multiplied = new AtomicInteger(0);
    static AtomicInteger printed = new AtomicInteger(0);

    public static void main(String[] args) {

        FileWriter file;
        Long time1 = System.currentTimeMillis();

        try {
            file = new FileWriter("output.txt");
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        CustomQueue<Matrices> queueMatrices = new LockFreeQueue<>();
        CustomQueue<Matrix> queueResults = new LockFreeQueue<>();

        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < PRODUCERS_NUM; i++) {
            threads.add(new Thread(() -> producer(queueMatrices)));
        }

        for (int i = 0; i < CONSUMERS_NUM; i++) {
            threads.add(new Thread(() -> consumer(queueMatrices, queueResults)));
        }

        threads.add(new Thread(() -> writer(queueResults, file)));

        for (Thread thread : threads) {
            thread.start();
        }

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        finished = true;

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        Long time2 = System.currentTimeMillis();

        try {
            file.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Matrix generated: " + generated);
        System.out.println("Matrix multiplied: " + multiplied);
        System.out.println("Matrix printed: " + printed);
        System.out.println("Time spent: " + (time2 - time1));
    }


    static void producer(CustomQueue<Matrices> queueMatrices) {
        while (!finished) {
            queueMatrices.add(new Matrices(new Matrix(MATRIX_SIZE), new Matrix(MATRIX_SIZE)));
            generated.incrementAndGet();
        }
    }

    static void consumer(CustomQueue<Matrices> queueMatrices, CustomQueue<Matrix> queueResults) {

        while (!finished) {
            try {
                Matrices matrices = queueMatrices.take();
                Matrix result = matrices.first.multiply(matrices.second);
                queueResults.add(result);
                multiplied.incrementAndGet();
            } catch (Exception ignored) {

            }
        }
    }

    static void writer(CustomQueue<Matrix> queueResults, FileWriter file) {
        while (!finished) {
            try {
                Matrix result = queueResults.take();
                if (result == null) {
                    return;
                }

                // Write the matrix to the file
                try {
                    file.write(result.toString());
                    printed.incrementAndGet();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } catch (Exception ignored) {

            }
        }
    }

}
