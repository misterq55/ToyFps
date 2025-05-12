// Fill out your copyright notice in the Description page of Project Settings.


#include "ToyFpsCharacter.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponSystem/Weapon/Weapon.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/AnimInstance/ArmsAnimInstanceBase.h"

// Sets default values
AToyFpsCharacter::AToyFpsCharacter()
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponPivot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Weapon"));

	if (!IsValid(WeaponPivot))
	{
		return;
	}

	WeaponPivot->SetupAttachment(ArmsMeshComponent, TEXT("WeaponSocket"));
}

// Called when the game starts or when spawned
void AToyFpsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CurrentWeapon = Cast<AWeaponBase>(GetWorld()->SpawnActor(AWeapon::StaticClass()));

	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->SetOwningCharacter(this);
	CurrentWeapon->SetWeaponData(WeaponAsset->GetWeaponData());
	CurrentWeapon->AttachToComponent(WeaponPivot, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentWeapon->ResetWeapon(WeaponAsset->GetWeaponData());

	UArmsAnimInstanceBase* ArmsAnimInstance = Cast<UArmsAnimInstanceBase>(ArmsMeshComponent->GetAnimInstance());
	ArmsAnimInstance->SetWeaponData(CurrentWeapon->GetWeaponData());

	UWeaponCrossHairWidget* CrossHair = CreateWidget<UWeaponCrossHairWidget>(GetWorld(), WeaponAsset->GetWeaponData().CrossHair);

	if (IsValid(CrossHair))
	{
		CrossHair->StartTimer();
		CrossHair->AddToViewport();
	}
}

// Called every frame
void AToyFpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToyFpsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AToyFpsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AToyFpsCharacter::DoCrouching()
{
	Crouch();
}

void AToyFpsCharacter::StopCrouching()
{
	UnCrouch();
}

void AToyFpsCharacter::Sprint()
{
	bSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AToyFpsCharacter::StopSprinting()
{
	bSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void AToyFpsCharacter::Attack()
{
	if (bSprinting || bReloading)
		return;

	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->Attack();
}

void AToyFpsCharacter::StopAttacking()
{
	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->StopAttacking();
}

void AToyFpsCharacter::Reload()
{
	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->Reload();
}

void AToyFpsCharacter::DoAimimgDownSight()
{
	if (bReloading)
		return;

	bAimDownSight = true;

	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->SniperZoom(bAimDownSight);
}

void AToyFpsCharacter::StopAimingDownSight()
{
	if (bReloading)
		return;

	bAimDownSight = false;

	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->SniperZoom(bAimDownSight);
}

// Called to bind functionality to input
void AToyFpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AToyFpsCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AToyFpsCharacter::Look);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AToyFpsCharacter::DoCrouching);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AToyFpsCharacter::StopCrouching);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AToyFpsCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AToyFpsCharacter::StopSprinting);

		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AToyFpsCharacter::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AToyFpsCharacter::StopAttacking);

		//Reload
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AToyFpsCharacter::Reload);

		//Aiming Down Sight
		EnhancedInputComponent->BindAction(AimDownSightAction, ETriggerEvent::Started, this, &AToyFpsCharacter::DoAimimgDownSight);
		EnhancedInputComponent->BindAction(AimDownSightAction, ETriggerEvent::Completed, this, &AToyFpsCharacter::StopAimingDownSight);
	}
}

