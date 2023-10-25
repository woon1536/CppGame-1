// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "MyAIController.h"
#include "MyEnemyAnimInstance.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_MyEnemy.ABP_MyEnemy_C'"));
	if (AnimInstance.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("AnimInstance.Succeeded"));
		GetMesh()->SetAnimClass(AnimInstance.Class);
	}

	AIControllerClass = AMyAIController::StaticClass();

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemy::Attack()
{
	auto EnemyAnimInstace = Cast<UMyEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	UE_LOG(LogTemp, Log, TEXT("Attack OUT"));
	if (IsValid(EnemyAnimInstace))
	{
		UE_LOG(LogTemp, Log, TEXT("Attack IN"));
		EnemyAnimInstace->PlayAttackMontage();
	}
	else
	{

	}
}

