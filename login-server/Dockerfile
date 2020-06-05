FROM ubuntu:20.10 AS builder
RUN apt update
RUN apt install tzdata
RUN apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ wget cmake git -y
WORKDIR /
ADD rathena-source/* /
ADD rathena-source/src /src
ADD rathena-source/3rdparty /3rdparty
RUN ./configure
RUN make login
ADD rathena-source/conf /conf

FROM ubuntu:20.10
RUN apt update
RUN apt install libmysqlclient21 zlib1g libpcre3 gcc g++ wget cmake -y
COPY --from=builder /login-server /
COPY --from=builder /conf/ /conf
COPY --from=builder /usr/local/lib/ /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/local/lib/ /usr/local/lib/
RUN ls -l /usr/lib/x86_64-linux-gnu/
RUN chmod a+x login-server
RUN useradd -ms /bin/bash login-server
USER login-server
ADD wait.sh .
CMD ["./wait.sh", "database:3306", "--", "./login-server"]
