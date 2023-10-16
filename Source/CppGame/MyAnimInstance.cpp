// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"

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
		Speed = MyCharacter->GetVelocity().Size();
	}
}
