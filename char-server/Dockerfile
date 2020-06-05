FROM ubuntu:20.10 AS builder
RUN apt update 
RUN apt install tzdata
RUN apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ -y
WORKDIR /
ADD rathena-source/* /
ADD rathena-source/src /src
ADD rathena-source/3rdparty /3rdparty
RUN ./configure
RUN make char
ADD rathena-source/conf /conf
ADD rathena-source/db /db

FROM ubuntu:20.10
RUN apt update && apt install libmysqlclient21 zlib1g libpcre3 -y
COPY --from=builder /char-server .
COPY --from=builder /conf/ /conf
COPY --from=builder /db/ /db
RUN chmod a+x char-server
RUN useradd -ms /bin/bash char-server
USER char-server
ADD wait.sh .
CMD ["./wait.sh", "login-server:6900", "--", "./char-server"]
