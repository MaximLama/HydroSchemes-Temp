// HydroSchemes Simulator. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InventoryInteractInterface.h"
#include "Inventory/InventoryElement.h"
#include "HUBaseCharacter.generated.h"

class UCameraComponent;
class UInventoryComponent;

struct FInventoryElement;

UCLASS()
class HYDROSCHEMES_API AHUBaseCharacter : public ACharacter, public IInventoryInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHUBaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Interact();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FName PlacingElementAttachSocketName = "HSItemSocket";

	virtual void AddToUIInventory_Implementation(FInventoryElement InventoryElement) override;

	UFUNCTION(BlueprintCallable)
	void SpawnActorInHand(FInventoryElement InventoryElement);

	UPROPERTY(BlueprintReadWrite)
	bool CanInteractWithBoard = false;

	UPROPERTY()
	TObjectPtr<ASchemeActor>PlacingElement = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ASchemeActor> HoloSchemeActor;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* HoloMaterial;

	UFUNCTION()
	void ShowHolo();

	UFUNCTION(BlueprintCallable)
	void DestroyHolo();

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
};
