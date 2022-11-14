
#include "TacticalCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ATacticalCharacter::ATacticalCharacter()
{
	// set max acceleration for character
	
	GetCharacterMovement()->MaxAcceleration = 150.f;

	
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ATacticalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATacticalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

void ATacticalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);*/

	PlayerInputComponent->BindAxis("MoveForward", this, &ATacticalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATacticalCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ATacticalCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ATacticalCharacter::LookUp);
}

void ATacticalCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ATacticalCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ATacticalCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ATacticalCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}


