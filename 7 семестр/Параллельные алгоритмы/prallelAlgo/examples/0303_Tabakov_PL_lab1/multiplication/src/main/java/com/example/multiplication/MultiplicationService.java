package com.example.multiplication;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Service
public class MultiplicationService {

    private final InputClient inputClient;

    private static final int THREAD_COUNT = 1;

    public MultiplicationService(InputClient inputClient) {
        this.inputClient = inputClient;
        System.out.println("Thread count: " + THREAD_COUNT);
    }

    public List<List<Integer>> multiplicate(int size) {
        ExecutorService executorService = Executors.newFixedThreadPool(THREAD_COUNT);

        List<List<Integer>> tasksIJ = new ArrayList<>(THREAD_COUNT); // indexes for each thread

        for (int counter = 0; counter < THREAD_COUNT; counter++) {
            tasksIJ.add(new ArrayList<>());
        }

        for (int counter = 0; counter < size; counter++) {
            tasksIJ.get(counter % THREAD_COUNT).add(counter);
        }

        MatricesDTO matrices = inputClient.getMatrices(size);

        int[][] result = new int[size][size];

        for (int threadNum = 0; threadNum < THREAD_COUNT; threadNum++) {

            tasksIJ.get(threadNum).forEach(i -> {
                executorService.submit(() -> {
                    calculateIJMult(i, result, matrices, size);
                });
            });
        }

        executorService.shutdown();

        List<List<Integer>> resultList = new ArrayList<>();

        while (!executorService.isTerminated()) {

        }

        for (int i = 0; i < size; i++) {
            resultList.add(Arrays.stream(result[i]).boxed().toList());
        }

        return resultList;
    }

    void calculateIJMult(int i, int[][] result, MatricesDTO matrices, int size) {

        for (var j = 0; j < size; j++) {
            for (var k = 0; k < size; k++) {
                result[i][j] += matrices.getMatrix1().get(i).get(k) * matrices.getMatrix2().get(k).get(j);
            }
        }

    }
}
