#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");

#define PROC_NAME "tsulab"

static struct proc_dir_entry *proc_file;

static int tsulab_show(struct seq_file *m, void *v) {
    seq_printf(m, "Welcome to the Tomsk State University\n");
    return 0;
}

static int tsulab_open(struct inode *inode, struct file *file) {
    return single_open(file, tsulab_show, NULL);
}

static const struct file_operations tsulab_fops = {
    .owner = THIS_MODULE,
    .open = tsulab_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init tsu_module_init(void) {
    pr_info("Welcome to the Tomsk State University\n");
    proc_file = proc_create(PROC_NAME, 0, NULL, &tsulab_fops);
    if (!proc_file) {
        pr_err("Failed to create /proc/%s\n", PROC_NAME);
        return -ENOMEM;
    }
    return 0;
}

static void __exit tsu_module_exit(void) {
    pr_info("Tomsk State University forever!\n");
    proc_remove(proc_file);
}

module_init(tsu_module_init);
module_exit(tsu_module_exit);


/*Сумма последовательностей чисел фибоначи*/