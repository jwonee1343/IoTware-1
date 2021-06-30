/* includes */

#include "oal_os.h"

#include "zephyr.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* variables */
static uint32_t __crit_lock = 0U;

/* functions */

void oal_os_init(void)
{
    /* nothing to do */
}

void oal_os_start(void (*init_app)(void))
{
    init_app();
}

void oal_yield(void)
{
    /* not supported */
}

void oal_yield_isr(int32_t arg)
{
    /* not supported */
}

void oal_crit_enter(void)
{
    if (!__crit_lock)
        __crit_lock = irq_lock();
}

void oal_crit_exit(void)
{
    if (__crit_lock) {
        irq_unlock(__crit_lock);
        __crit_lock = 0U;
    }
}

#define __STACK_MAX_LEN 20
K_THREAD_STACK_ARRAY_DEFINE(__stack, __STACK_MAX_LEN, 1024);
static int __stack_n;

int32_t oal_task_create(oal_task_t *p_task, void (*func)(void *), void *arg, const char *name, uint32_t stacklen, int32_t prio, void *ext)
{
    struct k_thread *new_thread;
    k_tid_t tid;

    (void)stacklen;

    if (__STACK_MAX_LEN < __stack_n)
        return -1;

    new_thread = oal_malloc(sizeof *new_thread);
	if (!new_thread)
        return -1;

    tid = k_thread_create(new_thread, __stack[__stack_n], K_THREAD_STACK_SIZEOF(__stack[__stack_n]), (void (*)(void *, void *, void *))func, arg, NULL, NULL, prio, K_USER, K_NO_WAIT);
    if (!tid) {
        oal_free(new_thread);
        return -1;
    }

#if CONFIG_THREAD_MONITOR
	k_thread_name_set(tid, name);
#else
	(void)name;
#endif /* CONFIG_THREAD_MONITOR */

    *p_task = (oal_task_t)tid;
	++__stack_n;
	return 0;
}

void oal_task_delete(oal_task_t task)
{
    k_thread_abort(task);
	oal_free(task);
}

void oal_task_exit(void)
{
    k_thread_abort(k_current_get());
}

void oal_task_suspend(oal_task_t task)
{
    k_thread_suspend((k_tid_t)task);
}

void oal_task_resume(oal_task_t task)
{
    k_thread_resume((k_tid_t)task);
}

int32_t oal_task_get(oal_task_t *p_task)
{
    *p_task = (oal_task_t)k_current_get();
    return *p_task ? 0 : -1;
}

int64_t oal_task_get_freesize(oal_task_t task)
{
    /* not supported */
    (void)task;
    return -1;
}

int32_t oal_signal(int32_t signal, oal_task_t target, bool isisr)
{
    /* not supported */
    return -1;
}

int64_t oal_signal_wait(int32_t signal, oal_tick_t timeout)
{
    /* not supported */
    return -1;
}

int32_t oal_mutex_create(oal_mutex_t *p_mutex)
{
    struct k_mutex *new_mutex;

    new_mutex = oal_malloc(sizeof(*new_mutex));
    if (!new_mutex)
        return -1;

    k_mutex_init(new_mutex);
    *p_mutex = (oal_mutex_t)new_mutex;
    return 0;
}

void oal_mutex_delete(oal_mutex_t mutex)
{
    oal_free(mutex);
}

int32_t oal_mutex_lock(oal_mutex_t mutex, oal_tick_t timeout)
{
    if (timeout == OAL_TICK_FOREVER)
        return k_mutex_lock((struct k_mutex *)mutex, K_FOREVER);
    else
        return k_mutex_lock((struct k_mutex *)mutex, K_TICKS(timeout));
}

int32_t oal_mutex_unlock(oal_mutex_t mutex)
{
    k_mutex_unlock((struct k_mutex *)mutex);
    return 0;
}

int32_t oal_sem_create(oal_sem_t *p_sem, uint32_t max_val, uint32_t init_val)
{
    struct k_sem *new_sem;

    new_sem = oal_malloc(sizeof(*new_sem));
    if (!new_sem)
        return -1;

    k_sem_init(new_sem, init_val, max_val);
    return 0;
}

void oal_sem_delete(oal_sem_t sem)
{
    oal_free(sem);
}

int32_t oal_sem_lock(oal_sem_t sem, oal_tick_t timeout)
{
    if (timeout == OAL_TICK_FOREVER)
        return k_sem_take((struct k_sem *)sem, K_FOREVER);
    else
        return k_sem_take(sem, K_TICKS(timeout));
}

int32_t oal_sem_unlock(oal_sem_t sem, oal_task_t target)
{
    (void)target;

    k_sem_give((struct k_sem *)sem);
    return 0;
}

int32_t oal_sem_unlock_isr(oal_sem_t sem, int32_t *p_woken)
{
    /* not supported */
    return -1;
}

int32_t oal_queue_create(oal_queue_t *p_queue, uint32_t len, uint32_t nbyte)
{
    struct k_msgq *new_msgq;
    int32_t error;

    new_msgq = oal_malloc(sizeof(*new_msgq));
    if (!new_msgq)
        return -1;

    error = k_msgq_alloc_init(new_msgq, nbyte, len);
    if (error) {
        oal_free(new_msgq);
        return -1;
    }
    return 0;
}

void oal_queue_delete(oal_queue_t queue)
{
    oal_free(queue);
}

int32_t oal_queue_send(oal_queue_t queue, void *p_data, oal_tick_t timeout, oal_task_t target)
{
    (void)target;

    if (timeout == OAL_TICK_FOREVER)
        return k_msgq_put((struct k_msgq *)queue, p_data, K_FOREVER);
    else
        return k_msgq_put((struct k_msgq *)queue, p_data, K_TICKS(timeout));
}

int32_t oal_queue_send_isr(oal_queue_t queue, void *p_data, int32_t *p_woken)
{
    /* not supported */
    return -1;
}

int32_t oal_queue_recv(oal_queue_t queue, void *p_data, bool blocking)
{
    if (blocking)
        return k_msgq_get((struct k_msgq *)queue, p_data, K_FOREVER);
    else
        return k_msgq_get((struct k_msgq *)queue, p_data, K_TICKS(100));
}

int32_t oal_queue_peek(oal_queue_t queue, void *p_data, oal_tick_t timeout)
{
    (void)timeout;

    return k_msgq_peek((struct k_msgq *)queue, p_data);
}

int32_t oal_queue_reset(oal_queue_t queue)
{
    k_msgq_purge((struct k_msgq *)queue);
    return 0;
}

void *oal_malloc(uint32_t size)
{
    return k_malloc(size);
}

void oal_free(void *ptr)
{
    k_free(ptr);
}

oal_tick_t oal_tick_get(void)
{
    return k_uptime_get_32();
}

void oal_sleep(uint32_t ms)
{
    if (ms == OAL_TICK_FOREVER)
        k_sleep(K_FOREVER);
    else
        k_sleep(K_MSEC(ms));
}