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
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x89892632, "malloc_sizes" },
	{ 0x467cf91f, "dev_get_by_name" },
	{ 0x1d26aa98, "sprintf" },
	{ 0xdd132261, "printk" },
	{ 0xbe499d81, "copy_to_user" },
	{ 0xee5f6131, "proc_dostring" },
	{ 0x52668fd, "skb_over_panic" },
	{ 0x4c503ced, "kmem_cache_alloc" },
	{ 0xa7484702, "__alloc_skb" },
	{ 0xfedec258, "unregister_sysctl_table" },
	{ 0x1000e51, "schedule" },
	{ 0xaccc9f83, "kfree_skb" },
	{ 0xeb0ece80, "register_chrdev" },
	{ 0x19cacd0, "init_waitqueue_head" },
	{ 0xdb09708f, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x65f4af5f, "prepare_to_wait" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x271f4d2a, "finish_wait" },
	{ 0x6501bcc5, "dev_queue_xmit" },
	{ 0x945bc6a7, "copy_from_user" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "076B14126BE4382833E535F");
