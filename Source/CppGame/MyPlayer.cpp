// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h"
#include "Arrow.h"

AMyPlayer::AMyPlayer()
{	 // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->SocketOffset = FVector(0.f, 120.f, 75.f); //�߰�
	SpringArm->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.0f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_MyCharacter.ABP_MyCharacter_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimInstance.Class);
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPlayer::KeyUpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPlayer::KeyLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyPlayer::LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &AMyPlayer::LookUpDown);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyPlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyPlayer::Attack);

}

void AMyPlayer::KeyUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyPlayer::KeyLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyPlayer::LookLeftRight(float value)
{
	AddControllerYawInput(value);
}

void AMyPlayer::LookUpDown(float value)
{
	AddControllerPitchInput(value);
}

void AMyPlayer::Attack()
{
	if (IsValid(CreatureAnimInstance))
	{
		CreatureAnimInstance->PlayAttackMontage();
		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("BowEmitterSocket"));
		FVector ActorLocation = SocketTransform.GetLocation();
		FRotator ActorRotation = SocketTransform.GetRotation().Rotator();
		FActorSpawnParameters params;
		params.Owner = this;

		auto MyArrow = GetWorld()->SpawnActor<AArrow>(ActorLocation, ActorRotation, params);

	}
}
