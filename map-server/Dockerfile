FROM ubuntu:latest AS builder
RUN apt update && apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ -y
WORKDIR /
ADD rathena-source/ .
RUN ./configure
RUN make clean && make map

FROM ubuntu:latest
RUN apt update && apt install libmysqlclient20 zlib1g libpcre3 -y
COPY --from=builder /map-server .
COPY --from=builder /conf/ /conf
COPY --from=builder /db/ /db
COPY --from=builder /npc/ /npc
RUN chmod a+x map-server
RUN useradd -ms /bin/bash map-server
USER map-server
ADD wait.sh .
CMD ["./wait.sh", "char-server:6121", "--", "./map-server"]
