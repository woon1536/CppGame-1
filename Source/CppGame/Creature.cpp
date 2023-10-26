// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "CratureAnim.h"


void ACreature::BeginPlay()
{
	CreatureAnimInstance = Cast<UCratureAnim>(GetMesh()->GetAnimInstance());
}
