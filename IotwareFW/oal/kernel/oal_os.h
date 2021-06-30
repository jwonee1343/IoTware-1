/*
Copyright (C) <2020> <ETRI>

This License and Service Agreement (LSA) applies to all works and their derivative works based on source form version and object form version of IoTware Project. Currently, the LSA for IoTware Project has two policies, 'Open Source License' and 'Commercial License'. Therefore, all works including the source code and executable code of IoTware Project and derivative works based thereon are subject to either 'Open Source License' or 'Commercial License' depending on the user's needs and purpose. Details related to the selection of the applicable license are specified in this LSA. If you use any or all of IoTware Project in any form, you are deemed to have consented to this LSA. If you breach any of the terms and conditions set forth in this LSA, you are solely responsible for any losses or damages incurred by Electronics and Communications Research Institute (ETRI), and ETRI assume no responsibility for you or any third party.
If you use the source form version or object form version of IoTware Project in whole or in part to develop a code or a derivative work, and you want to commercialize the result in some form, you will be covered under a commercial license. And if you are subject to a commercial license, the contract for the use of IoTware Project is subject to TECHNOLOGY LICENSE AGREEMENT of ETRI. You acknowledge that ETRI has all legal rights, title and interest, including intellectual property rights in the IoTware Project (regardless of whether such intellectual property rights are registered or where such rights exist) and agree with no objection thereto. Except as provided in a subsidiary agreement, nothing in this LSA grants you the right to use IoTware Project or the name, service mark, logo, domain name and other unique identification marks of ETRI.
If you use the source form version or object form version of IoTware Project in whole or in part to develop a code or a derivative work, and you do not commercialize the result in any form, you will be covered under an open source license. IoTware Project is in accordance with Free Software Foundation (FSF)'s open source policy, and is allowed to use it in the appropriate scope and manner, and you must comply with the applicable open source license policy applied to IoTware Project. IoTware Project is, in principle, subject to GNU Lesser General Public License version 2.1 (LGPLv2.1). If you have acquired all or a part of the IoTware Project in any way and it is subject to a license other than the open source license described above, please contact the following address for the technical support and other inquiries before use, and check the usage information.
*/

#ifndef	OAL_OS_H
#define	OAL_OS_H

/* includes */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* macros */
#define TOTAL_HEAP_SIZE 0
#define FREE_HEAP_SIZE 0
#define GLOBAL_DATA_SIZE 0

#define OAL_OS_NAME ""
#define	OAL_TICK_PER_MS 1
#define OAL_TICK_FOREVER 0
#define OAL_TASK_PRIO_IDLE 0
#define OAL_TASK_PRIO_HIGH 0
#define	OAL_MIN_STACKLEN 0

/* types */
typedef void *oal_task_t;
typedef void *oal_queue_t;
typedef void *oal_sem_t;
typedef void *oal_mutex_t;
typedef uint32_t oal_tick_t;

/* functions */

static inline oal_tick_t oal_tick_from_ms(uint32_t ms)
{
    return ms / OAL_TICK_PER_MS;
}

static inline uint32_t oal_tick_to_ms(oal_tick_t tick)
{
    return tick * OAL_TICK_PER_MS;
}

void oal_os_init(void);
void oal_os_start(void (*init_app)(void));
void oal_yield(void);
void oal_yield_isr(int32_t arg);
void oal_crit_enter(void);
void oal_crit_exit(void);
int32_t oal_task_create(oal_task_t *p_task, void (*func)(void *), void *arg, const char *name, uint32_t stacklen, int32_t prio, void *ext);
void oal_task_delete(oal_task_t task);
void oal_task_exit(void);
void oal_task_suspend(oal_task_t task);
void oal_task_resume(oal_task_t task);
int32_t oal_task_get(oal_task_t *p_task);
int64_t	oal_task_get_freesize(oal_task_t task);
int32_t oal_signal(int32_t signal, oal_task_t target, bool isisr);
int64_t oal_signal_wait(int32_t signal, oal_tick_t timeout);
int32_t oal_mutex_create(oal_mutex_t *p_mutex);
void oal_mutex_delete(oal_mutex_t mutex);
int32_t oal_mutex_lock(oal_mutex_t mutex, oal_tick_t timeout);
int32_t oal_mutex_unlock(oal_mutex_t mutex);
int32_t oal_sem_create(oal_sem_t *p_sem, uint32_t max_val, uint32_t init_val);
void oal_sem_delete(oal_sem_t sem);
int32_t oal_sem_lock(oal_sem_t sem, oal_tick_t timeout);
int32_t oal_sem_unlock(oal_sem_t sem, oal_task_t target);
int32_t	oal_sem_unlock_isr(oal_sem_t sem, int32_t *p_woken);
int32_t oal_queue_create(oal_queue_t *p_queue, uint32_t len, uint32_t nbyte);
void oal_queue_delete(oal_queue_t queue);
int32_t oal_queue_send(oal_queue_t queue, void *p_data, oal_tick_t timeout, oal_task_t target);
int32_t oal_queue_send_isr(oal_queue_t queue, void *p_data, int32_t *p_woken);
int32_t oal_queue_recv(oal_queue_t queue, void *p_data, bool blocking);
int32_t oal_queue_peek(oal_queue_t queue, void *p_data, oal_tick_t timeout);
int32_t oal_queue_reset(oal_queue_t queue);
void *oal_malloc(uint32_t size);
void oal_free(void *ptr);
oal_tick_t oal_tick_get(void);
void oal_sleep(uint32_t ms);

#endif /* OAL_OS_H */
