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
	{ 0x6d172fe6, "pci_unregister_driver" },
	{ 0xaaa30118, "pci_register_driver" },
	{ 0x59f73b9, "unregister_netdev" },
	{ 0x1683aa15, "del_timer" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x25b5f62b, "__netdev_watchdog_up" },
	{ 0x4dcbeade, "linkwatch_fire_event" },
	{ 0xa0593b02, "eth_type_trans" },
	{ 0x3cec27c5, "skb_over_panic" },
	{ 0xd8c152cd, "raise_softirq_irqoff" },
	{ 0x9000f1d5, "per_cpu__softnet_data" },
	{ 0xc397d995, "__kfree_skb" },
	{ 0x69b3cc1b, "alloc_skb" },
	{ 0x1075bf0, "panic" },
	{ 0xf34350ab, "__mod_timer" },
	{ 0xda02d67, "jiffies" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x26e96637, "request_irq" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0xb7c82d3b, "pci_disable_device" },
	{ 0xb02b2495, "pci_release_regions" },
	{ 0x9bab5333, "free_netdev" },
	{ 0x9774eaa5, "dma_free_coherent" },
	{ 0xb85b20fe, "register_netdev" },
	{ 0xd3624ac6, "pci_bus_read_config_byte" },
	{ 0xe1e0a7ea, "dma_alloc_coherent" },
	{ 0xe89eabc3, "alloc_etherdev" },
	{ 0xc2669443, "pci_set_master" },
	{ 0xd4bde4d6, "pci_request_regions" },
	{ 0x7a93221b, "pci_enable_device" },
	{ 0x1b7d4074, "printk" },
	{ 0x89b301d4, "param_get_int" },
	{ 0x98bd6f46, "param_set_int" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v00001186d00004000sv*sd*bc*sc*i*");
