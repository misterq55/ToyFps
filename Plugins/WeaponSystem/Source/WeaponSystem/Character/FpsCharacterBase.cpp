// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsCharacterBase.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFpsCharacterBase::AFpsCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(45.f, 100.f);
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GetCapsuleComponent()->SetAreaClassOverride(nullptr);

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	USkeletalMeshComponent* characterMeshComponent = GetMesh();

	if (!IsValid(characterMeshComponent))
	{
		return;
	}

	characterMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	characterMeshComponent->SetRelativeRotation(FRotator(-0.f, -90.f, -0.f));

	HeadMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));

	if (!IsValid(HeadMeshComponent))
	{
		return;
	}

	HeadMeshComponent->SetRelativeLocation(FVector(-165.869286, -1.064955, -16.934584));
	HeadMeshComponent->SetRelativeRotation(FRotator(-69.414944, -285.594594, 287.355255));
	HeadMeshComponent->SetupAttachment(characterMeshComponent, TEXT("head"));

	MainCameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	if (!IsValid(MainCameraComponent))
	{
		return;
	}

	MainCameraComponent->SetRelativeLocation(FVector(-5.453166, 9.761212, 6.619132));
	MainCameraComponent->SetRelativeRotation(FRotator(1.364551, -253.552927, 279.690763));
	MainCameraComponent->SetupAttachment(characterMeshComponent, TEXT("head"));
	MainCameraComponent->bUsePawnControlRotation = true;

	ArmsMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));

	if (!IsValid(ArmsMeshComponent))
	{
		return;
	}

	ArmsMeshComponent->SetRelativeLocation(FVector(-7.729098, -3.047225, -165.559958));
	ArmsMeshComponent->SetRelativeRotation(FRotator(-0.080375, -89.856430, -0.083177));
	ArmsMeshComponent->SetupAttachment(MainCameraComponent);
}

// Called when the game starts or when spawned
void AFpsCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFpsCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpreadCurrent >= SpreadMin)
	{
		DecreaseSpread(DeltaTime * SpreadDecreaseSpeed);
	}

	if (RunningCameraShake == nullptr)
		return;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(playerController))
	{
		return;
	}

	if (GetVelocity().Length() > 400.f)
	{
		bRunningCameraShake = true;
		playerController->ClientStartCameraShake(RunningCameraShake);
	}
	else
	{
		if (bRunningCameraShake)
		{
			bRunningCameraShake = false;
			playerController->ClientStopCameraShake(RunningCameraShake);
		}
	}
}

// Called to bind functionality to input
void AFpsCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFpsCharacterBase::IncreaseSpread(float increaseAmount)
{
	if (SpreadCurrent + increaseAmount >= SpreadMax)
	{
		SpreadCurrent = SpreadMax;
	}
	else
	{
		SpreadCurrent = SpreadCurrent + increaseAmount;
	}
}

void AFpsCharacterBase::DecreaseSpread(float decreaseAmount)
{
	if (SpreadCurrent - decreaseAmount <= SpreadMin)
	{
		SpreadCurrent = SpreadMin;
	}
	else
	{
		SpreadCurrent = SpreadCurrent - decreaseAmount;
	}
}