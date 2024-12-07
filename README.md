#  Philosophers - School 42

Implementations of the Dining Philosophers Problem in C.

[The Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) is a classic synchronization problem involving philosophers sitting around a table, sharing a limited number of forks. Each philosopher alternates between thinking, eating and sleeping while following certain rules to avoid deadlocks and starvation.

1. **philo/** - Multi-threaded implementation using POSIX threads (`pthread`) and mutexes.

2. **philo_bonus/** - Parallel processing implementation using processes and semaphores.

---

### Build and run

```bash
make

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep[number_of_times_each_philosopher_must_eat]
```
