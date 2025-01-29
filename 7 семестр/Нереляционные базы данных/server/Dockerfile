FROM golang:alpine3.21 as modules
COPY go.mod go.sum /modules/
WORKDIR /modules
RUN go mod download

FROM golang:alpine3.21 as builder
COPY --from=modules /go/pkg /go/pkg
COPY .. /app
WORKDIR /app
RUN CGO_ENABLED=0 GOOS=linux GOARCH=amd64 \
    go build -o /bin/app ./cmd

FROM scratch
ENV CONFIG_PATH=/config/prod.yaml
COPY --from=builder /app/config/prod.yaml /config/
COPY --from=builder /bin/app /app
CMD ["/app"]
