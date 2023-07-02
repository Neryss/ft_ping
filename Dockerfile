FROM debian:latest
RUN apt-get update -y && apt-get install gcc -y && apt-get install make -y && apt-get install tcpdump
COPY app /app