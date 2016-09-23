#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"


EECoreException_t::EECoreException_t() :
	mExType(ExType::EX_RESET)
{
}

EECoreException_t::EECoreException_t(const ExType & type) : 
	mExType(type),
	mTLBExceptionInfo(),
	mIntExceptionInfo(),
	mCOPExceptionInfo()
{
}

EECoreException_t::EECoreException_t(const ExType & type, const TLBExceptionInfo_t * TLBExceptionInfo, const IntExceptionInfo_t * IntExceptionInfo, const COPExceptionInfo_t * COPExceptionInfo) :
	mExType(type)
{
	if (TLBExceptionInfo != nullptr)
		mTLBExceptionInfo = *TLBExceptionInfo;
	if (IntExceptionInfo != nullptr)
		mIntExceptionInfo = *IntExceptionInfo;
	if (COPExceptionInfo != nullptr)
		mCOPExceptionInfo = *COPExceptionInfo;
}
