상세 구현내용

A. 저주파 통과 필터

1. 저주파 통과 필터인 Mean 필터와 Median 필터를 각각 2가지 사이즈(3x3, 5x5)로 설계.

2. 준비한 입력 이미지를 대상으로 각 필터별, 사이즈별로 필터링(컨볼루션) 처리한다.

3. 필터링 결과를 출력(디스플레이) 한다.

[참고] 저주파 통과 필터의 역할(이미지 부드럽게 하기/노이즈 제거하기)을 고려하여 입력 이미지를 준비한다.

(노이즈 제거 정도를 보려면 노이즈가 포함된 이미지를 준비할 것을 권장함)

 

B. 고주파 통과 필터

1. 고주파 통과 필터는 3x3 사이즈의 라플라시안 필터를 설계한다(필터 요소의 가중치는 임의로 설정).

2. 준비한 입력 이미지를 대상으로 필터링(컨볼루션) 처리한다.

3. 필터링 결과를 출력(디스플레이) 한다.

[참고] 고주파 통과 필터는 고주파 성분을 추출하는 역할을 한다. 

 

채점기준

1. 먼저, 각 필터별로 정상적인 결과가 나오는지를 확인함.

2. 위 상세 구현내용 A, B는 최소 기본 구현 조건으로써, 각자 여력에 따라 UI 등, 추가 확장할 경우 가점을 부여함.

3. 사용언어는 각자 자율로 함.

4. 위에 언급되지 않은 사항은 자율로 정해도 무방함.