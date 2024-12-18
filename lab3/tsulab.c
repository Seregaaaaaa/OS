#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");

#define PROC_NAME "tsulab"

static struct proc_dir_entry *proc_file;
static int fib1 = 0, fib2 = 1, Sfib = 0;

static int tsulab_show(struct seq_file *m, void *v) {
    int next_fib = fib1 + fib2;
    Sfib += next_fib;
    fib1 = fib2;
    fib2 = next_fib;
    seq_printf(m, "%lu\n", Sfib);
    return 0;
}

static int tsulab_open(struct inode *inode, struct file *file) {
    return single_open(file, tsulab_show, NULL);
}

static const struct proc_ops tsulab_fops = {
    .proc_open = tsulab_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
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