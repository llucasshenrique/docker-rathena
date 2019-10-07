FROM ubuntu:latest AS builder
RUN apt update && apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ -y
WORKDIR /
ADD rathena-source/ .
RUN ./configure
RUN make char

FROM ubuntu:latest
RUN apt update && apt install libmysqlclient20 zlib1g libpcre3 -y
COPY --from=builder /char-server .
COPY --from=builder /conf/ /conf
COPY --from=builder /db/ /db
RUN chmod a+x char-server
RUN useradd -ms /bin/bash char-server
USER char-server
ADD wait.sh .
CMD ["./wait.sh", "login-server:6900", "--", "./char-server"]
