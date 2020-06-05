FROM ubuntu:20.10 AS builder
RUN apt update
RUN apt install tzdata
RUN apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ wget cmake git -y
WORKDIR /
ADD rathena-source/* /
ADD rathena-source/src /src
ADD rathena-source/3rdparty /3rdparty
RUN ./configure
RUN make clean && make map
ADD rathena-source/conf /conf
ADD rathena-source/db /db
ADD rathena-source/npc /npc

FROM ubuntu:20.10
RUN apt update && apt install libmysqlclient21 zlib1g libpcre3 -y
COPY --from=builder /map-server .
COPY --from=builder /conf/ /conf
COPY --from=builder /db/ /db
COPY --from=builder /npc/ /npc
RUN chmod a+x map-server
RUN useradd -ms /bin/bash map-server
USER map-server
ADD wait.sh .
CMD ["./wait.sh", "char-server:6121", "--", "./map-server"]
