#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/IOP/IOPExceptions/Types/IOPException_t.h"


IOPException_t::IOPException_t() :
	mExType(ExType::EX_RESET)
{
}

IOPException_t::IOPException_t(const ExType & type) : 
	mExType(type),
	mTLBExceptionInfo(),
	mIntExceptionInfo(),
	mCOPExceptionInfo()
{
}

IOPException_t::IOPException_t(const ExType & type, const TLBExceptionInfo_t * TLBExceptionInfo, const IntExceptionInfo_t * IntExceptionInfo, const COPExceptionInfo_t * COPExceptionInfo) :
	mExType(type)
{
	if (TLBExceptionInfo != nullptr)
		mTLBExceptionInfo = *TLBExceptionInfo;
	if (IntExceptionInfo != nullptr)
		mIntExceptionInfo = *IntExceptionInfo;
	if (COPExceptionInfo != nullptr)
		mCOPExceptionInfo = *COPExceptionInfo;
}
