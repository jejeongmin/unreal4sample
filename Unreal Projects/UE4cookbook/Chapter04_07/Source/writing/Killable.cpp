#include "Killable.h"

bool IKillable::IsDead()
{
    return false;
}

void IKillable::Die()
{
    GEngine->AddOnScreenDebugMessage(-1,1, FColor::Red,"Arrrgh");
    AActor* Me = Cast<AActor>(this);
    if (Me)
    {
		// 액터 객체가 유효하다면 인스턴스 파괴를 호출하고, 기비지 컬렉트될 때 비로소 파괴될 것이다.
		// SetLifeSpan(sec) 함수를 이용하면 명시한 초 단위 시간이 지난 후에 액터가 Destory() 함수를 호출한다.
        Me->Destroy();
    }

}