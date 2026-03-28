_This project has been created as part of the 42 curriculum by habe._

## Description

By implementing the Dining Philosophers problem in C, I learned the basics of parallel processing using threads and mutual exclusion control using mutexes.
To address the issues of race conditions and deadlocks that arise when multiple threads access shared resources, I avoided them by carefully controlling the order in which forks were acquired.
Additionally, I managed each philosopher as a thread and controlled state transitions using loops to achieve parallel operation.
Through this implementation, I gained an understanding of the difficulty of timing-dependent race condition bugs and the importance of precise synchronization.

## Instructions

### Compilation

To compile and run this project, you need:

- A Unix-based operating system (Linux or macOS)
- GCC or Clang compiler
- GNU Make

Compile the project using:

```bash
make
```

### Execution

```bash
./philo [ number_of_philosophers ] [ time_to_die ] [ time_to_eat ] [ time_to_sleep ] [number_of_times_each_philosopher_must_eat]
```

- number_of_philosophers : The number of philosophers and also the number of forks
- time_to_die : If a philosopher has not started eating within
  time_to_die milliseconds since the start of their last meal or the start of the
  simulation, they die.
- time_to_eat : The time it takes for a philosopher to eat.
  During that time, they will need to hold two forks.
- time_to_sleep : The time a philosopher will spend sleeping.
- [number_of_times_each_philosopher_must_eat] : If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times,
  the simulation stops. If not specified, the simulation stops when a philosopher dies.


## Resources

### References

- [Parallel Processing Using pthreads and Mutexes](https://qiita.com/ryo_manba/items/e48faf2ba84f9e5d31c8)
- [How to Use pthreads](https://qiita.com/miyamoto_works/items/8ede26b07099606e50db)
- [Trying out multithreading](https://zenn.dev/rinngo0302/articles/d1aa031137de9f)
- [The Basics of std::thread::join(): "Waiting" for Another Thread to Finish](https://note.com/morinokabu/n/n5d3c0b1df213)
- [Dining Philosophers Problem - Wikipedia](https://ja.wikipedia.org/wiki/%E9%A3%9F%E4%BA%8B%E3%81%99%E3%82%8B%E5%93%B2%E5%AD%A6%E8%80%85%E3%81%AE%E5%95%8F%E9%A1%8C)

### philosophers-visualizer

- [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/)

### AI Usage

AI tools (ChatGPT, Gemini, Claude Code) were used to:

- Deepening understanding of threads and mutexes concepts through discussion
- Reviewing logic and conducting code review

All final implementation choices and code were written and validated by the authors.
