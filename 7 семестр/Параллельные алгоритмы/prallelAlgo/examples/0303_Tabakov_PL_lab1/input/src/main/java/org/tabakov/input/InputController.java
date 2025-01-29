package org.tabakov.input;

import lombok.NonNull;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class InputController {

    private final MatrixGenerator matrixGenerator;

    public InputController(MatrixGenerator matrixGenerator) {
        this.matrixGenerator = matrixGenerator;
    }

    @GetMapping("/matrices/{size}")
    public ResponseEntity<?> getMatrices(@PathVariable @NonNull Integer size) {
        MatricesDTO matrices = new MatricesDTO(
                matrixGenerator.generate(size),
                matrixGenerator.generate(size)
        );

        return ResponseEntity.ok(matrices);
    }

    private void multiplyAndPrint(List<List<Integer>> m1, List<List<Integer>> m2) {
        int[][] res = new int[m1.size()][m1.size()];
        for (int i = 0; i < m1.size(); i++) {
            for (int j = 0; j < m1.size(); j++) {
                for (int k = 0; k < m1.size(); k++) {
                    res[i][j] += m1.get(i).get(k) * m2.get(k).get(j);
                }
            }
        }

        System.out.println("result: ");
        for (int i = 0; i < res.length; i++) {
            for (int j = 0; j < res[0].length; j++) {
                System.out.format("%6d ", res[i][j]);
            }
            System.out.println();
        }
    }
}
