// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Engine/AssetManager.h"
#include "ABItemData.h"

// Sets default values
AABItemBox::AABItemBox()
{
	//3가지 포인터에 대한 객체 생성
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	
	//액터 내부의 씬을 셋업
	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	//각각에 대한 설정 진행
	//트리거용 전용 프로필 사용
	Trigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	//박스 컴포넌트의 사이즈 지정
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	//트리거 컴포넌트의 델리게이트. 블루프린트에서도 사용 가능하도록 AddDynamic 사용. 
	//현재 객체에 대해서 방금 생성한 AABItemBox 클래스의 OnOverlapBegin 함수를 바인딩.
	//트리거가 발동되면 OnOverlapBegin이 호출됨.
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnOverlapBegin);

	//박스 메쉬는 Props 폴더의 상자에 해당
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	//상자의 위치 값을 조정
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	//상자와 캐릭터가 충돌하지 않도록 프로필 지정
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	//이펙트 컴포넌트는 이펙트 폴더의 P_Treasure Chest Open 이펙트 사용
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (EffectRef.Object)
	{
		//이펙트에 지정
		Effect->SetTemplate(EffectRef.Object);
		//처음에는 바로 발동하지 않도록 해줌.
		Effect->bAutoActivate = false;
	}
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//에셋 매니저는 엔진이 초기화될 때 로딩 보장해줌.
	UAssetManager& Manager = UAssetManager::Get();

	TArray<FPrimaryAssetId> Assets;
	//매니저로부터 목록 가져옴. ABItemData의 태그 정보 넘겨주면 에셋에 대해 배열로 반환해줌.
	Manager.GetPrimaryAssetIdList(TEXT("ABItemData"), Assets);
	ensure(0 < Assets.Num());//잘 동작하는지 체크

	int32 RandomIndex = FMath::RandRange(0, Assets.Num() - 1);//전체중 하나 선택
	//약참조 걸어서 로딩 안되어 있다면 로딩 시켜주도록 선언
	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomIndex]));
	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}
	//로딩 완료 시 아이템 변수에 로딩된 에셋 지정하고
	Item = Cast<UABItemData>(AssetPtr.Get());
	//이것이 null인지 아닌지 확인
	ensure(Item);
}

void AABItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//캐릭터가 들어왔을 때 아이템 데이터가 없으면 (= 꽝이면)
	if (nullptr == Item)
	{
		Destroy();//이펙트 없이 제거해줌.
		return;
	}

	//형변환 진행. 
	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	
	if (OverlappingPawn)//부딪힌 액터가 해당 인터페이스를 구현했다면 
	{
		//아이템을 획득했을 때 획득한 액터에게 TakeItem 함수를 호출
		OverlappingPawn->TakeItem(Item);//캐릭터가 들어왔을 때 아이템 데이터가 있다면 인자로 Item 넘겨줌
	}
	
	//이펙트 발동
	Effect->Activate(true);
	//메쉬 숨김
	Mesh->SetHiddenInGame(true);
	//액터에 대한 콜리전들을 모두 없앰
	SetActorEnableCollision(false);
	//발동된 이벤트 종료될 때, 발동되는 델리게이트. 
	Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	//액터가 스스로 없어지게 선언.
	Destroy();
}


