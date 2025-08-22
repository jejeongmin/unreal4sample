인프런의 이득우님 UE5 GameplayAbilitySystem 강의 예제.


## ArenaBattleGAS

- 책과 인프런의 또다른 UE5 강의에서 예제로 만들었던 ArenaBattle 을 GAS 를 이용해서 재구현
- GameplayTag 를 이용한 메시지 시스템
- AbilitySystemComponent 를 이용한 능력 시스템
- AbilityTask 를 이용한 능력 실행
- AttributeSet 을 이용한 능력치 시스템
- GameplayEffect 를 이용한 능력 효과
- GameplayCue 를 이용한 능력 효과 시각화
- GameplayAbility 를 이용한 능력 실행
- GameplayEvent 를 이용한 능력 이벤트
- GameplayCueNotify 를 이용한 능력 효과 시각화
- GameplayTag 를 이용한 능력 상태 관리
- 아.. 이거 놀랍네.. 위에 멘트들을 내가 정리한 게 아니라, 코파일럿이 알아서 정리해줬네.. ( 이득우님 강의 내용이랑 거의 비슷함 ), 심지어 이 문장까지도 작성 중간에 나머지를 완성해줬음.



## 할 일

죽으면 차차 가라앉다가 없어지도록 수정 ( 완료 )
적이 죽었는데도, 탐지 하는 스피어가 계속 그려진다. ( 죽으면 StopAI 시켜버림, AI Node 중 Detect Node 에서 DrawSphere 하지 않게 됨)
컴보 공격을 하면 앞으로 이동하도록 수정 ( 코파일럿한테 물어봐서 수정 )
아이템 효과 박스 샘플로 1~2개 더 작업