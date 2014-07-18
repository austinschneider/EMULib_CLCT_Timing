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
	{ 0xeb0ece80, "register_chrdev" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x4c503ced, "kmem_cache_alloc" },
	{ 0x89892632, "malloc_sizes" },
	{ 0xec5f438f, "remap_pfn_range" },
	{ 0xcb51d0fd, "vmalloc_to_pfn" },
	{ 0x37a0cba, "kfree" },
	{ 0x2fd1d81c, "vfree" },
	{ 0x260f87da, "mem_section" },
	{ 0xdd132261, "printk" },
	{ 0x45956ad5, "vmalloc_to_page" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x4f7f1c1a, "cdev_del" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C0FDC08BEDA665CC4AE0C49");
