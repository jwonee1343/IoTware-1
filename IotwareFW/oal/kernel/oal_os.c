/* includes */

#include "oal_os.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* functions */

void oal_os_init(void)
{
    
}

void oal_os_start(void (*init_app)(void))
{
    
}

void oal_yield(void)
{
    
}

void oal_yield_isr(int32_t arg)
{
    
}

void oal_crit_enter(void)
{
    
}

void oal_crit_exit(void)
{
    
}

int32_t oal_task_create(oal_task_t *p_task, void (*func)(void *), void *arg, const char *name, uint32_t stacklen, int32_t prio, void *ext)
{
    return -1;   
}

void oal_task_delete(oal_task_t task)
{
    
}

void oal_task_exit(void)
{
    
}

void oal_task_suspend(oal_task_t task)
{
    
}

void oal_task_resume(oal_task_t task)
{
    
}

int32_t oal_task_get(oal_task_t *p_task)
{
    return -1;
}

int64_t	oal_task_get_freesize(oal_task_t task)
{
    return -1;
}

int32_t oal_signal(int32_t signal, oal_task_t target, bool isisr)
{
    return -1;
}

int64_t oal_signal_wait(int32_t signal, oal_tick_t timeout)
{
    return -1;
}

int32_t oal_mutex_create(oal_mutex_t *p_mutex)
{
    return -1;
}

void oal_mutex_delete(oal_mutex_t mutex)
{
    
}

int32_t oal_mutex_lock(oal_mutex_t mutex, oal_tick_t timeout)
{
    return -1;
}

int32_t oal_mutex_unlock(oal_mutex_t mutex)
{
    return -1;
}

int32_t oal_sem_create(oal_sem_t *p_sem, uint32_t max_val, uint32_t init_val)
{
    return -1;
}

void oal_sem_delete(oal_sem_t sem)
{
    
}

int32_t oal_sem_lock(oal_sem_t sem, oal_tick_t timeout)
{
    return -1;
}

int32_t oal_sem_unlock(oal_sem_t sem, oal_task_t target)
{
    return -1;
}

int32_t	oal_sem_unlock_isr(oal_sem_t sem, int32_t *p_woken)
{
    return -1;
}

int32_t oal_queue_create(oal_queue_t *p_queue, uint32_t len, uint32_t nbyte)
{
    return -1;
}

void oal_queue_delete(oal_queue_t queue)
{
    
}

int32_t oal_queue_send(oal_queue_t queue, void *p_data, oal_tick_t timeout, oal_task_t target)
{
    return -1;
}

int32_t oal_queue_send_isr(oal_queue_t queue, void *p_data, int32_t *p_woken)
{
    return -1;
}

int32_t oal_queue_recv(oal_queue_t queue, void *p_data, bool blocking)
{
    return -1;
}

int32_t oal_queue_peek(oal_queue_t queue, void *p_data, oal_tick_t timeout)
{
    return -1;
}

int32_t oal_queue_reset(oal_queue_t queue)
{
    return -1;
}

void *oal_malloc(uint32_t size)
{
    return NULL;
}

void oal_free(void *ptr)
{
    
}

oal_tick_t oal_tick_get(void)
{
    return 0;
}

void oal_sleep(uint32_t ms)
{
    
}