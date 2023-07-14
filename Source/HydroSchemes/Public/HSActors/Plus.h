// HydroSchemes Simulator. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "Plus.generated.h"

UCLASS()
class HYDROSCHEMES_API APlus : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlus();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
