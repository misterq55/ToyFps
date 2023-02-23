// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsCharacterBase.h"
#include "UObject/ConstructorHelpers.h"
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

	USkeletalMeshComponent* CharacterMeshComponent = GetMesh();

	if (!CharacterMeshComponent)
		return;

	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/PlayerMannequin.PlayerMannequin'"));
	CharacterMeshComponent->SetSkeletalMesh(MeshObj.Object);*/
	CharacterMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	CharacterMeshComponent->SetRelativeRotation(FRotator(-0.f, -90.f, -0.f));

	HeadMeshComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));

	if (!HeadMeshComponent)
		return;

	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> HeadObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Head.Head'"));
	HeadMeshComponent->SetSkeletalMesh(HeadObj.Object);*/
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

	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Arms.Arms'"));
	ArmsMeshComponent->SetSkeletalMesh(ArmsObj.Object);*/
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

// Called to bind functionality to input
void AFpsCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFpsCharacterBase::IncreaseSpread(float InIncreaseAmount)
{
	if (SpreadCurrent + InIncreaseAmount >= SpreadMax)
	{
		SpreadCurrent = SpreadMax;
	}
	else
	{
		SpreadCurrent = SpreadCurrent + InIncreaseAmount;
	}
}

void AFpsCharacterBase::DecreaseSpread(float InDecreaseAmount)
{
	if (SpreadCurrent - InDecreaseAmount <= SpreadMin)
	{
		SpreadCurrent = SpreadMin;
	}
	else
	{
		SpreadCurrent = SpreadCurrent - InDecreaseAmount;
	}
}