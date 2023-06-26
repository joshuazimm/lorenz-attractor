FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    libsdl2-dev \
    x11-apps \
    xauth

WORKDIR /app

ENV XDG_RUNTIME_DIR=/tmp/runtime-root

ENV DISPLAY=host.docker.internal:0

COPY . .

RUN g++ -std=c++17 lorenz.cpp -o dc -lSDL2 -ldl

CMD ["./dc"]