FROM mongodb/mongodb-community-server:6.0-ubi8
WORKDIR /
COPY mongo-init.js /docker-entrypoint-initdb.d/mongo-init.js
CMD ["mongod", "--port", "27017"]