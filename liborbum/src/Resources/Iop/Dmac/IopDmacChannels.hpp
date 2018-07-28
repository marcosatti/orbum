#pragma once

#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Dmac/IopDmacChannelRegisters.hpp"

/// DMAC channel abstraction type.
class IopDmacChannel
{
public:
    IopDmacChannel() :
        channel_id(nullptr),
        dma_fifo_queue(nullptr),
        madr(nullptr),
        bcr(nullptr),
        chcr(nullptr),
        tadr(nullptr)
    {
    }

    int* channel_id;
    DmaFifoQueue<>* dma_fifo_queue;
    SizedWordRegister* madr;
    IopDmacChannelRegister_Bcr* bcr;
    IopDmacChannelRegister_Chcr* chcr;
    SizedWordRegister* tadr;
};

/// Normal IOP DMAC channel, contains a MADR, BCR and CHCR register.
/// Able to specialise for a CHCR register (used with SIF channels).
template <typename IopDmacChannelRegister_Chcr_Ty>
class IopDmacChannel_Base
{
public:
    IopDmacChannel_Base(const int channel_id) :
        channel_id(channel_id)
    {
    }

    int channel_id;

    SizedWordRegister madr;
    IopDmacChannelRegister_Bcr bcr;
    IopDmacChannelRegister_Chcr_Ty chcr;
};

/// TADR IOP DMAC channel, contains normal registers plus TADR register.
template <typename IopDmacChannelRegister_Chcr_Ty>
class IopDmacChannel_Tadr : public IopDmacChannel_Base<IopDmacChannelRegister_Chcr_Ty>
{
public:
    IopDmacChannel_Tadr(const int channel_id) :
        IopDmacChannel_Base<IopDmacChannelRegister_Chcr_Ty>(channel_id)
    {
    }

    SizedWordRegister tadr;
};