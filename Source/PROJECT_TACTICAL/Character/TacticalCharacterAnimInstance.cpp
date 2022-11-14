// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalCharacterAnimInstance.h"
#include "TacticalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UTacticalCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	TacticalCharacter = Cast<ATacticalCharacter>(TryGetPawnOwner());
}

void UTacticalCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (TacticalCharacter == nullptr)
	{
		TacticalCharacter = Cast<ATacticalCharacter>(TryGetPawnOwner());
	}

	if (TacticalCharacter == nullptr) return;

	FVector Velocity = TacticalCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = TacticalCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = TacticalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = TacticalCharacter->IsWeaponEquipped();
	bIsCrouched = TacticalCharacter->bIsCrouched;
}