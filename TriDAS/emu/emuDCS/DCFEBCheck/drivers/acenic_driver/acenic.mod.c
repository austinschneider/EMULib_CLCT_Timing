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
	{ 0x25da070, "snprintf" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x43ca7336, "mem_map" },
	{ 0x79ad224b, "tasklet_kill" },
	{ 0xa5808bbf, "tasklet_init" },
	{ 0xed5c73bf, "__tasklet_schedule" },
	{ 0x2afb5635, "netif_rx" },
	{ 0x71c90087, "memcmp" },
	{ 0xd8c152cd, "raise_softirq_irqoff" },
	{ 0x9000f1d5, "per_cpu__softnet_data" },
	{ 0xa0593b02, "eth_type_trans" },
	{ 0x3cec27c5, "skb_over_panic" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0x69b3cc1b, "alloc_skb" },
	{ 0xda02d67, "jiffies" },
	{ 0x26e96637, "request_irq" },
	{ 0x123d3b6a, "kmem_cache_alloc" },
	{ 0x6c3397fb, "malloc_sizes" },
	{ 0x863d23a3, "pci_set_dma_mask" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xedc03953, "iounmap" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x37a0cba, "kfree" },
	{ 0xe1e0a7ea, "dma_alloc_coherent" },
	{ 0x9774eaa5, "dma_free_coherent" },
	{ 0x6d172fe6, "pci_unregister_driver" },
	{ 0xaaa30118, "pci_register_driver" },
	{ 0xc397d995, "__kfree_skb" },
	{ 0x59f73b9, "unregister_netdev" },
	{ 0x9bab5333, "free_netdev" },
	{ 0xb85b20fe, "register_netdev" },
	{ 0x9eac042a, "__ioremap" },
	{ 0xa1e60194, "pci_bus_write_config_byte" },
	{ 0xd3624ac6, "pci_bus_read_config_byte" },
	{ 0xb6ba13c7, "pci_bus_write_config_word" },
	{ 0xc6edbc73, "pci_bus_read_config_word" },
	{ 0xc2669443, "pci_set_master" },
	{ 0x7a93221b, "pci_enable_device" },
	{ 0x1b7d4074, "printk" },
	{ 0xe89eabc3, "alloc_etherdev" },
	{ 0x806d5133, "param_array_get" },
	{ 0x89cef6fb, "param_array_set" },
	{ 0x89b301d4, "param_get_int" },
	{ 0x98bd6f46, "param_set_int" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v000012AEd00000001sv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v000012AEd00000002sv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v000010B7d00000001sv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v00001385d0000620Asv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v00001385d0000630Asv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v00001011d0000001Asv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v000012AEd000000FAsv*sd*bc02sc00i*");
MODULE_ALIAS("pci:v000010A9d00000009sv*sd*bc02sc00i*");
