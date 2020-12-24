# minirt를 끝내보자!!!!!!
## phong!!!
### 2020/12/13 (일)
#### plane 추가 했을 때 0으로 나누지 말라는 에러가 발생함.
- 원인
	- plane의 위치가 0, 0, 0으로 정해지면 문제가 발생함.
- 해결법
	- 위치가 0, 0, 0으로 하면 아예 표현이 안되게 해버림.
- 문제점
	- 화각보다 낮은 각으로 넣어주면 보여줘야 하는줄 알았는데 생각해보니까 아닌거 같음.
- 추가
	- 실제 문제는 tmin을 0로 잡아서 그럼.

#### 그림자가 제대로 적용안되었다. 반쪽이 검정색으로 표현됨..
- 원인
	- ray가 부딪힌 곳에서 광원으로 ray를 쏠 때에 ray.dir을 그냥 광원의 point로 잡은게 문제였다...
#### 광원이 2개 이상일 때 그림자가 연하게 적용도 안되고 세상이 너무 밝아진다....
- 원인
	- shadow_color의 위치가 잘 못 되었다.
- 해결법
	- shadow_color는 rec->obj_color를 건드리지 말고 그냥 shadow인지 아닌지 확인만 하고 return 하는 함수로 바꿈
	- 그리고 hit_light에 집어넣어준다.
#### objects가 많아지고 광원과 멀어지거나 할 때에 그림자가 이상하게 짐
- 원인
	- tmax값을 inf로 줬었는데 shadow_color 함수 안에서는 tmax값을 inf로 주면 안된다.
	- 광원보다 멀리 있는 친구도 고려해버리기 때문...
- 해결법
	- 광원과 ray를 맞은 표면 사이의 t값을 구하여 tmax값을 더 작게 한정시킨다.
	- 두 점사이의 t값을 구하는게 조금 어려웠는데 ray_at함수를 보고 역으로 계산하면 구할 수 있음.

### 2020/12/14 (월)
#### 두 벡터를 외적하면 왜 법선벡터가 구해지는가...
- 해결
	- 안됨...

#### 삼각형 내부에 점이 존재하는가에 대한 답.
- [사이트](https://soooprmx.com/archives/10607)

### 2020/12/16 (수)
#### 광원의 x위치가 0일 경우 가운데 검정선이 생긴다.
- 원인
	- 아직 불명....
#### 원기둥에 specular 적용이 안된다.
- 원인
	- specular에서 rec->normal을 구해줄 때에 단위벡터로 만들어준다고 radius를 나눠준다는걸 root를 나눠줬음...
### 2020/12/21 (월)
#### dtoa가 완벽하게 되어있지 않음. 그걸 항상 고려하기.

### 2020/12/22
#### 변환

행렬 곱에서 교환법칙은 안되지만! 결합, 분배법칙은 가능.

[mit.edu>ppt](http://groups.csail.mit.edu/graphics/classes/6.837/F03/lectures/05_transformation_hierarchy.ppt


[4*4 역행렬 구하기 공식](https://semath.info/src/inverse-cofactor-ex4.html)
[4*4 가우스 소거법으로 역행렬 구하기](https://www.intmath.com/matrices-determinants/inverse-matrix-gauss-jordan-elimination.php)


[법선 벡터 변환 행렬](https://tails.tistory.com/entry/%EC%A3%BC%EC%96%B4%EC%A7%84-%EB%85%B8%EB%A9%80%EB%B2%A1%ED%84%B0%EC%97%90-Model%ED%96%89%EB%A0%AC%EC%9D%98-%EC%A0%84%EC%B9%98%EC%97%AD%ED%96%89%EB%A0%AC%EC%9D%84-%EA%B3%B1%ED%95%98%EB%8A%94-%EC%9D%B4%EC%9C%A0)

[법선 벡터의 변환을 위한 법선 행렬](http://www.gisdeveloper.co.kr/?p=2224)