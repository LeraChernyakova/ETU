package org.tabakov.input;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

@Service
@RequiredArgsConstructor
public class MatrixGenerator {

    public List<List<Integer>> generate(int size) {

        Random random = new Random(0);

        List<List<Integer>> matrix = new ArrayList<>(size);

        for (int i = 0; i < size; i++) {
            List<Integer> row = new ArrayList<>(size);

            for (int j = 0; j < size; j++) {
                row.add(random.nextInt(750) % 150);
            }

            matrix.add(row);
        }

        return matrix;
    }

}
