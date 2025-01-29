package com.example.multiplication;

import lombok.NonNull;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MutiplicationController {

    private final MultiplicationService multiplicationService;

    public MutiplicationController(MultiplicationService multiplicationService) {
        this.multiplicationService = multiplicationService;
    }

    @GetMapping("/multiplicated/{size}")
    public ResponseEntity<?> getMultiplicated(@PathVariable @NonNull Integer size) {
        return ResponseEntity.ok(multiplicationService.multiplicate(size));
    }
}
