package com.example.multiplication;

import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
public class MatricesDTO {

    private final List<List<Integer>> matrix1 = new ArrayList<>();

    private final List<List<Integer>> matrix2 = new ArrayList<>();

}
