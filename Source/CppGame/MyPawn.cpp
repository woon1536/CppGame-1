// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGreystone/FX/Meshes/Misc/SM_Boulders_1.SM_Boulders_1'"));

	//찾았으면
	if (StaticMesh.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Succeeded"));
		Mesh->SetStaticMesh(StaticMesh.Object);
	}
	else
	{

		UE_LOG(LogTemp, Log, TEXT("Failed"));
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

