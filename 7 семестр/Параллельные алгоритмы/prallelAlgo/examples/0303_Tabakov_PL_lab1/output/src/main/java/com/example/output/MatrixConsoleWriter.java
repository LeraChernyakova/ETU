package com.example.output;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class MatrixConsoleWriter {

    public void write(List<List<Integer>> matrix) {
        matrix.forEach(x -> System.out.println(x + "\n"));
    }
}
