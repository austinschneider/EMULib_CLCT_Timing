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
	{ 0x98af416e, "struct_module" },
	{ 0x2e9ca3e1, "__kfree_skb" },
	{ 0xdb19f1c4, "register_sysctl_table" },
	{ 0x9957ab9d, "autoremove_wake_function" },
	{ 0x467e82db, "malloc_sizes" },
	{ 0x6be70cd8, "dev_get_by_name" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x9925ce9c, "__might_sleep" },
	{ 0xd7474566, "__copy_to_user_ll" },
	{ 0x1af40e18, "__copy_from_user_ll" },
	{ 0x1b7d4074, "printk" },
	{ 0x48d35066, "alloc_skb" },
	{ 0x2fc64a00, "proc_dostring" },
	{ 0x49e79940, "__cond_resched" },
	{ 0x463a476a, "skb_over_panic" },
	{ 0x99e3ad92, "kmem_cache_alloc" },
	{ 0xb3240cac, "unregister_sysctl_table" },
	{ 0x4292364c, "schedule" },
	{ 0x2071e84e, "register_chrdev" },
	{ 0xdfb5f711, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x2e60bace, "memcpy" },
	{ 0x83c10f50, "prepare_to_wait" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x5ac6c754, "finish_wait" },
	{ 0x7112ead2, "dev_queue_xmit" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

