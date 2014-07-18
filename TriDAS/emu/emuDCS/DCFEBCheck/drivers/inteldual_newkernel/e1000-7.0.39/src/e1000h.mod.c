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
	{ 0x6f0530cb, "alloc_pages_current" },
	{ 0x3ce4ca6f, "disable_irq" },
	{ 0x8b8fd95a, "pci_bus_read_config_byte" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0x3922d605, "_spin_trylock" },
	{ 0xf9a482f9, "msleep" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x89b301d4, "param_get_int" },
	{ 0x1c178628, "alloc_etherdev" },
	{ 0xe1b7029c, "print_tainted" },
	{ 0x36249e28, "pci_disable_device" },
	{ 0xa1c9a512, "netif_carrier_on" },
	{ 0x429328d9, "_spin_lock" },
	{ 0xa82be0e3, "ethtool_op_get_sg" },
	{ 0x7ad5eec9, "schedule_work" },
	{ 0x806d5133, "param_array_get" },
	{ 0x7f17303b, "netif_carrier_off" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xd20f583f, "pci_release_regions" },
	{ 0x6876581b, "raise_softirq_irqoff" },
	{ 0x99b4e8e4, "pci_enable_wake" },
	{ 0x2fd1d81c, "vfree" },
	{ 0x59d87ef5, "pci_bus_write_config_word" },
	{ 0x98bd6f46, "param_set_int" },
	{ 0xdd5a37a7, "_spin_lock_irqsave" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x89cef6fb, "param_array_set" },
	{ 0xfe6f6aa1, "pci_dev_driver" },
	{ 0x7d11c268, "jiffies" },
	{ 0xe589de52, "__pskb_pull_tail" },
	{ 0x490ef5ac, "pci_set_master" },
	{ 0xc659d5a, "del_timer_sync" },
	{ 0xde0bdcff, "memset" },
	{ 0x52f4bcd2, "pci_set_dma_mask" },
	{ 0xc16fe12d, "__memcpy" },
	{ 0xdd132261, "printk" },
	{ 0x38afe44d, "ethtool_op_get_link" },
	{ 0x8e0caa25, "pci_find_device" },
	{ 0x1715f7ba, "free_netdev" },
	{ 0x7ec9bfbc, "strncpy" },
	{ 0xa8b48a3f, "register_netdev" },
	{ 0xd1b9b39e, "dma_free_coherent" },
	{ 0x35e0d91d, "pci_bus_write_config_dword" },
	{ 0x260f87da, "mem_section" },
	{ 0x521445b, "list_del" },
	{ 0xdf15005, "_spin_unlock_irqrestore" },
	{ 0xf3b39202, "mod_timer" },
	{ 0x1902adf, "netpoll_trap" },
	{ 0x9eac042a, "__ioremap" },
	{ 0x26e9c85f, "pci_enable_msi" },
	{ 0x75512166, "dev_kfree_skb_any" },
	{ 0xfb999f65, "dma_alloc_coherent" },
	{ 0xe523ad75, "synchronize_irq" },
	{ 0x3980aac1, "unregister_reboot_notifier" },
	{ 0xb40cb096, "pci_set_mwi" },
	{ 0x52668fd, "skb_over_panic" },
	{ 0x7dceceac, "capable" },
	{ 0xea7b3577, "netif_device_attach" },
	{ 0xec4b3e2f, "netif_device_detach" },
	{ 0xa7484702, "__alloc_skb" },
	{ 0xb11e2cf, "pci_bus_read_config_word" },
	{ 0x1cc6719a, "register_reboot_notifier" },
	{ 0x3fd1c8a5, "ethtool_op_set_sg" },
	{ 0x65b75503, "pci_bus_read_config_dword" },
	{ 0x5271af5d, "request_irq" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x4accc1ba, "eth_type_trans" },
	{ 0x57d6046f, "pskb_expand_head" },
	{ 0x1a35c71c, "pci_unregister_driver" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0xa5c89579, "init_timer" },
	{ 0xb85cff09, "pci_set_power_state" },
	{ 0xddc144e1, "pci_clear_mwi" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x9c55cec, "schedule_timeout_interruptible" },
	{ 0x37a0cba, "kfree" },
	{ 0x6067a146, "memcpy" },
	{ 0x801678, "flush_scheduled_work" },
	{ 0x4c5b4b9f, "pci_request_regions" },
	{ 0xecbc6b8d, "pci_disable_msi" },
	{ 0xedc03953, "iounmap" },
	{ 0x769a5e96, "__pci_register_driver" },
	{ 0x4c6c6926, "put_page" },
	{ 0xa9a6b541, "unregister_netdev" },
	{ 0x19c0f186, "ethtool_op_get_tso" },
	{ 0x5761ca5f, "pci_choose_state" },
	{ 0x5ea3b37e, "__netif_schedule" },
	{ 0x498c5804, "consume_skb" },
	{ 0x399280fc, "pci_enable_device" },
	{ 0x29f44b06, "pci_set_consistent_dma_mask" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xd64b746f, "dma_ops" },
	{ 0x72f52ed7, "ethtool_op_get_perm_addr" },
	{ 0x2f21f9f4, "__netif_rx_schedule" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xe914e41e, "strcpy" },
	{ 0x61d6d186, "per_cpu__softnet_data" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v00008086d00001000sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001004sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001008sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001009sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000100Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000100Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000100Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000100Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001010sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001011sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001012sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001013sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001015sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001016sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001017sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001018sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001019sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000101Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000101Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000101Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001026sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001027sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001028sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000105Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000105Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001060sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "10DC9E0BB65451D4AD4EC06");
