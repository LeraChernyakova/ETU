package com.example.multiplication;

import lombok.NonNull;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@FeignClient(value = "client", url = "localhost:8082")
public interface InputClient {

    @RequestMapping(method = RequestMethod.GET, value = "/matrices/{size}")
    MatricesDTO getMatrices(@PathVariable @NonNull Integer size);
}
