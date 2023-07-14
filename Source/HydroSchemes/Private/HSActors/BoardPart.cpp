// HydroSchemes Simulator. All rights reserved.


#include "HSActors/BoardPart.h"
#include "HSActors/Board.h"

DEFINE_LOG_CATEGORY_STATIC(BaseBoardPartLog, All, All)

// Sets default values
ABoardPart::ABoardPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	//SetRootComponent(SceneComponent);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABoardPart::BeginPlay()
{
	Super::BeginPlay();
	
	if (!StaticMesh) return;
	FVector Min = FVector();
	FVector Max = FVector();
	StaticMesh->GetLocalBounds(Min, Max);
	UE_LOG(BaseBoardPartLog, Display, TEXT("MIN: %s"), *Min.ToString());
	UE_LOG(BaseBoardPartLog, Display, TEXT("MIN: %s"), *Max.ToString());
}

