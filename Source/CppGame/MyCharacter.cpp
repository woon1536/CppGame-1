// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true; //Ãß°¡

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));
	
	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.0f), FRotator(0.f, -90.f, 0.f));
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::KeyUpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::KeyLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyCharacter::LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &AMyCharacter::LookUpDown);

}

void AMyCharacter::KeyUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::KeyLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::LookLeftRight(float value)
{
	AddControllerYawInput(value);
}

void AMyCharacter::LookUpDown(float value)
{
	AddControllerPitchInput(value);
}

