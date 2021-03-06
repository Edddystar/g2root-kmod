#include <linux/module.h>
#include <linux/init.h>

#include <linux/kobject.h>
#include <linux/platform_device.h>
#include "../fs/sysfs/sysfs.h"

struct kobject *pbus_kobject;
struct sysfs_dirent *sd;
struct sysfs_dirent *dir;

static void walk_dir(struct sysfs_dirent *dir) {
	
	printk("dirent flags: %d\n", dir->s_flags);
	printk("dirent name: %s\n", dir->s_name);

	if (dir->s_flags & SYSFS_DIR) {
		walk_dir(dir->s_dir.children);
		return;
	};

	if (dir->s_flags & SYSFS_KOBJ_ATTR) {
		return;
	};

	return;
}

static int __init test_init(void) {
        printk("test module loaded\n");

	pbus_kobject = &platform_bus.kobj;
	sd = pbus_kobject->sd;

	printk("platform_bus kobject: %.8x\n", (unsigned int)pbus_kobject);

	walk_dir(sd);

	return 0;
}

static void __exit test_exit(void) {
        printk("test module unloaded\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
