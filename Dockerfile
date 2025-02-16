FROM gcc:11.3.0
COPY . /usr/src/shared_memory
WORKDIR /usr/src/shared_memory
RUN g++ -o program_1 src/program_1.cpp -pthread
RUN g++ -o program_2 src/program_2.cpp -pthread
RUN touch shm_key
CMD ["sh", "-c", "./program_1 | ./program_2"]