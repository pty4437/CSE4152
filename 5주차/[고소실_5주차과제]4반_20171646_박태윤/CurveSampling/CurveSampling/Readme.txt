
[ CurveSampling 프로그램 실행방법 ]


1. 프로그램을 실행시킵니다.

2. 화면상에 마우스를 클릭하면서 point 를 찍습니다.

3. 상단 [curve생성] 메뉴를 누르면 마우스로 찍은 point 를 연결하는
   그래프가 만들어지게 됩니다.

4. 이 그래프에 대해서 샘플링할 개수를 지정하고 [curve샘플링] 버튼을
   누르면 그래프를 원하는 point 개수로 샘플링합니다.

5. 최종적으로 [샘플링결과저장] 버튼을 누르면 sampling.txt 파일로 샘플링
   한 데이터를 저장해 줍니다.

6. 새로 데이터를 만들기 위해서는 [초기화] 버튼을 누르고 1번 부터 다시
   시작하면 됩니다.

-------------------------------------------------------------------------------

[ sampling.txt ] 파일 포맷

첫줄에는 총 몇개의 샘플링데이터가 있는지와 샘플링 간격이 옵니다.
그 아래부터 float 형태의 x y 데이터가 한줄씩 나오게 됩니다.

ex)

400 1.436090		<--- 400 개의 샘플링 데이터가 있고, x 간격이 1.436090 이라는 의미
16.000000 310.000000	<--- x 값 16.000000 y값 310.000000
17.436090 310.515625
18.872181 311.136475
20.308271 311.855438
21.744362 312.665436
23.180450 313.559357
24.616541 314.530090
26.052631 315.570557
..
..

--------------------------------------------------------------------------------

위 데이터를 읽어들여서 각자 normalizing 을 하여 pdf 함수를 구성하면 됩니다.





