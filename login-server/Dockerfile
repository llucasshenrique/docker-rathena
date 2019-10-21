FROM debian:latest AS builder
RUN apt update && apt install make libmariadbclient-dev-compat zlib1g-dev libpcre3-dev gcc g++ wget cmake git -y
#RUN apt update && apt install make libmysqlclient-dev zlib1g-dev libpcre3-dev gcc g++ wget cmake git -y
WORKDIR /
ADD rathena-source/dd-opentracing-cpp.sh /
ENV LD_LIBRARY_PATH=/usr/local/lib
RUN ./dd-opentracing-cpp.sh

ADD rathena-source/* /
ADD rathena-source/src /src
#ADD rathena-source/Make* /
ADD rathena-source/3rdparty /3rdparty
RUN ./configure
#RUN env
#RUN echo $LD_LIBRARY_PATH
#RUN ls -lR $LD_LIBRARY_PATH
#RUN find / | grep \\.so$
#RUN find / | grep libopentracing
#RUN cat /src/login/Makefile
RUN make login
ADD rathena-source/conf /conf

FROM debian:latest
RUN apt update && apt install libmariadbclient-dev zlib1g libpcre3 gcc g++ wget cmake -y
#RUN apt update && apt install libmysqlclient20 zlib1g libpcre3 gcc g++ wget cmake -y
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
