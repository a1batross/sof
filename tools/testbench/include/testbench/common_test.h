/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#ifndef _COMMON_TEST_H
#define _COMMON_TEST_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <sof/sof.h>
#include <sof/audio/component_ext.h>
#include <sof/math/numbers.h>
#include <sof/audio/format.h>

#include <sof/lib/uuid.h>

#define DEBUG_MSG_LEN		1024
#define MAX_LIB_NAME_LEN	1024

#define MAX_OUTPUT_FILE_NUM	16

/* number of widgets types supported in testbench */
#define NUM_WIDGETS_SUPPORTED	11

struct tplg_context;

struct testbench_prm {
	char *tplg_file; /* topology file to use */
	char *input_file; /* input file name */
	char *output_file[MAX_OUTPUT_FILE_NUM]; /* output file names */
	int output_file_num; /* number of output files */
	char *bits_in; /* input bit format */
	int pipelines[MAX_OUTPUT_FILE_NUM]; /* output file names */
	int pipeline_num;
	/*
	 * input and output sample rate parameters
	 * By default, these are calculated from pipeline frames_per_sched
	 * and period but they can also be overridden via input arguments
	 * to the testbench.
	 */
	uint32_t fs_in;
	uint32_t fs_out;
	uint32_t channels_in;
	uint32_t channels_out;
	int fr_id;
	int fw_id;
	int sched_id;
	int max_pipeline_id;
	enum sof_ipc_frame frame_fmt;
	int copy_iterations;
	bool copy_check;
	bool quiet;
	int dynamic_pipeline_iterations;
	int num_vcores;
	int tick_period_us;
	int pipeline_duration_ms;
	int real_time;
	FILE *file;
	char *pipeline_string;
	int output_file_index;
};

struct shared_lib_table {
	char *comp_name;
	char library_name[MAX_LIB_NAME_LEN];
	uint32_t widget_type;
	struct sof_uuid *uid;
	int register_drv;
	void *handle;
};

extern struct shared_lib_table lib_table[];

extern int debug;

int edf_scheduler_init(void);

void sys_comp_file_init(void);

void sys_comp_filewrite_init(void);

int tb_setup(struct sof *sof, struct testbench_prm *tp);
void tb_free(struct sof *sof);

int tb_pipeline_start(struct ipc *ipc, struct pipeline *p,
		      struct testbench_prm *tp);

int tb_pipeline_params(struct ipc *ipc, struct pipeline *p,
		       struct testbench_prm *tp);

int tb_pipeline_stop(struct ipc *ipc, struct pipeline *p,
		     struct testbench_prm *tp);

int tb_pipeline_reset(struct ipc *ipc, struct pipeline *p,
		      struct testbench_prm *tp);

void debug_print(char *message);

int get_index_by_name(char *comp_name,
		      struct shared_lib_table *lib_table);

int get_index_by_type(uint32_t comp_type,
		      struct shared_lib_table *lib_table);

int get_index_by_uuid(struct sof_ipc_comp_ext *comp_ext,
		      struct shared_lib_table *lib_table);
#endif
