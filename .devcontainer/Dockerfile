# Стандартный GCC и Cmake
FROM gcc:14.2.0

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    cmake python3 python3-dev python3-pip wrk clangd\
    && rm -rf /var/lib/apt/lists/*

RUN pip install numpy --break-system-packages

# Установка рабочей директории
WORKDIR /workspace