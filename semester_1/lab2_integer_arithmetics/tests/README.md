
## Установка зависимостей (Ubuntu/WSL)

Установка библиотек

```bash
sudo apt-get update
sudo apt-get install cmake g++ libgtest-dev libboost-test-dev
```

## Сборка и запуск

Чтобы собрать проект выполните следующие команды из папки tests

```bash
mkdir build && cd build
cmake .. && make
```

Чтобы запустить

```bash
./gtest    # Google Test
./boost    # Boost Test
```
