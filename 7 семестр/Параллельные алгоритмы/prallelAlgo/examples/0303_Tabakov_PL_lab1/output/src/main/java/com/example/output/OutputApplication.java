package com.example.output;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.openfeign.EnableFeignClients;

@EnableFeignClients
@SpringBootApplication
public class OutputApplication {

    public static void main(String[] args) {
        SpringApplication.run(OutputApplication.class, args);
    }

}
