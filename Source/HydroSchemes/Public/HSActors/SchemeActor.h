// HydroSchemes Simulator. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryElement.h"
#include "Interfaces/PickUpInterface.h"
#include "SchemeActor.generated.h"

UCLASS(Blueprintable)
class HYDROSCHEMES_API ASchemeActor : public AActor, public IPickUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASchemeActor();

	UPROPERTY(EditDefaultsOnly, Category="InventoryData")
	FName ActorName;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	virtual void PickUpItem(FInventoryElement& InventoryElement) override;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
