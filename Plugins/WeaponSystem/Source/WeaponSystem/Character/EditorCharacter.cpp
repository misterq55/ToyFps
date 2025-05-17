// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "WeaponSystem/Weapon/WeaponAsset.h"
#include "WeaponSystem/Weapon/Weapon.h"
#include "WeaponSystem/AnimInstance/armsAnimInstanceBase.h"

AEditorCharacter::AEditorCharacter()
	: Super()
{
	GetCapsuleComponent()->SetVisibility(false);
	GetArrowComponent()->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Mesh/PlayerMannequin.PlayerMannequin'"));
	GetMesh()->SetSkeletalMesh(meshObj.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> meshAnim(TEXT("/Script/Engine.AnimBlueprint'/WeaponSystem/BP_EditorCh_AnimBP.BP_EditorCh_AnimBP_C'"));
	GetMesh()->SetAnimInstanceClass(meshAnim.Class);
	GetMesh()->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> headObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Mesh/Head.Head'"));
	HeadMeshComponent->SetSkeletalMesh(headObj.Object);
	HeadMeshComponent->SetVisibility(false);

	MainCameraComponent->SetCameraMesh(nullptr);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> armsObj(TEXT("/Script/Engine.SkeletalMesh'/Game/UltimateFPSAnimationsKIT/Mesh/Arms.Arms'"));
	ArmsMeshComponent->SetSkeletalMesh(armsObj.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> armsAnim(TEXT("/Script/Engine.AnimBlueprint'/WeaponSystem/BP_EditorCh_Arms_AnimsBP.BP_EditorCh_Arms_AnimsBP_C'"));
	ArmsMeshComponent->SetAnimInstanceClass(armsAnim.Class);

	WeaponPivot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Weapon"));

	if (!WeaponPivot)
		return;

	WeaponPivot->SetupAttachment(ArmsMeshComponent, TEXT("WeaponSocket"));
}

void AEditorCharacter::SpawnWeaponActor()
{
	CurrentWeapon = Cast<AWeaponBase>(GetWorld()->SpawnActor(AWeapon::StaticClass()));
	
	if (!CurrentWeapon)
		return;

	CurrentWeapon->SetOwningCharacter(this);
	CurrentWeapon->SetWeaponData(WeaponAsset->GetWeaponData());
	CurrentWeapon->AttachToComponent(WeaponPivot, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentWeapon->ResetWeapon(WeaponAsset->GetWeaponData());
	ResetArmsAnimInstance();
}

void AEditorCharacter::SetWeaponAsset(UWeaponAsset* weaponAsset)
{
	WeaponAsset = weaponAsset;
}

void AEditorCharacter::ResetArmsAnimInstance()
{
	UArmsAnimInstanceBase* armsAnimInstance = Cast<UArmsAnimInstanceBase>(ArmsMeshComponent->GetAnimInstance());
	if (!IsValid(armsAnimInstance))
	{
		return;
	}
	
	armsAnimInstance->SetWeaponData(WeaponAsset->GetWeaponData());
}

void AEditorCharacter::ResetWeaponData(const FWeaponData& InWeaponData)
{
	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->ResetWeapon(WeaponAsset->GetWeaponData());
}
