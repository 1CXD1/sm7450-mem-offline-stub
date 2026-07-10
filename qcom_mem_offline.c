‎#include <linux/module.h>
‎#include <linux/platform_device.h>
‎#include <linux/of.h>
‎
‎/*
‎* qcom_mem_offline_stub: yeah I made that I'm cool baby 😎 
‎* only for : Xiaomi Mi 13 Lite (ziyi) / SM7450
‎
‎* This stub is to fix those problems son :

‎* 1- Fix 6 gigs of ram problem 

‎* 2- Prevents ASoC error -22

‎* 3- Make the sys hangs by bypassing PASR i guess
‎*/
‎
‎static int qcom_mem_offline_probe(struct platform_device *pdev)
‎{

‎dev_info(&pdev->dev, "mem-offline: Stub probed. RAM and Blobs satisfied.\n");
‎return 0;
‎}
‎
‎static const struct of_device_id qcom_mem_offline_match[] = {
‎{ .compatible = "qcom,mem-offline" },
‎{ }
‎};
‎
‎/* 
‎* PLEASE FOLLOW README.md instructions.
‎*/
‎MODULE_DEVICE_TABLE(of, qcom_mem_offline_match);
‎
‎static struct platform_driver qcom_mem_offline_driver = {
‎.probe = qcom_mem_offline_probe,
‎.driver = {
‎.name = "qcom_mem_offline", /* exact name so the blobs work perfectly */
‎.of_match_table = qcom_mem_offline_match,
‎.suppress_bind_attrs = true, /* for no unbind panics */
‎},
‎};
‎
‎/* 
‎* MUST be as built-in (obj-y) 
‎*/
‎static int __init qcom_mem_offline_init(void)
‎{
‎return platform_driver_register(&qcom_mem_offline_driver);
‎}
‎subsys_initcall(qcom_mem_offline_init);
‎
‎MODULE_DESCRIPTION("QCOM Memory Offline Stub (Final Production Version)");
‎MODULE_LICENSE("GPL v2");
‎
