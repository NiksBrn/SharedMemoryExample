#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <semaphore.h>
#include  <fcntl.h>

#define SHM_SIZE 1000
#define SHM_KEY "shm_key" // имя файла для генерации ключа
#define SEM "/syn" //  имя семафора

int main() {
    // создание семафора
    sem_t* sem = sem_open(SEM, O_CREAT, 0604, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // генерация уникального ключа
    key_t key = ftok(SHM_KEY, 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    // создание региона раздляемой памяти
    int shmid = shmget(key, SHM_SIZE, 0600 | IPC_CREAT | IPC_EXCL);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    // присоединение региона разделеяемой памяти к адрессному простарнству процесса
    char* str = (char*)shmat(shmid, NULL, 0);
    if (str == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    // копирование в регион разделяемой памяти Hello world!
    strcpy(str, "Hello world!");

    // отправка ключа в стандартный поток вывода
    std::cout << key << std::endl;

    // отсоединение региона разделяемой памяти
    shmdt(str);

    // возврат доступа другим процессам
    sem_post(sem);
    // закрытие семафора в данном процессе
    sem_close(sem);

    return 0;
}