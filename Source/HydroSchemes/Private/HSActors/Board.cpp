// HydroSchemes Simulator. All rights reserved.


#include "HSActors/Board.h"
#include "HSActors/BoardPart.h"
#include "HSActors/Plus.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseBoardLog, All, All)

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");

	BoxComponent->SetupAttachment(GetRootComponent());
}

void ABoard::AddParts(const APlus* Button)
{
	if (!GetWorld()) return;
	const float MeshLength = 11.0f;
	if (Button == ButtonUp) {
		PartsMatrix.Add(TArray<ABoardPart*>());
		for (int32 i=0; i < ColumnPartsCount; i++) {
			auto TempPart = GetWorld()->SpawnActor<ABoardPart>(BoardPartClass);
			TempPart->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			TempPart->SetActorRelativeLocation(FVector(FirstPartLocation.X + RowPartsCount * MeshLength, FirstPartLocation.Y + i * MeshLength, 0.0f));
			PartsMatrix[RowPartsCount].Add(TempPart);
		}
		ButtonUp->AddActorLocalOffset(FVector(MeshLength, 0.0f, 0.0f));
		ButtonLeft->AddActorLocalOffset(FVector(MeshLength / 2.0f, 0.0f, 0.0f));
		ButtonRight->AddActorLocalOffset(FVector(MeshLength / 2.0f, 0.0f, 0.0f));
		RowPartsCount++;
		BoxComponent->AddLocalOffset(FVector(MeshLength / 2.0f, 0.0f, 0.0f));
		BoxComponent->SetRelativeScale3D(FVector((RowPartsCount + 4) * ScaleCollision, (ColumnPartsCount + 4) * ScaleCollision, CollisionWidth));
	}
	else if (Button == ButtonLeft) {
		for (int32 i = 0; i < RowPartsCount; i++) {
			auto TempPart = GetWorld()->SpawnActor<ABoardPart>(BoardPartClass);
			TempPart->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			TempPart->SetActorRelativeLocation(FVector(FirstPartLocation.X + i * MeshLength, FirstPartLocation.Y - MeshLength, 0.0f));
			PartsMatrix[i].Insert(TempPart, 0);
		}
		ButtonLeft->AddActorLocalOffset(FVector(0.0f, 0.0f, -MeshLength));
		ButtonUp->AddActorLocalOffset(FVector(0.0f, 0.0f, -MeshLength / 2.0f));
		ButtonDown->AddActorLocalOffset(FVector(0.0f, 0.0f, -MeshLength / 2.0f));

		ColumnPartsCount++;
		FirstPartLocation = FVector(FirstPartLocation.X, FirstPartLocation.Y - MeshLength, 0.0f);

		BoxComponent->AddLocalOffset(FVector(0.0f, 0.0f, -MeshLength / 2.0f));
		BoxComponent->SetRelativeScale3D(FVector((RowPartsCount + 4) * ScaleCollision, (ColumnPartsCount + 4) * ScaleCollision, CollisionWidth));
	}
	else if (Button == ButtonDown) {
		PartsMatrix.Insert(TArray<ABoardPart*>(), 0);
		for (int32 i = 0; i < ColumnPartsCount; i++) {
			auto TempPart = GetWorld()->SpawnActor<ABoardPart>(BoardPartClass);
			TempPart->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			TempPart->SetActorRelativeLocation(FVector(FirstPartLocation.X - MeshLength, FirstPartLocation.Y + i * MeshLength, 0.0f));
			PartsMatrix[0].Add(TempPart);
		}
		ButtonDown->AddActorLocalOffset(FVector(-MeshLength, 0.0f, 0.0f));
		ButtonLeft->AddActorLocalOffset(FVector(-MeshLength / 2.0f, 0.0f, 0.0f));
		ButtonRight->AddActorLocalOffset(FVector(-MeshLength / 2.0f, 0.0f, 0.0f));

		RowPartsCount++;
		FirstPartLocation = FVector(FirstPartLocation.X - MeshLength, FirstPartLocation.Y, 0.0f);

		BoxComponent->AddLocalOffset(FVector( -MeshLength / 2.0f, 0.0f, 0.0f));
		BoxComponent->SetRelativeScale3D(FVector((RowPartsCount + 4) * ScaleCollision, (ColumnPartsCount + 4) * ScaleCollision, CollisionWidth));
	}
	else if (Button == ButtonRight) {
		for (int32 i = 0; i < RowPartsCount; i++) {
			auto TempPart = GetWorld()->SpawnActor<ABoardPart>(BoardPartClass);
			TempPart->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			TempPart->SetActorRelativeLocation(FVector(FirstPartLocation.X + i * MeshLength, FirstPartLocation.Y + ColumnPartsCount * MeshLength, 0.0f));
			PartsMatrix[i].Add(TempPart);
		}
		ButtonRight->AddActorLocalOffset(FVector(0.0f, 0.0f, MeshLength));
		ButtonUp->AddActorLocalOffset(FVector(0.0f, 0.0f, MeshLength / 2.0f));
		ButtonDown->AddActorLocalOffset(FVector(0.0f, 0.0f, MeshLength / 2.0f));

		ColumnPartsCount++;

		BoxComponent->AddLocalOffset(FVector(0.0f, 0.0f, MeshLength / 2.0f));
		BoxComponent->SetRelativeScale3D(FVector((RowPartsCount + 4) * ScaleCollision, (ColumnPartsCount + 4) * ScaleCollision, CollisionWidth));
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	const float MeshLength = 11.0f;

	//FTransform ButtonTransform = FTransform(FRotator(0.0f, 0.0f, 90.0f), FVector(MeshLength * 1.5f, 0.0f, 0.0f), FVector(MeshScale, MeshScale, MeshScale));

	if (!GetWorld()) return;

	ButtonUp = GetWorld()->SpawnActor<APlus>(PlusPartClass);
	ButtonUp->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	ButtonUp->SetActorRelativeLocation(FVector(1.5f * MeshLength, 0.0f, 0.0f));

	ButtonDown = GetWorld()->SpawnActor<APlus>(PlusPartClass);
	ButtonDown->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	ButtonDown->SetActorRelativeLocation(FVector(-1.5f * MeshLength, 0.0f, 0.0f));

	ButtonLeft = GetWorld()->SpawnActor<APlus>(PlusPartClass);
	ButtonLeft->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	ButtonLeft->SetActorRelativeLocation(FVector(0.0f, -1.5f * MeshLength, 0.0f));

	ButtonRight = GetWorld()->SpawnActor<APlus>(PlusPartClass);
	ButtonRight->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	ButtonRight->SetActorRelativeLocation(FVector(0.0f, 1.5f * MeshLength, 0.0f));

	FirstPartLocation = FVector((- RowPartsCount / 2.0f + 0.5) * MeshLength, (-ColumnPartsCount / 2.0f + 0.5) * MeshLength, 0.0f);

	if (RowPartsCount && ColumnPartsCount) {
		for (int32 i = 0; i < RowPartsCount; i++) {
			PartsMatrix.Add(TArray<ABoardPart*>());
			for (int32 j = 0; j < ColumnPartsCount; j++) {
				auto TempPart = GetWorld()->SpawnActor<ABoardPart>(BoardPartClass);
				TempPart->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				TempPart->SetActorRelativeLocation(FVector((-RowPartsCount / 2.0f + i + 0.5) * MeshLength, (-ColumnPartsCount / 2.0f + j + 0.5) * MeshLength, 0.0f));
				PartsMatrix[i].Add(TempPart);
			}
		}

		ButtonUp->AddActorLocalOffset(FVector(RowPartsCount / 2.0f * MeshLength, 0.0f, 0.0f));
		ButtonDown->AddActorLocalOffset(FVector(-RowPartsCount / 2.0f * MeshLength, 0.0f, 0.0f));
		ButtonLeft->AddActorLocalOffset(FVector(0.0f, 0.0f, - ColumnPartsCount / 2.0f * MeshLength));
		ButtonRight->AddActorLocalOffset(FVector(0.0f, 0.0f, ColumnPartsCount / 2.0f * MeshLength));
	}

	BoxComponent->SetRelativeScale3D(FVector((RowPartsCount + 4) * ScaleCollision, (ColumnPartsCount + 4) * ScaleCollision, CollisionWidth));
}

