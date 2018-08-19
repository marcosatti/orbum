#include "Resources/RResources.hpp"

RResources::RResources() :
    boot_rom(Constants::EE::ROM::SIZE_BOOT_ROM, 0, true),
    rom1(Constants::EE::ROM::SIZE_ROM1, 0, true),
    erom(Constants::EE::ROM::SIZE_EROM, 0, true),
    rom2(Constants::EE::ROM::SIZE_ROM2, 0, true),
    sbus_f260(0, true)
{
}

void initialise_cdvd(RResources* r)
{
    r->cdvd.n_data_out.ns_rdy_din = &r->cdvd.n_rdy_din;
    r->cdvd.s_data_out.ns_rdy_din = &r->cdvd.s_rdy_din;
    r->cdvd.n_command.ns_rdy_din = &r->cdvd.n_rdy_din;
    r->cdvd.s_command.ns_rdy_din = &r->cdvd.s_rdy_din;
}

void initialise_spu2(RResources* r)
{
    r->spu2.core_0.dma_fifo_queue = &r->fifo_spu2c0;
    r->spu2.core_1.dma_fifo_queue = &r->fifo_spu2c1;
    r->spu2.cores[0] = &r->spu2.core_0;
    r->spu2.cores[1] = &r->spu2.core_1;
    r->spu2.core_0.admas.core_id = &r->spu2.core_0.core_id;
    r->spu2.core_1.admas.core_id = &r->spu2.core_1.core_id;
}

void initialise_ee_timers(RResources* r)
{
    r->ee.timers.units[0].unit_id = &r->ee.timers.unit_0.unit_id;
    r->ee.timers.units[1].unit_id = &r->ee.timers.unit_1.unit_id;
    r->ee.timers.units[2].unit_id = &r->ee.timers.unit_2.unit_id;
    r->ee.timers.units[3].unit_id = &r->ee.timers.unit_3.unit_id;

    r->ee.timers.units[0].count = &r->ee.timers.unit_0.count;
    r->ee.timers.units[1].count = &r->ee.timers.unit_1.count;
    r->ee.timers.units[2].count = &r->ee.timers.unit_2.count;
    r->ee.timers.units[3].count = &r->ee.timers.unit_3.count;

    r->ee.timers.units[0].mode = &r->ee.timers.unit_0.mode;
    r->ee.timers.units[1].mode = &r->ee.timers.unit_1.mode;
    r->ee.timers.units[2].mode = &r->ee.timers.unit_2.mode;
    r->ee.timers.units[3].mode = &r->ee.timers.unit_3.mode;

    r->ee.timers.units[0].compare = &r->ee.timers.unit_0.compare;
    r->ee.timers.units[1].compare = &r->ee.timers.unit_1.compare;
    r->ee.timers.units[2].compare = &r->ee.timers.unit_2.compare;
    r->ee.timers.units[3].compare = &r->ee.timers.unit_3.compare;

    r->ee.timers.units[0].hold = &r->ee.timers.unit_0.hold;
    r->ee.timers.units[1].hold = &r->ee.timers.unit_1.hold;
}

void initialise_ee_dmac(RResources* r)
{
    // Init SIF sbus references.
    r->ee.dmac.channel_sif0.chcr.sbus_f240 = &r->sbus_f240;
    r->ee.dmac.channel_sif1.chcr.sbus_f240 = &r->sbus_f240;
    r->ee.dmac.channel_sif2.chcr.sbus_f240 = &r->sbus_f240;

    // Init channel abstrations.
    r->ee.dmac.channels[0].channel_id = &r->ee.dmac.channel_vif0.channel_id;
    r->ee.dmac.channels[0].madr = &r->ee.dmac.channel_vif0.madr;
    r->ee.dmac.channels[0].qwc = &r->ee.dmac.channel_vif0.qwc;
    r->ee.dmac.channels[0].chcr = &r->ee.dmac.channel_vif0.chcr;
    r->ee.dmac.channels[0].tadr = &r->ee.dmac.channel_vif0.tadr;
    r->ee.dmac.channels[0].asr[0] = &r->ee.dmac.channel_vif0.asr[0];
    r->ee.dmac.channels[0].asr[1] = &r->ee.dmac.channel_vif0.asr[1];
    r->ee.dmac.channels[1].channel_id = &r->ee.dmac.channel_vif1.channel_id;
    r->ee.dmac.channels[1].madr = &r->ee.dmac.channel_vif1.madr;
    r->ee.dmac.channels[1].qwc = &r->ee.dmac.channel_vif1.qwc;
    r->ee.dmac.channels[1].chcr = &r->ee.dmac.channel_vif1.chcr;
    r->ee.dmac.channels[1].tadr = &r->ee.dmac.channel_vif1.tadr;
    r->ee.dmac.channels[1].asr[0] = &r->ee.dmac.channel_vif1.asr[0];
    r->ee.dmac.channels[1].asr[1] = &r->ee.dmac.channel_vif1.asr[1];
    r->ee.dmac.channels[2].channel_id = &r->ee.dmac.channel_gif.channel_id;
    r->ee.dmac.channels[2].madr = &r->ee.dmac.channel_gif.madr;
    r->ee.dmac.channels[2].qwc = &r->ee.dmac.channel_gif.qwc;
    r->ee.dmac.channels[2].chcr = &r->ee.dmac.channel_gif.chcr;
    r->ee.dmac.channels[2].tadr = &r->ee.dmac.channel_gif.tadr;
    r->ee.dmac.channels[2].asr[0] = &r->ee.dmac.channel_gif.asr[0];
    r->ee.dmac.channels[2].asr[1] = &r->ee.dmac.channel_gif.asr[1];
    r->ee.dmac.channels[3].channel_id = &r->ee.dmac.channel_fromipu.channel_id;
    r->ee.dmac.channels[3].madr = &r->ee.dmac.channel_fromipu.madr;
    r->ee.dmac.channels[3].qwc = &r->ee.dmac.channel_fromipu.qwc;
    r->ee.dmac.channels[3].chcr = &r->ee.dmac.channel_fromipu.chcr;
    r->ee.dmac.channels[4].channel_id = &r->ee.dmac.channel_toipu.channel_id;
    r->ee.dmac.channels[4].madr = &r->ee.dmac.channel_toipu.madr;
    r->ee.dmac.channels[4].qwc = &r->ee.dmac.channel_toipu.qwc;
    r->ee.dmac.channels[4].chcr = &r->ee.dmac.channel_toipu.chcr;
    r->ee.dmac.channels[4].tadr = &r->ee.dmac.channel_toipu.tadr;
    r->ee.dmac.channels[5].channel_id = &r->ee.dmac.channel_sif0.channel_id;
    r->ee.dmac.channels[5].madr = &r->ee.dmac.channel_sif0.madr;
    r->ee.dmac.channels[5].qwc = &r->ee.dmac.channel_sif0.qwc;
    r->ee.dmac.channels[5].chcr = &r->ee.dmac.channel_sif0.chcr;
    r->ee.dmac.channels[6].channel_id = &r->ee.dmac.channel_sif1.channel_id;
    r->ee.dmac.channels[6].madr = &r->ee.dmac.channel_sif1.madr;
    r->ee.dmac.channels[6].qwc = &r->ee.dmac.channel_sif1.qwc;
    r->ee.dmac.channels[6].chcr = &r->ee.dmac.channel_sif1.chcr;
    r->ee.dmac.channels[6].tadr = &r->ee.dmac.channel_sif1.tadr;
    r->ee.dmac.channels[7].channel_id = &r->ee.dmac.channel_sif2.channel_id;
    r->ee.dmac.channels[7].madr = &r->ee.dmac.channel_sif2.madr;
    r->ee.dmac.channels[7].qwc = &r->ee.dmac.channel_sif2.qwc;
    r->ee.dmac.channels[7].chcr = &r->ee.dmac.channel_sif2.chcr;
    r->ee.dmac.channels[8].channel_id = &r->ee.dmac.channel_fromspr.channel_id;
    r->ee.dmac.channels[8].madr = &r->ee.dmac.channel_fromspr.madr;
    r->ee.dmac.channels[8].qwc = &r->ee.dmac.channel_fromspr.qwc;
    r->ee.dmac.channels[8].chcr = &r->ee.dmac.channel_fromspr.chcr;
    r->ee.dmac.channels[8].sadr = &r->ee.dmac.channel_fromspr.sadr;
    r->ee.dmac.channels[9].channel_id = &r->ee.dmac.channel_tospr.channel_id;
    r->ee.dmac.channels[9].madr = &r->ee.dmac.channel_tospr.madr;
    r->ee.dmac.channels[9].qwc = &r->ee.dmac.channel_tospr.qwc;
    r->ee.dmac.channels[9].chcr = &r->ee.dmac.channel_tospr.chcr;
    r->ee.dmac.channels[9].tadr = &r->ee.dmac.channel_tospr.tadr;
    r->ee.dmac.channels[9].sadr = &r->ee.dmac.channel_tospr.sadr;

    // Init DMA FIFO queues.
    r->ee.dmac.channels[0].dma_fifo_queue = &r->fifo_vif0;
    r->ee.dmac.channels[1].dma_fifo_queue = &r->fifo_vif1;
    r->ee.dmac.channels[2].dma_fifo_queue = &r->fifo_gif_path3;
    r->ee.dmac.channels[3].dma_fifo_queue = &r->fifo_fromipu;
    r->ee.dmac.channels[4].dma_fifo_queue = &r->fifo_toipu;
    r->ee.dmac.channels[5].dma_fifo_queue = &r->fifo_sif0;
    r->ee.dmac.channels[6].dma_fifo_queue = &r->fifo_sif1;
    r->ee.dmac.channels[7].dma_fifo_queue = &r->fifo_sif2;
}

void initialise_ee_vpu(RResources* r)
{
    // Init VIF resources.
    r->ee.vpu.vif.unit_0.dma_fifo_queue = &r->fifo_vif0;
    r->ee.vpu.vif.unit_1.dma_fifo_queue = &r->fifo_vif1;

    r->ee.vpu.vif.units[0] = &r->ee.vpu.vif.unit_0;
    r->ee.vpu.vif.units[1] = &r->ee.vpu.vif.unit_1;

    // Init vi_32 wrappers.
    for (int i = 0; i < Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
    {
        r->ee.vpu.vu.unit_0.vi_32[i].hword_register = &r->ee.vpu.vu.unit_0.vi[i];
        r->ee.vpu.vu.unit_1.vi_32[i].hword_register = &r->ee.vpu.vu.unit_1.vi[i];
    }

    // Init unit_0.ccr registers.
    r->ee.vpu.vu.unit_0.ccr[0] = &r->ee.vpu.vu.unit_0.vi_32[0];
    r->ee.vpu.vu.unit_0.ccr[1] = &r->ee.vpu.vu.unit_0.vi_32[1];
    r->ee.vpu.vu.unit_0.ccr[2] = &r->ee.vpu.vu.unit_0.vi_32[2];
    r->ee.vpu.vu.unit_0.ccr[3] = &r->ee.vpu.vu.unit_0.vi_32[3];
    r->ee.vpu.vu.unit_0.ccr[4] = &r->ee.vpu.vu.unit_0.vi_32[4];
    r->ee.vpu.vu.unit_0.ccr[5] = &r->ee.vpu.vu.unit_0.vi_32[5];
    r->ee.vpu.vu.unit_0.ccr[6] = &r->ee.vpu.vu.unit_0.vi_32[6];
    r->ee.vpu.vu.unit_0.ccr[7] = &r->ee.vpu.vu.unit_0.vi_32[7];
    r->ee.vpu.vu.unit_0.ccr[8] = &r->ee.vpu.vu.unit_0.vi_32[8];
    r->ee.vpu.vu.unit_0.ccr[9] = &r->ee.vpu.vu.unit_0.vi_32[9];
    r->ee.vpu.vu.unit_0.ccr[10] = &r->ee.vpu.vu.unit_0.vi_32[10];
    r->ee.vpu.vu.unit_0.ccr[11] = &r->ee.vpu.vu.unit_0.vi_32[11];
    r->ee.vpu.vu.unit_0.ccr[12] = &r->ee.vpu.vu.unit_0.vi_32[12];
    r->ee.vpu.vu.unit_0.ccr[13] = &r->ee.vpu.vu.unit_0.vi_32[13];
    r->ee.vpu.vu.unit_0.ccr[14] = &r->ee.vpu.vu.unit_0.vi_32[14];
    r->ee.vpu.vu.unit_0.ccr[15] = &r->ee.vpu.vu.unit_0.vi_32[15];
    r->ee.vpu.vu.unit_0.ccr[16] = &r->ee.vpu.vu.unit_0.status;
    r->ee.vpu.vu.unit_0.ccr[17] = &r->ee.vpu.vu.unit_0.mac;
    r->ee.vpu.vu.unit_0.ccr[18] = &r->ee.vpu.vu.unit_0.clipping;
    r->ee.vpu.vu.unit_0.ccr[20] = &r->ee.vpu.vu.unit_0.r;
    r->ee.vpu.vu.unit_0.ccr[21] = &r->ee.vpu.vu.unit_0.i;
    r->ee.vpu.vu.unit_0.ccr[22] = &r->ee.vpu.vu.unit_0.q;
    r->ee.vpu.vu.unit_0.ccr[26] = &r->ee.vpu.vu.unit_0.pc; // TPC.
    r->ee.vpu.vu.unit_0.ccr[27] = &r->ee.vpu.vu.unit_0.cmsar;
    r->ee.vpu.vu.unit_0.ccr[28] = &r->ee.vpu.vu.fbrst;
    r->ee.vpu.vu.unit_0.ccr[29] = &r->ee.vpu.stat;
    r->ee.vpu.vu.unit_0.ccr[31] = &r->ee.vpu.vu.unit_1.cmsar;

    // Init VU units array.
    r->ee.vpu.vu.units[0] = &r->ee.vpu.vu.unit_0;
    r->ee.vpu.vu.units[1] = &r->ee.vpu.vu.unit_1;

    // Init VU0 memory.
    {
        // Memory + mirrors.
        r->ee.vpu.vu.unit_0.bus.map(0x0000, &r->ee.vpu.vu.unit_0.memory_mem);
        r->ee.vpu.vu.unit_0.bus.map(0x1000, &r->ee.vpu.vu.unit_0.memory_mem);
        r->ee.vpu.vu.unit_0.bus.map(0x2000, &r->ee.vpu.vu.unit_0.memory_mem);
        r->ee.vpu.vu.unit_0.bus.map(0x3000, &r->ee.vpu.vu.unit_0.memory_mem);

        // VU1.vf Registers, see VU Users Manual page 222.
        for (auto i = 0; i < Constants::EE::VPU::VU::NUMBER_VF_REGISTERS; i++)
            r->ee.vpu.vu.unit_0.bus.map(0x4000 + i * NUMBER_BYTES_IN_QWORD, &r->ee.vpu.vu.unit_1.vf[i]);

        // VU1.vi Registers. Aligned on 128-bit boundaries, accessed by 32-bit r/w, but upper 16-bits discarded!
        // NOT mapped as the true register size of 16-bit. See EE Users Manual page 84.
        for (auto i = 0; i < Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
            r->ee.vpu.vu.unit_0.bus.map(0x4200 + i * NUMBER_BYTES_IN_QWORD, &r->ee.vpu.vu.unit_1.vi_32[i]);

        // Misc Registers.
        r->ee.vpu.vu.unit_0.bus.map(0x4300, &r->ee.vpu.vu.unit_1.status);
        r->ee.vpu.vu.unit_0.bus.map(0x4310, &r->ee.vpu.vu.unit_1.mac);
        r->ee.vpu.vu.unit_0.bus.map(0x4320, &r->ee.vpu.vu.unit_1.clipping);
        r->ee.vpu.vu.unit_0.bus.map(0x4340, &r->ee.vpu.vu.unit_1.r);
        r->ee.vpu.vu.unit_0.bus.map(0x4350, &r->ee.vpu.vu.unit_1.i);
        r->ee.vpu.vu.unit_0.bus.map(0x4360, &r->ee.vpu.vu.unit_1.q);
        r->ee.vpu.vu.unit_0.bus.map(0x4370, &r->ee.vpu.vu.unit_1.p);
        r->ee.vpu.vu.unit_0.bus.map(0x43A0, &r->ee.vpu.vu.unit_1.pc); // TPC.

        r->ee.vpu.vu.unit_0.bus.optimise();
    }

    // Init VU1 memory.
    r->ee.vpu.vu.unit_1.bus.map(0x0000, &r->ee.vpu.vu.unit_1.memory_mem);
    r->ee.vpu.vu.unit_1.bus.optimise();

    // Init VU0 COP0.
    r->ee.vpu.vu.unit_0.cop0 = &r->ee.core.cop0;

    // Init MAC registers.
    r->ee.vpu.vu.unit_0.mac.status = &r->ee.vpu.vu.unit_0.status;
    r->ee.vpu.vu.unit_1.mac.status = &r->ee.vpu.vu.unit_1.status;
}

void initialise_iop_dmac(RResources* r)
{
    // Init SIF sbus references.
    r->iop.dmac.channel_sif0.chcr.sbus_f240 = &r->sbus_f240;
    r->iop.dmac.channel_sif1.chcr.sbus_f240 = &r->sbus_f240;
    r->iop.dmac.channel_sif2.chcr.sbus_f240 = &r->sbus_f240;

    // Init channel abstrations.
    r->iop.dmac.channels[0].channel_id = &r->iop.dmac.channel_tomdec.channel_id;
    r->iop.dmac.channels[0].madr = &r->iop.dmac.channel_tomdec.madr;
    r->iop.dmac.channels[0].bcr = &r->iop.dmac.channel_tomdec.bcr;
    r->iop.dmac.channels[0].chcr = &r->iop.dmac.channel_tomdec.chcr;
    r->iop.dmac.channels[1].channel_id = &r->iop.dmac.channel_frommdec.channel_id;
    r->iop.dmac.channels[1].madr = &r->iop.dmac.channel_frommdec.madr;
    r->iop.dmac.channels[1].bcr = &r->iop.dmac.channel_frommdec.bcr;
    r->iop.dmac.channels[1].chcr = &r->iop.dmac.channel_frommdec.chcr;
    r->iop.dmac.channels[2].channel_id = &r->iop.dmac.channel_sif2.channel_id;
    r->iop.dmac.channels[2].madr = &r->iop.dmac.channel_sif2.madr;
    r->iop.dmac.channels[2].bcr = &r->iop.dmac.channel_sif2.bcr;
    r->iop.dmac.channels[2].chcr = &r->iop.dmac.channel_sif2.chcr;
    r->iop.dmac.channels[3].channel_id = &r->iop.dmac.channel_cdvd.channel_id;
    r->iop.dmac.channels[3].madr = &r->iop.dmac.channel_cdvd.madr;
    r->iop.dmac.channels[3].bcr = &r->iop.dmac.channel_cdvd.bcr;
    r->iop.dmac.channels[3].chcr = &r->iop.dmac.channel_cdvd.chcr;
    r->iop.dmac.channels[4].channel_id = &r->iop.dmac.channel_spu2c0.channel_id;
    r->iop.dmac.channels[4].madr = &r->iop.dmac.channel_spu2c0.madr;
    r->iop.dmac.channels[4].bcr = &r->iop.dmac.channel_spu2c0.bcr;
    r->iop.dmac.channels[4].chcr = &r->iop.dmac.channel_spu2c0.chcr;
    r->iop.dmac.channels[4].tadr = &r->iop.dmac.channel_spu2c0.tadr;
    r->iop.dmac.channels[5].channel_id = &r->iop.dmac.channel_pio.channel_id;
    r->iop.dmac.channels[5].madr = &r->iop.dmac.channel_pio.madr;
    r->iop.dmac.channels[5].bcr = &r->iop.dmac.channel_pio.bcr;
    r->iop.dmac.channels[5].chcr = &r->iop.dmac.channel_pio.chcr;
    r->iop.dmac.channels[6].channel_id = &r->iop.dmac.channel_otclear.channel_id;
    r->iop.dmac.channels[6].madr = &r->iop.dmac.channel_otclear.madr;
    r->iop.dmac.channels[6].bcr = &r->iop.dmac.channel_otclear.bcr;
    r->iop.dmac.channels[6].chcr = &r->iop.dmac.channel_otclear.chcr;
    r->iop.dmac.channels[7].channel_id = &r->iop.dmac.channel_spu2c1.channel_id;
    r->iop.dmac.channels[7].madr = &r->iop.dmac.channel_spu2c1.madr;
    r->iop.dmac.channels[7].bcr = &r->iop.dmac.channel_spu2c1.bcr;
    r->iop.dmac.channels[7].chcr = &r->iop.dmac.channel_spu2c1.chcr;
    r->iop.dmac.channels[8].channel_id = &r->iop.dmac.channel_dev9.channel_id;
    r->iop.dmac.channels[8].madr = &r->iop.dmac.channel_dev9.madr;
    r->iop.dmac.channels[8].bcr = &r->iop.dmac.channel_dev9.bcr;
    r->iop.dmac.channels[8].chcr = &r->iop.dmac.channel_dev9.chcr;
    r->iop.dmac.channels[9].channel_id = &r->iop.dmac.channel_sif0.channel_id;
    r->iop.dmac.channels[9].madr = &r->iop.dmac.channel_sif0.madr;
    r->iop.dmac.channels[9].bcr = &r->iop.dmac.channel_sif0.bcr;
    r->iop.dmac.channels[9].chcr = &r->iop.dmac.channel_sif0.chcr;
    r->iop.dmac.channels[9].tadr = &r->iop.dmac.channel_sif0.tadr;
    r->iop.dmac.channels[10].channel_id = &r->iop.dmac.channel_sif1.channel_id;
    r->iop.dmac.channels[10].madr = &r->iop.dmac.channel_sif1.madr;
    r->iop.dmac.channels[10].bcr = &r->iop.dmac.channel_sif1.bcr;
    r->iop.dmac.channels[10].chcr = &r->iop.dmac.channel_sif1.chcr;
    r->iop.dmac.channels[11].channel_id = &r->iop.dmac.channel_tosio2.channel_id;
    r->iop.dmac.channels[11].madr = &r->iop.dmac.channel_tosio2.madr;
    r->iop.dmac.channels[11].bcr = &r->iop.dmac.channel_tosio2.bcr;
    r->iop.dmac.channels[11].chcr = &r->iop.dmac.channel_tosio2.chcr;
    r->iop.dmac.channels[12].channel_id = &r->iop.dmac.channel_fromsio2.channel_id;
    r->iop.dmac.channels[12].madr = &r->iop.dmac.channel_fromsio2.madr;
    r->iop.dmac.channels[12].bcr = &r->iop.dmac.channel_fromsio2.bcr;
    r->iop.dmac.channels[12].chcr = &r->iop.dmac.channel_fromsio2.chcr;

    // Init DMA FIFO queues.
    r->iop.dmac.channels[0].dma_fifo_queue = &r->fifo_frommdec;
    r->iop.dmac.channels[1].dma_fifo_queue = &r->fifo_tomdec;
    r->iop.dmac.channels[2].dma_fifo_queue = &r->fifo_sif2;
    r->iop.dmac.channels[3].dma_fifo_queue = &r->fifo_cdvd;
    r->iop.dmac.channels[4].dma_fifo_queue = &r->fifo_spu2c0;
    r->iop.dmac.channels[5].dma_fifo_queue = &r->fifo_pio;
    r->iop.dmac.channels[6].dma_fifo_queue = &r->fifo_otclear;
    r->iop.dmac.channels[7].dma_fifo_queue = &r->fifo_spu2c1;
    r->iop.dmac.channels[8].dma_fifo_queue = &r->fifo_dev9;
    r->iop.dmac.channels[9].dma_fifo_queue = &r->fifo_sif0;
    r->iop.dmac.channels[10].dma_fifo_queue = &r->fifo_sif1;
    r->iop.dmac.channels[11].dma_fifo_queue = &r->fifo_fromsio2;
    r->iop.dmac.channels[12].dma_fifo_queue = &r->fifo_tosio2;

    // Init PCR / ICR.
    r->iop.dmac.icr1.icr0 = &r->iop.dmac.icr0;
    r->iop.dmac.pcrw.pcr0 = &r->iop.dmac.pcr0;
    r->iop.dmac.pcrw.pcr1 = &r->iop.dmac.pcr1;
    r->iop.dmac.icrw.icr0 = &r->iop.dmac.icr0;
    r->iop.dmac.icrw.icr1 = &r->iop.dmac.icr1;
}

void initialise_ee(RResources* r)
{
    // Initialise physical memory map of EE.
    {
        // EE Memory.
        {
            // Main Memory.
            r->ee.bus.map(0x00000000, &r->ee.main_memory);

            // Scratchpad Memory.
            r->ee.bus.map(0x70000000, &r->ee.core.scratchpad_memory);

            // Various ROMs.
            r->ee.bus.map(0x1FC00000, &r->boot_rom);
            r->ee.bus.map(0x1E000000, &r->rom1);
            r->ee.bus.map(0x1E040000, &r->erom);
            r->ee.bus.map(0x1E400000, &r->rom2);

            // Unknown memory.
            r->ee.bus.map(0x1A000000, &r->ee.unknown_1a000000);
        }

        // EE Registers.
        {
            // MISC EE registers.
            r->ee.bus.map(0x1000F100, &r->ee.memory_sio);
            r->ee.bus.map(0x1000f400, &r->ee.register_f400);
            r->ee.bus.map(0x1000f410, &r->ee.memory_f410);
            r->ee.bus.map(0x1000f420, &r->ee.register_f420);
            r->ee.bus.map(0x1000F430, &r->ee.memory_mch);
            r->ee.bus.map(0x1000f450, &r->ee.memory_f450);

            // Timers Registers.
            r->ee.bus.map(0x10000000, &r->ee.timers.unit_0.count);
            r->ee.bus.map(0x10000010, &r->ee.timers.unit_0.mode);
            r->ee.bus.map(0x10000020, &r->ee.timers.unit_0.compare);
            r->ee.bus.map(0x10000030, &r->ee.timers.unit_0.hold);
            r->ee.bus.map(0x10000800, &r->ee.timers.unit_1.count);
            r->ee.bus.map(0x10000810, &r->ee.timers.unit_1.mode);
            r->ee.bus.map(0x10000820, &r->ee.timers.unit_1.compare);
            r->ee.bus.map(0x10000830, &r->ee.timers.unit_1.hold);
            r->ee.bus.map(0x10001000, &r->ee.timers.unit_2.count);
            r->ee.bus.map(0x10001010, &r->ee.timers.unit_2.mode);
            r->ee.bus.map(0x10001020, &r->ee.timers.unit_2.compare);
            r->ee.bus.map(0x10001800, &r->ee.timers.unit_3.count);
            r->ee.bus.map(0x10001810, &r->ee.timers.unit_3.mode);
            r->ee.bus.map(0x10001820, &r->ee.timers.unit_3.compare);

            // IPU Registers.
            r->ee.bus.map(0x10002000, &r->ee.ipu.cmd);
            r->ee.bus.map(0x10002010, &r->ee.ipu.ctrl);
            r->ee.bus.map(0x10002020, &r->ee.ipu.bp);
            r->ee.bus.map(0x10002030, &r->ee.ipu.top);

            // GIF Registers.
            r->ee.bus.map(0x10003000, &r->ee.gif.ctrl);
            r->ee.bus.map(0x10003010, &r->ee.gif.mode);
            r->ee.bus.map(0x10003020, &r->ee.gif.stat);
            r->ee.bus.map(0x10003040, &r->ee.gif.tag0);
            r->ee.bus.map(0x10003050, &r->ee.gif.tag1);
            r->ee.bus.map(0x10003060, &r->ee.gif.tag2);
            r->ee.bus.map(0x10003070, &r->ee.gif.tag3);
            r->ee.bus.map(0x10003080, &r->ee.gif.cnt);
            r->ee.bus.map(0x10003090, &r->ee.gif.p3cnt);
            r->ee.bus.map(0x100030a0, &r->ee.gif.p3tag);

            // VIF0 Registers.
            r->ee.bus.map(0x10003800, &r->ee.vpu.vif.unit_0.stat);
            r->ee.bus.map(0x10003810, &r->ee.vpu.vif.unit_0.fbrst);
            r->ee.bus.map(0x10003820, &r->ee.vpu.vif.unit_0.err);
            r->ee.bus.map(0x10003830, &r->ee.vpu.vif.unit_0.mark);
            r->ee.bus.map(0x10003840, &r->ee.vpu.vif.unit_0.cycle);
            r->ee.bus.map(0x10003850, &r->ee.vpu.vif.unit_0.mode);
            r->ee.bus.map(0x10003860, &r->ee.vpu.vif.unit_0.num);
            r->ee.bus.map(0x10003870, &r->ee.vpu.vif.unit_0.mask);
            r->ee.bus.map(0x10003880, &r->ee.vpu.vif.unit_0.code);
            r->ee.bus.map(0x10003890, &r->ee.vpu.vif.unit_0.itops);
            r->ee.bus.map(0x100038d0, &r->ee.vpu.vif.unit_0.itop);
            r->ee.bus.map(0x10003900, &r->ee.vpu.vif.unit_0.r0);
            r->ee.bus.map(0x10003910, &r->ee.vpu.vif.unit_0.r1);
            r->ee.bus.map(0x10003920, &r->ee.vpu.vif.unit_0.r2);
            r->ee.bus.map(0x10003930, &r->ee.vpu.vif.unit_0.r3);
            r->ee.bus.map(0x10003940, &r->ee.vpu.vif.unit_0.c0);
            r->ee.bus.map(0x10003950, &r->ee.vpu.vif.unit_0.c1);
            r->ee.bus.map(0x10003960, &r->ee.vpu.vif.unit_0.c2);
            r->ee.bus.map(0x10003970, &r->ee.vpu.vif.unit_0.c3);

            // VIF1 Registers.
            r->ee.bus.map(0x10003c00, &r->ee.vpu.vif.unit_1.stat);
            r->ee.bus.map(0x10003c10, &r->ee.vpu.vif.unit_1.fbrst);
            r->ee.bus.map(0x10003c20, &r->ee.vpu.vif.unit_1.err);
            r->ee.bus.map(0x10003c30, &r->ee.vpu.vif.unit_1.mark);
            r->ee.bus.map(0x10003c40, &r->ee.vpu.vif.unit_1.cycle);
            r->ee.bus.map(0x10003c50, &r->ee.vpu.vif.unit_1.mode);
            r->ee.bus.map(0x10003c60, &r->ee.vpu.vif.unit_1.num);
            r->ee.bus.map(0x10003c70, &r->ee.vpu.vif.unit_1.mask);
            r->ee.bus.map(0x10003c80, &r->ee.vpu.vif.unit_1.code);
            r->ee.bus.map(0x10003c90, &r->ee.vpu.vif.unit_1.itops);
            r->ee.bus.map(0x10003ca0, &r->ee.vpu.vif.unit_1.base);
            r->ee.bus.map(0x10003cb0, &r->ee.vpu.vif.unit_1.ofst);
            r->ee.bus.map(0x10003cc0, &r->ee.vpu.vif.unit_1.tops);
            r->ee.bus.map(0x10003cd0, &r->ee.vpu.vif.unit_1.itop);
            r->ee.bus.map(0x10003ce0, &r->ee.vpu.vif.unit_1.top);
            r->ee.bus.map(0x10003d00, &r->ee.vpu.vif.unit_1.r0);
            r->ee.bus.map(0x10003d10, &r->ee.vpu.vif.unit_1.r1);
            r->ee.bus.map(0x10003d20, &r->ee.vpu.vif.unit_1.r2);
            r->ee.bus.map(0x10003d30, &r->ee.vpu.vif.unit_1.r3);
            r->ee.bus.map(0x10003d40, &r->ee.vpu.vif.unit_1.c0);
            r->ee.bus.map(0x10003d50, &r->ee.vpu.vif.unit_1.c1);
            r->ee.bus.map(0x10003d60, &r->ee.vpu.vif.unit_1.c2);
            r->ee.bus.map(0x10003d70, &r->ee.vpu.vif.unit_1.c3);

            // FIFO Registers.
            r->ee.bus.map(0x10004000, &r->fifo_vif0);
            r->ee.bus.map(0x10005000, &r->fifo_vif1);
            r->ee.bus.map(0x10006000, &r->fifo_gif_path3);
            r->ee.bus.map(0x10007000, &r->fifo_fromipu);
            r->ee.bus.map(0x10007010, &r->fifo_toipu);

            // DMAC registers.
            r->ee.bus.map(0x10008000, &r->ee.dmac.channel_vif0.chcr);
            r->ee.bus.map(0x10008010, &r->ee.dmac.channel_vif0.madr);
            r->ee.bus.map(0x10008020, &r->ee.dmac.channel_vif0.qwc);
            r->ee.bus.map(0x10008030, &r->ee.dmac.channel_vif0.tadr);
            r->ee.bus.map(0x10008040, &r->ee.dmac.channel_vif0.asr[0]);
            r->ee.bus.map(0x10008050, &r->ee.dmac.channel_vif0.asr[1]);
            r->ee.bus.map(0x10008060, &r->ee.dmac.memory_8060);
            r->ee.bus.map(0x10009000, &r->ee.dmac.channel_vif1.chcr);
            r->ee.bus.map(0x10009010, &r->ee.dmac.channel_vif1.madr);
            r->ee.bus.map(0x10009020, &r->ee.dmac.channel_vif1.qwc);
            r->ee.bus.map(0x10009030, &r->ee.dmac.channel_vif1.tadr);
            r->ee.bus.map(0x10009040, &r->ee.dmac.channel_vif1.asr[0]);
            r->ee.bus.map(0x10009050, &r->ee.dmac.channel_vif1.asr[1]);
            r->ee.bus.map(0x10009060, &r->ee.dmac.memory_9060);
            r->ee.bus.map(0x1000a000, &r->ee.dmac.channel_gif.chcr);
            r->ee.bus.map(0x1000a010, &r->ee.dmac.channel_gif.madr);
            r->ee.bus.map(0x1000a020, &r->ee.dmac.channel_gif.qwc);
            r->ee.bus.map(0x1000a030, &r->ee.dmac.channel_gif.tadr);
            r->ee.bus.map(0x1000a040, &r->ee.dmac.channel_gif.asr[0]);
            r->ee.bus.map(0x1000a050, &r->ee.dmac.channel_gif.asr[1]);
            r->ee.bus.map(0x1000a060, &r->ee.dmac.memory_a060);
            r->ee.bus.map(0x1000b000, &r->ee.dmac.channel_fromipu.chcr);
            r->ee.bus.map(0x1000b010, &r->ee.dmac.channel_fromipu.madr);
            r->ee.bus.map(0x1000b020, &r->ee.dmac.channel_fromipu.qwc);
            r->ee.bus.map(0x1000b030, &r->ee.dmac.memory_b030);
            r->ee.bus.map(0x1000b400, &r->ee.dmac.channel_toipu.chcr);
            r->ee.bus.map(0x1000b410, &r->ee.dmac.channel_toipu.madr);
            r->ee.bus.map(0x1000b420, &r->ee.dmac.channel_toipu.qwc);
            r->ee.bus.map(0x1000b430, &r->ee.dmac.channel_toipu.tadr);
            r->ee.bus.map(0x1000b440, &r->ee.dmac.memory_b440);
            r->ee.bus.map(0x1000c000, &r->ee.dmac.channel_sif0.chcr);
            r->ee.bus.map(0x1000c010, &r->ee.dmac.channel_sif0.madr);
            r->ee.bus.map(0x1000c020, &r->ee.dmac.channel_sif0.qwc);
            r->ee.bus.map(0x1000c030, &r->ee.dmac.memory_c030);
            r->ee.bus.map(0x1000c400, &r->ee.dmac.channel_sif1.chcr);
            r->ee.bus.map(0x1000c410, &r->ee.dmac.channel_sif1.madr);
            r->ee.bus.map(0x1000c420, &r->ee.dmac.channel_sif1.qwc);
            r->ee.bus.map(0x1000c430, &r->ee.dmac.channel_sif1.tadr);
            r->ee.bus.map(0x1000c440, &r->ee.dmac.memory_c440);
            r->ee.bus.map(0x1000c800, &r->ee.dmac.channel_sif2.chcr);
            r->ee.bus.map(0x1000c810, &r->ee.dmac.channel_sif2.madr);
            r->ee.bus.map(0x1000c820, &r->ee.dmac.channel_sif2.qwc);
            r->ee.bus.map(0x1000c830, &r->ee.dmac.memory_c830);
            r->ee.bus.map(0x1000d000, &r->ee.dmac.channel_fromspr.chcr);
            r->ee.bus.map(0x1000d010, &r->ee.dmac.channel_fromspr.madr);
            r->ee.bus.map(0x1000d020, &r->ee.dmac.channel_fromspr.qwc);
            r->ee.bus.map(0x1000d030, &r->ee.dmac.memory_d030);
            r->ee.bus.map(0x1000d080, &r->ee.dmac.channel_fromspr.sadr);
            r->ee.bus.map(0x1000d090, &r->ee.dmac.memory_d090);
            r->ee.bus.map(0x1000d400, &r->ee.dmac.channel_tospr.chcr);
            r->ee.bus.map(0x1000d410, &r->ee.dmac.channel_tospr.madr);
            r->ee.bus.map(0x1000d420, &r->ee.dmac.channel_tospr.qwc);
            r->ee.bus.map(0x1000d430, &r->ee.dmac.channel_tospr.tadr);
            r->ee.bus.map(0x1000d440, &r->ee.dmac.memory_d440);
            r->ee.bus.map(0x1000d480, &r->ee.dmac.channel_tospr.sadr);
            r->ee.bus.map(0x1000d490, &r->ee.dmac.memory_d490);
            r->ee.bus.map(0x1000e000, &r->ee.dmac.ctrl);
            r->ee.bus.map(0x1000e010, &r->ee.dmac.stat);
            r->ee.bus.map(0x1000e020, &r->ee.dmac.pcr);
            r->ee.bus.map(0x1000e030, &r->ee.dmac.sqwc);
            r->ee.bus.map(0x1000e040, &r->ee.dmac.rbsr);
            r->ee.bus.map(0x1000e050, &r->ee.dmac.rbor);
            r->ee.bus.map(0x1000e060, &r->ee.dmac.stadr);

            // INTC registers.
            r->ee.bus.map(0x1000f000, &r->ee.intc.stat);
            r->ee.bus.map(0x1000f010, &r->ee.intc.mask);

            // DMAC registers (extended).
            r->ee.bus.map(0x1000f500, &r->ee.dmac.memory_f500);
            r->ee.bus.map(0x1000f520, &r->ee.dmac.enable_r);
            r->ee.bus.map(0x1000f590, &r->ee.dmac.enable_w);
        }

        // VU0/1 Memory.
        {
            r->ee.bus.map(0x11000000, &r->ee.vpu.vu.unit_0.memory_micro);
            r->ee.bus.map(0x11004000, &r->ee.vpu.vu.unit_0.memory_mem);
            r->ee.bus.map(0x11008000, &r->ee.vpu.vu.unit_1.memory_micro);
            r->ee.bus.map(0x1100c000, &r->ee.vpu.vu.unit_1.memory_mem);
        }

        // GS Privileged Registers.
        {
            r->ee.bus.map(0x12000000, &r->gs.pmode);
            r->ee.bus.map(0x12000010, &r->gs.smode1);
            r->ee.bus.map(0x12000020, &r->gs.smode2);
            r->ee.bus.map(0x12000030, &r->gs.srfsh);
            r->ee.bus.map(0x12000040, &r->gs.synch1);
            r->ee.bus.map(0x12000050, &r->gs.synch2);
            r->ee.bus.map(0x12000060, &r->gs.syncv);
            r->ee.bus.map(0x12000070, &r->gs.dispfb1);
            r->ee.bus.map(0x12000080, &r->gs.display1);
            r->ee.bus.map(0x12000090, &r->gs.dispfb2);
            r->ee.bus.map(0x120000a0, &r->gs.display2);
            r->ee.bus.map(0x120000b0, &r->gs.extbuf);
            r->ee.bus.map(0x120000c0, &r->gs.extdata);
            r->ee.bus.map(0x120000d0, &r->gs.extwrite);
            r->ee.bus.map(0x120000e0, &r->gs.bgcolor);

            r->ee.bus.map(0x12001000, &r->gs.csr);
            r->ee.bus.map(0x12001010, &r->gs.imr);
            r->ee.bus.map(0x12001040, &r->gs.busdir);
            r->ee.bus.map(0x12001080, &r->gs.siglblid);
        }

        // IOP Mirrors.
        {
            // Misc IOP Registers.
            r->ee.bus.map(0x1F80141C, &r->iop.hw_ssbus_dev9_delay3);
            r->ee.bus.map(0x1F801470, &r->iop.register_1470);
            r->ee.bus.map(0x1F803800, &r->iop.register_3800);

            // Main Memory.
            r->ee.bus.map(0x1C000000, &r->iop.main_memory);
        }

        // SIF Registers.
        {
            r->ee.bus.map(0x1000F200, &r->sbus_mscom);
            r->ee.bus.map(0x1000F210, &r->sbus_smcom);
            r->ee.bus.map(0x1000F220, &r->sbus_msflg);
            r->ee.bus.map(0x1000F230, &r->sbus_smflg);
            r->ee.bus.map(0x1000F240, &r->sbus_f240);
            r->ee.bus.map(0x1000F250, &r->sbus_f250);
            r->ee.bus.map(0x1000F260, &r->sbus_f260);
            r->ee.bus.map(0x1000F300, &r->sbus_f300);
            r->ee.bus.map(0x1000F380, &r->sbus_f380);
        }

        // CDVD Registers.
        {
            r->ee.bus.map(0x1F402004, &r->cdvd.n_command);
            r->ee.bus.map(0x1F402005, &r->cdvd.n_rdy_din);
            r->ee.bus.map(0x1F402006, &r->cdvd.n_data_out);
            r->ee.bus.map(0x1F402007, &r->cdvd.break_);
            r->ee.bus.map(0x1F402008, &r->cdvd.intr_stat);
            r->ee.bus.map(0x1F40200A, &r->cdvd.status);
            r->ee.bus.map(0x1F40200B, &r->cdvd.tray_state);
            r->ee.bus.map(0x1F40200C, &r->cdvd.crt_minute);
            r->ee.bus.map(0x1F40200D, &r->cdvd.crt_second);
            r->ee.bus.map(0x1F40200E, &r->cdvd.crt_frame);
            r->ee.bus.map(0x1F40200F, &r->cdvd.type);
            r->ee.bus.map(0x1F402013, &r->cdvd.register_2013);
            r->ee.bus.map(0x1F402015, &r->cdvd.rsv);
            r->ee.bus.map(0x1F402016, &r->cdvd.s_command);
            r->ee.bus.map(0x1F402017, &r->cdvd.s_rdy_din);
            r->ee.bus.map(0x1F402018, &r->cdvd.s_data_out);
            r->ee.bus.map(0x1F402020, &r->cdvd.key_20);
            r->ee.bus.map(0x1F402021, &r->cdvd.key_21);
            r->ee.bus.map(0x1F402022, &r->cdvd.key_22);
            r->ee.bus.map(0x1F402023, &r->cdvd.key_23);
            r->ee.bus.map(0x1F402024, &r->cdvd.key_24);
            r->ee.bus.map(0x1F402028, &r->cdvd.key_28);
            r->ee.bus.map(0x1F402029, &r->cdvd.key_29);
            r->ee.bus.map(0x1F40202A, &r->cdvd.key_2a);
            r->ee.bus.map(0x1F40202B, &r->cdvd.key_2b);
            r->ee.bus.map(0x1F40202C, &r->cdvd.key_2c);
            r->ee.bus.map(0x1F402030, &r->cdvd.key_30);
            r->ee.bus.map(0x1F402031, &r->cdvd.key_31);
            r->ee.bus.map(0x1F402032, &r->cdvd.key_32);
            r->ee.bus.map(0x1F402033, &r->cdvd.key_33);
            r->ee.bus.map(0x1F402034, &r->cdvd.key_34);
            r->ee.bus.map(0x1F402038, &r->cdvd.key_38);
            r->ee.bus.map(0x1F402039, &r->cdvd.key_xor);
            r->ee.bus.map(0x1F40203A, &r->cdvd.dec_set);
        }

        r->ee.bus.optimise();
    }
}

void initialise_iop(RResources* r)
{
    // Initialise physical memory map of IOP.
    {
        // IOP Memory.
        {
            // Main Memory.
            r->iop.bus.map(0x00000000, &r->iop.main_memory);

            // Various ROMs.
            r->iop.bus.map(0x1FC00000, &r->boot_rom);
            r->iop.bus.map(0x1E000000, &r->rom1);

            // Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initialisation. TODO: related to cache control (this is probably very wrong), investigate.
            r->iop.bus.map(0xFFC00000, &r->boot_rom);

            // Scratchpad Memory.
            r->iop.bus.map(0x1F800000, &r->iop.core.scratchpad_memory);
        }

        // IOP Registers.
        {
            // Misc IOP Registers.
            r->iop.bus.map(0x1F801000, &r->iop.hw_ssbus_spd_addr);
            r->iop.bus.map(0x1F801004, &r->iop.hw_ssbus_pio_addr);
            r->iop.bus.map(0x1F801008, &r->iop.hw_ssbus_spd_delay);
            r->iop.bus.map(0x1F80100C, &r->iop.hw_ssbus_dev1_delay);
            r->iop.bus.map(0x1F801010, &r->iop.hw_ssbus_rom_delay);
            r->iop.bus.map(0x1F801014, &r->iop.hw_ssbus_spu_delay);
            r->iop.bus.map(0x1F801018, &r->iop.hw_ssbus_dev5_delay);
            r->iop.bus.map(0x1F80101C, &r->iop.hw_ssbus_pio_delay);
            r->iop.bus.map(0x1F801020, &r->iop.hw_ssbus_com_delay);
            r->iop.bus.map(0x1F801060, &r->iop.hw_ram_size);
            r->iop.bus.map(0x1F801400, &r->iop.hw_ssbus_dev1_addr);
            r->iop.bus.map(0x1F801404, &r->iop.hw_ssbus_spu_addr);
            r->iop.bus.map(0x1F801408, &r->iop.hw_ssbus_dev5_addr);
            r->iop.bus.map(0x1F80140C, &r->iop.hw_ssbus_spu1_addr);
            r->iop.bus.map(0x1F801410, &r->iop.hw_ssbus_dev9_addr3);
            r->iop.bus.map(0x1F801414, &r->iop.hw_ssbus_spu1_delay);
            r->iop.bus.map(0x1F801418, &r->iop.hw_ssbus_dev9_delay2);
            r->iop.bus.map(0x1F80141C, &r->iop.hw_ssbus_dev9_delay3);
            r->iop.bus.map(0x1F801420, &r->iop.hw_ssbus_dev9_delay1);
            r->iop.bus.map(0x1F801450, &r->iop.hw_icfg);
            r->iop.bus.map(0x1F801560, &r->iop.register_1560);
            r->iop.bus.map(0x1F801564, &r->iop.register_1564);
            r->iop.bus.map(0x1F801568, &r->iop.register_1568);
            r->iop.bus.map(0x1F8015F0, &r->iop.register_15f0);
            r->iop.bus.map(0x1F802070, &r->iop.register_2070);

            // DMAC Registers.
            r->iop.bus.map(0x1F801080, &r->iop.dmac.channel_tomdec.madr);
            r->iop.bus.map(0x1F801084, &r->iop.dmac.channel_tomdec.bcr);
            r->iop.bus.map(0x1F801088, &r->iop.dmac.channel_tomdec.chcr);
            r->iop.bus.map(0x1F801090, &r->iop.dmac.channel_frommdec.madr);
            r->iop.bus.map(0x1F801094, &r->iop.dmac.channel_frommdec.bcr);
            r->iop.bus.map(0x1F801098, &r->iop.dmac.channel_frommdec.chcr);
            r->iop.bus.map(0x1F8010A0, &r->iop.dmac.channel_sif2.madr);
            r->iop.bus.map(0x1F8010A4, &r->iop.dmac.channel_sif2.bcr);
            r->iop.bus.map(0x1F8010A8, &r->iop.dmac.channel_sif2.chcr);
            r->iop.bus.map(0x1F8010B0, &r->iop.dmac.channel_cdvd.madr);
            r->iop.bus.map(0x1F8010B4, &r->iop.dmac.channel_cdvd.bcr);
            r->iop.bus.map(0x1F8010B8, &r->iop.dmac.channel_cdvd.chcr);
            r->iop.bus.map(0x1F8010C0, &r->iop.dmac.channel_spu2c0.madr);
            r->iop.bus.map(0x1F8010C4, &r->iop.dmac.channel_spu2c0.bcr);
            r->iop.bus.map(0x1F8010C8, &r->iop.dmac.channel_spu2c0.chcr);
            r->iop.bus.map(0x1F8010CC, &r->iop.dmac.channel_spu2c0.tadr);
            r->iop.bus.map(0x1F8010D0, &r->iop.dmac.channel_pio.madr);
            r->iop.bus.map(0x1F8010D4, &r->iop.dmac.channel_pio.bcr);
            r->iop.bus.map(0x1F8010D8, &r->iop.dmac.channel_pio.chcr);
            r->iop.bus.map(0x1F8010E0, &r->iop.dmac.channel_otclear.madr);
            r->iop.bus.map(0x1F8010E4, &r->iop.dmac.channel_otclear.bcr);
            r->iop.bus.map(0x1F8010E8, &r->iop.dmac.channel_otclear.chcr);
            r->iop.bus.map(0x1F801500, &r->iop.dmac.channel_spu2c1.madr);
            r->iop.bus.map(0x1F801504, &r->iop.dmac.channel_spu2c1.bcr);
            r->iop.bus.map(0x1F801508, &r->iop.dmac.channel_spu2c1.chcr);
            r->iop.bus.map(0x1F801510, &r->iop.dmac.channel_dev9.madr);
            r->iop.bus.map(0x1F801514, &r->iop.dmac.channel_dev9.bcr);
            r->iop.bus.map(0x1F801518, &r->iop.dmac.channel_dev9.chcr);
            r->iop.bus.map(0x1F801520, &r->iop.dmac.channel_sif0.madr);
            r->iop.bus.map(0x1F801524, &r->iop.dmac.channel_sif0.bcr);
            r->iop.bus.map(0x1F801528, &r->iop.dmac.channel_sif0.chcr);
            r->iop.bus.map(0x1F80152C, &r->iop.dmac.channel_sif0.tadr);
            r->iop.bus.map(0x1F801530, &r->iop.dmac.channel_sif1.madr);
            r->iop.bus.map(0x1F801534, &r->iop.dmac.channel_sif1.bcr);
            r->iop.bus.map(0x1F801538, &r->iop.dmac.channel_sif1.chcr);
            r->iop.bus.map(0x1F801540, &r->iop.dmac.channel_tosio2.madr);
            r->iop.bus.map(0x1F801544, &r->iop.dmac.channel_tosio2.bcr);
            r->iop.bus.map(0x1F801548, &r->iop.dmac.channel_tosio2.chcr);
            r->iop.bus.map(0x1F801550, &r->iop.dmac.channel_fromsio2.madr);
            r->iop.bus.map(0x1F801554, &r->iop.dmac.channel_fromsio2.bcr);
            r->iop.bus.map(0x1F801558, &r->iop.dmac.channel_fromsio2.chcr);
            r->iop.bus.map(0x1F8010F0, &r->iop.dmac.pcr0);
            r->iop.bus.map(0x1F8010F4, &r->iop.dmac.icr0);
            r->iop.bus.map(0x1F801570, &r->iop.dmac.pcr1);
            r->iop.bus.map(0x1F801574, &r->iop.dmac.icr1);
            r->iop.bus.map(0x1F801578, &r->iop.dmac.gctrl);

            // INTC Registers.
            r->iop.bus.map(0x1F801070, &r->iop.intc.stat);
            r->iop.bus.map(0x1F801074, &r->iop.intc.mask);
            r->iop.bus.map(0x1F801078, &r->iop.intc.ctrl);

            // CDVD Registers.
            r->iop.bus.map(0x1F402004, &r->cdvd.n_command);
            r->iop.bus.map(0x1F402005, &r->cdvd.n_rdy_din);
            r->iop.bus.map(0x1F402006, &r->cdvd.n_data_out);
            r->iop.bus.map(0x1F402007, &r->cdvd.break_);
            r->iop.bus.map(0x1F402008, &r->cdvd.intr_stat);
            r->iop.bus.map(0x1F40200A, &r->cdvd.status);
            r->iop.bus.map(0x1F40200B, &r->cdvd.tray_state);
            r->iop.bus.map(0x1F40200C, &r->cdvd.crt_minute);
            r->iop.bus.map(0x1F40200D, &r->cdvd.crt_second);
            r->iop.bus.map(0x1F40200E, &r->cdvd.crt_frame);
            r->iop.bus.map(0x1F40200F, &r->cdvd.type);
            r->iop.bus.map(0x1F402013, &r->cdvd.register_2013);
            r->iop.bus.map(0x1F402015, &r->cdvd.rsv);
            r->iop.bus.map(0x1F402016, &r->cdvd.s_command);
            r->iop.bus.map(0x1F402017, &r->cdvd.s_rdy_din);
            r->iop.bus.map(0x1F402018, &r->cdvd.s_data_out);
            r->iop.bus.map(0x1F402020, &r->cdvd.key_20);
            r->iop.bus.map(0x1F402021, &r->cdvd.key_21);
            r->iop.bus.map(0x1F402022, &r->cdvd.key_22);
            r->iop.bus.map(0x1F402023, &r->cdvd.key_23);
            r->iop.bus.map(0x1F402024, &r->cdvd.key_24);
            r->iop.bus.map(0x1F402028, &r->cdvd.key_28);
            r->iop.bus.map(0x1F402029, &r->cdvd.key_29);
            r->iop.bus.map(0x1F40202A, &r->cdvd.key_2a);
            r->iop.bus.map(0x1F40202B, &r->cdvd.key_2b);
            r->iop.bus.map(0x1F40202C, &r->cdvd.key_2c);
            r->iop.bus.map(0x1F402030, &r->cdvd.key_30);
            r->iop.bus.map(0x1F402031, &r->cdvd.key_31);
            r->iop.bus.map(0x1F402032, &r->cdvd.key_32);
            r->iop.bus.map(0x1F402033, &r->cdvd.key_33);
            r->iop.bus.map(0x1F402034, &r->cdvd.key_34);
            r->iop.bus.map(0x1F402038, &r->cdvd.key_38);
            r->iop.bus.map(0x1F402039, &r->cdvd.key_xor);
            r->iop.bus.map(0x1F40203A, &r->cdvd.dec_set);

            // SPU2 Registers.
            r->iop.bus.map(0x1F900000, &r->spu2.core_0.voice_0.voll);
            r->iop.bus.map(0x1F900002, &r->spu2.core_0.voice_0.volr);
            r->iop.bus.map(0x1F900004, &r->spu2.core_0.voice_0.pitch);
            r->iop.bus.map(0x1F900006, &r->spu2.core_0.voice_0.adsr1);
            r->iop.bus.map(0x1F900008, &r->spu2.core_0.voice_0.adsr2);
            r->iop.bus.map(0x1F90000A, &r->spu2.core_0.voice_0.envx);
            r->iop.bus.map(0x1F90000C, &r->spu2.core_0.voice_0.volxl);
            r->iop.bus.map(0x1F90000E, &r->spu2.core_0.voice_0.volxr);
            r->iop.bus.map(0x1F900010, &r->spu2.core_0.voice_1.voll);
            r->iop.bus.map(0x1F900012, &r->spu2.core_0.voice_1.volr);
            r->iop.bus.map(0x1F900014, &r->spu2.core_0.voice_1.pitch);
            r->iop.bus.map(0x1F900016, &r->spu2.core_0.voice_1.adsr1);
            r->iop.bus.map(0x1F900018, &r->spu2.core_0.voice_1.adsr2);
            r->iop.bus.map(0x1F90001A, &r->spu2.core_0.voice_1.envx);
            r->iop.bus.map(0x1F90001C, &r->spu2.core_0.voice_1.volxl);
            r->iop.bus.map(0x1F90001E, &r->spu2.core_0.voice_1.volxr);
            r->iop.bus.map(0x1F900020, &r->spu2.core_0.voice_2.voll);
            r->iop.bus.map(0x1F900022, &r->spu2.core_0.voice_2.volr);
            r->iop.bus.map(0x1F900024, &r->spu2.core_0.voice_2.pitch);
            r->iop.bus.map(0x1F900026, &r->spu2.core_0.voice_2.adsr1);
            r->iop.bus.map(0x1F900028, &r->spu2.core_0.voice_2.adsr2);
            r->iop.bus.map(0x1F90002A, &r->spu2.core_0.voice_2.envx);
            r->iop.bus.map(0x1F90002C, &r->spu2.core_0.voice_2.volxl);
            r->iop.bus.map(0x1F90002E, &r->spu2.core_0.voice_2.volxr);
            r->iop.bus.map(0x1F900030, &r->spu2.core_0.voice_3.voll);
            r->iop.bus.map(0x1F900032, &r->spu2.core_0.voice_3.volr);
            r->iop.bus.map(0x1F900034, &r->spu2.core_0.voice_3.pitch);
            r->iop.bus.map(0x1F900036, &r->spu2.core_0.voice_3.adsr1);
            r->iop.bus.map(0x1F900038, &r->spu2.core_0.voice_3.adsr2);
            r->iop.bus.map(0x1F90003A, &r->spu2.core_0.voice_3.envx);
            r->iop.bus.map(0x1F90003C, &r->spu2.core_0.voice_3.volxl);
            r->iop.bus.map(0x1F90003E, &r->spu2.core_0.voice_3.volxr);
            r->iop.bus.map(0x1F900040, &r->spu2.core_0.voice_4.voll);
            r->iop.bus.map(0x1F900042, &r->spu2.core_0.voice_4.volr);
            r->iop.bus.map(0x1F900044, &r->spu2.core_0.voice_4.pitch);
            r->iop.bus.map(0x1F900046, &r->spu2.core_0.voice_4.adsr1);
            r->iop.bus.map(0x1F900048, &r->spu2.core_0.voice_4.adsr2);
            r->iop.bus.map(0x1F90004A, &r->spu2.core_0.voice_4.envx);
            r->iop.bus.map(0x1F90004C, &r->spu2.core_0.voice_4.volxl);
            r->iop.bus.map(0x1F90004E, &r->spu2.core_0.voice_4.volxr);
            r->iop.bus.map(0x1F900050, &r->spu2.core_0.voice_5.voll);
            r->iop.bus.map(0x1F900052, &r->spu2.core_0.voice_5.volr);
            r->iop.bus.map(0x1F900054, &r->spu2.core_0.voice_5.pitch);
            r->iop.bus.map(0x1F900056, &r->spu2.core_0.voice_5.adsr1);
            r->iop.bus.map(0x1F900058, &r->spu2.core_0.voice_5.adsr2);
            r->iop.bus.map(0x1F90005A, &r->spu2.core_0.voice_5.envx);
            r->iop.bus.map(0x1F90005C, &r->spu2.core_0.voice_5.volxl);
            r->iop.bus.map(0x1F90005E, &r->spu2.core_0.voice_5.volxr);
            r->iop.bus.map(0x1F900060, &r->spu2.core_0.voice_6.voll);
            r->iop.bus.map(0x1F900062, &r->spu2.core_0.voice_6.volr);
            r->iop.bus.map(0x1F900064, &r->spu2.core_0.voice_6.pitch);
            r->iop.bus.map(0x1F900066, &r->spu2.core_0.voice_6.adsr1);
            r->iop.bus.map(0x1F900068, &r->spu2.core_0.voice_6.adsr2);
            r->iop.bus.map(0x1F90006A, &r->spu2.core_0.voice_6.envx);
            r->iop.bus.map(0x1F90006C, &r->spu2.core_0.voice_6.volxl);
            r->iop.bus.map(0x1F90006E, &r->spu2.core_0.voice_6.volxr);
            r->iop.bus.map(0x1F900070, &r->spu2.core_0.voice_7.voll);
            r->iop.bus.map(0x1F900072, &r->spu2.core_0.voice_7.volr);
            r->iop.bus.map(0x1F900074, &r->spu2.core_0.voice_7.pitch);
            r->iop.bus.map(0x1F900076, &r->spu2.core_0.voice_7.adsr1);
            r->iop.bus.map(0x1F900078, &r->spu2.core_0.voice_7.adsr2);
            r->iop.bus.map(0x1F90007A, &r->spu2.core_0.voice_7.envx);
            r->iop.bus.map(0x1F90007C, &r->spu2.core_0.voice_7.volxl);
            r->iop.bus.map(0x1F90007E, &r->spu2.core_0.voice_7.volxr);
            r->iop.bus.map(0x1F900080, &r->spu2.core_0.voice_8.voll);
            r->iop.bus.map(0x1F900082, &r->spu2.core_0.voice_8.volr);
            r->iop.bus.map(0x1F900084, &r->spu2.core_0.voice_8.pitch);
            r->iop.bus.map(0x1F900086, &r->spu2.core_0.voice_8.adsr1);
            r->iop.bus.map(0x1F900088, &r->spu2.core_0.voice_8.adsr2);
            r->iop.bus.map(0x1F90008A, &r->spu2.core_0.voice_8.envx);
            r->iop.bus.map(0x1F90008C, &r->spu2.core_0.voice_8.volxl);
            r->iop.bus.map(0x1F90008E, &r->spu2.core_0.voice_8.volxr);
            r->iop.bus.map(0x1F900090, &r->spu2.core_0.voice_9.voll);
            r->iop.bus.map(0x1F900092, &r->spu2.core_0.voice_9.volr);
            r->iop.bus.map(0x1F900094, &r->spu2.core_0.voice_9.pitch);
            r->iop.bus.map(0x1F900096, &r->spu2.core_0.voice_9.adsr1);
            r->iop.bus.map(0x1F900098, &r->spu2.core_0.voice_9.adsr2);
            r->iop.bus.map(0x1F90009A, &r->spu2.core_0.voice_9.envx);
            r->iop.bus.map(0x1F90009C, &r->spu2.core_0.voice_9.volxl);
            r->iop.bus.map(0x1F90009E, &r->spu2.core_0.voice_9.volxr);
            r->iop.bus.map(0x1F9000A0, &r->spu2.core_0.voice_10.voll);
            r->iop.bus.map(0x1F9000A2, &r->spu2.core_0.voice_10.volr);
            r->iop.bus.map(0x1F9000A4, &r->spu2.core_0.voice_10.pitch);
            r->iop.bus.map(0x1F9000A6, &r->spu2.core_0.voice_10.adsr1);
            r->iop.bus.map(0x1F9000A8, &r->spu2.core_0.voice_10.adsr2);
            r->iop.bus.map(0x1F9000AA, &r->spu2.core_0.voice_10.envx);
            r->iop.bus.map(0x1F9000AC, &r->spu2.core_0.voice_10.volxl);
            r->iop.bus.map(0x1F9000AE, &r->spu2.core_0.voice_10.volxr);
            r->iop.bus.map(0x1F9000B0, &r->spu2.core_0.voice_11.voll);
            r->iop.bus.map(0x1F9000B2, &r->spu2.core_0.voice_11.volr);
            r->iop.bus.map(0x1F9000B4, &r->spu2.core_0.voice_11.pitch);
            r->iop.bus.map(0x1F9000B6, &r->spu2.core_0.voice_11.adsr1);
            r->iop.bus.map(0x1F9000B8, &r->spu2.core_0.voice_11.adsr2);
            r->iop.bus.map(0x1F9000BA, &r->spu2.core_0.voice_11.envx);
            r->iop.bus.map(0x1F9000BC, &r->spu2.core_0.voice_11.volxl);
            r->iop.bus.map(0x1F9000BE, &r->spu2.core_0.voice_11.volxr);
            r->iop.bus.map(0x1F9000C0, &r->spu2.core_0.voice_12.voll);
            r->iop.bus.map(0x1F9000C2, &r->spu2.core_0.voice_12.volr);
            r->iop.bus.map(0x1F9000C4, &r->spu2.core_0.voice_12.pitch);
            r->iop.bus.map(0x1F9000C6, &r->spu2.core_0.voice_12.adsr1);
            r->iop.bus.map(0x1F9000C8, &r->spu2.core_0.voice_12.adsr2);
            r->iop.bus.map(0x1F9000CA, &r->spu2.core_0.voice_12.envx);
            r->iop.bus.map(0x1F9000CC, &r->spu2.core_0.voice_12.volxl);
            r->iop.bus.map(0x1F9000CE, &r->spu2.core_0.voice_12.volxr);
            r->iop.bus.map(0x1F9000D0, &r->spu2.core_0.voice_13.voll);
            r->iop.bus.map(0x1F9000D2, &r->spu2.core_0.voice_13.volr);
            r->iop.bus.map(0x1F9000D4, &r->spu2.core_0.voice_13.pitch);
            r->iop.bus.map(0x1F9000D6, &r->spu2.core_0.voice_13.adsr1);
            r->iop.bus.map(0x1F9000D8, &r->spu2.core_0.voice_13.adsr2);
            r->iop.bus.map(0x1F9000DA, &r->spu2.core_0.voice_13.envx);
            r->iop.bus.map(0x1F9000DC, &r->spu2.core_0.voice_13.volxl);
            r->iop.bus.map(0x1F9000DE, &r->spu2.core_0.voice_13.volxr);
            r->iop.bus.map(0x1F9000E0, &r->spu2.core_0.voice_14.voll);
            r->iop.bus.map(0x1F9000E2, &r->spu2.core_0.voice_14.volr);
            r->iop.bus.map(0x1F9000E4, &r->spu2.core_0.voice_14.pitch);
            r->iop.bus.map(0x1F9000E6, &r->spu2.core_0.voice_14.adsr1);
            r->iop.bus.map(0x1F9000E8, &r->spu2.core_0.voice_14.adsr2);
            r->iop.bus.map(0x1F9000EA, &r->spu2.core_0.voice_14.envx);
            r->iop.bus.map(0x1F9000EC, &r->spu2.core_0.voice_14.volxl);
            r->iop.bus.map(0x1F9000EE, &r->spu2.core_0.voice_14.volxr);
            r->iop.bus.map(0x1F9000F0, &r->spu2.core_0.voice_15.voll);
            r->iop.bus.map(0x1F9000F2, &r->spu2.core_0.voice_15.volr);
            r->iop.bus.map(0x1F9000F4, &r->spu2.core_0.voice_15.pitch);
            r->iop.bus.map(0x1F9000F6, &r->spu2.core_0.voice_15.adsr1);
            r->iop.bus.map(0x1F9000F8, &r->spu2.core_0.voice_15.adsr2);
            r->iop.bus.map(0x1F9000FA, &r->spu2.core_0.voice_15.envx);
            r->iop.bus.map(0x1F9000FC, &r->spu2.core_0.voice_15.volxl);
            r->iop.bus.map(0x1F9000FE, &r->spu2.core_0.voice_15.volxr);
            r->iop.bus.map(0x1F900100, &r->spu2.core_0.voice_16.voll);
            r->iop.bus.map(0x1F900102, &r->spu2.core_0.voice_16.volr);
            r->iop.bus.map(0x1F900104, &r->spu2.core_0.voice_16.pitch);
            r->iop.bus.map(0x1F900106, &r->spu2.core_0.voice_16.adsr1);
            r->iop.bus.map(0x1F900108, &r->spu2.core_0.voice_16.adsr2);
            r->iop.bus.map(0x1F90010A, &r->spu2.core_0.voice_16.envx);
            r->iop.bus.map(0x1F90010C, &r->spu2.core_0.voice_16.volxl);
            r->iop.bus.map(0x1F90010E, &r->spu2.core_0.voice_16.volxr);
            r->iop.bus.map(0x1F900110, &r->spu2.core_0.voice_17.voll);
            r->iop.bus.map(0x1F900112, &r->spu2.core_0.voice_17.volr);
            r->iop.bus.map(0x1F900114, &r->spu2.core_0.voice_17.pitch);
            r->iop.bus.map(0x1F900116, &r->spu2.core_0.voice_17.adsr1);
            r->iop.bus.map(0x1F900118, &r->spu2.core_0.voice_17.adsr2);
            r->iop.bus.map(0x1F90011A, &r->spu2.core_0.voice_17.envx);
            r->iop.bus.map(0x1F90011C, &r->spu2.core_0.voice_17.volxl);
            r->iop.bus.map(0x1F90011E, &r->spu2.core_0.voice_17.volxr);
            r->iop.bus.map(0x1F900120, &r->spu2.core_0.voice_18.voll);
            r->iop.bus.map(0x1F900122, &r->spu2.core_0.voice_18.volr);
            r->iop.bus.map(0x1F900124, &r->spu2.core_0.voice_18.pitch);
            r->iop.bus.map(0x1F900126, &r->spu2.core_0.voice_18.adsr1);
            r->iop.bus.map(0x1F900128, &r->spu2.core_0.voice_18.adsr2);
            r->iop.bus.map(0x1F90012A, &r->spu2.core_0.voice_18.envx);
            r->iop.bus.map(0x1F90012C, &r->spu2.core_0.voice_18.volxl);
            r->iop.bus.map(0x1F90012E, &r->spu2.core_0.voice_18.volxr);
            r->iop.bus.map(0x1F900130, &r->spu2.core_0.voice_19.voll);
            r->iop.bus.map(0x1F900132, &r->spu2.core_0.voice_19.volr);
            r->iop.bus.map(0x1F900134, &r->spu2.core_0.voice_19.pitch);
            r->iop.bus.map(0x1F900136, &r->spu2.core_0.voice_19.adsr1);
            r->iop.bus.map(0x1F900138, &r->spu2.core_0.voice_19.adsr2);
            r->iop.bus.map(0x1F90013A, &r->spu2.core_0.voice_19.envx);
            r->iop.bus.map(0x1F90013C, &r->spu2.core_0.voice_19.volxl);
            r->iop.bus.map(0x1F90013E, &r->spu2.core_0.voice_19.volxr);
            r->iop.bus.map(0x1F900140, &r->spu2.core_0.voice_20.voll);
            r->iop.bus.map(0x1F900142, &r->spu2.core_0.voice_20.volr);
            r->iop.bus.map(0x1F900144, &r->spu2.core_0.voice_20.pitch);
            r->iop.bus.map(0x1F900146, &r->spu2.core_0.voice_20.adsr1);
            r->iop.bus.map(0x1F900148, &r->spu2.core_0.voice_20.adsr2);
            r->iop.bus.map(0x1F90014A, &r->spu2.core_0.voice_20.envx);
            r->iop.bus.map(0x1F90014C, &r->spu2.core_0.voice_20.volxl);
            r->iop.bus.map(0x1F90014E, &r->spu2.core_0.voice_20.volxr);
            r->iop.bus.map(0x1F900150, &r->spu2.core_0.voice_21.voll);
            r->iop.bus.map(0x1F900152, &r->spu2.core_0.voice_21.volr);
            r->iop.bus.map(0x1F900154, &r->spu2.core_0.voice_21.pitch);
            r->iop.bus.map(0x1F900156, &r->spu2.core_0.voice_21.adsr1);
            r->iop.bus.map(0x1F900158, &r->spu2.core_0.voice_21.adsr2);
            r->iop.bus.map(0x1F90015A, &r->spu2.core_0.voice_21.envx);
            r->iop.bus.map(0x1F90015C, &r->spu2.core_0.voice_21.volxl);
            r->iop.bus.map(0x1F90015E, &r->spu2.core_0.voice_21.volxr);
            r->iop.bus.map(0x1F900160, &r->spu2.core_0.voice_22.voll);
            r->iop.bus.map(0x1F900162, &r->spu2.core_0.voice_22.volr);
            r->iop.bus.map(0x1F900164, &r->spu2.core_0.voice_22.pitch);
            r->iop.bus.map(0x1F900166, &r->spu2.core_0.voice_22.adsr1);
            r->iop.bus.map(0x1F900168, &r->spu2.core_0.voice_22.adsr2);
            r->iop.bus.map(0x1F90016A, &r->spu2.core_0.voice_22.envx);
            r->iop.bus.map(0x1F90016C, &r->spu2.core_0.voice_22.volxl);
            r->iop.bus.map(0x1F90016E, &r->spu2.core_0.voice_22.volxr);
            r->iop.bus.map(0x1F900170, &r->spu2.core_0.voice_23.voll);
            r->iop.bus.map(0x1F900172, &r->spu2.core_0.voice_23.volr);
            r->iop.bus.map(0x1F900174, &r->spu2.core_0.voice_23.pitch);
            r->iop.bus.map(0x1F900176, &r->spu2.core_0.voice_23.adsr1);
            r->iop.bus.map(0x1F900178, &r->spu2.core_0.voice_23.adsr2);
            r->iop.bus.map(0x1F90017A, &r->spu2.core_0.voice_23.envx);
            r->iop.bus.map(0x1F90017C, &r->spu2.core_0.voice_23.volxl);
            r->iop.bus.map(0x1F90017E, &r->spu2.core_0.voice_23.volxr);
            r->iop.bus.map(0x1F900180, &r->spu2.core_0.pmon0);
            r->iop.bus.map(0x1F900182, &r->spu2.core_0.pmon1);
            r->iop.bus.map(0x1F900184, &r->spu2.core_0.non0);
            r->iop.bus.map(0x1F900186, &r->spu2.core_0.non1);
            r->iop.bus.map(0x1F900188, &r->spu2.core_0.vmixl0);
            r->iop.bus.map(0x1F90018A, &r->spu2.core_0.vmixl1);
            r->iop.bus.map(0x1F90018C, &r->spu2.core_0.vmixel0);
            r->iop.bus.map(0x1F90018E, &r->spu2.core_0.vmixel1);
            r->iop.bus.map(0x1F900190, &r->spu2.core_0.vmixr0);
            r->iop.bus.map(0x1F900192, &r->spu2.core_0.vmixr1);
            r->iop.bus.map(0x1F900194, &r->spu2.core_0.vmixer0);
            r->iop.bus.map(0x1F900196, &r->spu2.core_0.vmixer1);
            r->iop.bus.map(0x1F900198, &r->spu2.core_0.mmix);
            r->iop.bus.map(0x1F90019A, &r->spu2.core_0.attr);
            r->iop.bus.map(0x1F90019C, &r->spu2.core_0.irqah);
            r->iop.bus.map(0x1F90019E, &r->spu2.core_0.irqal);
            r->iop.bus.map(0x1F9001A0, &r->spu2.core_0.kon0);
            r->iop.bus.map(0x1F9001A2, &r->spu2.core_0.kon1);
            r->iop.bus.map(0x1F9001A4, &r->spu2.core_0.kof0);
            r->iop.bus.map(0x1F9001A6, &r->spu2.core_0.kof1);
            r->iop.bus.map(0x1F9001A8, &r->spu2.core_0.tsah);
            r->iop.bus.map(0x1F9001AA, &r->spu2.core_0.tsal);
            r->iop.bus.map(0x1F9001AC, &r->spu2.core_0.data0);
            r->iop.bus.map(0x1F9001AE, &r->spu2.core_0.data1);
            r->iop.bus.map(0x1F9001B0, &r->spu2.core_0.admas);
            r->iop.bus.map(0x1F9001C0, &r->spu2.core_0.voice_0.ssah);
            r->iop.bus.map(0x1F9001C2, &r->spu2.core_0.voice_0.ssal);
            r->iop.bus.map(0x1F9001C4, &r->spu2.core_0.voice_0.lsaxh);
            r->iop.bus.map(0x1F9001C6, &r->spu2.core_0.voice_0.lsaxl);
            r->iop.bus.map(0x1F9001C8, &r->spu2.core_0.voice_0.naxh);
            r->iop.bus.map(0x1F9001CA, &r->spu2.core_0.voice_0.naxl);
            r->iop.bus.map(0x1F9001CC, &r->spu2.core_0.voice_1.ssah);
            r->iop.bus.map(0x1F9001CE, &r->spu2.core_0.voice_1.ssal);
            r->iop.bus.map(0x1F9001D0, &r->spu2.core_0.voice_1.lsaxh);
            r->iop.bus.map(0x1F9001D2, &r->spu2.core_0.voice_1.lsaxl);
            r->iop.bus.map(0x1F9001D4, &r->spu2.core_0.voice_1.naxh);
            r->iop.bus.map(0x1F9001D6, &r->spu2.core_0.voice_1.naxl);
            r->iop.bus.map(0x1F9001D8, &r->spu2.core_0.voice_2.ssah);
            r->iop.bus.map(0x1F9001DA, &r->spu2.core_0.voice_2.ssal);
            r->iop.bus.map(0x1F9001DC, &r->spu2.core_0.voice_2.lsaxh);
            r->iop.bus.map(0x1F9001DE, &r->spu2.core_0.voice_2.lsaxl);
            r->iop.bus.map(0x1F9001E0, &r->spu2.core_0.voice_2.naxh);
            r->iop.bus.map(0x1F9001E2, &r->spu2.core_0.voice_2.naxl);
            r->iop.bus.map(0x1F9001E4, &r->spu2.core_0.voice_3.ssah);
            r->iop.bus.map(0x1F9001E6, &r->spu2.core_0.voice_3.ssal);
            r->iop.bus.map(0x1F9001E8, &r->spu2.core_0.voice_3.lsaxh);
            r->iop.bus.map(0x1F9001EA, &r->spu2.core_0.voice_3.lsaxl);
            r->iop.bus.map(0x1F9001EC, &r->spu2.core_0.voice_3.naxh);
            r->iop.bus.map(0x1F9001EE, &r->spu2.core_0.voice_3.naxl);
            r->iop.bus.map(0x1F9001F0, &r->spu2.core_0.voice_4.ssah);
            r->iop.bus.map(0x1F9001F2, &r->spu2.core_0.voice_4.ssal);
            r->iop.bus.map(0x1F9001F4, &r->spu2.core_0.voice_4.lsaxh);
            r->iop.bus.map(0x1F9001F6, &r->spu2.core_0.voice_4.lsaxl);
            r->iop.bus.map(0x1F9001F8, &r->spu2.core_0.voice_4.naxh);
            r->iop.bus.map(0x1F9001FA, &r->spu2.core_0.voice_4.naxl);
            r->iop.bus.map(0x1F9001FC, &r->spu2.core_0.voice_5.ssah);
            r->iop.bus.map(0x1F9001FE, &r->spu2.core_0.voice_5.ssal);
            r->iop.bus.map(0x1F900200, &r->spu2.core_0.voice_5.lsaxh);
            r->iop.bus.map(0x1F900202, &r->spu2.core_0.voice_5.lsaxl);
            r->iop.bus.map(0x1F900204, &r->spu2.core_0.voice_5.naxh);
            r->iop.bus.map(0x1F900206, &r->spu2.core_0.voice_5.naxl);
            r->iop.bus.map(0x1F900208, &r->spu2.core_0.voice_6.ssah);
            r->iop.bus.map(0x1F90020A, &r->spu2.core_0.voice_6.ssal);
            r->iop.bus.map(0x1F90020C, &r->spu2.core_0.voice_6.lsaxh);
            r->iop.bus.map(0x1F90020E, &r->spu2.core_0.voice_6.lsaxl);
            r->iop.bus.map(0x1F900210, &r->spu2.core_0.voice_6.naxh);
            r->iop.bus.map(0x1F900212, &r->spu2.core_0.voice_6.naxl);
            r->iop.bus.map(0x1F900214, &r->spu2.core_0.voice_7.ssah);
            r->iop.bus.map(0x1F900216, &r->spu2.core_0.voice_7.ssal);
            r->iop.bus.map(0x1F900218, &r->spu2.core_0.voice_7.lsaxh);
            r->iop.bus.map(0x1F90021A, &r->spu2.core_0.voice_7.lsaxl);
            r->iop.bus.map(0x1F90021C, &r->spu2.core_0.voice_7.naxh);
            r->iop.bus.map(0x1F90021E, &r->spu2.core_0.voice_7.naxl);
            r->iop.bus.map(0x1F900220, &r->spu2.core_0.voice_8.ssah);
            r->iop.bus.map(0x1F900222, &r->spu2.core_0.voice_8.ssal);
            r->iop.bus.map(0x1F900224, &r->spu2.core_0.voice_8.lsaxh);
            r->iop.bus.map(0x1F900226, &r->spu2.core_0.voice_8.lsaxl);
            r->iop.bus.map(0x1F900228, &r->spu2.core_0.voice_8.naxh);
            r->iop.bus.map(0x1F90022A, &r->spu2.core_0.voice_8.naxl);
            r->iop.bus.map(0x1F90022C, &r->spu2.core_0.voice_9.ssah);
            r->iop.bus.map(0x1F90022E, &r->spu2.core_0.voice_9.ssal);
            r->iop.bus.map(0x1F900230, &r->spu2.core_0.voice_9.lsaxh);
            r->iop.bus.map(0x1F900232, &r->spu2.core_0.voice_9.lsaxl);
            r->iop.bus.map(0x1F900234, &r->spu2.core_0.voice_9.naxh);
            r->iop.bus.map(0x1F900236, &r->spu2.core_0.voice_9.naxl);
            r->iop.bus.map(0x1F900238, &r->spu2.core_0.voice_10.ssah);
            r->iop.bus.map(0x1F90023A, &r->spu2.core_0.voice_10.ssal);
            r->iop.bus.map(0x1F90023C, &r->spu2.core_0.voice_10.lsaxh);
            r->iop.bus.map(0x1F90023E, &r->spu2.core_0.voice_10.lsaxl);
            r->iop.bus.map(0x1F900240, &r->spu2.core_0.voice_10.naxh);
            r->iop.bus.map(0x1F900242, &r->spu2.core_0.voice_10.naxl);
            r->iop.bus.map(0x1F900244, &r->spu2.core_0.voice_11.ssah);
            r->iop.bus.map(0x1F900246, &r->spu2.core_0.voice_11.ssal);
            r->iop.bus.map(0x1F900248, &r->spu2.core_0.voice_11.lsaxh);
            r->iop.bus.map(0x1F90024A, &r->spu2.core_0.voice_11.lsaxl);
            r->iop.bus.map(0x1F90024C, &r->spu2.core_0.voice_11.naxh);
            r->iop.bus.map(0x1F90024E, &r->spu2.core_0.voice_11.naxl);
            r->iop.bus.map(0x1F900250, &r->spu2.core_0.voice_12.ssah);
            r->iop.bus.map(0x1F900252, &r->spu2.core_0.voice_12.ssal);
            r->iop.bus.map(0x1F900254, &r->spu2.core_0.voice_12.lsaxh);
            r->iop.bus.map(0x1F900256, &r->spu2.core_0.voice_12.lsaxl);
            r->iop.bus.map(0x1F900258, &r->spu2.core_0.voice_12.naxh);
            r->iop.bus.map(0x1F90025A, &r->spu2.core_0.voice_12.naxl);
            r->iop.bus.map(0x1F90025C, &r->spu2.core_0.voice_13.ssah);
            r->iop.bus.map(0x1F90025E, &r->spu2.core_0.voice_13.ssal);
            r->iop.bus.map(0x1F900260, &r->spu2.core_0.voice_13.lsaxh);
            r->iop.bus.map(0x1F900262, &r->spu2.core_0.voice_13.lsaxl);
            r->iop.bus.map(0x1F900264, &r->spu2.core_0.voice_13.naxh);
            r->iop.bus.map(0x1F900266, &r->spu2.core_0.voice_13.naxl);
            r->iop.bus.map(0x1F900268, &r->spu2.core_0.voice_14.ssah);
            r->iop.bus.map(0x1F90026A, &r->spu2.core_0.voice_14.ssal);
            r->iop.bus.map(0x1F90026C, &r->spu2.core_0.voice_14.lsaxh);
            r->iop.bus.map(0x1F90026E, &r->spu2.core_0.voice_14.lsaxl);
            r->iop.bus.map(0x1F900270, &r->spu2.core_0.voice_14.naxh);
            r->iop.bus.map(0x1F900272, &r->spu2.core_0.voice_14.naxl);
            r->iop.bus.map(0x1F900274, &r->spu2.core_0.voice_15.ssah);
            r->iop.bus.map(0x1F900276, &r->spu2.core_0.voice_15.ssal);
            r->iop.bus.map(0x1F900278, &r->spu2.core_0.voice_15.lsaxh);
            r->iop.bus.map(0x1F90027A, &r->spu2.core_0.voice_15.lsaxl);
            r->iop.bus.map(0x1F90027C, &r->spu2.core_0.voice_15.naxh);
            r->iop.bus.map(0x1F90027E, &r->spu2.core_0.voice_15.naxl);
            r->iop.bus.map(0x1F900280, &r->spu2.core_0.voice_16.ssah);
            r->iop.bus.map(0x1F900282, &r->spu2.core_0.voice_16.ssal);
            r->iop.bus.map(0x1F900284, &r->spu2.core_0.voice_16.lsaxh);
            r->iop.bus.map(0x1F900286, &r->spu2.core_0.voice_16.lsaxl);
            r->iop.bus.map(0x1F900288, &r->spu2.core_0.voice_16.naxh);
            r->iop.bus.map(0x1F90028A, &r->spu2.core_0.voice_16.naxl);
            r->iop.bus.map(0x1F90028C, &r->spu2.core_0.voice_17.ssah);
            r->iop.bus.map(0x1F90028E, &r->spu2.core_0.voice_17.ssal);
            r->iop.bus.map(0x1F900290, &r->spu2.core_0.voice_17.lsaxh);
            r->iop.bus.map(0x1F900292, &r->spu2.core_0.voice_17.lsaxl);
            r->iop.bus.map(0x1F900294, &r->spu2.core_0.voice_17.naxh);
            r->iop.bus.map(0x1F900296, &r->spu2.core_0.voice_17.naxl);
            r->iop.bus.map(0x1F900298, &r->spu2.core_0.voice_18.ssah);
            r->iop.bus.map(0x1F90029A, &r->spu2.core_0.voice_18.ssal);
            r->iop.bus.map(0x1F90029C, &r->spu2.core_0.voice_18.lsaxh);
            r->iop.bus.map(0x1F90029E, &r->spu2.core_0.voice_18.lsaxl);
            r->iop.bus.map(0x1F9002A0, &r->spu2.core_0.voice_18.naxh);
            r->iop.bus.map(0x1F9002A2, &r->spu2.core_0.voice_18.naxl);
            r->iop.bus.map(0x1F9002A4, &r->spu2.core_0.voice_19.ssah);
            r->iop.bus.map(0x1F9002A6, &r->spu2.core_0.voice_19.ssal);
            r->iop.bus.map(0x1F9002A8, &r->spu2.core_0.voice_19.lsaxh);
            r->iop.bus.map(0x1F9002AA, &r->spu2.core_0.voice_19.lsaxl);
            r->iop.bus.map(0x1F9002AC, &r->spu2.core_0.voice_19.naxh);
            r->iop.bus.map(0x1F9002AE, &r->spu2.core_0.voice_19.naxl);
            r->iop.bus.map(0x1F9002B0, &r->spu2.core_0.voice_20.ssah);
            r->iop.bus.map(0x1F9002B2, &r->spu2.core_0.voice_20.ssal);
            r->iop.bus.map(0x1F9002B4, &r->spu2.core_0.voice_20.lsaxh);
            r->iop.bus.map(0x1F9002B6, &r->spu2.core_0.voice_20.lsaxl);
            r->iop.bus.map(0x1F9002B8, &r->spu2.core_0.voice_20.naxh);
            r->iop.bus.map(0x1F9002BA, &r->spu2.core_0.voice_20.naxl);
            r->iop.bus.map(0x1F9002BC, &r->spu2.core_0.voice_21.ssah);
            r->iop.bus.map(0x1F9002BE, &r->spu2.core_0.voice_21.ssal);
            r->iop.bus.map(0x1F9002C0, &r->spu2.core_0.voice_21.lsaxh);
            r->iop.bus.map(0x1F9002C2, &r->spu2.core_0.voice_21.lsaxl);
            r->iop.bus.map(0x1F9002C4, &r->spu2.core_0.voice_21.naxh);
            r->iop.bus.map(0x1F9002C6, &r->spu2.core_0.voice_21.naxl);
            r->iop.bus.map(0x1F9002C8, &r->spu2.core_0.voice_22.ssah);
            r->iop.bus.map(0x1F9002CA, &r->spu2.core_0.voice_22.ssal);
            r->iop.bus.map(0x1F9002CC, &r->spu2.core_0.voice_22.lsaxh);
            r->iop.bus.map(0x1F9002CE, &r->spu2.core_0.voice_22.lsaxl);
            r->iop.bus.map(0x1F9002D0, &r->spu2.core_0.voice_22.naxh);
            r->iop.bus.map(0x1F9002D2, &r->spu2.core_0.voice_22.naxl);
            r->iop.bus.map(0x1F9002D4, &r->spu2.core_0.voice_23.ssah);
            r->iop.bus.map(0x1F9002D6, &r->spu2.core_0.voice_23.ssal);
            r->iop.bus.map(0x1F9002D8, &r->spu2.core_0.voice_23.lsaxh);
            r->iop.bus.map(0x1F9002DA, &r->spu2.core_0.voice_23.lsaxl);
            r->iop.bus.map(0x1F9002DC, &r->spu2.core_0.voice_23.naxh);
            r->iop.bus.map(0x1F9002DE, &r->spu2.core_0.voice_23.naxl);
            r->iop.bus.map(0x1F9002E0, &r->spu2.core_0.esah);
            r->iop.bus.map(0x1F9002E2, &r->spu2.core_0.esal);
            r->iop.bus.map(0x1F9002E4, &r->spu2.core_0.apf1_sizeh);
            r->iop.bus.map(0x1F9002E6, &r->spu2.core_0.apf1_sizel);
            r->iop.bus.map(0x1F9002E8, &r->spu2.core_0.apf2_sizeh);
            r->iop.bus.map(0x1F9002EA, &r->spu2.core_0.apf2_sizel);
            r->iop.bus.map(0x1F9002EC, &r->spu2.core_0.same_l_dsth);
            r->iop.bus.map(0x1F9002EE, &r->spu2.core_0.same_l_dstl);
            r->iop.bus.map(0x1F9002F0, &r->spu2.core_0.same_r_dsth);
            r->iop.bus.map(0x1F9002F2, &r->spu2.core_0.same_r_dstl);
            r->iop.bus.map(0x1F9002F4, &r->spu2.core_0.comb1_l_srch);
            r->iop.bus.map(0x1F9002F6, &r->spu2.core_0.comb1_l_srcl);
            r->iop.bus.map(0x1F9002F8, &r->spu2.core_0.comb1_r_srch);
            r->iop.bus.map(0x1F9002FA, &r->spu2.core_0.comb1_r_srcl);
            r->iop.bus.map(0x1F9002FC, &r->spu2.core_0.comb2_l_srch);
            r->iop.bus.map(0x1F9002FE, &r->spu2.core_0.comb2_l_srcl);
            r->iop.bus.map(0x1F900300, &r->spu2.core_0.comb2_r_srch);
            r->iop.bus.map(0x1F900302, &r->spu2.core_0.comb2_r_srcl);
            r->iop.bus.map(0x1F900304, &r->spu2.core_0.same_l_srch);
            r->iop.bus.map(0x1F900306, &r->spu2.core_0.same_l_srcl);
            r->iop.bus.map(0x1F900308, &r->spu2.core_0.same_r_srch);
            r->iop.bus.map(0x1F90030A, &r->spu2.core_0.same_r_srcl);
            r->iop.bus.map(0x1F90030C, &r->spu2.core_0.diff_l_dsth);
            r->iop.bus.map(0x1F90030E, &r->spu2.core_0.diff_l_dstl);
            r->iop.bus.map(0x1F900310, &r->spu2.core_0.diff_r_dsth);
            r->iop.bus.map(0x1F900312, &r->spu2.core_0.diff_r_dstl);
            r->iop.bus.map(0x1F900314, &r->spu2.core_0.comb3_l_srch);
            r->iop.bus.map(0x1F900316, &r->spu2.core_0.comb3_l_srcl);
            r->iop.bus.map(0x1F900318, &r->spu2.core_0.comb3_r_srch);
            r->iop.bus.map(0x1F90031A, &r->spu2.core_0.comb3_r_srcl);
            r->iop.bus.map(0x1F90031C, &r->spu2.core_0.comb4_l_srch);
            r->iop.bus.map(0x1F90031E, &r->spu2.core_0.comb4_l_srcl);
            r->iop.bus.map(0x1F900320, &r->spu2.core_0.comb4_r_srch);
            r->iop.bus.map(0x1F900322, &r->spu2.core_0.comb4_r_srcl);
            r->iop.bus.map(0x1F900324, &r->spu2.core_0.diff_l_srch);
            r->iop.bus.map(0x1F900326, &r->spu2.core_0.diff_l_srcl);
            r->iop.bus.map(0x1F900328, &r->spu2.core_0.diff_r_srch);
            r->iop.bus.map(0x1F90032A, &r->spu2.core_0.diff_r_srcl);
            r->iop.bus.map(0x1F90032C, &r->spu2.core_0.apf1_l_dsth);
            r->iop.bus.map(0x1F90032E, &r->spu2.core_0.apf1_l_dstl);
            r->iop.bus.map(0x1F900330, &r->spu2.core_0.apf1_r_dsth);
            r->iop.bus.map(0x1F900332, &r->spu2.core_0.apf1_r_dstl);
            r->iop.bus.map(0x1F900334, &r->spu2.core_0.apf2_l_dsth);
            r->iop.bus.map(0x1F900336, &r->spu2.core_0.apf2_l_dstl);
            r->iop.bus.map(0x1F900338, &r->spu2.core_0.apf2_r_dsth);
            r->iop.bus.map(0x1F90033A, &r->spu2.core_0.apf2_r_dstl);
            r->iop.bus.map(0x1F90033C, &r->spu2.core_0.eeah);
            r->iop.bus.map(0x1F90033E, &r->spu2.core_0.eeal);
            r->iop.bus.map(0x1F900340, &r->spu2.core_0.endx0);
            r->iop.bus.map(0x1F900342, &r->spu2.core_0.endx1);
            r->iop.bus.map(0x1F900344, &r->spu2.core_0.statx);
            r->iop.bus.map(0x1F900346, &r->spu2.memory_0346);
            r->iop.bus.map(0x1F900400, &r->spu2.core_1.voice_0.voll);
            r->iop.bus.map(0x1F900402, &r->spu2.core_1.voice_0.volr);
            r->iop.bus.map(0x1F900404, &r->spu2.core_1.voice_0.pitch);
            r->iop.bus.map(0x1F900406, &r->spu2.core_1.voice_0.adsr1);
            r->iop.bus.map(0x1F900408, &r->spu2.core_1.voice_0.adsr2);
            r->iop.bus.map(0x1F90040A, &r->spu2.core_1.voice_0.envx);
            r->iop.bus.map(0x1F90040C, &r->spu2.core_1.voice_0.volxl);
            r->iop.bus.map(0x1F90040E, &r->spu2.core_1.voice_0.volxr);
            r->iop.bus.map(0x1F900410, &r->spu2.core_1.voice_1.voll);
            r->iop.bus.map(0x1F900412, &r->spu2.core_1.voice_1.volr);
            r->iop.bus.map(0x1F900414, &r->spu2.core_1.voice_1.pitch);
            r->iop.bus.map(0x1F900416, &r->spu2.core_1.voice_1.adsr1);
            r->iop.bus.map(0x1F900418, &r->spu2.core_1.voice_1.adsr2);
            r->iop.bus.map(0x1F90041A, &r->spu2.core_1.voice_1.envx);
            r->iop.bus.map(0x1F90041C, &r->spu2.core_1.voice_1.volxl);
            r->iop.bus.map(0x1F90041E, &r->spu2.core_1.voice_1.volxr);
            r->iop.bus.map(0x1F900420, &r->spu2.core_1.voice_2.voll);
            r->iop.bus.map(0x1F900422, &r->spu2.core_1.voice_2.volr);
            r->iop.bus.map(0x1F900424, &r->spu2.core_1.voice_2.pitch);
            r->iop.bus.map(0x1F900426, &r->spu2.core_1.voice_2.adsr1);
            r->iop.bus.map(0x1F900428, &r->spu2.core_1.voice_2.adsr2);
            r->iop.bus.map(0x1F90042A, &r->spu2.core_1.voice_2.envx);
            r->iop.bus.map(0x1F90042C, &r->spu2.core_1.voice_2.volxl);
            r->iop.bus.map(0x1F90042E, &r->spu2.core_1.voice_2.volxr);
            r->iop.bus.map(0x1F900430, &r->spu2.core_1.voice_3.voll);
            r->iop.bus.map(0x1F900432, &r->spu2.core_1.voice_3.volr);
            r->iop.bus.map(0x1F900434, &r->spu2.core_1.voice_3.pitch);
            r->iop.bus.map(0x1F900436, &r->spu2.core_1.voice_3.adsr1);
            r->iop.bus.map(0x1F900438, &r->spu2.core_1.voice_3.adsr2);
            r->iop.bus.map(0x1F90043A, &r->spu2.core_1.voice_3.envx);
            r->iop.bus.map(0x1F90043C, &r->spu2.core_1.voice_3.volxl);
            r->iop.bus.map(0x1F90043E, &r->spu2.core_1.voice_3.volxr);
            r->iop.bus.map(0x1F900440, &r->spu2.core_1.voice_4.voll);
            r->iop.bus.map(0x1F900442, &r->spu2.core_1.voice_4.volr);
            r->iop.bus.map(0x1F900444, &r->spu2.core_1.voice_4.pitch);
            r->iop.bus.map(0x1F900446, &r->spu2.core_1.voice_4.adsr1);
            r->iop.bus.map(0x1F900448, &r->spu2.core_1.voice_4.adsr2);
            r->iop.bus.map(0x1F90044A, &r->spu2.core_1.voice_4.envx);
            r->iop.bus.map(0x1F90044C, &r->spu2.core_1.voice_4.volxl);
            r->iop.bus.map(0x1F90044E, &r->spu2.core_1.voice_4.volxr);
            r->iop.bus.map(0x1F900450, &r->spu2.core_1.voice_5.voll);
            r->iop.bus.map(0x1F900452, &r->spu2.core_1.voice_5.volr);
            r->iop.bus.map(0x1F900454, &r->spu2.core_1.voice_5.pitch);
            r->iop.bus.map(0x1F900456, &r->spu2.core_1.voice_5.adsr1);
            r->iop.bus.map(0x1F900458, &r->spu2.core_1.voice_5.adsr2);
            r->iop.bus.map(0x1F90045A, &r->spu2.core_1.voice_5.envx);
            r->iop.bus.map(0x1F90045C, &r->spu2.core_1.voice_5.volxl);
            r->iop.bus.map(0x1F90045E, &r->spu2.core_1.voice_5.volxr);
            r->iop.bus.map(0x1F900460, &r->spu2.core_1.voice_6.voll);
            r->iop.bus.map(0x1F900462, &r->spu2.core_1.voice_6.volr);
            r->iop.bus.map(0x1F900464, &r->spu2.core_1.voice_6.pitch);
            r->iop.bus.map(0x1F900466, &r->spu2.core_1.voice_6.adsr1);
            r->iop.bus.map(0x1F900468, &r->spu2.core_1.voice_6.adsr2);
            r->iop.bus.map(0x1F90046A, &r->spu2.core_1.voice_6.envx);
            r->iop.bus.map(0x1F90046C, &r->spu2.core_1.voice_6.volxl);
            r->iop.bus.map(0x1F90046E, &r->spu2.core_1.voice_6.volxr);
            r->iop.bus.map(0x1F900470, &r->spu2.core_1.voice_7.voll);
            r->iop.bus.map(0x1F900472, &r->spu2.core_1.voice_7.volr);
            r->iop.bus.map(0x1F900474, &r->spu2.core_1.voice_7.pitch);
            r->iop.bus.map(0x1F900476, &r->spu2.core_1.voice_7.adsr1);
            r->iop.bus.map(0x1F900478, &r->spu2.core_1.voice_7.adsr2);
            r->iop.bus.map(0x1F90047A, &r->spu2.core_1.voice_7.envx);
            r->iop.bus.map(0x1F90047C, &r->spu2.core_1.voice_7.volxl);
            r->iop.bus.map(0x1F90047E, &r->spu2.core_1.voice_7.volxr);
            r->iop.bus.map(0x1F900480, &r->spu2.core_1.voice_8.voll);
            r->iop.bus.map(0x1F900482, &r->spu2.core_1.voice_8.volr);
            r->iop.bus.map(0x1F900484, &r->spu2.core_1.voice_8.pitch);
            r->iop.bus.map(0x1F900486, &r->spu2.core_1.voice_8.adsr1);
            r->iop.bus.map(0x1F900488, &r->spu2.core_1.voice_8.adsr2);
            r->iop.bus.map(0x1F90048A, &r->spu2.core_1.voice_8.envx);
            r->iop.bus.map(0x1F90048C, &r->spu2.core_1.voice_8.volxl);
            r->iop.bus.map(0x1F90048E, &r->spu2.core_1.voice_8.volxr);
            r->iop.bus.map(0x1F900490, &r->spu2.core_1.voice_9.voll);
            r->iop.bus.map(0x1F900492, &r->spu2.core_1.voice_9.volr);
            r->iop.bus.map(0x1F900494, &r->spu2.core_1.voice_9.pitch);
            r->iop.bus.map(0x1F900496, &r->spu2.core_1.voice_9.adsr1);
            r->iop.bus.map(0x1F900498, &r->spu2.core_1.voice_9.adsr2);
            r->iop.bus.map(0x1F90049A, &r->spu2.core_1.voice_9.envx);
            r->iop.bus.map(0x1F90049C, &r->spu2.core_1.voice_9.volxl);
            r->iop.bus.map(0x1F90049E, &r->spu2.core_1.voice_9.volxr);
            r->iop.bus.map(0x1F9004A0, &r->spu2.core_1.voice_10.voll);
            r->iop.bus.map(0x1F9004A2, &r->spu2.core_1.voice_10.volr);
            r->iop.bus.map(0x1F9004A4, &r->spu2.core_1.voice_10.pitch);
            r->iop.bus.map(0x1F9004A6, &r->spu2.core_1.voice_10.adsr1);
            r->iop.bus.map(0x1F9004A8, &r->spu2.core_1.voice_10.adsr2);
            r->iop.bus.map(0x1F9004AA, &r->spu2.core_1.voice_10.envx);
            r->iop.bus.map(0x1F9004AC, &r->spu2.core_1.voice_10.volxl);
            r->iop.bus.map(0x1F9004AE, &r->spu2.core_1.voice_10.volxr);
            r->iop.bus.map(0x1F9004B0, &r->spu2.core_1.voice_11.voll);
            r->iop.bus.map(0x1F9004B2, &r->spu2.core_1.voice_11.volr);
            r->iop.bus.map(0x1F9004B4, &r->spu2.core_1.voice_11.pitch);
            r->iop.bus.map(0x1F9004B6, &r->spu2.core_1.voice_11.adsr1);
            r->iop.bus.map(0x1F9004B8, &r->spu2.core_1.voice_11.adsr2);
            r->iop.bus.map(0x1F9004BA, &r->spu2.core_1.voice_11.envx);
            r->iop.bus.map(0x1F9004BC, &r->spu2.core_1.voice_11.volxl);
            r->iop.bus.map(0x1F9004BE, &r->spu2.core_1.voice_11.volxr);
            r->iop.bus.map(0x1F9004C0, &r->spu2.core_1.voice_12.voll);
            r->iop.bus.map(0x1F9004C2, &r->spu2.core_1.voice_12.volr);
            r->iop.bus.map(0x1F9004C4, &r->spu2.core_1.voice_12.pitch);
            r->iop.bus.map(0x1F9004C6, &r->spu2.core_1.voice_12.adsr1);
            r->iop.bus.map(0x1F9004C8, &r->spu2.core_1.voice_12.adsr2);
            r->iop.bus.map(0x1F9004CA, &r->spu2.core_1.voice_12.envx);
            r->iop.bus.map(0x1F9004CC, &r->spu2.core_1.voice_12.volxl);
            r->iop.bus.map(0x1F9004CE, &r->spu2.core_1.voice_12.volxr);
            r->iop.bus.map(0x1F9004D0, &r->spu2.core_1.voice_13.voll);
            r->iop.bus.map(0x1F9004D2, &r->spu2.core_1.voice_13.volr);
            r->iop.bus.map(0x1F9004D4, &r->spu2.core_1.voice_13.pitch);
            r->iop.bus.map(0x1F9004D6, &r->spu2.core_1.voice_13.adsr1);
            r->iop.bus.map(0x1F9004D8, &r->spu2.core_1.voice_13.adsr2);
            r->iop.bus.map(0x1F9004DA, &r->spu2.core_1.voice_13.envx);
            r->iop.bus.map(0x1F9004DC, &r->spu2.core_1.voice_13.volxl);
            r->iop.bus.map(0x1F9004DE, &r->spu2.core_1.voice_13.volxr);
            r->iop.bus.map(0x1F9004E0, &r->spu2.core_1.voice_14.voll);
            r->iop.bus.map(0x1F9004E2, &r->spu2.core_1.voice_14.volr);
            r->iop.bus.map(0x1F9004E4, &r->spu2.core_1.voice_14.pitch);
            r->iop.bus.map(0x1F9004E6, &r->spu2.core_1.voice_14.adsr1);
            r->iop.bus.map(0x1F9004E8, &r->spu2.core_1.voice_14.adsr2);
            r->iop.bus.map(0x1F9004EA, &r->spu2.core_1.voice_14.envx);
            r->iop.bus.map(0x1F9004EC, &r->spu2.core_1.voice_14.volxl);
            r->iop.bus.map(0x1F9004EE, &r->spu2.core_1.voice_14.volxr);
            r->iop.bus.map(0x1F9004F0, &r->spu2.core_1.voice_15.voll);
            r->iop.bus.map(0x1F9004F2, &r->spu2.core_1.voice_15.volr);
            r->iop.bus.map(0x1F9004F4, &r->spu2.core_1.voice_15.pitch);
            r->iop.bus.map(0x1F9004F6, &r->spu2.core_1.voice_15.adsr1);
            r->iop.bus.map(0x1F9004F8, &r->spu2.core_1.voice_15.adsr2);
            r->iop.bus.map(0x1F9004FA, &r->spu2.core_1.voice_15.envx);
            r->iop.bus.map(0x1F9004FC, &r->spu2.core_1.voice_15.volxl);
            r->iop.bus.map(0x1F9004FE, &r->spu2.core_1.voice_15.volxr);
            r->iop.bus.map(0x1F900500, &r->spu2.core_1.voice_16.voll);
            r->iop.bus.map(0x1F900502, &r->spu2.core_1.voice_16.volr);
            r->iop.bus.map(0x1F900504, &r->spu2.core_1.voice_16.pitch);
            r->iop.bus.map(0x1F900506, &r->spu2.core_1.voice_16.adsr1);
            r->iop.bus.map(0x1F900508, &r->spu2.core_1.voice_16.adsr2);
            r->iop.bus.map(0x1F90050A, &r->spu2.core_1.voice_16.envx);
            r->iop.bus.map(0x1F90050C, &r->spu2.core_1.voice_16.volxl);
            r->iop.bus.map(0x1F90050E, &r->spu2.core_1.voice_16.volxr);
            r->iop.bus.map(0x1F900510, &r->spu2.core_1.voice_17.voll);
            r->iop.bus.map(0x1F900512, &r->spu2.core_1.voice_17.volr);
            r->iop.bus.map(0x1F900514, &r->spu2.core_1.voice_17.pitch);
            r->iop.bus.map(0x1F900516, &r->spu2.core_1.voice_17.adsr1);
            r->iop.bus.map(0x1F900518, &r->spu2.core_1.voice_17.adsr2);
            r->iop.bus.map(0x1F90051A, &r->spu2.core_1.voice_17.envx);
            r->iop.bus.map(0x1F90051C, &r->spu2.core_1.voice_17.volxl);
            r->iop.bus.map(0x1F90051E, &r->spu2.core_1.voice_17.volxr);
            r->iop.bus.map(0x1F900520, &r->spu2.core_1.voice_18.voll);
            r->iop.bus.map(0x1F900522, &r->spu2.core_1.voice_18.volr);
            r->iop.bus.map(0x1F900524, &r->spu2.core_1.voice_18.pitch);
            r->iop.bus.map(0x1F900526, &r->spu2.core_1.voice_18.adsr1);
            r->iop.bus.map(0x1F900528, &r->spu2.core_1.voice_18.adsr2);
            r->iop.bus.map(0x1F90052A, &r->spu2.core_1.voice_18.envx);
            r->iop.bus.map(0x1F90052C, &r->spu2.core_1.voice_18.volxl);
            r->iop.bus.map(0x1F90052E, &r->spu2.core_1.voice_18.volxr);
            r->iop.bus.map(0x1F900530, &r->spu2.core_1.voice_19.voll);
            r->iop.bus.map(0x1F900532, &r->spu2.core_1.voice_19.volr);
            r->iop.bus.map(0x1F900534, &r->spu2.core_1.voice_19.pitch);
            r->iop.bus.map(0x1F900536, &r->spu2.core_1.voice_19.adsr1);
            r->iop.bus.map(0x1F900538, &r->spu2.core_1.voice_19.adsr2);
            r->iop.bus.map(0x1F90053A, &r->spu2.core_1.voice_19.envx);
            r->iop.bus.map(0x1F90053C, &r->spu2.core_1.voice_19.volxl);
            r->iop.bus.map(0x1F90053E, &r->spu2.core_1.voice_19.volxr);
            r->iop.bus.map(0x1F900540, &r->spu2.core_1.voice_20.voll);
            r->iop.bus.map(0x1F900542, &r->spu2.core_1.voice_20.volr);
            r->iop.bus.map(0x1F900544, &r->spu2.core_1.voice_20.pitch);
            r->iop.bus.map(0x1F900546, &r->spu2.core_1.voice_20.adsr1);
            r->iop.bus.map(0x1F900548, &r->spu2.core_1.voice_20.adsr2);
            r->iop.bus.map(0x1F90054A, &r->spu2.core_1.voice_20.envx);
            r->iop.bus.map(0x1F90054C, &r->spu2.core_1.voice_20.volxl);
            r->iop.bus.map(0x1F90054E, &r->spu2.core_1.voice_20.volxr);
            r->iop.bus.map(0x1F900550, &r->spu2.core_1.voice_21.voll);
            r->iop.bus.map(0x1F900552, &r->spu2.core_1.voice_21.volr);
            r->iop.bus.map(0x1F900554, &r->spu2.core_1.voice_21.pitch);
            r->iop.bus.map(0x1F900556, &r->spu2.core_1.voice_21.adsr1);
            r->iop.bus.map(0x1F900558, &r->spu2.core_1.voice_21.adsr2);
            r->iop.bus.map(0x1F90055A, &r->spu2.core_1.voice_21.envx);
            r->iop.bus.map(0x1F90055C, &r->spu2.core_1.voice_21.volxl);
            r->iop.bus.map(0x1F90055E, &r->spu2.core_1.voice_21.volxr);
            r->iop.bus.map(0x1F900560, &r->spu2.core_1.voice_22.voll);
            r->iop.bus.map(0x1F900562, &r->spu2.core_1.voice_22.volr);
            r->iop.bus.map(0x1F900564, &r->spu2.core_1.voice_22.pitch);
            r->iop.bus.map(0x1F900566, &r->spu2.core_1.voice_22.adsr1);
            r->iop.bus.map(0x1F900568, &r->spu2.core_1.voice_22.adsr2);
            r->iop.bus.map(0x1F90056A, &r->spu2.core_1.voice_22.envx);
            r->iop.bus.map(0x1F90056C, &r->spu2.core_1.voice_22.volxl);
            r->iop.bus.map(0x1F90056E, &r->spu2.core_1.voice_22.volxr);
            r->iop.bus.map(0x1F900570, &r->spu2.core_1.voice_23.voll);
            r->iop.bus.map(0x1F900572, &r->spu2.core_1.voice_23.volr);
            r->iop.bus.map(0x1F900574, &r->spu2.core_1.voice_23.pitch);
            r->iop.bus.map(0x1F900576, &r->spu2.core_1.voice_23.adsr1);
            r->iop.bus.map(0x1F900578, &r->spu2.core_1.voice_23.adsr2);
            r->iop.bus.map(0x1F90057A, &r->spu2.core_1.voice_23.envx);
            r->iop.bus.map(0x1F90057C, &r->spu2.core_1.voice_23.volxl);
            r->iop.bus.map(0x1F90057E, &r->spu2.core_1.voice_23.volxr);
            r->iop.bus.map(0x1F900580, &r->spu2.core_1.pmon0);
            r->iop.bus.map(0x1F900582, &r->spu2.core_1.pmon1);
            r->iop.bus.map(0x1F900584, &r->spu2.core_1.non0);
            r->iop.bus.map(0x1F900586, &r->spu2.core_1.non1);
            r->iop.bus.map(0x1F900588, &r->spu2.core_1.vmixl0);
            r->iop.bus.map(0x1F90058A, &r->spu2.core_1.vmixl1);
            r->iop.bus.map(0x1F90058C, &r->spu2.core_1.vmixel0);
            r->iop.bus.map(0x1F90058E, &r->spu2.core_1.vmixel1);
            r->iop.bus.map(0x1F900590, &r->spu2.core_1.vmixr0);
            r->iop.bus.map(0x1F900592, &r->spu2.core_1.vmixr1);
            r->iop.bus.map(0x1F900594, &r->spu2.core_1.vmixer0);
            r->iop.bus.map(0x1F900596, &r->spu2.core_1.vmixer1);
            r->iop.bus.map(0x1F900598, &r->spu2.core_1.mmix);
            r->iop.bus.map(0x1F90059A, &r->spu2.core_1.attr);
            r->iop.bus.map(0x1F90059C, &r->spu2.core_1.irqah);
            r->iop.bus.map(0x1F90059E, &r->spu2.core_1.irqal);
            r->iop.bus.map(0x1F9005A0, &r->spu2.core_1.kon0);
            r->iop.bus.map(0x1F9005A2, &r->spu2.core_1.kon1);
            r->iop.bus.map(0x1F9005A4, &r->spu2.core_1.kof0);
            r->iop.bus.map(0x1F9005A6, &r->spu2.core_1.kof1);
            r->iop.bus.map(0x1F9005A8, &r->spu2.core_1.tsah);
            r->iop.bus.map(0x1F9005AA, &r->spu2.core_1.tsal);
            r->iop.bus.map(0x1F9005AC, &r->spu2.core_1.data0);
            r->iop.bus.map(0x1F9005AE, &r->spu2.core_1.data1);
            r->iop.bus.map(0x1F9005B0, &r->spu2.core_1.admas);
            r->iop.bus.map(0x1F9005C0, &r->spu2.core_1.voice_0.ssah);
            r->iop.bus.map(0x1F9005C2, &r->spu2.core_1.voice_0.ssal);
            r->iop.bus.map(0x1F9005C4, &r->spu2.core_1.voice_0.lsaxh);
            r->iop.bus.map(0x1F9005C6, &r->spu2.core_1.voice_0.lsaxl);
            r->iop.bus.map(0x1F9005C8, &r->spu2.core_1.voice_0.naxh);
            r->iop.bus.map(0x1F9005CA, &r->spu2.core_1.voice_0.naxl);
            r->iop.bus.map(0x1F9005CC, &r->spu2.core_1.voice_1.ssah);
            r->iop.bus.map(0x1F9005CE, &r->spu2.core_1.voice_1.ssal);
            r->iop.bus.map(0x1F9005D0, &r->spu2.core_1.voice_1.lsaxh);
            r->iop.bus.map(0x1F9005D2, &r->spu2.core_1.voice_1.lsaxl);
            r->iop.bus.map(0x1F9005D4, &r->spu2.core_1.voice_1.naxh);
            r->iop.bus.map(0x1F9005D6, &r->spu2.core_1.voice_1.naxl);
            r->iop.bus.map(0x1F9005D8, &r->spu2.core_1.voice_2.ssah);
            r->iop.bus.map(0x1F9005DA, &r->spu2.core_1.voice_2.ssal);
            r->iop.bus.map(0x1F9005DC, &r->spu2.core_1.voice_2.lsaxh);
            r->iop.bus.map(0x1F9005DE, &r->spu2.core_1.voice_2.lsaxl);
            r->iop.bus.map(0x1F9005E0, &r->spu2.core_1.voice_2.naxh);
            r->iop.bus.map(0x1F9005E2, &r->spu2.core_1.voice_2.naxl);
            r->iop.bus.map(0x1F9005E4, &r->spu2.core_1.voice_3.ssah);
            r->iop.bus.map(0x1F9005E6, &r->spu2.core_1.voice_3.ssal);
            r->iop.bus.map(0x1F9005E8, &r->spu2.core_1.voice_3.lsaxh);
            r->iop.bus.map(0x1F9005EA, &r->spu2.core_1.voice_3.lsaxl);
            r->iop.bus.map(0x1F9005EC, &r->spu2.core_1.voice_3.naxh);
            r->iop.bus.map(0x1F9005EE, &r->spu2.core_1.voice_3.naxl);
            r->iop.bus.map(0x1F9005F0, &r->spu2.core_1.voice_4.ssah);
            r->iop.bus.map(0x1F9005F2, &r->spu2.core_1.voice_4.ssal);
            r->iop.bus.map(0x1F9005F4, &r->spu2.core_1.voice_4.lsaxh);
            r->iop.bus.map(0x1F9005F6, &r->spu2.core_1.voice_4.lsaxl);
            r->iop.bus.map(0x1F9005F8, &r->spu2.core_1.voice_4.naxh);
            r->iop.bus.map(0x1F9005FA, &r->spu2.core_1.voice_4.naxl);
            r->iop.bus.map(0x1F9005FC, &r->spu2.core_1.voice_5.ssah);
            r->iop.bus.map(0x1F9005FE, &r->spu2.core_1.voice_5.ssal);
            r->iop.bus.map(0x1F900600, &r->spu2.core_1.voice_5.lsaxh);
            r->iop.bus.map(0x1F900602, &r->spu2.core_1.voice_5.lsaxl);
            r->iop.bus.map(0x1F900604, &r->spu2.core_1.voice_5.naxh);
            r->iop.bus.map(0x1F900606, &r->spu2.core_1.voice_5.naxl);
            r->iop.bus.map(0x1F900608, &r->spu2.core_1.voice_6.ssah);
            r->iop.bus.map(0x1F90060A, &r->spu2.core_1.voice_6.ssal);
            r->iop.bus.map(0x1F90060C, &r->spu2.core_1.voice_6.lsaxh);
            r->iop.bus.map(0x1F90060E, &r->spu2.core_1.voice_6.lsaxl);
            r->iop.bus.map(0x1F900610, &r->spu2.core_1.voice_6.naxh);
            r->iop.bus.map(0x1F900612, &r->spu2.core_1.voice_6.naxl);
            r->iop.bus.map(0x1F900614, &r->spu2.core_1.voice_7.ssah);
            r->iop.bus.map(0x1F900616, &r->spu2.core_1.voice_7.ssal);
            r->iop.bus.map(0x1F900618, &r->spu2.core_1.voice_7.lsaxh);
            r->iop.bus.map(0x1F90061A, &r->spu2.core_1.voice_7.lsaxl);
            r->iop.bus.map(0x1F90061C, &r->spu2.core_1.voice_7.naxh);
            r->iop.bus.map(0x1F90061E, &r->spu2.core_1.voice_7.naxl);
            r->iop.bus.map(0x1F900620, &r->spu2.core_1.voice_8.ssah);
            r->iop.bus.map(0x1F900622, &r->spu2.core_1.voice_8.ssal);
            r->iop.bus.map(0x1F900624, &r->spu2.core_1.voice_8.lsaxh);
            r->iop.bus.map(0x1F900626, &r->spu2.core_1.voice_8.lsaxl);
            r->iop.bus.map(0x1F900628, &r->spu2.core_1.voice_8.naxh);
            r->iop.bus.map(0x1F90062A, &r->spu2.core_1.voice_8.naxl);
            r->iop.bus.map(0x1F90062C, &r->spu2.core_1.voice_9.ssah);
            r->iop.bus.map(0x1F90062E, &r->spu2.core_1.voice_9.ssal);
            r->iop.bus.map(0x1F900630, &r->spu2.core_1.voice_9.lsaxh);
            r->iop.bus.map(0x1F900632, &r->spu2.core_1.voice_9.lsaxl);
            r->iop.bus.map(0x1F900634, &r->spu2.core_1.voice_9.naxh);
            r->iop.bus.map(0x1F900636, &r->spu2.core_1.voice_9.naxl);
            r->iop.bus.map(0x1F900638, &r->spu2.core_1.voice_10.ssah);
            r->iop.bus.map(0x1F90063A, &r->spu2.core_1.voice_10.ssal);
            r->iop.bus.map(0x1F90063C, &r->spu2.core_1.voice_10.lsaxh);
            r->iop.bus.map(0x1F90063E, &r->spu2.core_1.voice_10.lsaxl);
            r->iop.bus.map(0x1F900640, &r->spu2.core_1.voice_10.naxh);
            r->iop.bus.map(0x1F900642, &r->spu2.core_1.voice_10.naxl);
            r->iop.bus.map(0x1F900644, &r->spu2.core_1.voice_11.ssah);
            r->iop.bus.map(0x1F900646, &r->spu2.core_1.voice_11.ssal);
            r->iop.bus.map(0x1F900648, &r->spu2.core_1.voice_11.lsaxh);
            r->iop.bus.map(0x1F90064A, &r->spu2.core_1.voice_11.lsaxl);
            r->iop.bus.map(0x1F90064C, &r->spu2.core_1.voice_11.naxh);
            r->iop.bus.map(0x1F90064E, &r->spu2.core_1.voice_11.naxl);
            r->iop.bus.map(0x1F900650, &r->spu2.core_1.voice_12.ssah);
            r->iop.bus.map(0x1F900652, &r->spu2.core_1.voice_12.ssal);
            r->iop.bus.map(0x1F900654, &r->spu2.core_1.voice_12.lsaxh);
            r->iop.bus.map(0x1F900656, &r->spu2.core_1.voice_12.lsaxl);
            r->iop.bus.map(0x1F900658, &r->spu2.core_1.voice_12.naxh);
            r->iop.bus.map(0x1F90065A, &r->spu2.core_1.voice_12.naxl);
            r->iop.bus.map(0x1F90065C, &r->spu2.core_1.voice_13.ssah);
            r->iop.bus.map(0x1F90065E, &r->spu2.core_1.voice_13.ssal);
            r->iop.bus.map(0x1F900660, &r->spu2.core_1.voice_13.lsaxh);
            r->iop.bus.map(0x1F900662, &r->spu2.core_1.voice_13.lsaxl);
            r->iop.bus.map(0x1F900664, &r->spu2.core_1.voice_13.naxh);
            r->iop.bus.map(0x1F900666, &r->spu2.core_1.voice_13.naxl);
            r->iop.bus.map(0x1F900668, &r->spu2.core_1.voice_14.ssah);
            r->iop.bus.map(0x1F90066A, &r->spu2.core_1.voice_14.ssal);
            r->iop.bus.map(0x1F90066C, &r->spu2.core_1.voice_14.lsaxh);
            r->iop.bus.map(0x1F90066E, &r->spu2.core_1.voice_14.lsaxl);
            r->iop.bus.map(0x1F900670, &r->spu2.core_1.voice_14.naxh);
            r->iop.bus.map(0x1F900672, &r->spu2.core_1.voice_14.naxl);
            r->iop.bus.map(0x1F900674, &r->spu2.core_1.voice_15.ssah);
            r->iop.bus.map(0x1F900676, &r->spu2.core_1.voice_15.ssal);
            r->iop.bus.map(0x1F900678, &r->spu2.core_1.voice_15.lsaxh);
            r->iop.bus.map(0x1F90067A, &r->spu2.core_1.voice_15.lsaxl);
            r->iop.bus.map(0x1F90067C, &r->spu2.core_1.voice_15.naxh);
            r->iop.bus.map(0x1F90067E, &r->spu2.core_1.voice_15.naxl);
            r->iop.bus.map(0x1F900680, &r->spu2.core_1.voice_16.ssah);
            r->iop.bus.map(0x1F900682, &r->spu2.core_1.voice_16.ssal);
            r->iop.bus.map(0x1F900684, &r->spu2.core_1.voice_16.lsaxh);
            r->iop.bus.map(0x1F900686, &r->spu2.core_1.voice_16.lsaxl);
            r->iop.bus.map(0x1F900688, &r->spu2.core_1.voice_16.naxh);
            r->iop.bus.map(0x1F90068A, &r->spu2.core_1.voice_16.naxl);
            r->iop.bus.map(0x1F90068C, &r->spu2.core_1.voice_17.ssah);
            r->iop.bus.map(0x1F90068E, &r->spu2.core_1.voice_17.ssal);
            r->iop.bus.map(0x1F900690, &r->spu2.core_1.voice_17.lsaxh);
            r->iop.bus.map(0x1F900692, &r->spu2.core_1.voice_17.lsaxl);
            r->iop.bus.map(0x1F900694, &r->spu2.core_1.voice_17.naxh);
            r->iop.bus.map(0x1F900696, &r->spu2.core_1.voice_17.naxl);
            r->iop.bus.map(0x1F900698, &r->spu2.core_1.voice_18.ssah);
            r->iop.bus.map(0x1F90069A, &r->spu2.core_1.voice_18.ssal);
            r->iop.bus.map(0x1F90069C, &r->spu2.core_1.voice_18.lsaxh);
            r->iop.bus.map(0x1F90069E, &r->spu2.core_1.voice_18.lsaxl);
            r->iop.bus.map(0x1F9006A0, &r->spu2.core_1.voice_18.naxh);
            r->iop.bus.map(0x1F9006A2, &r->spu2.core_1.voice_18.naxl);
            r->iop.bus.map(0x1F9006A4, &r->spu2.core_1.voice_19.ssah);
            r->iop.bus.map(0x1F9006A6, &r->spu2.core_1.voice_19.ssal);
            r->iop.bus.map(0x1F9006A8, &r->spu2.core_1.voice_19.lsaxh);
            r->iop.bus.map(0x1F9006AA, &r->spu2.core_1.voice_19.lsaxl);
            r->iop.bus.map(0x1F9006AC, &r->spu2.core_1.voice_19.naxh);
            r->iop.bus.map(0x1F9006AE, &r->spu2.core_1.voice_19.naxl);
            r->iop.bus.map(0x1F9006B0, &r->spu2.core_1.voice_20.ssah);
            r->iop.bus.map(0x1F9006B2, &r->spu2.core_1.voice_20.ssal);
            r->iop.bus.map(0x1F9006B4, &r->spu2.core_1.voice_20.lsaxh);
            r->iop.bus.map(0x1F9006B6, &r->spu2.core_1.voice_20.lsaxl);
            r->iop.bus.map(0x1F9006B8, &r->spu2.core_1.voice_20.naxh);
            r->iop.bus.map(0x1F9006BA, &r->spu2.core_1.voice_20.naxl);
            r->iop.bus.map(0x1F9006BC, &r->spu2.core_1.voice_21.ssah);
            r->iop.bus.map(0x1F9006BE, &r->spu2.core_1.voice_21.ssal);
            r->iop.bus.map(0x1F9006C0, &r->spu2.core_1.voice_21.lsaxh);
            r->iop.bus.map(0x1F9006C2, &r->spu2.core_1.voice_21.lsaxl);
            r->iop.bus.map(0x1F9006C4, &r->spu2.core_1.voice_21.naxh);
            r->iop.bus.map(0x1F9006C6, &r->spu2.core_1.voice_21.naxl);
            r->iop.bus.map(0x1F9006C8, &r->spu2.core_1.voice_22.ssah);
            r->iop.bus.map(0x1F9006CA, &r->spu2.core_1.voice_22.ssal);
            r->iop.bus.map(0x1F9006CC, &r->spu2.core_1.voice_22.lsaxh);
            r->iop.bus.map(0x1F9006CE, &r->spu2.core_1.voice_22.lsaxl);
            r->iop.bus.map(0x1F9006D0, &r->spu2.core_1.voice_22.naxh);
            r->iop.bus.map(0x1F9006D2, &r->spu2.core_1.voice_22.naxl);
            r->iop.bus.map(0x1F9006D4, &r->spu2.core_1.voice_23.ssah);
            r->iop.bus.map(0x1F9006D6, &r->spu2.core_1.voice_23.ssal);
            r->iop.bus.map(0x1F9006D8, &r->spu2.core_1.voice_23.lsaxh);
            r->iop.bus.map(0x1F9006DA, &r->spu2.core_1.voice_23.lsaxl);
            r->iop.bus.map(0x1F9006DC, &r->spu2.core_1.voice_23.naxh);
            r->iop.bus.map(0x1F9006DE, &r->spu2.core_1.voice_23.naxl);
            r->iop.bus.map(0x1F9006E0, &r->spu2.core_1.esah);
            r->iop.bus.map(0x1F9006E2, &r->spu2.core_1.esal);
            r->iop.bus.map(0x1F9006E4, &r->spu2.core_1.apf1_sizeh);
            r->iop.bus.map(0x1F9006E6, &r->spu2.core_1.apf1_sizel);
            r->iop.bus.map(0x1F9006E8, &r->spu2.core_1.apf2_sizeh);
            r->iop.bus.map(0x1F9006EA, &r->spu2.core_1.apf2_sizel);
            r->iop.bus.map(0x1F9006EC, &r->spu2.core_1.same_l_dsth);
            r->iop.bus.map(0x1F9006EE, &r->spu2.core_1.same_l_dstl);
            r->iop.bus.map(0x1F9006F0, &r->spu2.core_1.same_r_dsth);
            r->iop.bus.map(0x1F9006F2, &r->spu2.core_1.same_r_dstl);
            r->iop.bus.map(0x1F9006F4, &r->spu2.core_1.comb1_l_srch);
            r->iop.bus.map(0x1F9006F6, &r->spu2.core_1.comb1_l_srcl);
            r->iop.bus.map(0x1F9006F8, &r->spu2.core_1.comb1_r_srch);
            r->iop.bus.map(0x1F9006FA, &r->spu2.core_1.comb1_r_srcl);
            r->iop.bus.map(0x1F9006FC, &r->spu2.core_1.comb2_l_srch);
            r->iop.bus.map(0x1F9006FE, &r->spu2.core_1.comb2_l_srcl);
            r->iop.bus.map(0x1F900700, &r->spu2.core_1.comb2_r_srch);
            r->iop.bus.map(0x1F900702, &r->spu2.core_1.comb2_r_srcl);
            r->iop.bus.map(0x1F900704, &r->spu2.core_1.same_l_srch);
            r->iop.bus.map(0x1F900706, &r->spu2.core_1.same_l_srcl);
            r->iop.bus.map(0x1F900708, &r->spu2.core_1.same_r_srch);
            r->iop.bus.map(0x1F90070A, &r->spu2.core_1.same_r_srcl);
            r->iop.bus.map(0x1F90070C, &r->spu2.core_1.diff_l_dsth);
            r->iop.bus.map(0x1F90070E, &r->spu2.core_1.diff_l_dstl);
            r->iop.bus.map(0x1F900710, &r->spu2.core_1.diff_r_dsth);
            r->iop.bus.map(0x1F900712, &r->spu2.core_1.diff_r_dstl);
            r->iop.bus.map(0x1F900714, &r->spu2.core_1.comb3_l_srch);
            r->iop.bus.map(0x1F900716, &r->spu2.core_1.comb3_l_srcl);
            r->iop.bus.map(0x1F900718, &r->spu2.core_1.comb3_r_srch);
            r->iop.bus.map(0x1F90071A, &r->spu2.core_1.comb3_r_srcl);
            r->iop.bus.map(0x1F90071C, &r->spu2.core_1.comb4_l_srch);
            r->iop.bus.map(0x1F90071E, &r->spu2.core_1.comb4_l_srcl);
            r->iop.bus.map(0x1F900720, &r->spu2.core_1.comb4_r_srch);
            r->iop.bus.map(0x1F900722, &r->spu2.core_1.comb4_r_srcl);
            r->iop.bus.map(0x1F900724, &r->spu2.core_1.diff_l_srch);
            r->iop.bus.map(0x1F900726, &r->spu2.core_1.diff_l_srcl);
            r->iop.bus.map(0x1F900728, &r->spu2.core_1.diff_r_srch);
            r->iop.bus.map(0x1F90072A, &r->spu2.core_1.diff_r_srcl);
            r->iop.bus.map(0x1F90072C, &r->spu2.core_1.apf1_l_dsth);
            r->iop.bus.map(0x1F90072E, &r->spu2.core_1.apf1_l_dstl);
            r->iop.bus.map(0x1F900730, &r->spu2.core_1.apf1_r_dsth);
            r->iop.bus.map(0x1F900732, &r->spu2.core_1.apf1_r_dstl);
            r->iop.bus.map(0x1F900734, &r->spu2.core_1.apf2_l_dsth);
            r->iop.bus.map(0x1F900736, &r->spu2.core_1.apf2_l_dstl);
            r->iop.bus.map(0x1F900738, &r->spu2.core_1.apf2_r_dsth);
            r->iop.bus.map(0x1F90073A, &r->spu2.core_1.apf2_r_dstl);
            r->iop.bus.map(0x1F90073C, &r->spu2.core_1.eeah);
            r->iop.bus.map(0x1F90073E, &r->spu2.core_1.eeal);
            r->iop.bus.map(0x1F900740, &r->spu2.core_1.endx0);
            r->iop.bus.map(0x1F900742, &r->spu2.core_1.endx1);
            r->iop.bus.map(0x1F900744, &r->spu2.core_1.statx);
            r->iop.bus.map(0x1F900746, &r->spu2.memory_0746);
            r->iop.bus.map(0x1F900760, &r->spu2.core_0.mvoll);
            r->iop.bus.map(0x1F900762, &r->spu2.core_0.mvolr);
            r->iop.bus.map(0x1F900764, &r->spu2.core_0.evoll);
            r->iop.bus.map(0x1F900766, &r->spu2.core_0.evolr);
            r->iop.bus.map(0x1F900768, &r->spu2.core_0.avoll);
            r->iop.bus.map(0x1F90076A, &r->spu2.core_0.avolr);
            r->iop.bus.map(0x1F90076C, &r->spu2.core_0.bvoll);
            r->iop.bus.map(0x1F90076E, &r->spu2.core_0.bvolr);
            r->iop.bus.map(0x1F900770, &r->spu2.core_0.mvolxl);
            r->iop.bus.map(0x1F900772, &r->spu2.core_0.mvolxr);
            r->iop.bus.map(0x1F900774, &r->spu2.core_0.iir_vol);
            r->iop.bus.map(0x1F900776, &r->spu2.core_0.comb1_vol);
            r->iop.bus.map(0x1F900778, &r->spu2.core_0.comb2_vol);
            r->iop.bus.map(0x1F90077A, &r->spu2.core_0.comb3_vol);
            r->iop.bus.map(0x1F90077C, &r->spu2.core_0.comb4_vol);
            r->iop.bus.map(0x1F90077E, &r->spu2.core_0.wall_vol);
            r->iop.bus.map(0x1F900780, &r->spu2.core_0.apf1_vol);
            r->iop.bus.map(0x1F900782, &r->spu2.core_0.apf2_vol);
            r->iop.bus.map(0x1F900784, &r->spu2.core_0.in_coef_l);
            r->iop.bus.map(0x1F900786, &r->spu2.core_0.in_coef_r);
            r->iop.bus.map(0x1F900788, &r->spu2.core_1.mvoll);
            r->iop.bus.map(0x1F90078A, &r->spu2.core_1.mvolr);
            r->iop.bus.map(0x1F90078C, &r->spu2.core_1.evoll);
            r->iop.bus.map(0x1F90078E, &r->spu2.core_1.evolr);
            r->iop.bus.map(0x1F900790, &r->spu2.core_1.avoll);
            r->iop.bus.map(0x1F900792, &r->spu2.core_1.avolr);
            r->iop.bus.map(0x1F900794, &r->spu2.core_1.bvoll);
            r->iop.bus.map(0x1F900796, &r->spu2.core_1.bvolr);
            r->iop.bus.map(0x1F900798, &r->spu2.core_1.mvolxl);
            r->iop.bus.map(0x1F90079A, &r->spu2.core_1.mvolxr);
            r->iop.bus.map(0x1F90079C, &r->spu2.core_1.iir_vol);
            r->iop.bus.map(0x1F90079E, &r->spu2.core_1.comb1_vol);
            r->iop.bus.map(0x1F9007A0, &r->spu2.core_1.comb2_vol);
            r->iop.bus.map(0x1F9007A2, &r->spu2.core_1.comb3_vol);
            r->iop.bus.map(0x1F9007A4, &r->spu2.core_1.comb4_vol);
            r->iop.bus.map(0x1F9007A6, &r->spu2.core_1.wall_vol);
            r->iop.bus.map(0x1F9007A8, &r->spu2.core_1.apf1_vol);
            r->iop.bus.map(0x1F9007AA, &r->spu2.core_1.apf2_vol);
            r->iop.bus.map(0x1F9007AC, &r->spu2.core_1.in_coef_l);
            r->iop.bus.map(0x1F9007AE, &r->spu2.core_1.in_coef_r);
            r->iop.bus.map(0x1F9007B0, &r->spu2.memory_07b0);
            r->iop.bus.map(0x1F9007C0, &r->spu2.spdif_out);
            r->iop.bus.map(0x1F9007C2, &r->spu2.spdif_irqinfo);
            r->iop.bus.map(0x1F9007C4, &r->spu2.spdif_07c4);
            r->iop.bus.map(0x1F9007C6, &r->spu2.spdif_mode);
            r->iop.bus.map(0x1F9007C8, &r->spu2.spdif_media);
            r->iop.bus.map(0x1F9007CA, &r->spu2.spdif_07ca);
            r->iop.bus.map(0x1F9007CC, &r->spu2.spdif_protect);
            r->iop.bus.map(0x1F9007CE, &r->spu2.memory_07ce);
            r->iop.bus.map(0x1F900B46, &r->spu2.memory_0346); // 0x346 mirrored at 0xB46.

            // Timers Registers.
            r->iop.bus.map(0x1F801100, &r->iop.timers.unit_0.count);
            r->iop.bus.map(0x1F801104, &r->iop.timers.unit_0.mode);
            r->iop.bus.map(0x1F801108, &r->iop.timers.unit_0.compare);
            r->iop.bus.map(0x1F801110, &r->iop.timers.unit_1.count);
            r->iop.bus.map(0x1F801114, &r->iop.timers.unit_1.mode);
            r->iop.bus.map(0x1F801118, &r->iop.timers.unit_1.compare);
            r->iop.bus.map(0x1F801120, &r->iop.timers.unit_2.count);
            r->iop.bus.map(0x1F801124, &r->iop.timers.unit_2.mode);
            r->iop.bus.map(0x1F801128, &r->iop.timers.unit_2.compare);
            r->iop.bus.map(0x1F801480, &r->iop.timers.unit_3.count);
            r->iop.bus.map(0x1F801484, &r->iop.timers.unit_3.mode);
            r->iop.bus.map(0x1F801488, &r->iop.timers.unit_3.compare);
            r->iop.bus.map(0x1F801490, &r->iop.timers.unit_4.count);
            r->iop.bus.map(0x1F801494, &r->iop.timers.unit_4.mode);
            r->iop.bus.map(0x1F801498, &r->iop.timers.unit_4.compare);
            r->iop.bus.map(0x1F8014A0, &r->iop.timers.unit_5.count);
            r->iop.bus.map(0x1F8014A4, &r->iop.timers.unit_5.mode);
            r->iop.bus.map(0x1F8014A8, &r->iop.timers.unit_5.compare);

            // Parallel Port.
            r->iop.bus.map(0x1F000000, &r->iop.parallel_port);

            // SIO Registers.
            r->iop.bus.map(0x1F801040, &r->iop.sio0.data);
            r->iop.bus.map(0x1F801044, &r->iop.sio0.stat);
            r->iop.bus.map(0x1F801048, &r->iop.sio0.mode);
            r->iop.bus.map(0x1F80104C, &r->iop.sio0.ctrl);

            // SIO2 Registers.
            r->iop.bus.map(0x1F808200, &r->iop.sio2.port_0.ctrl_3);
            r->iop.bus.map(0x1F808204, &r->iop.sio2.port_1.ctrl_3);
            r->iop.bus.map(0x1F808208, &r->iop.sio2.port_2.ctrl_3);
            r->iop.bus.map(0x1F80820C, &r->iop.sio2.port_3.ctrl_3);
            r->iop.bus.map(0x1F808210, &r->iop.sio2.port_4.ctrl_3);
            r->iop.bus.map(0x1F808214, &r->iop.sio2.port_5.ctrl_3);
            r->iop.bus.map(0x1F808218, &r->iop.sio2.port_6.ctrl_3);
            r->iop.bus.map(0x1F80821C, &r->iop.sio2.port_7.ctrl_3);
            r->iop.bus.map(0x1F808220, &r->iop.sio2.port_8.ctrl_3);
            r->iop.bus.map(0x1F808224, &r->iop.sio2.port_9.ctrl_3);
            r->iop.bus.map(0x1F808228, &r->iop.sio2.port_a.ctrl_3);
            r->iop.bus.map(0x1F80822C, &r->iop.sio2.port_b.ctrl_3);
            r->iop.bus.map(0x1F808230, &r->iop.sio2.port_c.ctrl_3);
            r->iop.bus.map(0x1F808234, &r->iop.sio2.port_d.ctrl_3);
            r->iop.bus.map(0x1F808238, &r->iop.sio2.port_e.ctrl_3);
            r->iop.bus.map(0x1F80823C, &r->iop.sio2.port_f.ctrl_3);
            r->iop.bus.map(0x1F808240, &r->iop.sio2.port_0.ctrl_1);
            r->iop.bus.map(0x1F808244, &r->iop.sio2.port_0.ctrl_2);
            r->iop.bus.map(0x1F808248, &r->iop.sio2.port_1.ctrl_1);
            r->iop.bus.map(0x1F80824C, &r->iop.sio2.port_1.ctrl_2);
            r->iop.bus.map(0x1F808250, &r->iop.sio2.port_2.ctrl_1);
            r->iop.bus.map(0x1F808254, &r->iop.sio2.port_2.ctrl_2);
            r->iop.bus.map(0x1F808258, &r->iop.sio2.port_3.ctrl_1);
            r->iop.bus.map(0x1F80825C, &r->iop.sio2.port_3.ctrl_2);
            r->iop.bus.map(0x1F808260, &r->fifo_tosio2);
            r->iop.bus.map(0x1F808264, &r->fifo_fromsio2);
            r->iop.bus.map(0x1F808268, &r->iop.sio2.ctrl);
            r->iop.bus.map(0x1F80826C, &r->iop.sio2.recv1);
            r->iop.bus.map(0x1F808270, &r->iop.sio2.recv2);
            r->iop.bus.map(0x1F808274, &r->iop.sio2.recv3);
            r->iop.bus.map(0x1F808278, &r->iop.sio2.register_8278);
            r->iop.bus.map(0x1F80827C, &r->iop.sio2.register_827c);
            r->iop.bus.map(0x1F808280, &r->iop.sio2.intr);
        }

        // SIF Registers
        {
            r->iop.bus.map(0x1D000000, &r->sbus_mscom);
            r->iop.bus.map(0x1D000010, &r->sbus_smcom);
            r->iop.bus.map(0x1D000020, &r->sbus_msflg);
            r->iop.bus.map(0x1D000030, &r->sbus_smflg);
            r->iop.bus.map(0x1D000040, &r->sbus_f240);
            r->iop.bus.map(0x1D000060, &r->sbus_f260);
        }

        r->iop.bus.optimise();
    }
}

void initialise_iop_core(RResources* r)
{
    // COP0.
    r->iop.core.cop0.registers[0] = &r->iop.core.cop0.indx;
    r->iop.core.cop0.registers[1] = &r->iop.core.cop0.rand;
    r->iop.core.cop0.registers[2] = &r->iop.core.cop0.tlbl;
    r->iop.core.cop0.registers[3] = &r->iop.core.cop0.bpc;
    r->iop.core.cop0.registers[4] = &r->iop.core.cop0.context;
    r->iop.core.cop0.registers[5] = &r->iop.core.cop0.bda;
    r->iop.core.cop0.registers[6] = &r->iop.core.cop0.pidmask;
    r->iop.core.cop0.registers[7] = &r->iop.core.cop0.dcic;
    r->iop.core.cop0.registers[8] = &r->iop.core.cop0.badv;
    r->iop.core.cop0.registers[9] = &r->iop.core.cop0.bdam;
    r->iop.core.cop0.registers[10] = &r->iop.core.cop0.tlbh;
    r->iop.core.cop0.registers[11] = &r->iop.core.cop0.bpcm;
    r->iop.core.cop0.registers[12] = &r->iop.core.cop0.status;
    r->iop.core.cop0.registers[13] = &r->iop.core.cop0.cause;
    r->iop.core.cop0.registers[14] = &r->iop.core.cop0.epc;
    r->iop.core.cop0.registers[15] = &r->iop.core.cop0.prid;
    r->iop.core.cop0.registers[16] = &r->iop.core.cop0.erreg;
}

void initialise_iop_timers(RResources* r)
{
    r->iop.timers.units[0] = &r->iop.timers.unit_0;
    r->iop.timers.units[1] = &r->iop.timers.unit_1;
    r->iop.timers.units[2] = &r->iop.timers.unit_2;
    r->iop.timers.units[3] = &r->iop.timers.unit_3;
    r->iop.timers.units[4] = &r->iop.timers.unit_4;
    r->iop.timers.units[5] = &r->iop.timers.unit_5;
}

void initialise_iop_sio2(RResources* r)
{
    r->iop.sio2.ports[0].ctrl_1 = &r->iop.sio2.port_0.ctrl_1;
    r->iop.sio2.ports[0].ctrl_2 = &r->iop.sio2.port_0.ctrl_2;
    r->iop.sio2.ports[0].ctrl_3 = &r->iop.sio2.port_0.ctrl_3;

    r->iop.sio2.ports[1].ctrl_1 = &r->iop.sio2.port_1.ctrl_1;
    r->iop.sio2.ports[1].ctrl_2 = &r->iop.sio2.port_1.ctrl_2;
    r->iop.sio2.ports[1].ctrl_3 = &r->iop.sio2.port_1.ctrl_3;

    r->iop.sio2.ports[2].ctrl_1 = &r->iop.sio2.port_2.ctrl_1;
    r->iop.sio2.ports[2].ctrl_2 = &r->iop.sio2.port_2.ctrl_2;
    r->iop.sio2.ports[2].ctrl_3 = &r->iop.sio2.port_2.ctrl_3;

    r->iop.sio2.ports[3].ctrl_1 = &r->iop.sio2.port_3.ctrl_1;
    r->iop.sio2.ports[3].ctrl_2 = &r->iop.sio2.port_3.ctrl_2;
    r->iop.sio2.ports[3].ctrl_3 = &r->iop.sio2.port_3.ctrl_3;

    r->iop.sio2.ports[4].ctrl_3 = &r->iop.sio2.port_4.ctrl_3;
    r->iop.sio2.ports[5].ctrl_3 = &r->iop.sio2.port_5.ctrl_3;
    r->iop.sio2.ports[6].ctrl_3 = &r->iop.sio2.port_6.ctrl_3;
    r->iop.sio2.ports[7].ctrl_3 = &r->iop.sio2.port_7.ctrl_3;
    r->iop.sio2.ports[8].ctrl_3 = &r->iop.sio2.port_8.ctrl_3;
    r->iop.sio2.ports[9].ctrl_3 = &r->iop.sio2.port_9.ctrl_3;
    r->iop.sio2.ports[10].ctrl_3 = &r->iop.sio2.port_a.ctrl_3;
    r->iop.sio2.ports[11].ctrl_3 = &r->iop.sio2.port_b.ctrl_3;
    r->iop.sio2.ports[12].ctrl_3 = &r->iop.sio2.port_c.ctrl_3;
    r->iop.sio2.ports[13].ctrl_3 = &r->iop.sio2.port_d.ctrl_3;
    r->iop.sio2.ports[14].ctrl_3 = &r->iop.sio2.port_e.ctrl_3;
    r->iop.sio2.ports[15].ctrl_3 = &r->iop.sio2.port_f.ctrl_3;
}

void initialise_iop_sio0(RResources* r)
{
    r->iop.sio0.data.stat = &r->iop.sio0.stat;
}

void initialise_ee_core(RResources* r)
{
    // COP0.
    r->ee.core.cop0.registers[0] = &r->ee.core.cop0.index;
    r->ee.core.cop0.registers[1] = &r->ee.core.cop0.random;
    r->ee.core.cop0.registers[2] = &r->ee.core.cop0.entrylo0;
    r->ee.core.cop0.registers[3] = &r->ee.core.cop0.entrylo1;
    r->ee.core.cop0.registers[4] = &r->ee.core.cop0.context;
    r->ee.core.cop0.registers[5] = &r->ee.core.cop0.pagemask;
    r->ee.core.cop0.registers[6] = &r->ee.core.cop0.wired;
    r->ee.core.cop0.registers[7] = &r->ee.core.cop0.reserved7;
    r->ee.core.cop0.registers[8] = &r->ee.core.cop0.badvaddr;
    r->ee.core.cop0.registers[9] = &r->ee.core.cop0.count;
    r->ee.core.cop0.registers[10] = &r->ee.core.cop0.entryhi;
    r->ee.core.cop0.registers[11] = &r->ee.core.cop0.compare;
    r->ee.core.cop0.registers[12] = &r->ee.core.cop0.status;
    r->ee.core.cop0.registers[13] = &r->ee.core.cop0.cause;
    r->ee.core.cop0.registers[14] = &r->ee.core.cop0.epc;
    r->ee.core.cop0.registers[15] = &r->ee.core.cop0.prid;
    r->ee.core.cop0.registers[16] = &r->ee.core.cop0.config;
    r->ee.core.cop0.registers[17] = &r->ee.core.cop0.reserved17;
    r->ee.core.cop0.registers[18] = &r->ee.core.cop0.reserved18;
    r->ee.core.cop0.registers[19] = &r->ee.core.cop0.reserved19;
    r->ee.core.cop0.registers[20] = &r->ee.core.cop0.reserved20;
    r->ee.core.cop0.registers[21] = &r->ee.core.cop0.reserved21;
    r->ee.core.cop0.registers[22] = &r->ee.core.cop0.reserved22;
    r->ee.core.cop0.registers[23] = &r->ee.core.cop0.badpaddr;
    r->ee.core.cop0.registers[24] = &r->ee.core.cop0.bpc;
    r->ee.core.cop0.registers[25] = &r->ee.core.cop0.pccr;
    r->ee.core.cop0.registers[26] = &r->ee.core.cop0.reserved26;
    r->ee.core.cop0.registers[27] = &r->ee.core.cop0.reserved27;
    r->ee.core.cop0.registers[28] = &r->ee.core.cop0.taglo;
    r->ee.core.cop0.registers[29] = &r->ee.core.cop0.taghi;
    r->ee.core.cop0.registers[30] = &r->ee.core.cop0.errorepc;
    r->ee.core.cop0.registers[31] = &r->ee.core.cop0.reserved31;
    r->ee.core.cop0.pcr_registers[0] = &r->ee.core.cop0.pcr0;
    r->ee.core.cop0.pcr_registers[1] = &r->ee.core.cop0.pcr1;
    r->ee.core.cop0.compare.cause = &r->ee.core.cop0.cause;

    // FPU.
    r->ee.core.fpu.cop0 = &r->ee.core.cop0;
    r->ee.core.fpu.fcr[0] = &r->ee.core.fpu.irr;
    r->ee.core.fpu.fcr[31] = &r->ee.core.fpu.csr;
}

void initialise_resources(const std::unique_ptr<RResources>& r)
{
    initialise_ee_core(r.get());
    initialise_ee_timers(r.get());
    initialise_ee_dmac(r.get());
    initialise_ee_vpu(r.get());

    initialise_iop_core(r.get());
    initialise_iop_dmac(r.get());
    initialise_iop_timers(r.get());
    initialise_iop_sio2(r.get());
    initialise_iop_sio0(r.get());

    initialise_cdvd(r.get());

    initialise_spu2(r.get());

    initialise_ee(r.get());
    initialise_iop(r.get());
}
