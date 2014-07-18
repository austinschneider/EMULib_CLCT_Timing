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
	{ 0xf3d5f8af, "struct_module" },
	{ 0x70885d12, "__kfree_skb" },
	{ 0xf379776e, "register_sysctl_table" },
	{ 0x94beda0e, "dev_get_by_name" },
	{ 0xbee8653, "_spin_lock" },
	{ 0x2fd1d81c, "vfree" },
	{ 0xf74f3d15, "_spin_lock_irqsave" },
	{ 0x1d26aa98, "sprintf" },
	{ 0xda02d67, "jiffies" },
	{ 0xdd132261, "printk" },
	{ 0x4f55c698, "alloc_skb" },
	{ 0xbe499d81, "copy_to_user" },
	{ 0xeb69459d, "_spin_unlock_irqrestore" },
	{ 0x73f0fb6a, "_spin_unlock" },
	{ 0x6ba6a9a4, "proc_dostring" },
	{ 0xcfbea587, "skb_over_panic" },
	{ 0x4a3fd658, "unregister_sysctl_table" },
	{ 0xec7a7a54, "register_chrdev" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x3a151d58, "vmalloc_to_page" },
	{ 0x7bf895c2, "dev_queue_xmit" },
	{ 0xeeb761df, "kernel_flag" },
	{ 0x945bc6a7, "copy_from_user" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

