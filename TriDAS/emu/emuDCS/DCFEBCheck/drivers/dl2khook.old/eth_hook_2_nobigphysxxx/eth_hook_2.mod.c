#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

#undef unix
struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = __stringify(KBUILD_MODNAME),
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x65b4e613, "struct_module" },
	{ 0xc397d995, "__kfree_skb" },
	{ 0x43ca7336, "mem_map" },
	{ 0xdab7d40c, "register_sysctl_table" },
	{ 0x1e3c5d7c, "page_address" },
	{ 0x1922375c, "init_mm" },
	{ 0x32b5b0c0, "dev_get_by_name" },
	{ 0x2fd1d81c, "vfree" },
	{ 0x1d26aa98, "sprintf" },
	{ 0xda02d67, "jiffies" },
	{ 0x9925ce9c, "__might_sleep" },
	{ 0xd7474566, "__copy_to_user_ll" },
	{ 0x9ef719e7, "remap_page_range" },
	{ 0x1af40e18, "__copy_from_user_ll" },
	{ 0x1b7d4074, "printk" },
	{ 0x69b3cc1b, "alloc_skb" },
	{ 0x1075bf0, "panic" },
	{ 0x79b69b16, "proc_dostring" },
	{ 0x49e79940, "__cond_resched" },
	{ 0x3cec27c5, "skb_over_panic" },
	{ 0xe2260104, "unregister_sysctl_table" },
	{ 0x6506d836, "register_chrdev" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0xbd226810, "dev_queue_xmit" },
	{ 0x16969c4a, "kernel_flag" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

