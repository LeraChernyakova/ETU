#pragma once

#include "IFieldGenerator.h"

template<typename T>
concept TFieldChanger = requires(T obj) {
    obj(std::declval<FieldScheme&>());
};

template<int X, int Y, TFieldChanger ... Rules>
class FieldGenerator : public IFieldGenerator {
public:
    FieldScheme make() override {
        FieldScheme scheme;
        scheme.height = Y;
        scheme.width = X;
        scheme.array.resize(scheme.height);
        for (int i = 0; i < scheme.height; ++i) {
            scheme.array[i].resize(scheme.width);
        }
        (apply<Rules>(scheme), ...);
        return scheme;
    }
private:
    template<TFieldChanger Rule>
    void apply(FieldScheme& scheme) {
        Rule rule;
        rule(scheme);
    }
};