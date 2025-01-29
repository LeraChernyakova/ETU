package org.tabakov.input;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.List;

@Data
@AllArgsConstructor
public class MatricesDTO {

    private final List<List<Integer>> matrix1;

    private final List<List<Integer>> matrix2;

}
