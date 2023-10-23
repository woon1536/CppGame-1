// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector Velocity;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Horizontal;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Vertical;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool ShouldMove;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsFalling;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RotateYaw; 
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float YawOffset;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator AimRotation;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireMontage;
	UPROPERTY(VisibleAnywhere)
	FRotator MovingRotation;
	UPROPERTY(VisibleAnywhere)
	FRotator FinalRotation;
	UPROPERTY(VisibleAnywhere)
	float FinalDistanceCurve;
	UPROPERTY(VisibleAnywhere)
	float DistanceCurve;

	UPROPERTY(VisibleAnywhere)
	class AMyCharacter* MyCharacter;
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovement;
public:
	UMyAnimInstance();
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void PlayFireMontage();	  
	
};
