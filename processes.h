#ifndef PROCESSES_H
#define PROCESSES_H

/**
 * @brief Выводит список процессов в лог-файл или на стандартный вывод.
 *
 * @param log_file Путь к файлу для записи логов. Если NULL, вывод будет направлен на стандартный вывод.
 */
void list_processes(const char *log_file);

#endif // PROCESSES_H

