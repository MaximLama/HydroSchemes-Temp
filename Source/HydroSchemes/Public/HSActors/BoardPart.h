// HydroSchemes Simulator. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPart.generated.h"

UCLASS()
class HYDROSCHEMES_API ABoardPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardPart();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	FName SlotSocketName = "HSSlot";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
