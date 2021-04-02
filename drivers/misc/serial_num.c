#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <mt-plat/mtk_devinfo.h>
#include <linux/mmc/mmc.h>
#include <linux/of.h>
#include <linux/of_device.h>

#define HRID0 12
#define HRID1 13
#define HRID2 14
#define HRID3 15

#define PROC_SERIAL_NUM_FILE "serial_num"
#define PROC_CHIPID_FILE "chip_id"

static struct proc_dir_entry *entry;
/*Huaqin modify for K19A-22 by shiwenlong at 2021.4.01 start*/
static char dev_id[40], emmc_id_hash[9];
/*Huaqin modify for K19A-22 by shiwenlong at 2021.4.01 end*/
struct device_node *of_chosen_s;

static void init_ids(void)
{
	unsigned int temp0, temp1, temp2, temp3;

	temp0 = get_devinfo_with_index(HRID0);
	temp1 = get_devinfo_with_index(HRID1);
	temp2 = get_devinfo_with_index(HRID2);
	temp3 = get_devinfo_with_index(HRID3);

	sprintf(dev_id, "%08x%08x%08x%08x", temp0, temp1, temp2, temp3);
	printk("dev_id is %s\n", dev_id);

	of_chosen_s = of_find_node_by_path("/chosen");
	if (of_chosen_s == NULL)
		of_chosen_s = of_find_node_by_path("/chosen@0");

	if (of_chosen_s) {
		const char *name = NULL;

		if (!of_property_read_string(of_chosen_s, "emmc_id,hash", &name)) {
/*Huaqin modify for K19A-22 by shiwenlong at 2021.4.01 start*/
			snprintf(emmc_id_hash, 9, "%s", name);
/*Huaqin modify for K19A-22 by shiwenlong at 2021.4.01 end*/
			printk("emmc_id_hash is : %s\n", emmc_id_hash);
		}
	}
}

static int serial_num_proc_show(struct seq_file *file, void *data)
{
	seq_printf(file, "0x%s%s", dev_id, emmc_id_hash);
	return 0;
}

static int serial_num_proc_open (struct inode *inode, struct file *file)
{
	return single_open(file, serial_num_proc_show, inode->i_private);
}

static const struct file_operations serial_num_proc_fops = {
	.open = serial_num_proc_open,
	.read = seq_read,
};

static int chip_id_proc_show(struct seq_file *file, void *data)
{
	seq_printf(file, "0x%s", dev_id);
	return 0;
}

static int chip_id_proc_open (struct inode *inode, struct file *file)
{
	return single_open(file, chip_id_proc_show, inode->i_private);
}

static const struct file_operations chip_id_proc_fops = {
	.open = chip_id_proc_open,
	.read = seq_read,
};

static int __init sn_fuse_init(void)
{
	init_ids();

	entry = proc_create(PROC_SERIAL_NUM_FILE, 0644, NULL, &serial_num_proc_fops);
	if (entry == NULL)	{
		pr_err("[%s]: create_proc_entry entry failed\n", __func__);
	}

	entry = proc_create(PROC_CHIPID_FILE, 0644, NULL, &chip_id_proc_fops);

	return 0;
}

late_initcall(sn_fuse_init);

static void __exit sn_fuse_exit(void)
{
	printk("sn_fuse_exit\n");
}

module_exit(sn_fuse_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("JTag Fuse driver");

