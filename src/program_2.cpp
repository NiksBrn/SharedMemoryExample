#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include  <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define SEM "/syn" // имя семафора


int main() {
    // ожидание создания семафора первой программой
    sem_t* sem = nullptr;
    int cnt_try = 0;
    while (sem == nullptr && cnt_try < 50) {
        sem = sem_open(SEM, 0);
        if (sem == SEM_FAILED) {
            perror("sem_open failed, retrying...");
            sleep(1);
            cnt_try++;
        }
    }

    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // ожидания
    sem_wait(sem);

    // считвание ключа от первой программы
    int shm_key;
    std::cin >> shm_key;

    // получение доступа к региону разделеяемой памяти
    int shm_id = shmget(shm_key, 0, 0);

    // присодинение региона разделеяемой памяти к адрессному простарнству процесса для чтения
    char* data = (char* )shmat(shm_id, NULL, SHM_RDONLY);
    if (data == (char* )-1) {
        perror("shmat");
        exit(1);
    }

    // вывод сообщения в регионе разделяемой памяти
    std::cout << data << std::endl;

    // отсоединение региона разделяемой памяти
    shmdt(data);

    // освобождение региона разделяемой памяти
    shmctl(shm_id, IPC_RMID, NULL);

    // возврат доступа другим процессам
    sem_post(sem);
    // закрытие семафора в данном процессе
    sem_close(sem);
    // удаление семфаора из системы
    sem_unlink(SEM);

    return 0;
}