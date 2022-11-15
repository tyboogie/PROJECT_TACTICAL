#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_TACTICAL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class ATacticalCharacter;

	void EquipWeapon(class AWeapon* WeaponToEquip);
protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

private:
	class ATacticalCharacter* Character;
	AWeapon* EquippedWeapon;
	
	UPROPERTY()
		bool bAiming;
	
	UPROPERTY(EditAnywhere)
		float BaseWalkSpeed;

	UPROPERTY(EditAnywhere)
		float AimWalkSpeed;
public:

};