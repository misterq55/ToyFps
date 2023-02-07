// Fill out your copyright notice in the Description page of Project Settings.


#include "ToyFpsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AToyFpsCharacter::AToyFpsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/* USkeletalMeshComponent* CharacterMeshComponent = GetMesh();

	if (!CharacterMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/PlayerMannequin.PlayerMannequin'"));
	CharacterMeshComponent->SetSkeletalMesh(MeshObj.Object);
	CharacterMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	CharacterMeshComponent->SetRelativeRotation(FRotator(-0.f, -90.f, -0.f));

	HeadMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("HEAD"));
	
	if (!HeadMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HeadObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Head.Head'"));
	HeadMeshComponent->SetSkeletalMesh(HeadObj.Object);
	HeadMeshComponent->SetRelativeLocation(FVector(-165.869286, -1.064955, -16.934584));
	HeadMeshComponent->SetRelativeRotation(FRotator(-69.414944, -285.594594, 287.355255));
	HeadMeshComponent->SetupAttachment(CharacterMeshComponent, TEXT("head"));

	MainCameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	if (!MainCameraComponent)
		return;

	MainCameraComponent->SetRelativeLocation(FVector(-5.453166, 9.761212, 6.619132));
	MainCameraComponent->SetRelativeRotation(FRotator(1.364551, -253.552927, 279.690763));
	MainCameraComponent->SetupAttachment(CharacterMeshComponent, TEXT("head"));

	ArmsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("ARMS"));

	if (!ArmsMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Arms.Arms'"));
	ArmsMeshComponent->SetSkeletalMesh(ArmsObj.Object);
	ArmsMeshComponent->SetRelativeLocation(FVector(-7.729098, -3.047225, -165.559958));
	ArmsMeshComponent->SetRelativeRotation(FRotator(-0.080375, -89.856430, -0.083177));
	ArmsMeshComponent->SetupAttachment(MainCameraComponent);*/

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	MainCameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	if (!MainCameraComponent)
		return;

	MainCameraComponent->SetupAttachment(GetCapsuleComponent());
	MainCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	MainCameraComponent->bUsePawnControlRotation = true;

	ArmsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("ARMS"));

	if (!ArmsMeshComponent)
		return;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Arms.Arms'"));
	ArmsMeshComponent->SetSkeletalMesh(ArmsObj.Object);
	ArmsMeshComponent->SetupAttachment(MainCameraComponent);
	ArmsMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -150.f));
	ArmsMeshComponent->SetRelativeRotation(FRotator(0, -90, 0));
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

// Called to bind functionality to input
void AToyFpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AToyFpsCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AToyFpsCharacter::Look);
	}
}

