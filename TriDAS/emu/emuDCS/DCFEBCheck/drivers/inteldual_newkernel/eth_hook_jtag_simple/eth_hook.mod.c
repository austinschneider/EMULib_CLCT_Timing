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
	{ 0x6bd50ef5, "autoremove_wake_function" },
	{ 0xb5f8ad4b, "malloc_sizes" },
	{ 0x94beda0e, "dev_get_by_name" },
	{ 0x1d26aa98, "sprintf" },
	{ 0xdd132261, "printk" },
	{ 0x4f55c698, "alloc_skb" },
	{ 0xbe499d81, "copy_to_user" },
	{ 0x6ba6a9a4, "proc_dostring" },
	{ 0xcfbea587, "skb_over_panic" },
	{ 0xcb0d98f0, "kmem_cache_alloc" },
	{ 0x4a3fd658, "unregister_sysctl_table" },
	{ 0x1000e51, "schedule" },
	{ 0xec7a7a54, "register_chrdev" },
	{ 0x9eba8fa1, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0xe4ec5aa1, "prepare_to_wait" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x3e9450f3, "finish_wait" },
	{ 0x7bf895c2, "dev_queue_xmit" },
	{ 0x945bc6a7, "copy_from_user" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

