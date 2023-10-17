// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" //Ãß°¡

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
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

			UE_LOG(LogTemp, Log, TEXT("MyCharacter IsValid"));
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
		UE_LOG(LogTemp, Log, TEXT("Z :%f"), Rotation.Roll);
		FVector UnrotateVector = Rotation.UnrotateVector(Velocity);
		Vertical = UnrotateVector.X;
		Horizontal = UnrotateVector.Y;
		Speed = Velocity.Size2D();

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		ShouldMove = Speed > 3.f && Acceleration != FVector::Zero();
		IsFalling = CharacterMovement->IsFalling();
	}
}
