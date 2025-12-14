#pragma once


UENUM()
enum class EHDBConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EHDBValidType : uint8
{
	Valid,
	Invalid
};


UENUM()
enum class EHDBSuccessType : uint8
{
	Success,
	Failed
};

UENUM()
enum class EHDBCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EHDBCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};