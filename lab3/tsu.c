#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int __init tsu_module_init(void) {
    pr_info("Welcome to the Tomsk State University\n");
    return 0;
}

static void __exit tsu_module_exit(void) {
    pr_info("Tomsk State University forever!\n");
}

module_init(tsu_module_init);
module_exit(tsu_module_exit);