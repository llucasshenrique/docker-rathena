FROM ubuntu:latest AS builder
RUN apt update && apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ -y
WORKDIR /
ADD rathena-source/ .
RUN ./configure
RUN make login

FROM ubuntu:latest
RUN apt update && apt install libmysqlclient20 zlib1g libpcre3 -y
COPY --from=builder /login-server .
COPY --from=builder /conf/ /conf
RUN chmod a+x login-server
RUN useradd -ms /bin/bash login-server
USER login-server
ADD wait.sh .
CMD ["./wait.sh", "database:3306", "--", "./login-server"]