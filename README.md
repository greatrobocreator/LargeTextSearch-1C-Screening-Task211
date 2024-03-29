# Практическое задание для отбора на кафедру КИС

## Условие задачи

Необходимо реализовать эффективный алгоритм поиска по строке в очень большом текстовом файле. 
Файл загружается один раз, потом происходит большое количество запросов на поиск.

## Описание

Алгоритм основан на суффиксном автомате. 
Имеет две возможных конфигурации работы - в оперативной и во внешенй памяти.

Алгоритм посимвольно считывает входную строку/файл, выполняя построения суффиксного автомата.

Заметим, что при считывании из файла паттерн может не помещаться в оперативную память, так как файл считывается посимвольно.

При работе в оперативной памяти все вершины автомата хранятся в массиве, при работе во внешней памяти - в отдельном файле.

После построения автомата алгоритм готов обрабатывать запросы. 
Каждый паттерн пропускается через автомат. 
Если во время прохода все соответствующие ребра существовали, то алгоритм возвращает заранее подсчитанное число из вершины - индекс первого вхождения.
Иначе возвращается `-1`, означающее отсутствие вхождения. 

Асимптотика препроцессинга: `O(n)`, где `n` - размер текста

Асиптотика на один запрос: `O(m)`, где `m` - длина паттерна

Итоговая асимптотика: `O(n + m * q)`, где `q` - количество запросов

## Сборка

Стандартный `cmake` проект:

```
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```

## Запуск

```
cd cmake-build-debug
./Main
```

## Архитектура 

Для большей масшатибируемости и красоты кода была добавлена несложеная архитектура.

Суффиксный автомат ничего не знает про устройство и хранение вершин, про то, хранятся ли они в файле или в оперативной памяти.
За это отвечает класс `NodesManager`, от которого наследуется два класса, реализующих две способа работы. Именно этот класс работает напрямую с вершинами.

![Архитектура](https://github.com/greatrobocreator/LargeTextSearch-1C-Screening-Task211/blob/dev/diagram.png?raw=true)