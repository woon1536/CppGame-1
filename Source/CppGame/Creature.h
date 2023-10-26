// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

UCLASS()
class CPPGAME_API ACreature : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	class UCratureAnim* CreatureAnimInstance;
public:
	// Sets default values for this character's properties
	ACreature() {};		
protected:
		// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Attack() {};


};
