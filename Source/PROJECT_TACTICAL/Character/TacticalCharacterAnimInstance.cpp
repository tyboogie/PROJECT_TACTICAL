// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalCharacterAnimInstance.h"
#include "TacticalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PROJECT_TACTICAL/Weapon/Weapon.h"


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
	EquippedWeapon = TacticalCharacter->GetEquippedWeapon();
	bIsCrouched = TacticalCharacter->bIsCrouched;
	bAiming = TacticalCharacter->IsAiming();
	TurningInPlace = TacticalCharacter->GetTurningInPlace();

	//yaw offset for strafing
	FRotator AimRotation = TacticalCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(TacticalCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = TacticalCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);
	
	AO_Yaw = TacticalCharacter->GetAO_Yaw();
	AO_Pitch = TacticalCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && TacticalCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		TacticalCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
	}
}