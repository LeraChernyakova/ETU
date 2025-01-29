package com.example.output;

import lombok.NonNull;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import java.util.List;

@FeignClient(value = "client", url = "localhost:8081")
public interface OutputClient {

    @RequestMapping(method = RequestMethod.GET, value = "/multiplicated/{size}")
    List<List<Integer>> getMultiplicated(@PathVariable @NonNull Integer size);
}
