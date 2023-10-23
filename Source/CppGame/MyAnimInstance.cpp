// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

UMyAnimInstance::UMyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("/Script/Engine.AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));
	if (AnimMontage.Succeeded())
	{
		FireMontage = AnimMontage.Object;
	}
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		MyCharacter = Cast<AMyCharacter>(Pawn);

		if (IsValid(MyCharacter))
		{
			CharacterMovement = MyCharacter->GetCharacterMovement();
		}
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(MyCharacter))
	{
		Velocity = CharacterMovement->Velocity;
		FRotator Rotation = MyCharacter->GetActorRotation();
		FVector UnrotateVector = Rotation.UnrotateVector(Velocity);
		Vertical = UnrotateVector.X;
		Horizontal = UnrotateVector.Y;
		Speed = Velocity.Size2D();

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		ShouldMove = Speed > 3.f && Acceleration != FVector::Zero();
		IsFalling = CharacterMovement->IsFalling();

		AimRotation = MyCharacter->GetBaseAimRotation();
		FRotator BaseAimRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		
		FRotator DeltaRotation = BaseAimRotation - AimRotation;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;

		if (ShouldMove || IsFalling)
		{
			RotateYaw = FMath::FInterpTo(RotateYaw, 0.f, DeltaSeconds, 20.0f);
			MovingRotation = MyCharacter->GetActorRotation();
			FinalRotation = MovingRotation;
		}
		else
		{
			FinalRotation = MovingRotation;
			MovingRotation = MyCharacter->GetActorRotation();
			FRotator Delta = MovingRotation - FinalRotation;
			Delta.Normalize();
			RotateYaw -= Delta.Yaw;

			float TurnValue = GetCurveValue("Turn");
			if (TurnValue > 0.f)
			{
				FinalDistanceCurve = DistanceCurve;
				DistanceCurve = GetCurveValue("DistanceCurve");
				float DeltaDistanceCurve = DistanceCurve - FinalDistanceCurve;
				if (RotateYaw > 0.f)
				{
					RotateYaw -= DeltaDistanceCurve;
				}
				else
				{
					RotateYaw += DeltaDistanceCurve;
				}

				float AbsRotateYawOffset = FMath::Abs(RotateYaw);
			
				if (AbsRotateYawOffset > 0.f)
				{
					float YawExcess = AbsRotateYawOffset - 90.f;
					
					if (RotateYaw > 0.f)
					{
						
						RotateYaw -= YawExcess;
					}
					else
					{
						RotateYaw += YawExcess;
					}

				}
			}

		
		}

	}
}

void UMyAnimInstance::PlayFireMontage()
{
	if (IsValid(FireMontage))
	{
		if (!Montage_IsPlaying(FireMontage))
		{
			Montage_Play(FireMontage);
		}
	}
}
