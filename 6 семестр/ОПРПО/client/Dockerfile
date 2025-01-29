FROM node:16-alpine as builder
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build


FROM nginx:1.21.6-alpine as production-build
COPY nginx.conf /etc/nginx/nginx.conf
RUN rm -rf /usr/share/nginx/html/*
COPY --from=builder /dist /usr/share/nginx/html/nested-app
EXPOSE 8080
ENTRYPOINT ["nginx", "-g", "daemon off;"]