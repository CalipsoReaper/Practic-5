#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "processes.h"

#define PATH_MAX_LENGTH 256 // максимальная длина пути к файлу

// функция для вывода списка процессов
void list_processes(const char *log_file) {
    // открываем файл для записи логов или используем стандартный вывод
    FILE *output = log_file ? fopen(log_file, "a") : stdout;

    // проверка на успешное открытие файла
    if (!output) {
        fprintf(stderr, "Error: Cannot open log filen");
        return; // завершаем выполнение функции в случае ошибки
    }

    // открываем каталог /proc для чтения
    DIR *proc = opendir("/proc");
    struct dirent *entry;

    // считывание процессов из каталога /proc
    while ((entry = readdir(proc)) != NULL) {
        // проверяем, является ли имя директории числом (PID процесса)
        if (isdigit(entry->d_name[0])) {
            char path[PATH_MAX_LENGTH];
            // формируем путь к файлу статуса процесса
            if (snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name) >= sizeof(path)) {
                fprintf(stderr, "Warning: Path truncated for PID %sn", entry->d_name);
                continue; // пропускаем этот процесс, если путь слишком длинный
            }
            
            // открываем файл статуса процесса
            FILE *stat_file = fopen(path, "r");
            if (stat_file) {
                int pid;
                // считываем PID из файла статуса
                fscanf(stat_file, "%d", &pid);
                fprintf(output, "PID: %dn", pid); // записываем PID в лог или выводим на экран
                fclose(stat_file); // закрываем файл статуса процесса
            }
        }
    }

    closedir(proc); // закрываем каталог /proc
    if (log_file) fclose(output); // закрываем файл логов, если он был открыт
}

