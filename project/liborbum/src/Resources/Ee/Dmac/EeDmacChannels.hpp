#pragma once

#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Resources/Ee/Dmac/EeDmacChannelRegisters.hpp"

/// DMAC channel abstraction type.
class EeDmacChannel
{
public:
	EeDmacChannel() :
		channel_id(nullptr),
		dma_fifo_queue(nullptr),
		madr(nullptr),
		qwc(nullptr),
		chcr(nullptr),
		tadr(nullptr),
		asr{nullptr},
		sadr(nullptr)
	{
	}

	int * channel_id;
	DmaFifoQueue<> * dma_fifo_queue;
	EeDmacChannelRegister_Addr * madr;
	SizedWordRegister * qwc;
	EeDmacChannelRegister_Chcr * chcr;
	EeDmacChannelRegister_Addr * tadr;
	EeDmacChannelRegister_Addr * asr[2];
	SizedWordRegister * sadr;
};

/// Normal EE DMAC channel, contains a CHCR, QWC and MADR register.
/// Able to specialise for a CHCR register (used with SIF channels).
/// See EE Users Manual page 73 for the list of registers and more info.
template<typename EeDmacChannelRegister_Chcr_Ty>
class EeDmacChannel_Base
{
public:
	EeDmacChannel_Base(const int channel_id) :
		channel_id(channel_id)
	{
	}

	int channel_id;

	EeDmacChannelRegister_Addr    madr;
	SizedWordRegister             qwc;
	EeDmacChannelRegister_Chcr_Ty chcr;
};

/// TADR EE DMAC channel, contains normal registers plus TADR register.
template<typename EeDmacChannelRegister_Chcr_Ty>
class EeDmacChannel_Tadr : public EeDmacChannel_Base<EeDmacChannelRegister_Chcr_Ty>
{
public:
	EeDmacChannel_Tadr(const int channel_id) :
		EeDmacChannel_Base(channel_id)
	{
	}

	EeDmacChannelRegister_Addr tadr;
};

/// ASR EE DMAC channel, contains normal TADR registers plus ASR registers.
template<typename EeDmacChannelRegister_Chcr_Ty>
class EeDmacChannel_Asr : public EeDmacChannel_Tadr<EeDmacChannelRegister_Chcr_Ty>
{
public:
	EeDmacChannel_Asr(const int channel_id) :
		EeDmacChannel_Tadr(channel_id)
	{
	}

	EeDmacChannelRegister_Addr asr[2];	
};

/// SADR EE DMAC channel, contains normal registers plus SADR register.
template<typename EeDmacChannelRegister_Chcr_Ty>
class EeDmacChannel_Sadr : public EeDmacChannel_Base<EeDmacChannelRegister_Chcr_Ty>
{
public:
	EeDmacChannel_Sadr(const int channel_id) :
		EeDmacChannel_Base(channel_id)
	{
	}

	SizedWordRegister sadr;
};

/// TADR + SADR EE DMAC channel, contains normal registers plus TADR + SADR registers.
template<typename EeDmacChannelRegister_Chcr_Ty>
class EeDmacChannel_Tadr_Sadr : public EeDmacChannel_Base<EeDmacChannelRegister_Chcr_Ty>
{
public:
	EeDmacChannel_Tadr_Sadr(const int channel_id) :
		EeDmacChannel_Base(channel_id)
	{
	}

	EeDmacChannelRegister_Addr tadr;
	SizedWordRegister          sadr;
};