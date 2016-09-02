#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"


EECoreException_t::EECoreException_t(ExType type) 
	: mExType(type)
{
	mTLBExceptionInfo = nullptr;
	mIntExceptionInfo = nullptr;
	mCOPExceptionInfo = nullptr;
}

EECoreException_t::EECoreException_t(ExType type, TLBExceptionInfo_t* TLBExceptionInfo, IntExceptionInfo_t* IntExceptionInfo, COPExceptionInfo_t* COPExceptionInfo)
	: mExType(type)
{
	if (TLBExceptionInfo != nullptr)
		mTLBExceptionInfo = std::make_shared<TLBExceptionInfo_t>(*TLBExceptionInfo);
	else
		mTLBExceptionInfo = nullptr;

	if (IntExceptionInfo != nullptr)
		mIntExceptionInfo = std::make_shared<IntExceptionInfo_t>(*IntExceptionInfo);
	else
		mIntExceptionInfo = nullptr;

	if (COPExceptionInfo != nullptr)
		mCOPExceptionInfo = std::make_shared<COPExceptionInfo_t>(*COPExceptionInfo);
	else
		mCOPExceptionInfo = nullptr;
}
