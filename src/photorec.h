/*

    File: photorec.h

    Copyright (C) 1998-2008 Christophe GRENIER <grenier@cgsecurity.org>

    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */
#define MAX_FILES_PER_DIR	500
#define DEFAULT_RECUP_DIR "recup_dir"
#ifdef __cplusplus
extern "C" {
#endif

enum photorec_status { STATUS_FIND_OFFSET, STATUS_EXT2_ON, STATUS_EXT2_ON_BF, STATUS_EXT2_OFF, STATUS_EXT2_OFF_BF, STATUS_EXT2_ON_SAVE_EVERYTHING, STATUS_EXT2_OFF_SAVE_EVERYTHING, STATUS_QUIT };
typedef enum photorec_status photorec_status_t;
typedef struct list_cluster_struct list_cluster_t;
struct list_cluster_struct
{
  struct td_list_head list;
  uint64_t offset;
  uint32_t cluster;
  file_data_t *dir_list;
};

int get_prev_file_header(alloc_data_t *list_search_space, alloc_data_t **current_search_space, uint64_t *offset);
int file_finish(file_recovery_t *file_recovery, const char *recup_dir, const int paranoid, unsigned int *file_nbr,
    const unsigned int blocksize, alloc_data_t *list_search_space, alloc_data_t **current_search_space, uint64_t *offset,
    unsigned int *dir_num, const photorec_status_t status, const disk_t *disk);
alloc_data_t *file_finish2(file_recovery_t *file_recovery, const char *recup_dir, const int paranoid, unsigned int *file_nbr,
    const unsigned int blocksize, alloc_data_t *list_search_space,
    unsigned int *dir_num, const photorec_status_t status, const disk_t *disk);
void reset_file_stats(file_stat_t *file_stats);
void write_stats_log(const file_stat_t *file_stats);
void write_stats_stdout(const file_stat_t *file_stats);
void update_stats(file_stat_t *file_stats, alloc_data_t *list_search_space);
partition_t *new_whole_disk(const disk_t *disk_car);
unsigned int find_blocksize(alloc_data_t *list_file, const unsigned int default_blocksize, uint64_t *offset);
alloc_data_t * update_blocksize(unsigned int blocksize, alloc_data_t *list_search_space, const uint64_t offset);
void list_cluster_free(list_cluster_t *list_cluster);
void forget(alloc_data_t *list_search_space, alloc_data_t *current_search_space);
void init_search_space(alloc_data_t *list_search_space, const disk_t *disk_car, const partition_t *partition);
unsigned int remove_used_space(disk_t *disk_car, const partition_t *partition, alloc_data_t *list_search_space);
void free_list_search_space(alloc_data_t *list_search_space);
int sorfile_stat_ts(const void *p1, const void *p2);
unsigned int photorec_mkdir(const char *recup_dir, const unsigned int initial_dir_num);
void list_space_used(const file_recovery_t *file_recovery, const unsigned int sector_size);
void info_list_search_space(const alloc_data_t *list_search_space, const alloc_data_t *current_search_space, const unsigned int sector_size, const int keep_corrupted_file, const int verbose);
alloc_data_t *file_truncate(alloc_data_t *space, file_recovery_t *file, const unsigned int sector_size, const unsigned int blocksize);
void free_search_space(alloc_data_t *list_search_space);
#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

