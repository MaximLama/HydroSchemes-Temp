// HydroSchemes Simulator. All rights reserved.


#include "HSActors/Plus.h"
#include "HSActors/Board.h"

// Sets default values
APlus::APlus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	//SetRootComponent(SceneComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlus::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlus::Interact()
{
	auto Board = Cast<ABoard>(this->GetAttachParentActor());
	if (Board) {
		Board->AddParts(this);
	}
}

