// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HDBPlayerLinkedAnimLayer.h"
#include "HDBPlayerAnimInstance.h"


UHDBPlayerAnimInstance* UHDBPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
   return Cast<UHDBPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
