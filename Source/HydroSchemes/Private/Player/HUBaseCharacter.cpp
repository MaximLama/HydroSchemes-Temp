// HydroSchemes Simulator. All rights reserved.


#include "Player/HUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "HSActors/Plus.h"
#include "HSActors/Board.h"
#include "HSActors/BoardPart.h"
#include "Interfaces/InteractableInterface.h"
#include "Inventory/InventoryComponent.h"
#include "Interfaces/PickUpInterface.h"
#include "Interfaces/InventoryInteractInterface.h"
#include "HSActors/SchemeActor.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

#define INTERACT ECC_GameTraceChannel1
#define BOARD_CHANNEL ECC_GameTraceChannel2

// Sets default values
AHUBaseCharacter::AHUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetMesh(), "head");
	CameraComponent->bUsePawnControlRotation = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
}

// Called when the game starts or when spawned
void AHUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShowHolo();
}



// Called to bind functionality to input
void AHUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent) return;
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &AHUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AHUBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AHUBaseCharacter::Interact);
}

void AHUBaseCharacter::Interact()
{
	FVector ViewLocation;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FVector TraceStart = ViewLocation;
	FVector TraceEnd = TraceStart + ViewRotation.Vector() * 1500.0f;

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, INTERACT)) {
		if (!HitResult.bBlockingHit) return;
		auto HitActor = HitResult.GetActor();
		if (CanInteractWithBoard && HitActor->Implements<UInteractableInterface>()) {
			IInteractableInterface* InteractActor = Cast<IInteractableInterface>(HitActor);
			InteractActor->Interact();
		}
		if (HitActor->Implements<UPickUpInterface>()) {
			IPickUpInterface* PickUpActor = Cast<IPickUpInterface>(HitActor);
			auto InventoryElement = new FInventoryElement();
			PickUpActor->PickUpItem(*InventoryElement);
			InventoryComponent->AddItemToInventory(*InventoryElement);
			UE_LOG(BaseCharacterLog, Display, TEXT("CharacterLog - %s"), *InventoryElement->ElementName.ToString());
			UE_LOG(BaseCharacterLog, Display, TEXT("Class Name - %s"), *InventoryElement->ElementClass->GetName());
			Execute_AddToUIInventory(this, *InventoryElement); 
		}
		//if (HitActor->IsA<ABoardPart>() && HoloSchemeActor && !HoloSchemeActor->IsActorBeingDestroyed()) {
		//	auto NewSchemePart = 
		//}
	}
}

void AHUBaseCharacter::AddToUIInventory_Implementation(FInventoryElement InventoryElement)
{
	IInventoryInteractInterface::AddToUIInventory_Implementation(InventoryElement);
}

void AHUBaseCharacter::SpawnActorInHand(FInventoryElement InventoryElement)
{
	if (!InventoryElement.ElementClass || InventoryElement.ElementName == "") return;
	if (!GetWorld()) return;
	if (!PlacingElement && PlacingElement->StaticClass() == InventoryElement.ElementClass) return;
	if (PlacingElement) {
		PlacingElement->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PlacingElement->Destroy();
	}
	if (!PlacingElement || PlacingElement->IsActorBeingDestroyed()) {
		PlacingElement = GetWorld()->SpawnActor<ASchemeActor>(InventoryElement.ElementClass);
		PlacingElement->StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		PlacingElement->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PlacingElementAttachSocketName);
	}
}

void AHUBaseCharacter::ShowHolo()
{
	if (CanInteractWithBoard && PlacingElement && !PlacingElement->IsActorBeingDestroyed()) {
		FVector ViewLocation;
		FRotator ViewRotation;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

		FVector TraceStart = ViewLocation;
		FVector TraceEnd = TraceStart + ViewRotation.Vector() * 1500.0f;

		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, BOARD_CHANNEL)) {
			if (!HitResult.bBlockingHit) return;
			auto HitActor = HitResult.GetActor();
			if (HitActor->IsA<ABoardPart>()) {
				auto BoardPart = Cast<ABoardPart>(HitActor);
				if (!HoloSchemeActor || HoloSchemeActor->IsActorBeingDestroyed()) {
					HoloSchemeActor = GetWorld()->SpawnActor<ASchemeActor>(PlacingElement->GetClass());
					HoloSchemeActor->StaticMeshComponent->SetCollisionResponseToChannel(INTERACT, ECR_Ignore);
					HoloSchemeActor->StaticMeshComponent->SetRenderCustomDepth(true);
					HoloSchemeActor->AttachToActor(BoardPart, FAttachmentTransformRules::SnapToTargetNotIncludingScale, BoardPart->SlotSocketName);
					TObjectPtr<UMaterialInstanceDynamic> HoloDynMatInst = UMaterialInstanceDynamic::Create(HoloMaterial, HoloSchemeActor);
					HoloDynMatInst->SetVectorParameterValue(FName("Color"), FColor::Green);
					for (int32 i = 0; i < HoloSchemeActor->StaticMeshComponent->GetNumMaterials(); i++) {
						HoloSchemeActor->StaticMeshComponent->SetMaterial(i, HoloDynMatInst);
					}
				}
				if (HoloSchemeActor && !HoloSchemeActor->IsActorBeingDestroyed()) {
					if (HoloSchemeActor->GetAttachParentActor() != BoardPart) {
						HoloSchemeActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
						HoloSchemeActor->AttachToActor(BoardPart, FAttachmentTransformRules::SnapToTargetNotIncludingScale, BoardPart->SlotSocketName);
					}
				}
				//UE_LOG(BaseCharacterLog, Display, TEXT("My Location - %s"), *GetActorLocation().ToString());
			}
		}
	}
}

void AHUBaseCharacter::DestroyHolo()
{
	HoloSchemeActor->Destroy();
}

void AHUBaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AHUBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}