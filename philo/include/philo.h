/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:11:22 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/25 20:20:22 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <inttypes.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define BLACK "\033[30m"              /* Black */
# define RED "\033[31m"                /* Red */
# define GREEN "\033[32m"              /* Green */
# define YELLOW "\033[33m"             /* Yellow */
# define BLUE "\033[34m"               /* Blue */
# define MAGENTA "\033[35m"            /* Magenta */
# define CYAN "\033[36m"               /* Cyan */
# define WHITE "\033[37m"              /* White */
# define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
# define BOLDRED "\033[1m\033[31m"     /* Bold Red */
# define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
# define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
# define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
# define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
# define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum philo_status
{
	philo_eating,
	philo_sleeping,
	philo_thinking,
	take_left_fork,
	take_right_fork,
	philo_dead,
	philo_full
}						t_philo_status;

typedef enum e_orders
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_orders;

typedef struct s_monitor
{
	t_table				*table;
	pthread_t			monitor_thread;
	pthread_mutex_t		monitor_mutex;

}						t_monitor;

typedef struct s_table
{
	int					nbr_philos;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	bool				all_philos_full;
	int					nbr_meals;
	int					thread_runing_nbr;
	uint64_t			start_time;
	bool				all_threads_created;
	bool				end_time;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print_status;
	t_monitor			*monitor;
	t_philo				*philos;
}						t_table;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_mutex;
	bool				philo_full;
	bool				philo_died;
	long				count_nbr_meals;
	uint64_t			last_eat_time;
	pthread_t			thread_philo;
	t_table				*table;
}						t_philo;

int						ft_atoi(const char *nptr);
int						is_digit_nbr(char *av);
int						check_input(int ac, char **av);
void					init_table(t_table *table, char **av);
uint64_t				ft_get_time(void);
void					ft_usleep(uint64_t time_sleep);
void					error_inputs(char *str);
int						thread_handl(pthread_t *thread, t_orders order,
							void *(routine(void *)), void *data);
int						mutex_handl(pthread_mutex_t *mtx, t_orders order);
void					*malloc_safe(size_t data_byte);
void					assign_forks(t_table *table, int pos);
uint64_t				get_time_val(pthread_mutex_t *mutx, uint64_t dest);
void					set_time_val(pthread_mutex_t *mutx, uint64_t *dest,
							uint64_t value);
int						get_int(pthread_mutex_t *mutx, int *dest);
void					set_int(pthread_mutex_t *mutx, int *dest, int value);
bool					get_bool(pthread_mutex_t *mutx, bool *dest);
void					set_bool(pthread_mutex_t *mutx, bool *dest, bool value);
void					*philospher_routine(void *arg);
void					*start_dinner(t_table *table);
void					init_philo(t_table *table);
void					cleanup(t_table *table);
void					wait_to_be_ready(t_table *table);
void					eat_routine(t_philo *philo);
void					thinking_routine(t_philo *philo);
void					print_status(t_philo *philo, t_philo_status status);
bool					all_threads_runing(pthread_mutex_t *mutx, int *thread_r,
							int philo_nbr);
void					increase_thread_nbr(pthread_mutex_t *mutx, int *val);
bool					simulation_end(t_table *table);
void					*monitor_routine(void *arg);
void					desynchronize_philo(t_philo *philo);
bool					check_all_philos_full(t_table *table);
void					case_no_meals(t_philo *philo);
void					only_philo(t_table *table);

#endif