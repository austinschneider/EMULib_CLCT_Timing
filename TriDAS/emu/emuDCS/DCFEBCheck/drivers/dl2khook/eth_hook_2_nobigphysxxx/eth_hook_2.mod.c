#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0xf8e3dbd2, "struct_module" },
	{ 0x3621f8aa, "register_sysctl_table" },
	{ 0x95e0a76b, "init_level4_pgt" },
	{ 0x467cf91f, "dev_get_by_name" },
	{ 0x2fd1d81c, "vfree" },
	{ 0xdd5a37a7, "_spin_lock_irqsave" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0xdd132261, "printk" },
	{ 0x3656bf5a, "lock_kernel" },
	{ 0xbe499d81, "copy_to_user" },
	{ 0x260f87da, "mem_section" },
	{ 0xdf15005, "_spin_unlock_irqrestore" },
	{ 0xee5f6131, "proc_dostring" },
	{ 0xb1f975aa, "unlock_kernel" },
	{ 0x52668fd, "skb_over_panic" },
	{ 0xa7484702, "__alloc_skb" },
	{ 0xfedec258, "unregister_sysctl_table" },
	{ 0xaccc9f83, "kfree_skb" },
	{ 0xeb0ece80, "register_chrdev" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0xec5f438f, "remap_pfn_range" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x6501bcc5, "dev_queue_xmit" },
	{ 0x945bc6a7, "copy_from_user" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "75027EECB18F1E2FB643CC8");
