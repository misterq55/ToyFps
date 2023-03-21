// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/Weapon/WeaponWithAbilities.h"
#include "WeaponSystem/AnimInstance/ArmsAnimInstanceBase.h"

AEditorCharacter::AEditorCharacter()
	: Super()
{
	GetCapsuleComponent()->SetVisibility(false);
	GetArrowComponent()->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/PlayerMannequin.PlayerMannequin'"));
	GetMesh()->SetSkeletalMesh(MeshObj.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> MeshAnim(TEXT("/Script/Engine.AnimBlueprint'/WeaponSystem/BP_EditorCh_AnimBP.BP_EditorCh_AnimBP_C'"));
	GetMesh()->SetAnimInstanceClass(MeshAnim.Class);
	GetMesh()->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HeadObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Head.Head'"));
	HeadMeshComponent->SetSkeletalMesh(HeadObj.Object);
	HeadMeshComponent->SetVisibility(false);

	MainCameraComponent->SetCameraMesh(nullptr);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Demo/PlayerMannequin/Mesh/Arms.Arms'"));
	ArmsMeshComponent->SetSkeletalMesh(ArmsObj.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ArmsAnim(TEXT("/Script/Engine.AnimBlueprint'/WeaponSystem/BP_EditorCh_Arms_AnimsBP.BP_EditorCh_Arms_AnimsBP_C'"));
	ArmsMeshComponent->SetAnimInstanceClass(ArmsAnim.Class);

	WeaponPivot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Weapon"));

	if (!WeaponPivot)
		return;

	WeaponPivot->SetupAttachment(ArmsMeshComponent, TEXT("WeaponSocket"));
}

void AEditorCharacter::SpawnWeaponActor()
{
	CurrentWeapon = Cast<AWeaponBase>(GetWorld()->SpawnActor(AWeaponWithAbilities::StaticClass()));
	
	if (!CurrentWeapon)
		return;

	CurrentWeapon->SetOwningCharacter(this);
	CurrentWeapon->SetWeaponData(WeaponAsset->GetWeaponData());
	CurrentWeapon->AttachToComponent(WeaponPivot, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentWeapon->ResetWeapon(WeaponAsset->GetWeaponData());
	ResetArmsAnimInstance();
}

void AEditorCharacter::SetWeaponAsset(UWeaponAsset* InWeaponAsset)
{
	WeaponAsset = InWeaponAsset;
}

void AEditorCharacter::ResetArmsAnimInstance()
{
	UArmsAnimInstanceBase* ArmsAnimInstance = Cast<UArmsAnimInstanceBase>(ArmsMeshComponent->GetAnimInstance());
	ArmsAnimInstance->SetWeaponData(WeaponAsset->GetWeaponData());
}

void AEditorCharacter::ResetWeaponData(const FWeaponData& InWeaponData)
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->ResetWeapon(WeaponAsset->GetWeaponData());
}
