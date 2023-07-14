// HydroSchemes Simulator. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

//class ABoardPart;
class APlus;

UCLASS()
class HYDROSCHEMES_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlus> PlusPartClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABoardPart> BoardPartClass;

	UPROPERTY()
	APlus* ButtonUp;

	UPROPERTY()
	APlus* ButtonDown;

	UPROPERTY()
	APlus* ButtonLeft;

	UPROPERTY()
	APlus* ButtonRight;

	UPROPERTY(EditAnywhere)
	int32 RowPartsCount = 3;

	UPROPERTY(EditAnywhere)
	int32 ColumnPartsCount = 3;

	void AddParts(const APlus* Button);

	UPROPERTY(EditAnywhere)
	float ScaleCollision = 0.172f;

	UPROPERTY(EditAnywhere)
	float CollisionWidth = 3.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<TArray<ABoardPart*>> PartsMatrix;

	UPROPERTY()
	FVector FirstPartLocation;

};
