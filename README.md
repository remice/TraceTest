# TraceTest
 
 콜리전 테스트를 위한 프로젝트입니다.
 TestManager의 세팅 값을 조절하여 여러 테스트를 할 수 있습니다.
 
 - Attack Setting
    - Overlap Distance >> Overlap 검사가 시작될 위치를 조정하는 값입니다.
    - Weapon Length >> 트레이스의 길이입니다.
- Test Setting
    - First Method >> 테스트할 트레이스 방식을 선택합니다.
    - Pre Delay >> 사전 딜레이입니다.
    - Test Actor Spawn Count >> 레이를 쏘는 액터의 숫자입니다.
    - Checked Actor Spawn Count >> 레이를 받는 액터의 숫자입니다.(인스턴스드 매시)
    - Checked Actor Spawn Distance >> 레이를 받는 액터가 서로 얼마나 떨어져서 생성되는지의 값입니다.
- Line Trace Setting
    - Line Spawn Count >> 체크할 레이의 개수입니다. (모든 트레이스에 적용)
    - 액터의 수(`TestActorSpawnCount`) * 레이의 수(`LineSpawnCount`)만큼 충돌 체크가 실행됩니다.
- Sphere Setting
    - Sphere Radius >> SphereTrace(Sweep), Sphere/CapsuleOverlap에 사용될 구의 크기입니다.
- Box Setting
    - Box Half Size >> BoxTrace(Sweep), BoxOverlap에 사용될 박스의 크기입니다.
    - Box Orientation >> BoxTrace(Sweep)에 사용될 박스의 회전 값입니다.
