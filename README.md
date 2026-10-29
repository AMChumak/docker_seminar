# Seminar 4 Docker project

Готовый учебный проект для семинара по Docker. Писать C-код в рамках семинара не требуется.

## Структура

```text
seminar4-project/
├── Makefile
├── include/
│   └── text_stats.h
├── src/
│   ├── main.c
│   └── text_stats.c
├── data/
│   ├── input.txt
│   └── second.txt
└── resource-lab/
    ├── cpu_hog.c
    └── memory_hog.c
```

`Dockerfile` намеренно отсутствует: его создание — часть задания.

## Сборка без Docker

```bash
make
```

Будут созданы:

```text
bin/text-report
bin/cpu-hog
bin/memory-hog
```

Основное приложение:

```bash
./bin/text-report
```

По умолчанию оно анализирует `data/input.txt`. Другой файл можно передать аргументом:

```bash
./bin/text-report data/second.txt
```

## Для задачи с Dockerfile

После `make` приложение запускается так:

```bash
./bin/text-report data/input.txt
```

Поэтому эту команду удобно сделать командой контейнера по умолчанию.

Изменение `data/input.txt` подходит для эксперимента с повторной сборкой image и build cache.

## Resource lab

CPU workload:

```bash
./bin/cpu-hog
./bin/cpu-hog 20
```

Аргумент — длительность работы в секундах, по умолчанию 60.

Memory workload:

```bash
./bin/memory-hog
./bin/memory-hog 128 30
```

Аргументы: `<MiB> <seconds>`. По умолчанию программа выделяет 128 MiB и удерживает память 60 секунд.

Эти программы предназначены для задания с `docker stats`, `--cpus` и `--memory`.
