// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API UMyEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
public:
	UMyEnemyAnimInstance();
public:
	void PlayAttackMontage();
};
