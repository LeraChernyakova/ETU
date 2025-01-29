proto:
	rm -rf internal/pkg/pb && mkdir -p internal/pkg/pb
	protoc -I api -I $(GOPATH)/pkg/mod/github.com/grpc-ecosystem/grpc-gateway@v1.16.0/third_party/googleapis \
		--go_out=internal/pkg/pb --go_opt=paths=source_relative \
		--go-grpc_out=internal/pkg/pb --go-grpc_opt=paths=source_relative \
		--grpc-gateway_out=internal/pkg/pb --grpc-gateway_opt=paths=source_relative \
		--openapiv2_out gen/docs \
		./api/**/**/*.proto

win-gen-proto:
	if not exist ".\internal\pkg\pb" mkdir ".\internal\pkg\pb"
	powershell -Command "Get-ChildItem -Path \"api\" -Filter \"*proto\" -Recurse | ForEach{protoc -I api -I $(GOPATH)/pkg/mod/github.com/grpc-ecosystem/grpc-gateway@v1.16.0/third_party/googleapis --go_out=internal/pkg/pb --go_opt=paths=source_relative --go-grpc_out=./internal/pkg/pb --go-grpc_opt=paths=source_relative --grpc-gateway_out=./internal/pkg/pb --grpc-gateway_opt=paths=source_relative --openapiv2_out ./gen/docs $$_.FullName.Replace($$pwd.Path, '.')}"
