// Fill out your copyright notice in the Description page of Project Settings.


#include "ToyFpsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ToyFPS/Weapon/Weapon.h"

// Sets default values
AToyFpsCharacter::AToyFpsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(45.f, 100.f);
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GetCapsuleComponent()->SetAreaClassOverride(nullptr);

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	USkeletalMeshComponent* CharacterMeshComponent = GetMesh();

	if (!CharacterMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/PlayerMannequin.PlayerMannequin'"));
	CharacterMeshComponent->SetSkeletalMesh(MeshObj.Object);
	CharacterMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	CharacterMeshComponent->SetRelativeRotation(FRotator(-0.f, -90.f, -0.f));

	HeadMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	
	if (!HeadMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HeadObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Head.Head'"));
	HeadMeshComponent->SetSkeletalMesh(HeadObj.Object);
	HeadMeshComponent->SetRelativeLocation(FVector(-165.869286, -1.064955, -16.934584));
	HeadMeshComponent->SetRelativeRotation(FRotator(-69.414944, -285.594594, 287.355255));
	HeadMeshComponent->SetupAttachment(CharacterMeshComponent, TEXT("head"));

	MainCameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	if (!MainCameraComponent)
		return;

	MainCameraComponent->SetRelativeLocation(FVector(-5.453166, 9.761212, 6.619132));
	MainCameraComponent->SetRelativeRotation(FRotator(1.364551, -253.552927, 279.690763));
	MainCameraComponent->SetupAttachment(CharacterMeshComponent, TEXT("head"));
	MainCameraComponent->bUsePawnControlRotation = true;

	ArmsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));

	if (!ArmsMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Arms.Arms'"));
	ArmsMeshComponent->SetSkeletalMesh(ArmsObj.Object);
	ArmsMeshComponent->SetRelativeLocation(FVector(-7.729098, -3.047225, -165.559958));
	ArmsMeshComponent->SetRelativeRotation(FRotator(-0.080375, -89.856430, -0.083177));
	ArmsMeshComponent->SetupAttachment(MainCameraComponent);

	CurrentWeaponComponent = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));

	if (!CurrentWeaponComponent)
		return;

	CurrentWeaponComponent->SetChildActorClass(CurrentWeaponClass);
	CurrentWeaponComponent->SetupAttachment(ArmsMeshComponent, TEXT("WeaponSocket"));
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

	if (!CurrentWeaponClass)
		return;

	CurrentWeaponComponent->CreateChildActor();

	AActor* SpawnedWeapon = CurrentWeaponComponent->GetChildActor();
}

// Called every frame
void AToyFpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpreadCurrent >= SpreadMin)
	{
		DecreaseSpread(DeltaTime * SpreadDecreaseSpeed);
	}

	if (RunningCameraShake == nullptr)
		return;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
		return;

	if (GetVelocity().Length() > 400.f)
	{
			bRunningCameraShake = true;
			PlayerController->ClientStartCameraShake(RunningCameraShake);
	}
	else
	{
		if (bRunningCameraShake)
		{
			bRunningCameraShake = false;
			PlayerController->ClientStopCameraShake(RunningCameraShake);
		}
	}
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
	if (!CurrentWeaponClass)
		return;

	AWeapon* CurrentWeapon = Cast<AWeapon>(CurrentWeaponComponent->GetChildActor());
	if (!CurrentWeapon)
		return;

	CurrentWeapon->Attack();
}

void AToyFpsCharacter::StopAttacking()
{
	if (!CurrentWeaponClass)
		return;

	AWeapon* CurrentWeapon = Cast<AWeapon>(CurrentWeaponComponent->GetChildActor());
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopAttacking();
}

void AToyFpsCharacter::Reload()
{
	if (!CurrentWeaponClass)
		return;

	AWeapon* CurrentWeapon = Cast<AWeapon>(CurrentWeaponComponent->GetChildActor());
	if (!CurrentWeapon)
		return;

	CurrentWeapon->Reload();
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

		//Reloading
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AToyFpsCharacter::Reload);
	}
}

void AToyFpsCharacter::IncreaseSpread(float InIncreaseAmount)
{
	if (SpreadCurrent + InIncreaseAmount >= SpreadMax)
	{
		SpreadCurrent = SpreadCurrent + InIncreaseAmount;
	}
	else
	{
		SpreadCurrent = SpreadMax;
	}
}

void AToyFpsCharacter::DecreaseSpread(float InDecreaseAmount)
{
	if (SpreadCurrent - InDecreaseAmount <= SpreadMin)
	{
		SpreadCurrent = SpreadCurrent - InDecreaseAmount;
	}
	else
	{
		SpreadCurrent = SpreadMin;
	}
}

