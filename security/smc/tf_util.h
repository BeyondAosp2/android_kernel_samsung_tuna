/**
 * Copyright (c) 2011 Trusted Logic S.A.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __TF_UTIL_H__
#define __TF_UTIL_H__

#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/crypto.h>
#include <linux/mount.h>
#include <linux/pagemap.h>
#include <linux/vmalloc.h>
#include <asm/byteorder.h>

#include "tf_protocol.h"
#include "tf_defs.h"

/*----------------------------------------------------------------------------
 * Debug printing routines
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_TF_DRIVER_DEBUG_SUPPORT

void address_cache_property(unsigned long va);

#define dprintk  printk

void tf_dump_l1_shared_buffer(struct tf_l1_shared_buffer *buffer);

void tf_dump_command(union tf_command *command);

void tf_dump_answer(union tf_answer *answer);

#ifdef CONFIG_BENCH_SECURE_CYCLE
void setup_counters(void);
void run_bogo_mips(void);
int run_code_speed(unsigned int loop);
int run_data_speed(unsigned int loop, unsigned long va);
#endif /* CONFIG_BENCH_SECURE_CYCLE */

#else /* defined(CONFIG_TF_DRIVER_DEBUG_SUPPORT) */

#define dprintk(args...)  do { ; } while (0)
#define tf_dump_l1_shared_buffer(buffer)  ((void) 0)
#define tf_dump_command(command)  ((void) 0)
#define tf_dump_answer(answer)  ((void) 0)

#endif /* defined(CONFIG_TF_DRIVER_DEBUG_SUPPORT) */

#define SHA1_DIGEST_SIZE	20

/*----------------------------------------------------------------------------
 * Process identification
 *----------------------------------------------------------------------------*/

int tf_get_current_process_hash(void *hash);

#ifndef CONFIG_ANDROID
int tf_hash_application_path_and_data(char *buffer, void *data, u32 data_len);
#endif /* !CONFIG_ANDROID */

/*----------------------------------------------------------------------------
 * Statistic computation
 *----------------------------------------------------------------------------*/

void *internal_kmalloc(size_t size, int priority);
void internal_kfree(void *ptr);
void internal_vunmap(void *ptr);
void *internal_vmalloc(size_t size);
void internal_vfree(void *ptr);
unsigned long internal_get_zeroed_page(int priority);
void internal_free_page(unsigned long addr);
int internal_get_user_pages(
		struct task_struct *tsk,
		struct mm_struct *mm,
		unsigned long start,
		int len,
		int write,
		int force,
		struct page **pages,
		struct vm_area_struct **vmas);
void internal_get_page(struct page *page);
void internal_page_cache_release(struct page *page);
#endif  /* __TF_UTIL_H__ */
