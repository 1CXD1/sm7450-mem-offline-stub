# sm7450-mem-offline-stub
Production-grade QCOM Memory Offline Stub for SM7450 (Xiaomi Mi 13 Lite). Fixes 8GB RAM regression and ASoC audio error -22.

# QCOM Memory Offline Stub (SM7450 / Xiaomi ziyi)

A production-grade kernel stub driver designed for the Snapdragon 7 Gen 1 (SM7450) platform, specifically targeting the Xiaomi Mi 13 Lite (`ziyi`).

## ⚠️ The Problem
Custom ROM and kernel development on the SM7450 platform suffers from severe regressions due to proprietary vendor blobs relying on the Memory Offline driver. Missing or improper handling of this driver causes:
1. **RAM Detection Drop:** The system incorrectly reports 6GB of RAM instead of the physical 8GB.
2. **Audio Subsystem Failure:** ADSP/Binder blobs fail to probe, resulting in `ASoC error -22` and broken audio.
3. **Kernel Panics / Hangs:** Caused by the buggy PASR (Partially Allocated Shared RAM) logic.

## 🛠️ The Solution
This minimalist, production-ready stub driver bypasses the PASR logic while fulfilling the dependencies required by the proprietary blobs. 

**Technical Highlights:**
* Uses `subsys_initcall` to beat the vendor blobs in the kernel boot race.
* Properly exports `MODULE_DEVICE_TABLE` to ensure hotplug and Device Tree matching.
* Safely implements `.suppress_bind_attrs = true` to prevent userspace from accidentally unbinding the driver, preventing random kernel panics.

## 💻 Code Structure
The implementation is contained in a single C file (`qcom_mem_offline.c`), adhering strictly to Linux Kernel standards, making it easy to cherry-pick into any Android kernel tree.

## 🚀 How to Implement
1. Add `qcom_mem_offline.c` to your kernel source tree (e.g., under `drivers/soc/qcom/`).
2. Update the corresponding `Makefile`:
   ```makefile
   obj-y += qcom_mem_offline.o
   
