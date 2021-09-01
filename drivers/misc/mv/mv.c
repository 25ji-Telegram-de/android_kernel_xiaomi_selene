#include <linux/atomic.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/proc_fs.h>
#include <uapi/linux/sched/types.h>
#include <linux/seq_file.h>
#include <linux/fs.h>
#include <linux/kernel_stat.h>
#include <linux/cpu.h>
#include <linux/memblock.h>
#include <linux/byteorder/generic.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include "../hqsysfs/hqsys_misc.h"
#include "../../mmc/core/card.h"

#define PROC_MEMTYPE_FILE "memory_type"
#define PROC_MV_FILE "mv"
#define K(x) ((x) << (PAGE_SHIFT - 10))
extern  round_kbytes_to_readable_mbytes(unsigned int k);
extern	ssize_t hq_emmcinfo(char *buf);
extern char kernel_fwrew[10];
/* Huaqin modify for HQ-123324 by luocheng at 2021/04/23 start */
extern ddr_id[10];
/* Huaqin modify for HQ-123324 by luocheng at 2021/04/23 end */
static struct proc_dir_entry *mv_proc;
static struct proc_dir_entry *memory_type;
char part_num[30];


static int mv_proc_show(struct seq_file *file, void*data)
{
	struct sysinfo i;
	si_meminfo(&i);
	int status;
	char RAM_size[8];
	char emmc_size[8];
	char emmc_ssize[8];
	uint32_t manfidd;
	char manfid[32];
	char *product_version;

	status = hq_emmcinfo(emmc_size);
	snprintf(emmc_ssize, strlen(emmc_size)-1,"%s", emmc_size);
	if (round_kbytes_to_readable_mbytes(K(i.totalram)) >= 1024) {
		status = sprintf(RAM_size, "%d", round_kbytes_to_readable_mbytes(K(i.totalram))/1024);
	} else{
		status = sprintf(RAM_size, "%d", round_kbytes_to_readable_mbytes(K(i.totalram)));
	}
	/* Huaqin modify for HQ-123324 by luocheng at 2021/04/28 start */
	if(strcmp("K19A_Micro_9S9",part_num) == 0)
	{
		sprintf(part_num,"%s","MT29VZZZAD9GQFSM_046W_9S9");
	}
        /* Huaqin modify for K19A-274 by luocheng at 2021/05/14 start */
	else if(strcmp("K19A_Micro_9K9",part_num) == 0)
	{
		sprintf(part_num,"%s","MT29VZZZAD9DQKSM_046W_9K9");
	}
        /* Huaqin modify for K19A-274 by luocheng at 2021/05/14 end */
	/* Huaqin modify for HQ-123324 by luocheng at 2021/08/31 start */
	else if(strcmp("K19S_Micro_WTA",part_num) == 0)
	{
		sprintf(part_num,"%s","MT53E1536M32DDNQ_046_WTA");
	}
	/* Huaqin modify for HQ-123324 by luocheng at 2021/08/31 end */
	manfidd = mmc_get_manfid();
	snprintf(manfid, 5,"0x%x", manfidd);
	seq_printf(file,"D: %s %s\n", ddr_id, RAM_size);
	seq_printf(file,"U: %s %s %s 0x%x\n", manfid, emmc_ssize, part_num, kernel_fwrew[0]);
	/* Huaqin modify for HQ-123324 by luocheng at 2021/04/28 end */

	return 0;
}

static int __init part_num_setup(char *str)
{
	unsigned int i;
	sprintf(part_num,"%s",str);
	return 1;
}
__setup("part_num=", part_num_setup);


static int mv_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, mv_proc_show, NULL);
}

static const struct file_operations mv_proc_fops = {
	.open		= mv_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

int proc_mv_init(void)
{
	mv_proc = proc_create(PROC_MV_FILE, 0644, NULL, &mv_proc_fops);
	if (mv_proc == NULL)
	{
		pr_info("create mv node failed:%d\n",mv_proc);
	}
	return 0;
}

void proc_mv_exit(void)
{
	 pr_info("exit mv !\n");
	 remove_proc_entry(PROC_MV_FILE,NULL);
}

static int memtype_proc_show(struct seq_file *file, void*data)
{
	seq_printf(file,"%s\n", "EMMC");
	return 0;
}

static int memtype_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, memtype_proc_show, NULL);
}

static const struct file_operations memtype_proc_fops = {
	.open		= memtype_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};


int proc_memtype_init(void)
{
	memory_type = proc_create(PROC_MEMTYPE_FILE, 0644, NULL, &memtype_proc_fops);
	if (memory_type == NULL)
	{
		pr_info("create memory type node failed:%d\n",memory_type);
	}
	return 0;
}


void proc_memtype_exit(void)
{
	 pr_info("exit memory type !\n");
	 remove_proc_entry(PROC_MEMTYPE_FILE,NULL);
}


MODULE_LICENSE("GPL");
module_init(proc_mv_init);
module_exit(proc_mv_exit);
module_init(proc_memtype_init);
module_exit(proc_memtype_exit);
